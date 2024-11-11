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
 * @file       dmx_ips.c
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

#include "dmx_ips.h"
#include "dmx_gpio.h"
#include "dmx_delay.h"
#include "dmx_hard_spi.h"
#include "dmx_soft_spi.h"
#include "dmx_function.h"
#include "string.h"
#include "stdio.h"

// SPIЭ���д�����궨��,��ѧ�������޸�
#if IPS_HARD_SPI
#define IPS_Write_8bitData(data)    (write_8bit_hard_spi(IPS_SPI, (data)))
#define IPS_Write_16bitData(data)   (write_16bit_hard_spi(IPS_SPI, (data)))
#else
static  SOFT_SPI_struct             IPS_SPI;
#define IPS_Write_8bitData(data)    (write_8bitdata_soft_spi(&IPS_SPI, (data)))
#define IPS_Write_16bitData(data)   (write_16bitdata_soft_spi(&IPS_SPI, (data)))
#endif

// IPS��Ļ��͸�,�û������޸�,��dmx_ips.h��ѡ����ȷ��IPS��Ļ�ͺź��ʼ�����Զ��������
static unsigned short ips_width,ips_height;

/**
*
* @brief    ��ʼ��IPS��Ļ
* @param    void
* @return   void
* @notes    �޸Ĺܽſ���dmx_ips.h�ļ���ĺ궨��ܽŽ����޸�
* Example:  Init_IPS();
*
**/
void Init_IPS(void)
{
    // SPI��ʼ��
    #if IPS_HARD_SPI
        init_hard_spi(IPS_SPI, SPI_MODE0, IPS114_SPI_SPEED, IPS114_SCL_PIN, IPS114_SDA_PIN, IPS114_SDA_IN_PIN, SPI_CS_NULL);
    #else
        init_soft_spi(&IPS_SPI, 0,IPS_SCL_MODULE,IPS_SCL_PIN, IPS_SDA_MODULE,IPS_SDA_PIN,0,0);
    #endif

    init_gpio(IPS_DC_MODULE ,IPS_DC_PIN ,OutputPUSHPULL,0);
    init_gpio(IPS_RES_MODULE,IPS_RES_PIN,OutputPUSHPULL,0);
    init_gpio(IPS_CS_MODULE ,IPS_CS_PIN ,OutputPUSHPULL,1);
    init_gpio(IPS_BLK_MODULE,IPS_BLK_PIN,OutputPUSHPULL,1);

    // ������Ļ�ͺ�����Ӧ���
    if(IPS_MODEL==0)
    {
        if(IPS_SHOW_DIR==0||IPS_SHOW_DIR==1)
        {
            ips_width=135;ips_height=240;
        }
        else
        {
            ips_width=240;ips_height=135;
        }
    }
    else if(IPS_MODEL==1)
    {
        ips_width=240;ips_height=240;
    }
    else if(IPS_MODEL==2)
    {
        ips_width=240;ips_height=240;
    }
    else if(IPS_MODEL==3)
    {
        if(IPS_SHOW_DIR==0||IPS_SHOW_DIR==1)
        {
            ips_width=240;ips_height=320;
        }
        else
        {
            ips_width=320;ips_height=240;
        }
    }

    IPS_RES_LEVEL(0);
    Delay_ms(STM0, 100);
    IPS_RES_LEVEL(1);
    Delay_ms(STM0, 100);

    IPS_CS_LEVEL(0);
    Delay_ms(STM0, 150);
    Write_Cmd_IPS(0x11);
    Delay_ms(STM0, 150);
    Write_Cmd_IPS(0x36);

    if(IPS_SHOW_DIR == 0)
        Write_8bit_IPS(0x00);
    else if(IPS_SHOW_DIR == 1)
        Write_8bit_IPS(0xC0);
    else if(IPS_SHOW_DIR == 2)
        Write_8bit_IPS(0x70);
    else if(IPS_SHOW_DIR == 3)
        Write_8bit_IPS(0xA0);

    Write_Cmd_IPS(0x3A);
    Write_8bit_IPS(0x05);
    Write_Cmd_IPS(0xB2);
    Write_8bit_IPS(0x0C);
    Write_8bit_IPS(0x0C);
    Write_8bit_IPS(0x00);
    Write_8bit_IPS(0x33);
    Write_8bit_IPS(0x33);
    Write_Cmd_IPS(0xB7);
    Write_8bit_IPS(0x35);
    Write_Cmd_IPS(0xBB);
    Write_8bit_IPS(0x19);
    Write_Cmd_IPS(0xC0);
    Write_8bit_IPS(0x2C);
    Write_Cmd_IPS(0xC2);
    Write_8bit_IPS(0x01);
    Write_Cmd_IPS(0xC3);
    Write_8bit_IPS(0x12);
    Write_Cmd_IPS(0xC4);
    Write_8bit_IPS(0x20);
    Write_Cmd_IPS(0xC6);
    Write_8bit_IPS(0x0F);
    Write_Cmd_IPS(0xD0);
    Write_8bit_IPS(0xA4);
    Write_8bit_IPS(0xA1);
    Write_Cmd_IPS(0xE0);
    Write_8bit_IPS(0xD0);
    Write_8bit_IPS(0x04);
    Write_8bit_IPS(0x0D);
    Write_8bit_IPS(0x11);
    Write_8bit_IPS(0x13);
    Write_8bit_IPS(0x2B);
    Write_8bit_IPS(0x3F);
    Write_8bit_IPS(0x54);
    Write_8bit_IPS(0x4C);
    Write_8bit_IPS(0x18);
    Write_8bit_IPS(0x0D);
    Write_8bit_IPS(0x0B);
    Write_8bit_IPS(0x1F);
    Write_8bit_IPS(0x23);
    Write_Cmd_IPS(0xE1);
    Write_8bit_IPS(0xD0);
    Write_8bit_IPS(0x04);
    Write_8bit_IPS(0x0C);
    Write_8bit_IPS(0x11);
    Write_8bit_IPS(0x13);
    Write_8bit_IPS(0x2C);
    Write_8bit_IPS(0x3F);
    Write_8bit_IPS(0x44);
    Write_8bit_IPS(0x51);
    Write_8bit_IPS(0x2F);
    Write_8bit_IPS(0x1F);
    Write_8bit_IPS(0x1F);
    Write_8bit_IPS(0x20);
    Write_8bit_IPS(0x23);
    Write_Cmd_IPS(0x21);
    Write_Cmd_IPS(0x29);

    Clean_IPS(WHITE);
}

/**
*
* @brief    IPS��Ļ������ʼ�ͽ�������
* @param    x1                x������ʼ��(0~240)
* @param    y1                y������ʼ��(0~135)
* @param    x2                x���������(0~240)
* @param    y2                y���������(0~135)
* @return   void
* @notes
* Example:  Set_Pos_IPS(0,0,0,0);
*
**/
void Set_Pos_IPS(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    int offset_x = 0, offset_y = 0;
    if(IPS_SHOW_DIR == 0)
    {
        if(IPS_MODEL==0)
        {
            offset_x = 52;offset_y = 40;
        }
        else
        {
            offset_x = 0;offset_y = 0;
        }
    }
    else if(IPS_SHOW_DIR == 1)
    {
        if(IPS_MODEL==0)
        {
            offset_x = 53;offset_y = 40;
        }
        else if(IPS_MODEL==1||IPS_MODEL==2)
        {
            offset_x = 0;offset_y = 80;
        }
        else
        {
            offset_x = 0;offset_y = 0;
        }
    }
    else if(IPS_SHOW_DIR == 2)
    {
        if(IPS_MODEL==0)
        {
            offset_x = 40;offset_y = 53;
        }
        else
        {
            offset_x = 0;offset_y = 0;
        }
    }
    else if(IPS_SHOW_DIR == 3)
    {
        if(IPS_MODEL==0)
        {
            offset_x = 40;offset_y = 52;
        }
        else if(IPS_MODEL==1||IPS_MODEL==2)
        {
            offset_x = 80;offset_y = 0;
        }
        else
        {
            offset_x = 0;offset_y = 0;
        }
    }
    Write_Cmd_IPS(0x2A);    // �е�ַ����
    Write_16bit_IPS(x1 + offset_x);
    Write_16bit_IPS(x2 + offset_x);
    Write_Cmd_IPS(0x2B);    // �е�ַ����
    Write_16bit_IPS(y1 + offset_y);
    Write_16bit_IPS(y2 + offset_y);
    Write_Cmd_IPS(0x2C);    // ������д
}

/**
*
* @brief    IPS��Ļ��ָ��λ�û���
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    color               �����ɫ(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Draw_Point_IPS(0,0,BLACK);
*
**/
void Draw_Point_IPS(unsigned int x, unsigned int y, COLOR_enum color)
{
    IPS_CS_LEVEL(0);
    Set_Pos_IPS(x, y, x, y);
    Write_16bit_IPS(color);
}

/**
*
* @brief    IPS��Ļ���ָ������
* @param    x1                  x������ʼ��(0~240)
* @param    y1                  y������ʼ��(0~135)
* @param    x2                  x���������(0~240)
* @param    y2                  y���������(0~135)
* @param    color               �����ɫ(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Fill_IPS(0,0,240,135,WHITE);    // IPS114��Ļȫ��
*
**/
void Fill_IPS(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, COLOR_enum color)
{
    unsigned int i, j;
    Set_Pos_IPS(x1, y1, x2 - 1, y2 - 1);    // ������ʾ��Χ
    for(i = y1; i < y2; i++)
    {
        for(j = x1; j < x2; j++)
        {
            Write_16bit_IPS(color);
        }
    }
}

/**
*
* @brief    IPS��Ļ����
* @param    color               �����ɫ(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Clean_IPS(WHITE);   // IPS114��Ļȫ��
*
**/
void Clean_IPS(COLOR_enum color)
{
    Fill_IPS(0, 0, ips_width, ips_height, color);
}

/**
*
* @brief    IPS��Ļ��ʾ�����ַ�
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    data                �ַ�
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    fontsize            ����ߴ�(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Show_Char_IPS(0,0,'D',BLACK,WHITE,Show8X16);    // �����Ͻ���ʾ��ɫ������ɫ��8X16�ַ�'D'
*
**/
void Show_Char_IPS(unsigned int x, unsigned int y, unsigned char data, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize)
{
    unsigned char i,j,temp_start,temp_end;
    IPS_CS_LEVEL(0);
    switch(fontsize)
    {
        case Show6x8:
            for(i = 0; i < 6; i ++)
            {
                Set_Pos_IPS(x + i, y, x + i, y + 8);
                temp_start = Char6x8[data - 32][i];
                for(j = 0; j < 8; j ++)
                {
                    if(temp_start & 0x01)
                    {
                        Write_16bit_IPS(fc);
                    }
                    else
                    {
                        Write_16bit_IPS(bc);
                    }
                    temp_start >>= 1;
                }
            }
            break;
        case Show8x16:
            for(i = 0; i < 8; i ++)
            {
                Set_Pos_IPS(x + i, y, x + i, y + 15);
                temp_start = Char8x16[data - 32][i];
                temp_end = Char8x16[data - 32][i + 8];
                for(j = 0; j < 8; j ++)
                {
                    if(temp_start & 0x01)
                    {
                        Write_16bit_IPS(fc);
                    }
                    else
                    {
                        Write_16bit_IPS(bc);
                    }
                    temp_start >>= 1;
                }
                for(j = 0; j < 8; j ++)
                {
                    if(temp_end & 0x01)
                    {
                        Write_16bit_IPS(fc);
                    }
                    else
                    {
                        Write_16bit_IPS(bc);
                    }
                    temp_end >>= 1;
                }
            }
            break;
    }
}

/**
*
* @brief    IPS��Ļ��ʾ�ַ���
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    *p                  Ҫ��ʾ���ַ���
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    fontsize            ����ߴ�(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Show_String_IPS(0,0,"DMX",BLACK,WHITE,Show8X16);    // �����Ͻ���ʾ��ɫ������ɫ��8X16�ַ���'DMX'
*
**/
void Show_String_IPS(unsigned int x, unsigned int y, char *p, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize)
{
    while(*p != '\0')
    {
        Show_Char_IPS(x, y, *p, fc, bc, fontsize);
        if(fontsize==Show6x8)
            x += 6;
        else if(fontsize==Show8x16)
            x += 8;
        p++;
    }
}

/**
*
* @brief    IPS��Ļ��ʾInt�ͱ���
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    data                Ҫ��ʾ��Int�ͱ���
* @param    num                 Ҫ��ʾ��Int�ͱ���λ��
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    fontsize            ����ߴ�(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Show_Int_IPS(0,0,521,3,BLACK,WHITE,Show8X16);   // �����Ͻ���ʾ��ɫ������ɫ��8X16���֡�521��
*
**/
void Show_Int_IPS (unsigned short x, unsigned short y, const int data, unsigned char num, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize)
{
    char buff[6]={' ',' ',' ',' ',' ',' '};
    int_to_str_func(buff,data);
    Show_String_IPS(x, y, (char *)&buff, fc, bc, fontsize);
}

/**
*
* @brief    IPS��Ļ��ʾFloat�ͱ���
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    data                Ҫ��ʾ��Float�ͱ���
* @param    num                 Ҫ��ʾ��Float�ͱ�������λ��
* @param    pointnum            Ҫ��ʾ��Float�ͱ���С����λ��
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    fontsize            ����ߴ�(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Show_Float_IPS(0,0,521.22,3,2,BLACK,WHITE,Show8X16);    // �����Ͻ���ʾ��ɫ������ɫ��8X16���֡�521.22��
*
**/
void Show_Float_IPS (unsigned short x, unsigned short y, const float data, unsigned char num, unsigned char pointnum, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize)
{
    char buff[10];
    unsigned char i,j;

    sprintf(buff, "%f", data);
    while(buff[i] != '.')
        i++;
    for(j = i + pointnum + 1;j<9;j++)
        buff[j] = ' ';
    if(data<0)
        buff[9] = '\0';
    else
        buff[8] = '\0';
    Show_String_IPS(x, y, buff, fc, bc, fontsize);
}

/**
*
* @brief    IPS��Ļ��ʾ����
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    data                Ҫ��ʾ�ĺ�����������
* @param    startnumber         ��startnumber�����ֿ�ʼ
* @param    number              ��number�����ֽ���
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    size                16
* @return   void
* @notes    ʹ��PCtoLCD2002���ȡģ,����,����ʽ,˳��,16*16
* Example:  Show_Chinese16x16_IPS(0,0,IPSChinese16x16[0],0,3,BLACK,WHITE,16);   // �����Ͻ���ʾIPSChinese16x16�����еĵ�0~3�����ּ�����������
*
**/
void Show_Chinese16x16_IPS(unsigned int x, unsigned int y, const unsigned char *data, unsigned char startnumber,unsigned char number,COLOR_enum fc,COLOR_enum bc, unsigned char size)
{
    int i, j, k;
    const unsigned char *pdata;
    unsigned char temp;

    IPS_CS_LEVEL(0);
    Set_Pos_IPS(x, y, (number-startnumber) * size - 1 + x, y + size - 1);

    for(i = 0; i < size; i ++)
    {
        temp = number;
        pdata = data+startnumber*32 + i * (size / 8);
        for(;temp>startnumber;temp--)
        {
            for(k = 0; k < (size / 8); k ++)
            {
                for(j = 8; j > 0; j --)
                {
                    if((*pdata >> (j - 1)) & 0x01)
                    {
                        Write_16bit_IPS(fc);
                    }
                    else
                    {
                        Write_16bit_IPS(bc);
                    }
                }
                pdata ++;
            }
            pdata = pdata - (size / 8) + (size / 8) * size;
        }
    }
    IPS_CS_LEVEL(1);
}

/**
*
* @brief    IPS��Ļ��ʾ��ɫͼƬ
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    width               ͼƬ���
* @param    heigh               ͼƬ�߶�
* @param    pic                 ͼƬ����
* @return   void
* @notes
* Example:  Show_Picture_IPS(60,7,121,121,IPSEarth121x121); // ����Ļ�м���ʾ����ͼƬ
*
**/
void Show_Picture_IPS(unsigned int x, unsigned int y, unsigned int width, unsigned int heigh, const unsigned char pic[])
{
    unsigned int i, j;
    unsigned long k = 0;
    Set_Pos_IPS(x, y, x + width - 1, y + heigh - 1);
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < heigh; j++)
        {
            Write_8bit_IPS(pic[k * 2]);
            Write_8bit_IPS(pic[k * 2 + 1]);
            k++;
        }
    }
}

/**
*
* @brief    IPS��Ļ��ʾ����ͷ�Ҷ�ͼ��
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    image               ͼ������
* @param    width               ͼ������ʵ�ʿ��
* @param    heigh               ͼ������ʵ�ʸ߶�
* @param    show_width          ͼ��������ʾ���
* @param    show_height         ͼ��������ʾ�߶�
* @param    threshold           Ϊ0ʱ�رն�ֵ��
* @return   void
* @notes
* Example:  Show_Image_IPS(0,0,OriginalImageData[0],188,120,188,135,0);
*
**/
void Show_Image_IPS(unsigned short x, unsigned short y, unsigned char *image, unsigned short width, unsigned short height, unsigned short show_width, unsigned short show_height, unsigned char threshold)
{
    unsigned int i, j;
    unsigned short color,temp;
    unsigned int width_ratio, height_ratio;

    Set_Pos_IPS(x, y, x + show_width - 1, y + show_height - 1);

    for(i = 0; i < show_height; i ++)
    {
        height_ratio = i * height / show_height;
        for(j = 0; j < show_width; j ++)
        {
            width_ratio = j * width / show_width;
            temp = *(image + height_ratio * width + width_ratio);

            if(threshold == 0)
            {
                color = (0x001f & ((temp) >> 3)) << 11;
                color = color | (((0x003f) & ((temp) >> 2)) << 5);
                color = color | (0x001f & ((temp) >> 3));
                Write_16bit_IPS(color);
            }
            else if(temp < threshold)
            {
                Write_16bit_IPS(BLACK);
            }
            else
            {
                Write_16bit_IPS(WHITE);
            }

        }
    }
}

/**
*
* @brief    IPS��Ļ��ʾ����ͷ��ֵ��ͼ��
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    image               ͼ������
* @param    width               ͼ������ʵ�ʿ��
* @param    heigh               ͼ������ʵ�ʸ߶�
* @param    show_width          ͼ��������ʾ���
* @param    show_height         ͼ��������ʾ�߶�
* @return   void
* @notes
* Example:  Show_Image_Binary_IPS(0,0,Deal_Image_Binary[0],80,60,160,120);
*
**/
void Show_Image_Binary_IPS(unsigned short x, unsigned short y, unsigned char *image, unsigned short width, unsigned short height, unsigned short show_width, unsigned short show_height)
{
    unsigned int i, j;
    unsigned short temp;
    unsigned int width_ratio, height_ratio;

    Set_Pos_IPS(x, y, x + show_width - 1, y + show_height - 1);

    for(i = 0; i < show_height; i ++)
    {
        height_ratio = i * height / show_height;
        for(j = 0; j < show_width; j ++)
        {
            width_ratio = j * width / show_width;
            temp = *(image + height_ratio * width + width_ratio);

            switch(temp)
            {
                case 0:Write_16bit_IPS(BLACK);break;
                case 1:Write_16bit_IPS(WHITE);break;
                case 2:Write_16bit_IPS(BLUE);break;
                case 3:Write_16bit_IPS(RED);break;
                case 4:Write_16bit_IPS(GREEN);break;
            }
        }
    }
}

/**
*
* @brief    IPS��Ļд����
* @param    cmd             ����
* @return   void
* @notes    IPS.c�ļ��ڲ�����,�û�������ó���
* Example:  Write_Cmd_IPS(0x21);
*
**/
static void Write_Cmd_IPS(unsigned char cmd)
{
    IPS_DC_LEVEL(0);
    IPS_Write_8bitData(cmd);
}

/**
*
* @brief    IPS��Ļд8bit����
* @param    data            8bit����
* @return   void
* @notes    IPS.c�ļ��ڲ�����,�û�������ó���
* Example:  Write_8bit_IPS(0x23);
*
**/
static void Write_8bit_IPS(unsigned char data)
{
    IPS_DC_LEVEL(1);
    IPS_Write_8bitData(data);
}

/**
*
* @brief    IPS��Ļд16bit����
* @param    data                16bit����
* @return   void
* @notes    IPS.c�ļ��ڲ�����,�û�������ó���
* Example:  Write_16bit_IPS(0x0000);
*
**/
static void Write_16bit_IPS(unsigned short data)
{
    IPS_DC_LEVEL(1);
    IPS_Write_16bitData(data);
}

