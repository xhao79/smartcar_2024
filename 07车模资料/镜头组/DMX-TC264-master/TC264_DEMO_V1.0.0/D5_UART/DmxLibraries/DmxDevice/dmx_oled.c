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
 * @file       dmx_oled.c
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

#include "dmx_oled.h"
#include "dmx_gpio.h"
#include "dmx_delay.h"
#include "dmx_hard_spi.h"
#include "dmx_soft_spi.h"
#include "dmx_function.h"
#include "stdio.h"
#include "string.h"

#if OLED_HARD_SPI
#define OLED_Write_8bit(data)       (write_8bit_hard_spi(OLED_SPI, (data)))
#else
static  SOFT_SPI_struct             OLED_SPI;
#define OLED_Write_8bit(data)       (write_8bitdata_soft_spi(&OLED_SPI, (data)))
#endif

/**
*
* @brief    0.96寸6脚OLED屏幕初始化
* @param    void
* @return   void
* @notes    修改管脚定义可在dmx_oled.h文件里的宏定义管脚进行修改
* Example:  Init_OLED();
*
**/
void Init_OLED(void)
{
    #if OLED_HARD_SPI
        init_hard_spi(OLED_SPI, SPI_MODE0, OLED_SPI_SPEED, OLED_SCL_PIN, OLED_SDA_PIN, OLED_SDA_IN_PIN, SPI_CS_NULL);
    #else
        init_soft_spi(&OLED_SPI, 0, OLED_D0_MODULE,OLED_D0_PIN, OLED_D1_MODULE,OLED_D1_PIN,0,0);
    #endif

    init_gpio(OLED_DC_MODULE , OLED_DC_PIN , OutputPUSHPULL , 0);
    init_gpio(OLED_RES_MODULE, OLED_RES_PIN, OutputPUSHPULL , 0);
    init_gpio(OLED_CS_MODULE , OLED_CS_PIN , OutputPUSHPULL , 0);

    OLED_RES_LEVEL(0);
    OLED_Delay10ms(8);
    OLED_RES_LEVEL(1);

    Write_Data_OLED(0xae);
    Write_Data_OLED(0x00);
    Write_Data_OLED(0x10);
    Write_Data_OLED(0x40);
    Write_Data_OLED(0x81);
    Write_Data_OLED(0xcf);
    Write_Data_OLED(0xa1);
    Write_Data_OLED(0xc8);
    Write_Data_OLED(0xa6);
    Write_Data_OLED(0xa8);
    Write_Data_OLED(0x3f);
    Write_Data_OLED(0xd3);
    Write_Data_OLED(0x00);
    Write_Data_OLED(0xd5);
    Write_Data_OLED(0x80);
    Write_Data_OLED(0xd9);
    Write_Data_OLED(0xf1);
    Write_Data_OLED(0xda);
    Write_Data_OLED(0x12);
    Write_Data_OLED(0xdb);
    Write_Data_OLED(0x40);
    Write_Data_OLED(0x20);
    Write_Data_OLED(0x02);
    Write_Data_OLED(0x8d);
    Write_Data_OLED(0x14);
    Write_Data_OLED(0xa4);
    Write_Data_OLED(0xa6);
    Write_Data_OLED(0xaf);
    Clean_OLED();
    Set_Pos_OLED(0,0);
}

/**
*
* @brief    0.96寸6脚OLED屏幕画点
* @param    data
* @return   void
* @notes
* Example:  Draw_Point_OLED(0xff);
*
**/
void Draw_Point_OLED(unsigned char data)
{
    OLED_DC_LEVEL(1);
    OLED_Write_8bit(data);
    OLED_DC_LEVEL(0);
}

/**
*
* @brief    0.96寸6脚OLED屏幕设置点坐标
* @param    x           x轴坐标数据(0~127)
* @param    y           y轴坐标数据(0~7)
* @return   void
* @notes    左上角坐标为(0,0)
* Example:  Set_Pos_OLED(0,0);
*
**/
void Set_Pos_OLED(unsigned char x, unsigned char y)
{
    Write_Data_OLED(0xb0+y);
    Write_Data_OLED(((x&0xf0)>>4)|0x10);
    Write_Data_OLED((x&0x0f));
}

/**
*
* @brief    0.96寸6脚OLED屏幕点亮
* @param
* @return   void
* @notes
* Example:  Fill_OLED();
*
**/
void Fill_OLED(void)
{
    unsigned char y,x;

    for(y=0;y<8;y++)
    {
        Write_Data_OLED(0xb0+y);
        Write_Data_OLED(0x01);
        Write_Data_OLED(0x10);
        for(x=0;x<OLED_WIDTH;x++)
            Draw_Point_OLED(0xff);
    }
}

/**
*
* @brief    0.96寸6脚OLED屏幕清屏
* @param
* @return   void
* @notes    执行后效果是全黑,黑屏
* Example:  Clean_OLED();
*
**/
void Clean_OLED(void)
{
    unsigned char y,x;
    for(y=0;y<8;y++)
    {
        Write_Data_OLED(0xb0+y);
        Write_Data_OLED(0x01);
        Write_Data_OLED(0x10);
        for(x=0;x<OLED_WIDTH;x++)
            Draw_Point_OLED(0);
    }
}

/**
*
* @brief    0.96寸6脚OLED屏幕显示字符串
* @param    x           x轴坐标数据(0~127)
* @param    y           y轴坐标数据(0~7)
* @param    biglow      枚举字符显示大小
* @param    str         需要显示的字符串
* @return   void
* @notes
* Example:  Show_String_OLED(0,0,"123",OLED8X16);    //在屏幕左上角显示8X16大小的“123”
*
**/
void Show_String_OLED(unsigned char x,unsigned char y, char str[],SHOW_size_enum fontsize)
{
    unsigned char c=0,i=0,j=0;
    while (str[j]!='\0')
    {
        c =str[j]-32;
        if(fontsize==Show6x8)
        {
            if(x>126){x=0;y++;}
            Set_Pos_OLED(x,y);
            for(i=0;i<6;i++)
                Draw_Point_OLED(Char6x8[c][i]);
            x+=6;
        }
        else if(fontsize==Show8x16)
        {
            if(x>120){x=0;y++;}
            Set_Pos_OLED(x,y);
            for(i=0;i<8;i++)
                Draw_Point_OLED(Char8x16[c][i]);
            Set_Pos_OLED(x,y+1);
            for(i=0;i<8;i++)
                Draw_Point_OLED(Char8x16[c][i+8]);
            x+=8;
        }
        j++;
    }
}

/**
*
* @brief    0.96寸6脚OLED屏幕显示Int型数据
* @param    x           x轴坐标数据(0~127)
* @param    y           y轴坐标数据(0~7)
* @param    biglow      枚举字符显示大小
* @param    num         需要显示的数据
* @return   void
* @notes
* Example:  Show_Int_OLED(0,0,a,OLED8X16);    //在屏幕左上角显示8X16大小的a变量的数据
*
**/
void Show_Int_OLED(char x,char y,int num,SHOW_size_enum fontsize)
{
    char buff[6]={' ',' ',' ',' ',' ',' '};
    int_to_str_func(buff,num);
    Show_String_OLED(x, y, buff, fontsize);
}

/**
*
* @brief    0.96寸6脚OLED屏幕显示Float型数据
* @param    x           x轴坐标数据(0~127)
* @param    y           y轴坐标数据(0~7)
* @param    biglow      枚举字符显示大小
* @param    num         需要显示的数据
* @param    point       小数点后显示位数
* @return   void
* @notes    Float型数据小数点后最多显示6位
* Example:  Show_Float_OLED(64,0,3.1415926,3,OLED8X16);    //在屏幕左上角显示8X16大小的“3.142”
*
**/
void Show_Float_OLED(char x,char y,float num,unsigned char point,SHOW_size_enum fontsize)
{
    char buff[11];
    unsigned char i,j;

    sprintf(buff, "%f", num);
    while(buff[i] != '.')
        i++;
    for(j = i + point + 1;j<10;j++)
        buff[j] = ' ';
    if(num<0)
        buff[10] = '\0';
    else
        buff[9] = '\0';
    Show_String_OLED(x, y, buff, fontsize);
}

/**
*
* @brief    0.96寸6脚OLED屏幕显示16X16中文汉字
* @param    x           x轴坐标数据(0~127)
* @param    y           y轴坐标数据(0~7)
* @param    chinese     汉字数组的首地址
* @param    startnum    开始显示的汉字位号
* @param    endnum      结束显示的汉字位号
* @return   void
* @notes    如何取模在定义汉字字库时已说明
* Example:  Show_Chinese16x16_OLED(0,0,Chinese16x16,0,3);   // 在屏幕左上角显示16X16大小的汉字“呆萌侠”
*
**/
void Show_Chinese16x16_OLED(char x,char y,const unsigned char *chinese,char startnum,char endnum)
{
    unsigned int i,j,k;

    for(j = startnum;j < endnum;j++)
    {
        Set_Pos_OLED(x+(j-startnum)*16 , y);
        for(i = 0;i < 16;i++)
        {
            Draw_Point_OLED(chinese[startnum*16*2+k]);
            k++;
        }
        Set_Pos_OLED(x+(j-startnum)*16,y + 1);
        for(i = 0;i < 16;i++)
        {
            Draw_Point_OLED(chinese[startnum*16*2+k]);
            k++;
        }
    }
}

/**
*
* @brief    0.96寸6脚OLED屏幕显示BMP图片
* @param    x           x轴坐标数据(0~127)
* @param    y           y轴坐标数据(0~7)
* @param    wide        图片实际像素宽度(1~127)
* @param    high        图片实际像素高度(1~64)
* @param    bmp         图片数组首地址
* @return   void
* @notes    图片最大像素为128×64
* Example:  Show_BMP_OLED(0,0,Chinese16x16,0,3);    // 在屏幕左上角显示16X16大小的汉字“呆萌侠”
*
**/
void Show_BMP_OLED(unsigned char x,unsigned char y,unsigned char width,unsigned char height,const unsigned char * bmp)
{
    unsigned int i=0;
    unsigned char x0,y0,x1,y1;
    y1 = (y+height-1)/8;
    x1 = x + width;
    for(y0=y/8;y0<=y1;y0++)
    {
        Set_Pos_OLED(x,y0);
        for(x0=x;x0<x1;x0++)
        {
            Draw_Point_OLED(bmp[i++]);
        }
    }
}

/**
*
* @brief    OLED屏幕显示摄像头二值化图像
* @param    x                   x方向坐标
* @param    y                   y方向坐标
* @param    image               图像数组
* @param    width               图像数组实际宽度
* @param    heigh               图像数组实际高度
* @param    show_width          图像数组显示宽度
* @param    show_height         图像数组显示高度
* @param    threshold           二值化阈值
* @return   void
* @notes
* Example:  Show_Image_Oled(0,0,OriginalImageData[0],188,120,80,60,80);
*
**/
void Show_Image_Oled (unsigned short x, unsigned short y, const unsigned char *image, unsigned short width, unsigned short height, unsigned short show_width, unsigned short show_height, unsigned char threshold)
{
    short i, j;
    unsigned char dat;
    unsigned int width_ratio = 0, height_ratio = 0;

    OLED_CS_LEVEL(0);
    show_height = show_height - show_height % 8;
    for(i = 0; i < show_height; i += 8)
    {
        Set_Pos_OLED(x + 0, y + i / 8);
        height_ratio = i * height / show_height;
        for(j = 0; j < show_width; j ++)
        {
            width_ratio = j * width / show_width;
            dat = 0;
            if(*(image + height_ratio * width + width_ratio + width * 0) > threshold)
                dat |= 0x01;
            if(*(image + height_ratio * width + width_ratio + width * 1) > threshold)
                dat |= 0x02;
            if(*(image + height_ratio * width + width_ratio + width * 2) > threshold)
                dat |= 0x04;
            if(*(image + height_ratio * width + width_ratio + width * 3) > threshold)
                dat |= 0x08;
            if(*(image + height_ratio * width + width_ratio + width * 4) > threshold)
                dat |= 0x10;
            if(*(image + height_ratio * width + width_ratio + width * 5) > threshold)
                dat |= 0x20;
            if(*(image + height_ratio * width + width_ratio + width * 6) > threshold)
                dat |= 0x40;
            if(*(image + height_ratio * width + width_ratio + width * 7) > threshold)
                dat |= 0x80;
            Draw_Point_OLED(dat);
        }
    }
    OLED_CS_LEVEL(1);
}

/**
*
* @brief    0.96寸6脚OLED屏幕写命令
* @param    cmd         命令
* @return   void
* @notes    内部调用
* Example:  OLED_WrByte(0xff);
*
**/
static void Write_Data_OLED(unsigned char cmd)
{
    OLED_DC_LEVEL(0);
    OLED_Write_8bit(cmd);
    OLED_DC_LEVEL(1);
}
