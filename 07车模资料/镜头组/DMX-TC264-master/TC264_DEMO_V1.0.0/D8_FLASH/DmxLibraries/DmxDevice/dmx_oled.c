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
 * @file       dmx_oled.c
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
* @brief    0.96��6��OLED��Ļ��ʼ��
* @param    void
* @return   void
* @notes    �޸ĹܽŶ������dmx_oled.h�ļ���ĺ궨��ܽŽ����޸�
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
* @brief    0.96��6��OLED��Ļ����
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
* @brief    0.96��6��OLED��Ļ���õ�����
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @return   void
* @notes    ���Ͻ�����Ϊ(0,0)
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
* @brief    0.96��6��OLED��Ļ����
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
* @brief    0.96��6��OLED��Ļ����
* @param
* @return   void
* @notes    ִ�к�Ч����ȫ��,����
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
* @brief    0.96��6��OLED��Ļ��ʾ�ַ���
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @param    biglow      ö���ַ���ʾ��С
* @param    str         ��Ҫ��ʾ���ַ���
* @return   void
* @notes
* Example:  Show_String_OLED(0,0,"123",OLED8X16);    //����Ļ���Ͻ���ʾ8X16��С�ġ�123��
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
* @brief    0.96��6��OLED��Ļ��ʾInt������
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @param    biglow      ö���ַ���ʾ��С
* @param    num         ��Ҫ��ʾ������
* @return   void
* @notes
* Example:  Show_Int_OLED(0,0,a,OLED8X16);    //����Ļ���Ͻ���ʾ8X16��С��a����������
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
* @brief    0.96��6��OLED��Ļ��ʾFloat������
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @param    biglow      ö���ַ���ʾ��С
* @param    num         ��Ҫ��ʾ������
* @param    point       С�������ʾλ��
* @return   void
* @notes    Float������С����������ʾ6λ
* Example:  Show_Float_OLED(64,0,3.1415926,3,OLED8X16);    //����Ļ���Ͻ���ʾ8X16��С�ġ�3.142��
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
* @brief    0.96��6��OLED��Ļ��ʾ16X16���ĺ���
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @param    chinese     ����������׵�ַ
* @param    startnum    ��ʼ��ʾ�ĺ���λ��
* @param    endnum      ������ʾ�ĺ���λ��
* @return   void
* @notes    ���ȡģ�ڶ��庺���ֿ�ʱ��˵��
* Example:  Show_Chinese16x16_OLED(0,0,Chinese16x16,0,3);   // ����Ļ���Ͻ���ʾ16X16��С�ĺ��֡���������
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
* @brief    0.96��6��OLED��Ļ��ʾBMPͼƬ
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @param    wide        ͼƬʵ�����ؿ��(1~127)
* @param    high        ͼƬʵ�����ظ߶�(1~64)
* @param    bmp         ͼƬ�����׵�ַ
* @return   void
* @notes    ͼƬ�������Ϊ128��64
* Example:  Show_BMP_OLED(0,0,Chinese16x16,0,3);    // ����Ļ���Ͻ���ʾ16X16��С�ĺ��֡���������
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
* @brief    OLED��Ļ��ʾ����ͷ��ֵ��ͼ��
* @param    x                   x��������
* @param    y                   y��������
* @param    image               ͼ������
* @param    width               ͼ������ʵ�ʿ��
* @param    heigh               ͼ������ʵ�ʸ߶�
* @param    show_width          ͼ��������ʾ���
* @param    show_height         ͼ��������ʾ�߶�
* @param    threshold           ��ֵ����ֵ
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
* @brief    0.96��6��OLED��Ļд����
* @param    cmd         ����
* @return   void
* @notes    �ڲ�����
* Example:  OLED_WrByte(0xff);
*
**/
static void Write_Data_OLED(unsigned char cmd)
{
    OLED_DC_LEVEL(0);
    OLED_Write_8bit(cmd);
    OLED_DC_LEVEL(1);
}
