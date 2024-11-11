/****************************************************************************************
 *     COPYRIGHT NOTICE
 *     Copyright (C) 2023,AS DAIMXA
 *     copyright Copyright (C) ������DAIMXA,2023
 *     All rights reserved.
 *     ��������QQȺ��710026750
 *
 *     ��ע�������⣬�����������ݰ�Ȩ�������������ܿƼ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣�������������Ƽ��İ�Ȩ������
 *      ____    _    ___ __  ____  __    _
 *     |  _ \  / \  |_ _|  \/  \ \/ /   / \
 *     | | | |/ _ \  | || |\/| |\  /   / _ \
 *     | |_| / ___ \ | || |  | |/  \  / ___ \
 *     |____/_/   \_\___|_|  |_/_/\_\/_/   \_\
 *
 * @file       dmx_image_deal.c
 * @brief      ������TC264��Դ��
 * @company    �Ϸʴ��������ܿƼ����޹�˾
 * @author     �������Ƽ���QQ��2453520483��
 * @MCUcore    TC264
 * @Software   AURIX Development Stdio V1.8.0
 * @version    �鿴˵���ĵ���version�汾˵��
 * @Taobao     https://daimxa.taobao.com/
 * @Openlib    https://gitee.com/daimxa
 * @date       2023-11-10
****************************************************************************************/

#include "dmx_all.h"

unsigned char Deal_Image_Gray[DEAL_IMAGE_H][DEAL_IMAGE_W];      // ѹ����ĻҶ�ͼ��
unsigned char Deal_Image_Binary[DEAL_IMAGE_H][DEAL_IMAGE_W];    // ��ֵ��ͼ��

unsigned char *row_addr;                                        // �е�ַ
unsigned char image_row_mid = DEAL_IMAGE_W/2 - 1;               // ���е�
unsigned char bottom_left_line,bottom_right_line;               // �ײ������ұ���

unsigned char Deal_Image_Left_Line[DEAL_IMAGE_H];               // �����
unsigned char Deal_Image_Right_Line[DEAL_IMAGE_H];              // �ұ���
unsigned char Deal_Image_Mid_Line[DEAL_IMAGE_H];                // ����
unsigned char Deal_Image_Wide[DEAL_IMAGE_H];                    // ���
unsigned char Deal_Image_Left_Flag[DEAL_IMAGE_H];               // ���������
unsigned char Deal_Image_Right_Flag[DEAL_IMAGE_H];              // �ұ�������

unsigned char End_Line = 20;                                    // ɨ�߽�����
unsigned char Lost_Line;                                        // ��������
unsigned char Left_Lost_Line,Right_Lost_Line;                   // ���Ҷ�������
unsigned char Left_Border,Right_Border;                         // ���߿�ʼ��������ɨ�ߵ���������߽�ֵ
unsigned char Border_Interval = 3;                              // ���߿�ʼ��������ɨ�ߵ������С
unsigned char Mend_Start_Line;                                  // ���߿�ʼ��
unsigned char Mend_End_Line;                                    // ���߽�����
float Mend_Slope;                                               // ����б��
unsigned char Car_State = 1;                                    // ��״̬,0:ͣ��,1:����

/**
*
* @brief    ͼ��ѹ��
* @param    *in_image       ԭʼͼ��
* @param    *out_image      ѹ�����ͼ��
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
* @brief    ��򷨼��㰴ͼ���ֵ����ֵ
* @param    *image          ��Ҫ������ֵ��ͼ��
* @param    width           ͼ���
* @param    height          ͼ���
* @param    pixel_threshold ͼ����ֵ
* @return   unsigned char   �����ֵ
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
    unsigned char *data = image;    // ָ���������ݵ�ָ��
    for (i = 0; i < 256; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }
    unsigned long gray_sum = 0;
    // ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    for (i = 0; i < height; i += 1)
    {
        for (j = 0; j < width; j += 1)
        {
            pixelCount[(int)data[i * width + j]]++; // ����ǰ�ĵ������ֵ��Ϊ����������±�
            gray_sum += (int)data[i * width + j];   // �Ҷ�ֵ�ܺ�
        }
    }
    // ����ÿ������ֵ�ĵ�������ͼ���еı���
    for (i = 0; i < 256; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
    }
    // �����Ҷȼ�[0,255],[0,pixel_threshold]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
    for (j = 0; j < image_max_threshold; j++)
    {
        w0 += pixelPro[j];         // ��������ÿ���Ҷ�ֵ�����ص���ռ����֮�� ���������ֵı���
        u0tmp += j * pixelPro[j];  // ��������ÿ���Ҷ�ֵ�ĵ�ı���*�Ҷ�ֵ

        w1 = 1 - w0;
        u1tmp = gray_sum / pixelSum - u0tmp;

        u0 = u0tmp / w0;    // ����ƽ���Ҷ�
        u1 = u1tmp / w1;    // ǰ��ƽ���Ҷ�
        u = u0tmp + u1tmp;  // ȫ��ƽ���Ҷ�
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
* @brief    ͼ���ֵ��
* @param    *in_image       ѹ�����ͼ��
* @param    *out_image      ��ֵ�����ͼ��
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
            // ��ֵԽ��,��ʾ������Խ��,��ǳ��ͼ��Ҳ����ʾ����
            if ( *(in_image+temp+x) > final_threshold)
                *(out_image+temp+x) = 1;  // ��
            else
                *(out_image+temp+x) = 0;  // ��
        }
    }
}

/**
*
* @brief    ͼ��Sobel��ֵ��
* @param    *in_image       ѹ�����ͼ��
* @param    *out_image      Sobel��ֵ�����ͼ��
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
* @brief    ͼ���˲�
* @param    *in_image       ��Ҫ�˲���ͼ��
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
* @brief    ͼ��ɨ��
* @param    *in_image       ��Ҫ�����ͼ��
* @return   void
* @notes
* Example:  Image_Find_Line(Deal_Image_Binary[0]);
*
**/
void Image_Find_Line(unsigned char *in_image)
{
    unsigned char x, y, z;
    // ��ʼ����������
    for(y = 0,End_Line = 20,Lost_Line=0,Left_Lost_Line=0,Right_Lost_Line=0; y < End_Line; y++)
    {
        Deal_Image_Left_Line[y] = 0;                    // ��ʼ�������
        Deal_Image_Right_Line[y] = DEAL_IMAGE_W - 1;    // ��ʼ���ұ���
        Deal_Image_Mid_Line[y] = DEAL_IMAGE_W / 2;      // ��ʼ������
        Deal_Image_Wide[y] = DEAL_IMAGE_W - 1;          // ��ʼ�����
        Deal_Image_Left_Flag[y] = 0;                    // ��ʼ�����������
        Deal_Image_Right_Flag[y] = 0;                   // ��ʼ���ұ�������
    }
    // ������ɨ��ɨͼ��ײ���������,�ȶ����л�ɨ�߷�ʽ
    // �ײ��е���ʼ��ַ
    row_addr = (in_image + DEAL_IMAGE_W * (DEAL_IMAGE_H - 2 ) );
    // �ײ��е��е�Ϊ�ڵ�
    if((*(row_addr + image_row_mid)) == 0)
    {
        // ���е����������Ѱ�Ұ׵�
        for(x = 0;x < image_row_mid; x++)
        {
            // ����ҵ��׵��˳���forѭ��,��ʱx��ֵΪ�ð׵��x����
            if(*(row_addr + image_row_mid - x) == 1 )
                break;
            // �ұ��ҵ��׵��˳���forѭ��,��ʱx��ֵΪ�ð׵��x����
            if(*(row_addr + image_row_mid + x) == 1 )
                break;
        }
        // �ж�����forѭ���˳�ʱ��x����ĵ����е���߻����ұ�
        // �е��ȥx����Ϊ���������
        if(*(row_addr + image_row_mid - x) == 1 )
        {
            // �õ�ɿ����ײ��е��ұ߽�
            bottom_right_line = image_row_mid - x + 1;
            // �ײ����ұ��������ҵ��ڵ�����ҵ��������Ϊ�ײ��������
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
        // �е����x����Ϊ�������ұ�
        else if(*(row_addr + image_row_mid + x) ==1 )
        {
            // �õ�ɿ����ײ��е���߽�
            bottom_left_line = image_row_mid + x - 1;
            // �ײ�������������ҵ��ڵ�����ҵ����ұ���Ϊ�ײ����ұ���
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
    // �ײ��е��е�Ϊ�׵�
    else
    {
        // �е������ҵ��ڵ�����ҵ��������Ϊ�ײ��������
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
        // �е������ҵ��ڵ�����ҵ����ұ���Ϊ�ײ����ұ���
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
    // �洢�����
    Deal_Image_Left_Line[DEAL_IMAGE_H - 1] = bottom_left_line;
    // �洢�ұ���
    Deal_Image_Right_Line[DEAL_IMAGE_H - 1] = bottom_right_line;
    // �洢����
    Deal_Image_Mid_Line[DEAL_IMAGE_H - 1] = (bottom_left_line + bottom_right_line) / 2;
    // �洢���
    Deal_Image_Wide[DEAL_IMAGE_H - 1] = bottom_right_line - bottom_left_line;
    // �洢���������
    Deal_Image_Left_Flag[DEAL_IMAGE_H - 1] = 1;
    // �洢�ұ�������
    Deal_Image_Right_Flag[DEAL_IMAGE_H - 1] = 1;
    // �ӵײ�������ɨ5��
    for(y = DEAL_IMAGE_H - 2; y > DEAL_IMAGE_H - 7; y--)
    {
        // �е�ַ
        row_addr = (in_image + DEAL_IMAGE_W * y );
        // �е������ҵ��ڵ�����ҵ��������Ϊ�����
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
        // �е������ҵ��ڵ�����ҵ����ұ���Ϊ�ұ���
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
        // �洢����
        Deal_Image_Mid_Line[y] = (Deal_Image_Left_Line[y] + Deal_Image_Right_Line[y]) / 2;
        // �洢���
        Deal_Image_Wide[y] = Deal_Image_Right_Line[y] - Deal_Image_Left_Line[y];
        // �洢���������
        Deal_Image_Left_Flag[y] = 1;
        // �洢�ұ�������
        Deal_Image_Right_Flag[y] = 1;
    }

    // �л�ɨ�߷�ʽɨ�ߵ�������
    for(y = DEAL_IMAGE_H - 7; y > End_Line; y--)
    {
        // �е�ַ
        row_addr = (in_image + DEAL_IMAGE_W * y );
        // ����߿�ʼ��������ɨ�ߵ���������߽�ֵ
        Left_Border = Deal_Image_Left_Line[y+1] - Border_Interval;
        Right_Border = Deal_Image_Left_Line[y+1] + Border_Interval;
        // ��������߽�ֵ�޷�
        Left_Border < 1? Left_Border=1: Left_Border;
        Right_Border > DEAL_IMAGE_W - 1? Right_Border = DEAL_IMAGE_W - 1: Right_Border;
        // ��ʼɨ�������
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
        // �ұ��߿�ʼ��������ɨ�ߵ���������߽�ֵ
        Left_Border = Deal_Image_Right_Line[y+1] - Border_Interval;
        Right_Border = Deal_Image_Right_Line[y+1] + Border_Interval;
        // ��������߽�ֵ�޷�
        Left_Border < 1? Left_Border=1: Left_Border;
        Right_Border > DEAL_IMAGE_W - 1? Right_Border = DEAL_IMAGE_W - 1: Right_Border;
        // ��ʼɨ���ұ���
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
        // ��������߲����������������һ�������
        if( Deal_Image_Left_Flag[y] == 0)
        {
            Deal_Image_Left_Line[y] = Deal_Image_Left_Line[y+1];
        }
        // �����ұ��߲����������������һ���ұ���
        if( Deal_Image_Right_Flag[y] == 0)
        {
            Deal_Image_Right_Line[y] = Deal_Image_Right_Line[y+1];
        }
        // ����ȷ���������ڰ�����
        if( Deal_Image_Left_Flag[y] == 2 || Deal_Image_Right_Flag[y] == 2)
        {
            // ����߲�����
            if(Deal_Image_Left_Flag[y] == 2)
            {
                // �����ұ���֮�����������ɨ�������
                for(x = Deal_Image_Left_Line[y] + 1;x <= Deal_Image_Right_Line[y] - 1; x++)
                {
                    if(*(row_addr + x) == 0 && *(row_addr + x + 1) == 1)
                    {
                        Deal_Image_Left_Line[y] = x;
                        Deal_Image_Left_Flag[y] = 1;
                        break;
                    }
                    // ɨ���׵�ֱ������
                    else if(*(row_addr + x) == 1)
                    {
                        Deal_Image_Left_Flag[y] = 0;
                        break;
                    }
                    // ɨ����ɨ�����ұ���
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
            // �ұ��߲�����
            if(Deal_Image_Right_Flag[y] == 2)
            {
                // �����ұ���֮����ҵ�������ɨ���ұ���
                for(x = Deal_Image_Right_Line[y] - 1;x >= Deal_Image_Left_Line[y] + 1; x--)
                {
                    if(*(row_addr + x) == 0 && *(row_addr + x - 1) == 1)
                    {
                        Deal_Image_Right_Line[y] = x;
                        Deal_Image_Right_Flag[y] = 1;
                        break;
                    }
                    // ɨ���׵�ֱ������
                    else if(*(row_addr + x) == 1)
                    {
                        Deal_Image_Right_Flag[y] = 0;
                        break;
                    }
                    // ɨ����ɨ���������
                    else if(x == Deal_Image_Left_Line[y] + 1)
                    {
                        Deal_Image_Right_Line[y] = x;
                        Deal_Image_Right_Flag[y] = 1;
                        break;
                    }
                }

            }
            // ������ȵ���6,�˳�ɨ��
            if(Deal_Image_Right_Line[y] - Deal_Image_Left_Line[y] <= 6)
            {
                End_Line = y + 1;
                break;
            }
        }
        // ���ұ��߶�����,����++
        if( Deal_Image_Left_Flag[y] == 0 && Deal_Image_Right_Flag[y] == 0)
            Lost_Line++;
        // ����߶���,����++
        if(Deal_Image_Left_Flag[y] == 0)
            Left_Lost_Line++;
        // �ұ��߶���,����++
        if(Deal_Image_Right_Flag[y] == 0)
            Right_Lost_Line++;
        // ������޷�
        Deal_Image_Left_Line[y] < 1? Deal_Image_Left_Line[y]=1: Deal_Image_Left_Line[y];
        Deal_Image_Left_Line[y] > DEAL_IMAGE_W - 1? Deal_Image_Left_Line[y] = DEAL_IMAGE_W - 1: Deal_Image_Left_Line[y];
        // �ұ����޷�
        Deal_Image_Right_Line[y] < 1? Deal_Image_Right_Line[y]=1: Deal_Image_Right_Line[y];
        Deal_Image_Right_Line[y] > DEAL_IMAGE_W - 1? Deal_Image_Right_Line[y] = DEAL_IMAGE_W - 1: Deal_Image_Right_Line[y];
        // �洢����
        Deal_Image_Mid_Line[y] = (Deal_Image_Left_Line[y] + Deal_Image_Right_Line[y]) / 2;
        // �洢���
        Deal_Image_Wide[y] = Deal_Image_Right_Line[y] - Deal_Image_Left_Line[y];
        // ��������һ��ֵ�ҿ��С��һ��ֵ,�˳�ɨ��
        if(Deal_Image_Wide[y] <= 7 && y < 30)
        {
            End_Line = y + 1;
            break;
        }
        // ���ұ���̫����,�˳�ɨ��
        else if(Deal_Image_Left_Line[y] >= DEAL_IMAGE_W - 10 && Deal_Image_Right_Line[y] <=  10)
        {
            End_Line = y + 1;
            break;
        }
    }

    // ����ȱʧ,�ӵײ����ӳ��߲���
    if(Lost_Line >= 5)
        Mend_Start_Line = DEAL_IMAGE_H - 5;
    // ������
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
    // ������
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
    // �������ߺͿ��
    for(y = DEAL_IMAGE_H - 2; y >= End_Line; y--)
    {
        // ������޷�
        Deal_Image_Left_Line[y] < 1? Deal_Image_Left_Line[y]=1: Deal_Image_Left_Line[y];
        Deal_Image_Left_Line[y] > DEAL_IMAGE_W - 2? Deal_Image_Left_Line[y] = DEAL_IMAGE_W - 2: Deal_Image_Left_Line[y];
        // �ұ����޷�
        Deal_Image_Right_Line[y] < 1? Deal_Image_Right_Line[y]=1: Deal_Image_Right_Line[y];
        Deal_Image_Right_Line[y] > DEAL_IMAGE_W - 2? Deal_Image_Right_Line[y] = DEAL_IMAGE_W - 2: Deal_Image_Right_Line[y];
        // �洢����
        Deal_Image_Mid_Line[y] = (Deal_Image_Left_Line[y] + Deal_Image_Right_Line[y]) / 2;
        // �洢���
        Deal_Image_Wide[y] = Deal_Image_Right_Line[y] - Deal_Image_Left_Line[y];
    }

    // �����˲�
    for(y = DEAL_IMAGE_H - 2; y >= End_Line; y--)
    {
        // �е�ַ
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
        // ��������
        Deal_Image_Mid_Line[y] = (Deal_Image_Left_Line[y] + Deal_Image_Right_Line[y]) / 2;
        // ��ͼ����д���������,�����Ϊ2,����Ϊ3,�ұ���Ϊ4
        *(row_addr + Deal_Image_Left_Line[y] + 1) = 2;
        *(row_addr + Deal_Image_Mid_Line[y]) = 3;
        *(row_addr + Deal_Image_Right_Line[y] - 1) = 4;
    }
}


/**
*
* @brief    ��������
* @param    *in_line        ��Ҫ�������ʵı���
* @param    len             ���ߵĳ���
* @param    start           ��ʼ����ĳ���
* @param    end             ��������ĳ���
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
* @brief    ͼ����
* @param    prospect            ����ƫ���ǰհ
* @param    error_offset        ƫ���
* @return   void
* @notes
* Example:  Image_Deal(30,12.5);
*
**/
float Image_Deal(unsigned char prospect, float error_offset)
{
    float error;
    // ͼ��ѹ��
    Image_Compress(MT9V034_Image_Data[0],Deal_Image_Gray[0]);
    // ͼ���ֵ��
    Image_Binary(Deal_Image_Gray[0],Deal_Image_Binary[0],200);
//    Image_Sobel(Deal_Image_Gray, Deal_Image_Binary, 90);
    // ͼ���˲�
    Image_Filter(Deal_Image_Binary[0]);
    // ͼ��ɨ��
    Image_Find_Line(Deal_Image_Binary[0]);
    // ƫ�����
    error = 1.1 * (Deal_Image_Mid_Line[prospect] - DEAL_IMAGE_W/2) - 0.75 * Line_Curvature(Deal_Image_Mid_Line,DEAL_IMAGE_H,End_Line,DEAL_IMAGE_H - 5) + error_offset;
    // ���籣��
    if(End_Line >= 45)
        Car_State = 0;

    return error;
}
