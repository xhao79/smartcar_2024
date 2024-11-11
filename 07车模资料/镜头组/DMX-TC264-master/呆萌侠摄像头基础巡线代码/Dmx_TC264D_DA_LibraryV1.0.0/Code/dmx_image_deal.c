/****************************************************************************************
 *     COPYRIGHT NOTICE
 *     Copyright (C) 2023,AS DAIMXA
 *     copyright Copyright (C) 呆萌侠DAIMXA,2023
 *     All rights reserved.
 *     技术讨论QQ群：710026750
 *
 *     除注明出处外，以下所有内容版权均属呆萌侠智能科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留呆萌智能侠科技的版权声明。
 *      ____    _    ___ __  ____  __    _
 *     |  _ \  / \  |_ _|  \/  \ \/ /   / \
 *     | | | |/ _ \  | || |\/| |\  /   / _ \
 *     | |_| / ___ \ | || |  | |/  \  / ___ \
 *     |____/_/   \_\___|_|  |_/_/\_\/_/   \_\
 *
 * @file       dmx_image_deal.c
 * @brief      呆萌侠TC264开源库
 * @company    合肥呆萌侠智能科技有限公司
 * @author     呆萌侠科技（QQ：2453520483）
 * @MCUcore    TC264
 * @Software   AURIX Development Stdio V1.8.0
 * @version    查看说明文档内version版本说明
 * @Taobao     https://daimxa.taobao.com/
 * @Openlib    https://gitee.com/daimxa
 * @date       2023-11-10
****************************************************************************************/

#include "dmx_all.h"

unsigned char Deal_Image_Gray[DEAL_IMAGE_H][DEAL_IMAGE_W];      // 压缩后的灰度图像
unsigned char Deal_Image_Binary[DEAL_IMAGE_H][DEAL_IMAGE_W];    // 二值化图像

unsigned char *row_addr;                                        // 行地址
unsigned char image_row_mid = DEAL_IMAGE_W/2 - 1;               // 行中点
unsigned char bottom_left_line,bottom_right_line;               // 底部行左右边线

unsigned char Deal_Image_Left_Line[DEAL_IMAGE_H];               // 左边线
unsigned char Deal_Image_Right_Line[DEAL_IMAGE_H];              // 右边线
unsigned char Deal_Image_Mid_Line[DEAL_IMAGE_H];                // 中线
unsigned char Deal_Image_Wide[DEAL_IMAGE_H];                    // 宽度
unsigned char Deal_Image_Left_Flag[DEAL_IMAGE_H];               // 左边线特征
unsigned char Deal_Image_Right_Flag[DEAL_IMAGE_H];              // 右边线特征

unsigned char End_Line = 20;                                    // 扫线结束行
unsigned char Lost_Line;                                        // 丢线行数
unsigned char Left_Lost_Line,Right_Lost_Line;                   // 左右丢线行数
unsigned char Left_Border,Right_Border;                         // 边线开始左右来回扫线的左右区间边界值
unsigned char Border_Interval = 3;                              // 边线开始左右来回扫线的区间大小
unsigned char Mend_Start_Line;                                  // 补线开始行
unsigned char Mend_End_Line;                                    // 补线结束行
float Mend_Slope;                                               // 补线斜率
unsigned char Car_State = 1;                                    // 车状态,0:停车,1:正常

/**
*
* @brief    图像压缩
* @param    *in_image       原始图像
* @param    *out_image      压缩后的图像
* @return   void
* @notes
* Example:  Image_Compress(MT9V034_Image_Data[0],Deal_Image_Gray[0]);
*
**/
void Image_Compress(unsigned char *in_image,unsigned char *out_image)
{
    unsigned int CompressY, CompressX;
    unsigned int OriginalY, OriginalX;
    unsigned int CompressTemp,OriginalTemp;
    float Hight_Ratio = (float)((MT9V034_IMAGEH * 1.0 / DEAL_IMAGE_H));
    float Width_Ratio = (float)(MT9V034_IMAGEW* 1.0 / DEAL_IMAGE_W);

    for (CompressY = 0; CompressY < DEAL_IMAGE_H; CompressY++)
    {
        OriginalY = (unsigned int)(CompressY * Hight_Ratio);
        CompressTemp = DEAL_IMAGE_W*CompressY;
        OriginalTemp = MT9V034_IMAGEW*OriginalY;

        for (CompressX = 0; CompressX < DEAL_IMAGE_W; CompressX++)
        {
            OriginalX = (unsigned int)(CompressX * Width_Ratio);
            *(out_image+CompressTemp+CompressX) = *(in_image+OriginalTemp+OriginalX);
        }
    }
}

/**
*
* @brief    大津法计算按图像二值化阈值
* @param    *image          需要计算阈值的图像
* @param    width           图像宽
* @param    height          图像高
* @param    pixel_threshold 图像阈值
* @return   unsigned char   大津法阈值
* @notes
* Example:  Image_Threshold(Deal_Image_Gray[0],DEAL_IMAGE_W,DEAL_IMAGE_H,150);
*
**/
unsigned char Image_Threshold(unsigned char *image, unsigned short width, unsigned short height, unsigned int image_max_threshold)
{
    int pixelCount[256];
    float pixelPro[256];
    int i, j, pixelSum = width * height;
    unsigned char threshold = 0;
    unsigned char *data = image;    // 指向像素数据的指针
    for (i = 0; i < 256; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }
    unsigned long gray_sum = 0;
    // 统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i += 1)
    {
        for (j = 0; j < width; j += 1)
        {
            pixelCount[(int)data[i * width + j]]++; // 将当前的点的像素值作为计数数组的下标
            gray_sum += (int)data[i * width + j];   // 灰度值总和
        }
    }
    // 计算每个像素值的点在整幅图像中的比例
    for (i = 0; i < 256; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
    }
    // 遍历灰度级[0,255],[0,pixel_threshold]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
    for (j = 0; j < image_max_threshold; j++)
    {
        w0 += pixelPro[j];         // 背景部分每个灰度值的像素点所占比例之和 即背景部分的比例
        u0tmp += j * pixelPro[j];  // 背景部分每个灰度值的点的比例*灰度值

        w1 = 1 - w0;
        u1tmp = gray_sum / pixelSum - u0tmp;

        u0 = u0tmp / w0;    // 背景平均灰度
        u1 = u1tmp / w1;    // 前景平均灰度
        u = u0tmp + u1tmp;  // 全局平均灰度
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = (unsigned char)j;
        }
        if (deltaTmp < deltaMax)
        {
            break;
        }
    }
    return threshold;
}

/**
*
* @brief    图像二值化
* @param    *in_image       压缩后的图像
* @param    *out_image      二值化后的图像
* @return   void
* @notes
* Example:  Image_Binary(Deal_Image_Gray[0],Deal_Image_Binary[0],180);
*
**/
void Image_Binary(unsigned char *in_image,unsigned char *out_image, unsigned int image_max_threshold)
{
    unsigned char x, y;
    unsigned char final_threshold,threshold;
    unsigned int  temp;

    threshold = Image_Threshold(in_image, DEAL_IMAGE_W, DEAL_IMAGE_H, image_max_threshold) + 20;

    for (y = 0; y < DEAL_IMAGE_H; y++)
    {
        temp = DEAL_IMAGE_W*y;
        for (x = 0; x < DEAL_IMAGE_W; x++)
        {
            if (y <= 15)
                final_threshold = threshold + 20;
            else if (y >= 40)
                final_threshold = threshold + 10;
            else if (y >= 50)
                final_threshold = threshold - 10;
            else
                final_threshold = threshold;

            if(final_threshold<80) final_threshold=80;
            // 阈值越大,显示的内容越多,较浅的图像也能显示出来
            if ( *(in_image+temp+x) > final_threshold)
                *(out_image+temp+x) = 1;  // 白
            else
                *(out_image+temp+x) = 0;  // 黑
        }
    }
}

/**
*
* @brief    图像Sobel二值化
* @param    *in_image       压缩后的图像
* @param    *out_image      Sobel二值化后的图像
* @return   void
* @notes
* Example:  Image_Sobel(Deal_Image_Gray, Deal_Image_Binary, 120);
*
**/
#define Sobel_GX(addr, y, x)    (addr[UP][RR]+2*addr[y][RR]+addr[DN][RR]-(addr[UP][LL]+2*addr[y][LL]+addr[DN][LL]))
#define Sobel_GY(addr, y, x)    (addr[UP][LL]+2*addr[UP][x]+addr[UP][RR]-(addr[DN][LL]+2*addr[DN][x]+addr[DN][RR]))
#define Sobel_G(addr, y, x)     (abs(Sobel_GX(addr, y, x)) + abs(Sobel_GY(addr, y, x)))
void Image_Sobel(unsigned char in_image[DEAL_IMAGE_H][DEAL_IMAGE_W], unsigned char out_image[DEAL_IMAGE_H][DEAL_IMAGE_W], unsigned int threshold)
{
    unsigned char i, j;
    unsigned char UP, DN, LL, RR;
    for (i = 1; i <  DEAL_IMAGE_H - 1; i++)
    {
        DN = i + 1;
        UP = i - 1;
        for (j = 1; j < DEAL_IMAGE_W - 1; j++)
        {
            RR = j + 1;
            LL = j - 1;

            out_image[i][j] = (Sobel_G(in_image, i, j) >= threshold ? 0 : 1);
        }
    }
}

/**
*
* @brief    图像滤波
* @param    *in_image       需要滤波的图像
* @return   void
* @notes
* Example:  Image_Filter(Deal_Image_Binary[0]);
*
**/
void Image_Filter(unsigned char *in_image)
{
    unsigned char x, y;
    for (y = 2; y < DEAL_IMAGE_H-2; y++)
    {
        for (x = 2; x < DEAL_IMAGE_W-2; x++)
        {
            if ( (*(in_image+DEAL_IMAGE_W*y+x)==0) && ((*(in_image+DEAL_IMAGE_W*(y-1)+x) + *(in_image+DEAL_IMAGE_W*(y+1)+x) + *(in_image+DEAL_IMAGE_W*y+x+1) + *(in_image+DEAL_IMAGE_W*y+x-1)) >= 3) )
                *(in_image+DEAL_IMAGE_W*y+x) = 1;
            else if( (*(in_image+DEAL_IMAGE_W*y+x)==1) && ((*(in_image+DEAL_IMAGE_W*(y-1)+x) + *(in_image+DEAL_IMAGE_W*(y+1)+x) + *(in_image+DEAL_IMAGE_W*y+x+1) + *(in_image+DEAL_IMAGE_W*y+x-1)) <= 1) )
                *(in_image+DEAL_IMAGE_W*y+x) = 0;
        }
    }
}

/**
*
* @brief    图像扫线
* @param    *in_image       需要处理的图像
* @return   void
* @notes
* Example:  Image_Find_Line(Deal_Image_Binary[0]);
*
**/
void Image_Find_Line(unsigned char *in_image)
{
    unsigned char x, y, z;
    // 初始化边线数据
    for(y = 0,End_Line = 20,Lost_Line=0,Left_Lost_Line=0,Right_Lost_Line=0; y < End_Line; y++)
    {
        Deal_Image_Left_Line[y] = 0;                    // 初始化左边线
        Deal_Image_Right_Line[y] = DEAL_IMAGE_W - 1;    // 初始化右边线
        Deal_Image_Mid_Line[y] = DEAL_IMAGE_W / 2;      // 初始化中线
        Deal_Image_Wide[y] = DEAL_IMAGE_W - 1;          // 初始化宽度
        Deal_Image_Left_Flag[y] = 0;                    // 初始化左边线特征
        Deal_Image_Right_Flag[y] = 0;                   // 初始化右边线特征
    }
    // 先左右扫线扫图像底部连续五行,稳定后切换扫线方式
    // 底部行的起始地址
    row_addr = (in_image + DEAL_IMAGE_W * (DEAL_IMAGE_H - 2 ) );
    // 底部行的中点为黑点
    if((*(row_addr + image_row_mid)) == 0)
    {
        // 向中点的左右两边寻找白点
        for(x = 0;x < image_row_mid; x++)
        {
            // 左边找到白点退出此for循环,此时x的值为该白点的x坐标
            if(*(row_addr + image_row_mid - x) == 1 )
                break;
            // 右边找到白点退出此for循环,此时x的值为该白点的x坐标
            if(*(row_addr + image_row_mid + x) == 1 )
                break;
        }
        // 判断上面for循环退出时的x坐标的点在中点左边还是右边
        // 中点减去x坐标为白则在左边
        if(*(row_addr + image_row_mid - x) == 1 )
        {
            // 该点可看作底部行的右边界
            bottom_right_line = image_row_mid - x + 1;
            // 底部行右边线向左找到黑点或者找到最左边则为底部行左边线
            for(x = bottom_right_line; x > 0; x--)
            {
                if(*(row_addr + x - 1) == 0 && *(row_addr + x) == 0 )
                {
                    bottom_left_line = x;
                    break;
                }
                else if(x == 1)
                {
                    bottom_left_line = 0;
                }
            }
        }
        // 中点加上x坐标为白则在右边
        else if(*(row_addr + image_row_mid + x) ==1 )
        {
            // 该点可看作底部行的左边界
            bottom_left_line = image_row_mid + x - 1;
            // 底部行左边线向右找到黑点或者找到最右边则为底部行右边线
            for(x = bottom_left_line; x < DEAL_IMAGE_W - 1; x++)
            {
                if(*(row_addr + x + 1) == 0 && *(row_addr + x) == 0 )
                {
                    bottom_right_line = x;
                    break;
                }
                else if(x == DEAL_IMAGE_W - 2)
                {
                    bottom_right_line = DEAL_IMAGE_W - 1;
                }
            }
        }
    }
    // 底部行的中点为白点
    else
    {
        // 中点向左找到黑点或者找到最左边则为底部行左边线
        for(x = image_row_mid; x > 0; x--)
        {
            if(*(row_addr + x - 1) == 0 && *(row_addr + x) == 0 )
            {
                bottom_left_line = x;
                break;
            }
            else if(x == 1)
            {
                bottom_left_line = 0;
            }
        }
        // 中点向右找到黑点或者找到最右边则为底部行右边线
        for(x = bottom_left_line; x < DEAL_IMAGE_W - 1; x++)
        {
            if(*(row_addr + x + 1) == 0 && *(row_addr + x) == 0 )
            {
                bottom_right_line = x;
                break;
            }
            else if(x == DEAL_IMAGE_W - 2)
            {
                bottom_right_line = DEAL_IMAGE_W - 1;
            }
        }
    }
    // 存储左边线
    Deal_Image_Left_Line[DEAL_IMAGE_H - 1] = bottom_left_line;
    // 存储右边线
    Deal_Image_Right_Line[DEAL_IMAGE_H - 1] = bottom_right_line;
    // 存储中线
    Deal_Image_Mid_Line[DEAL_IMAGE_H - 1] = (bottom_left_line + bottom_right_line) / 2;
    // 存储宽度
    Deal_Image_Wide[DEAL_IMAGE_H - 1] = bottom_right_line - bottom_left_line;
    // 存储左边线特征
    Deal_Image_Left_Flag[DEAL_IMAGE_H - 1] = 1;
    // 存储右边线特征
    Deal_Image_Right_Flag[DEAL_IMAGE_H - 1] = 1;
    // 从底部向上再扫5行
    for(y = DEAL_IMAGE_H - 2; y > DEAL_IMAGE_H - 7; y--)
    {
        // 行地址
        row_addr = (in_image + DEAL_IMAGE_W * y );
        // 中点向左找到黑点或者找到最左边则为左边线
        for(x = Deal_Image_Mid_Line[y + 1]; x > 0; x--)
        {
            if(*(row_addr + x - 1) == 0 && *(row_addr + x) == 0 )
            {
                Deal_Image_Left_Line[y] = x;
                break;
            }
            else if(x == 1)
            {
                Deal_Image_Left_Line[y] = 0;
            }
        }
        // 中点向右找到黑点或者找到最右边则为右边线
        for(x = Deal_Image_Mid_Line[y + 1]; x < DEAL_IMAGE_W - 1; x++)
        {
            if(*(row_addr + x + 1) == 0 && *(row_addr + x) == 0 )
            {
                Deal_Image_Right_Line[y] = x;
                break;
            }
            else if(x == DEAL_IMAGE_W - 2)
            {
                Deal_Image_Right_Line[y] = DEAL_IMAGE_W - 1;
            }
        }
        // 存储中线
        Deal_Image_Mid_Line[y] = (Deal_Image_Left_Line[y] + Deal_Image_Right_Line[y]) / 2;
        // 存储宽度
        Deal_Image_Wide[y] = Deal_Image_Right_Line[y] - Deal_Image_Left_Line[y];
        // 存储左边线特征
        Deal_Image_Left_Flag[y] = 1;
        // 存储右边线特征
        Deal_Image_Right_Flag[y] = 1;
    }

    // 切换扫线方式扫线到结束行
    for(y = DEAL_IMAGE_H - 7; y > End_Line; y--)
    {
        // 行地址
        row_addr = (in_image + DEAL_IMAGE_W * y );
        // 左边线开始左右来回扫线的左右区间边界值
        Left_Border = Deal_Image_Left_Line[y+1] - Border_Interval;
        Right_Border = Deal_Image_Left_Line[y+1] + Border_Interval;
        // 左右区间边界值限幅
        Left_Border < 1? Left_Border=1: Left_Border;
        Right_Border > DEAL_IMAGE_W - 1? Right_Border = DEAL_IMAGE_W - 1: Right_Border;
        // 开始扫描左边线
        for(x = Left_Border; x <= Right_Border; x++)
        {
            if(*(row_addr + x) == 0 && *(row_addr + x + 1) == 1 )
            {
                Deal_Image_Left_Line[y] = x;
                Deal_Image_Left_Flag[y] = 1;
                break;
            }
            else if(x == Right_Border-1)
            {
                if(*(row_addr + (Left_Border + Right_Border) / 2) == 1)
                {
                    Deal_Image_Left_Line[y] = (Left_Border + Right_Border) / 2;
                    Deal_Image_Left_Flag[y] = 0;
                    break;
                }
                else
                {
                    Deal_Image_Left_Line[y] = Right_Border;
                    Deal_Image_Left_Flag[y] = 2;
                    break;
                }
            }
        }
        // 右边线开始左右来回扫线的左右区间边界值
        Left_Border = Deal_Image_Right_Line[y+1] - Border_Interval;
        Right_Border = Deal_Image_Right_Line[y+1] + Border_Interval;
        // 左右区间边界值限幅
        Left_Border < 1? Left_Border=1: Left_Border;
        Right_Border > DEAL_IMAGE_W - 1? Right_Border = DEAL_IMAGE_W - 1: Right_Border;
        // 开始扫描右边线
        for(x = Right_Border; x >= Left_Border; x--)
        {
            if(*(row_addr + x) == 0 && *(row_addr + x - 1) == 1 )
            {
                Deal_Image_Right_Line[y] = x;
                Deal_Image_Right_Flag[y] = 1;
                break;
            }
            else if(x == Left_Border + 1)
            {
                if(*(row_addr + (Left_Border + Right_Border) / 2) == 1)
                {
                    Deal_Image_Right_Line[y] = (Left_Border + Right_Border) / 2;
                    Deal_Image_Right_Flag[y] = 0;
                    break;
                }
                else
                {
                    Deal_Image_Right_Line[y] = Left_Border;
                    Deal_Image_Right_Flag[y] = 2;
                    break;
                }
            }
        }
        // 该行左边线不正常则继续保持上一行左边线
        if( Deal_Image_Left_Flag[y] == 0)
        {
            Deal_Image_Left_Line[y] = Deal_Image_Left_Line[y+1];
        }
        // 该行右边线不正常则继续保持上一行右边线
        if( Deal_Image_Right_Flag[y] == 0)
        {
            Deal_Image_Right_Line[y] = Deal_Image_Right_Line[y+1];
        }
        // 重新确定不正常黑白跳变
        if( Deal_Image_Left_Flag[y] == 2 || Deal_Image_Right_Flag[y] == 2)
        {
            // 左边线不正常
            if(Deal_Image_Left_Flag[y] == 2)
            {
                // 在左右边线之间从左到右重新扫描左边线
                for(x = Deal_Image_Left_Line[y] + 1;x <= Deal_Image_Right_Line[y] - 1; x++)
                {
                    if(*(row_addr + x) == 0 && *(row_addr + x + 1) == 1)
                    {
                        Deal_Image_Left_Line[y] = x;
                        Deal_Image_Left_Flag[y] = 1;
                        break;
                    }
                    // 扫到白点直接跳出
                    else if(*(row_addr + x) == 1)
                    {
                        Deal_Image_Left_Flag[y] = 0;
                        break;
                    }
                    // 扫左线扫到了右边线
                    else if(x == Deal_Image_Right_Line[y] - 1)
                    {
                        Deal_Image_Left_Line[y] = x;
                        Deal_Image_Left_Flag[y] = 1;
                        break;
                    }
                }
            }
            if(Deal_Image_Right_Line[y] - Deal_Image_Left_Line[y] <= 6)
            {
                End_Line = y + 1;
                break;
            }
            // 右边线不正常
            if(Deal_Image_Right_Flag[y] == 2)
            {
                // 在左右边线之间从右到左重新扫描右边线
                for(x = Deal_Image_Right_Line[y] - 1;x >= Deal_Image_Left_Line[y] + 1; x--)
                {
                    if(*(row_addr + x) == 0 && *(row_addr + x - 1) == 1)
                    {
                        Deal_Image_Right_Line[y] = x;
                        Deal_Image_Right_Flag[y] = 1;
                        break;
                    }
                    // 扫到白点直接跳出
                    else if(*(row_addr + x) == 1)
                    {
                        Deal_Image_Right_Flag[y] = 0;
                        break;
                    }
                    // 扫右线扫到了左边线
                    else if(x == Deal_Image_Left_Line[y] + 1)
                    {
                        Deal_Image_Right_Line[y] = x;
                        Deal_Image_Right_Flag[y] = 1;
                        break;
                    }
                }

            }
            // 赛道宽度低于6,退出扫线
            if(Deal_Image_Right_Line[y] - Deal_Image_Left_Line[y] <= 6)
            {
                End_Line = y + 1;
                break;
            }
        }
        // 左右边线都丢线,丢线++
        if( Deal_Image_Left_Flag[y] == 0 && Deal_Image_Right_Flag[y] == 0)
            Lost_Line++;
        // 左边线丢线,丢线++
        if(Deal_Image_Left_Flag[y] == 0)
            Left_Lost_Line++;
        // 右边线丢线,丢线++
        if(Deal_Image_Right_Flag[y] == 0)
            Right_Lost_Line++;
        // 左边线限幅
        Deal_Image_Left_Line[y] < 1? Deal_Image_Left_Line[y]=1: Deal_Image_Left_Line[y];
        Deal_Image_Left_Line[y] > DEAL_IMAGE_W - 1? Deal_Image_Left_Line[y] = DEAL_IMAGE_W - 1: Deal_Image_Left_Line[y];
        // 右边线限幅
        Deal_Image_Right_Line[y] < 1? Deal_Image_Right_Line[y]=1: Deal_Image_Right_Line[y];
        Deal_Image_Right_Line[y] > DEAL_IMAGE_W - 1? Deal_Image_Right_Line[y] = DEAL_IMAGE_W - 1: Deal_Image_Right_Line[y];
        // 存储中线
        Deal_Image_Mid_Line[y] = (Deal_Image_Left_Line[y] + Deal_Image_Right_Line[y]) / 2;
        // 存储宽度
        Deal_Image_Wide[y] = Deal_Image_Right_Line[y] - Deal_Image_Left_Line[y];
        // 行数低于一定值且宽度小于一定值,退出扫线
        if(Deal_Image_Wide[y] <= 7 && y < 30)
        {
            End_Line = y + 1;
            break;
        }
        // 左右边线太离谱,退出扫线
        else if(Deal_Image_Left_Line[y] >= DEAL_IMAGE_W - 10 && Deal_Image_Right_Line[y] <=  10)
        {
            End_Line = y + 1;
            break;
        }
    }

    // 边线缺失,从底部画延长线补线
    if(Lost_Line >= 5)
        Mend_Start_Line = DEAL_IMAGE_H - 5;
    // 补左线
    if(Left_Lost_Line >= 5)
    {
        Mend_Start_Line = DEAL_IMAGE_H - 5;
        for(y = Mend_Start_Line; y >= End_Line+2; y--)
        {
            if(Deal_Image_Left_Flag[y] == 0)
            {
                if(Deal_Image_Left_Line[y+1] >= DEAL_IMAGE_W - 10)
                {
                    End_Line = y + 1;
                    break;
                }
                while(y >= End_Line+2)
                {
                    y--;
                    if(Deal_Image_Left_Flag[y] == 1 && Deal_Image_Left_Flag[y-1] == 1 && Deal_Image_Left_Flag[y-2] == 1 && Deal_Image_Left_Line[y-2] > 0 && Deal_Image_Left_Line[y-2] < DEAL_IMAGE_W - 10)
                    {
                        Mend_End_Line = y-2;
                        break;
                    }
                }
                Mend_Slope = ((float)(Deal_Image_Left_Line[Mend_End_Line] - Deal_Image_Left_Line[Mend_Start_Line]))*1.0 / ((float)(Mend_End_Line - Mend_Start_Line));
                if(Mend_End_Line >= End_Line)
                {
                    for(z = Mend_Start_Line; z >= Mend_End_Line; z--)
                    {
                        Deal_Image_Left_Line[z] = (int)(Mend_Slope * ((float)(z - Mend_Start_Line))) + Deal_Image_Left_Line[Mend_Start_Line];
                    }
                }
            }
            else
                Mend_Start_Line = y + 2;
        }
    }
    // 补右线
    if(Right_Lost_Line >= 5)
    {
        Mend_Start_Line = DEAL_IMAGE_H - 5;
        for(y = Mend_Start_Line; y >= End_Line+2; y--)
        {
            if(Deal_Image_Right_Flag[y] == 0)
            {
                if(Deal_Image_Right_Line[y+1] <= 10)
                {
                    End_Line = y + 1;
                    break;
                }
                while(y >= End_Line+2)
                {
                    y--;
                    if(Deal_Image_Right_Flag[y] == 1 && Deal_Image_Right_Flag[y-1] == 1 && Deal_Image_Right_Flag[y-2] == 1 && Deal_Image_Right_Line[y-2] > 10 && Deal_Image_Right_Line[y-2] < DEAL_IMAGE_W - 1)
                    {
                        Mend_End_Line = y-2;
                        break;
                    }
                }
                Mend_Slope = ((float)(Deal_Image_Right_Line[Mend_End_Line] - Deal_Image_Right_Line[Mend_Start_Line]))*1.0 / ((float)(Mend_End_Line - Mend_Start_Line));
                if(Mend_End_Line >= End_Line)
                {
                    for(z = Mend_Start_Line; z >= Mend_End_Line; z--)
                    {
                        Deal_Image_Right_Line[z] = (int)(Mend_Slope * ((float)(z - Mend_Start_Line))) + Deal_Image_Right_Line[Mend_Start_Line];
                    }
                }
            }
            else
                Mend_Start_Line = y + 2;
        }
    }
    // 更新中线和宽度
    for(y = DEAL_IMAGE_H - 2; y >= End_Line; y--)
    {
        // 左边线限幅
        Deal_Image_Left_Line[y] < 1? Deal_Image_Left_Line[y]=1: Deal_Image_Left_Line[y];
        Deal_Image_Left_Line[y] > DEAL_IMAGE_W - 2? Deal_Image_Left_Line[y] = DEAL_IMAGE_W - 2: Deal_Image_Left_Line[y];
        // 右边线限幅
        Deal_Image_Right_Line[y] < 1? Deal_Image_Right_Line[y]=1: Deal_Image_Right_Line[y];
        Deal_Image_Right_Line[y] > DEAL_IMAGE_W - 2? Deal_Image_Right_Line[y] = DEAL_IMAGE_W - 2: Deal_Image_Right_Line[y];
        // 存储中线
        Deal_Image_Mid_Line[y] = (Deal_Image_Left_Line[y] + Deal_Image_Right_Line[y]) / 2;
        // 存储宽度
        Deal_Image_Wide[y] = Deal_Image_Right_Line[y] - Deal_Image_Left_Line[y];
    }

    // 中线滤波
    for(y = DEAL_IMAGE_H - 2; y >= End_Line; y--)
    {
        // 行地址
        row_addr = (in_image + DEAL_IMAGE_W * y );
        if(Deal_Image_Right_Flag[y] == 0 && Deal_Image_Right_Flag[y] == 0 && Deal_Image_Right_Flag[y-1] == 0 && Deal_Image_Right_Flag[y-1] == 0 && y<=50)
        {
            z = y;
            while(z >= End_Line)
            {
                z--;
                if(Deal_Image_Right_Flag[y] == 1 && Deal_Image_Right_Flag[y] == 1)
                {
                    Mend_Slope = (float)(Deal_Image_Mid_Line[z-1] - Deal_Image_Mid_Line[y+2])/(float)(z-y-2);
                    unsigned int mid_start_line = y+2;
                    while(y >= z)
                    {
                        y--;
                        Deal_Image_Mid_Line[y] = (int)(Deal_Image_Mid_Line[mid_start_line] + Mend_Slope*(float)(y - mid_start_line));
                    }
                    break;
                }
            }
        }
        // 更新中线
        Deal_Image_Mid_Line[y] = (Deal_Image_Left_Line[y] + Deal_Image_Right_Line[y]) / 2;
        // 在图像中写入边线数据,左边线为2,中线为3,右边线为4
        *(row_addr + Deal_Image_Left_Line[y] + 1) = 2;
        *(row_addr + Deal_Image_Mid_Line[y]) = 3;
        *(row_addr + Deal_Image_Right_Line[y] - 1) = 4;
    }
}


/**
*
* @brief    边线曲率
* @param    *in_line        需要计算曲率的边线
* @param    len             边线的长度
* @param    start           开始计算的长度
* @param    end             结束计算的长度
* @return   void
* @notes
* Example:  Line_Curvature(Deal_Image_Mid_Line[0],DEAL_IMAGE_H,End_Line,DEAL_IMAGE_H - 5);
*
**/
float Line_Curvature(unsigned char in_line[DEAL_IMAGE_H],unsigned char len,unsigned char start,unsigned char end)
{
    int i;
    float sumX = 0, sumY = 0, avrX = 0, avrY = 0 ;
    float B = 0, num = 0, B_up1 = 0, B_up2 = 0, B_up = 0, B_down = 0;
    if(end > len-5)
        end = len - 5;
    for(i = start; i <= end; i++)
    {
        num++;
        sumX += i;
        sumY += (in_line[i] + i);
    }
    avrX = sumX / num;
    avrY = sumY / num;
    for(i = start; i <= end; i++)
    {
        B_up1 = ((in_line[i] + i) - avrY);
        B_up2 = i - avrX;
        B_up += (int)(10 * (B_up1 * B_up2));
        B_up = B_up / 100 * 100;
        B_down += (int)(10 * ((i - avrX) * (i - avrX)));
    }
    if(B_down == 0)
        B = 0;
    else
        B = B_up * 16 / B_down;
    return B;
}

/**
*
* @brief    图像处理
* @param    prospect            计算偏差的前瞻
* @param    error_offset        偏差补偿
* @return   void
* @notes
* Example:  Image_Deal(30,12.5);
*
**/
float Image_Deal(unsigned char prospect, float error_offset)
{
    float error;
    // 图像压缩
    Image_Compress(MT9V034_Image_Data[0],Deal_Image_Gray[0]);
    // 图像二值化
    Image_Binary(Deal_Image_Gray[0],Deal_Image_Binary[0],200);
//    Image_Sobel(Deal_Image_Gray, Deal_Image_Binary, 90);
    // 图像滤波
    Image_Filter(Deal_Image_Binary[0]);
    // 图像扫线
    Image_Find_Line(Deal_Image_Binary[0]);
    // 偏差计算
    error = 1.1 * (Deal_Image_Mid_Line[prospect] - DEAL_IMAGE_W/2) - 0.75 * Line_Curvature(Deal_Image_Mid_Line,DEAL_IMAGE_H,End_Line,DEAL_IMAGE_H - 5) + error_offset;
    // 出界保护
    if(End_Line >= 45)
        Car_State = 0;

    return error;
}
