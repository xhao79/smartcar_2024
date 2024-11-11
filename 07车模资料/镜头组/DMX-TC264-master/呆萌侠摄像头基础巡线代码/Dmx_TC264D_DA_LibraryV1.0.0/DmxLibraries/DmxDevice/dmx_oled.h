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
 * @file       dmx_oled.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_OLED_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_OLED_H_

#include "dmx_font.h"

// ͨ�ŷ�ʽѡ��,0:���SPI,1:Ӳ��SPI
#define OLED_HARD_SPI       1

// ��OLED��Ļ�����������
#define OLED_WIDTH          128
#define OLED_HEIGH          64

// OLED��Ļ�ܽź궨��
#if OLED_HARD_SPI
#define OLED_SPI_SPEED              (60*1000*1000)                          // Ӳ�� SPI ����
#define OLED_SPI                    (SPI_2)                                 // Ӳ�� SPI ��
#define OLED_SCL_PIN                (SPI2_CLK_P15_3)                        // Ӳ�� SPI SCK ����
#define OLED_SDA_PIN                (SPI2_MOSI_P15_5)                       // Ӳ�� SPI MOSI ����
#define OLED_SDA_IN_PIN             (SPI2_MISO_P15_4)                       // ����SPI_MISO����  IPSû��MISO���ţ�����������Ȼ��Ҫ���壬��spi�ĳ�ʼ��ʱ��Ҫʹ��
#else
// OLED,CK�ܽŶ�ӦTC264����P15_3
#define OLED_D0_MODULE  P15
#define OLED_D0_PIN     3
// OLED,DI�ܽŶ�ӦTC264����P15_5
#define OLED_D1_MODULE  P15
#define OLED_D1_PIN     5
#endif
// OLED,RST�ܽŶ�ӦTC264����P15_1
#define OLED_RES_MODULE P15
#define OLED_RES_PIN    1
// OLED,DC�ܽŶ�ӦTC264����P15_0
#define OLED_DC_MODULE  P15
#define OLED_DC_PIN     0
// OLED,CS�ܽŶ�ӦTC264����P15_2
#define OLED_CS_MODULE  P15
#define OLED_CS_PIN     2

// ��OLED��Ļ�ܽŽ��иߵ͵�ƽ����
#define OLED_D0_LEVEL(level)  set_level_gpio(OLED_D0_MODULE ,OLED_D0_PIN , level);
#define OLED_D1_LEVEL(level)  set_level_gpio(OLED_D1_MODULE ,OLED_D1_PIN , level);
#define OLED_RES_LEVEL(level) set_level_gpio(OLED_RES_MODULE ,OLED_RES_PIN , level);
#define OLED_DC_LEVEL(level)  set_level_gpio(OLED_DC_MODULE ,OLED_DC_PIN , level);
#define OLED_CS_LEVEL(level)  set_level_gpio(OLED_CS_MODULE ,OLED_CS_PIN , level);

#define _nop_   __asm("NOP");
#define OLED_Delay10ms(count) Delay_ms(STM0,count*10);

/**
*
* @brief    0.96��6��OLED��Ļ��ʼ��
* @param    void
* @return   void
* @notes    �޸ĹܽŶ������dmx_oled.h�ļ���ĺ궨��ܽŽ����޸�
* Example:  Init_OLED();
*
**/
void Init_OLED(void);

/**
*
* @brief    0.96��6��OLED��Ļ����
* @param    data
* @return   void
* @notes
* Example:  Draw_Point_OLED(0xff);
*
**/
void Draw_Point_OLED(unsigned char data);

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
void Set_Pos_OLED(unsigned char x, unsigned char y);

/**
*
* @brief    0.96��6��OLED��Ļ����
* @param
* @return   void
* @notes
* Example:  Fill_OLED();
*
**/
void Fill_OLED(void);

/**
*
* @brief    0.96��6��OLED��Ļ����
* @param
* @return   void
* @notes    ִ�к�Ч����ȫ��,����
* Example:  Clean_OLED();
*
**/
void Clean_OLED(void);

/**
*
* @brief    0.96��6��OLED��Ļ��ʾ�ַ���
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @param    biglow      ö���ַ���ʾ��С
* @param    str         ��Ҫ��ʾ���ַ���
* @return   void
* @notes
* Example:  Show_String_OLED(0,0,"123",OLED8X16);   // ����Ļ���Ͻ���ʾ8X16��С�ġ�123��
*
**/
void Show_String_OLED(unsigned char x,unsigned char y,char str[],SHOW_size_enum fontsize);

/**
*
* @brief    0.96��6��OLED��Ļ��ʾInt������
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @param    biglow      ö���ַ���ʾ��С
* @param    num         ��Ҫ��ʾ������
* @return   void
* @notes
* Example:  Show_Int_OLED(0,0,a,OLED8X16);      // ����Ļ���Ͻ���ʾ8X16��С��a����������
*
**/
void Show_Int_OLED(char x,char y,int num,SHOW_size_enum fontsize);

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
* Example:  Show_Float_OLED(64,0,3.1415926,3,OLED8X16);     // ����Ļ���Ͻ���ʾ8X16��С�ġ�3.142��
*
**/
void Show_Float_OLED(char x,char y,float num,unsigned char point,SHOW_size_enum biglow);

/**
*
* @brief    0.96��6��OLED��Ļ��ʾInt������
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @param    chinese     ����������׵�ַ
* @param    startnum    ��ʼ��ʾ�ĺ���λ��
* @param    endnum      ������ʾ�ĺ���λ��
* @return   void
* @notes    ���ȡģ�ڶ��庺���ֿ�ʱ��˵��
* Example:  Show_Chinese16x16_OLED(0,0,Chinese16x16,0,3);       // ����Ļ���Ͻ���ʾ16X16��С�ĺ��֡���������
*
**/
void Show_Chinese16x16_OLED(char x,char y,const unsigned char *chinese,char startnum,char endnum);

/**
*
* @brief    0.96��6��OLED��Ļ��ʾBMPͼƬ
* @param    x           x����������(0~127)
* @param    y           y����������(0~7)
* @param    wide        ͼƬʵ�����ؿ��(1~127)
* @param    high        ͼƬʵ�����ظ߶�(1~64)
* @param    bmp         ͼƬ�����׵�ַ
* @return   void
* @notes    ͼƬ�������Ϊ128��64,���ȡģ�ڶ���ͼƬ����ʱ��˵��
* Example:  Show_BMP_OLED(0,0,Chinese16x16,0,3);    // ����Ļ���Ͻ���ʾ16X16��С�ĺ��֡���������
*
**/
void Show_BMP_OLED(unsigned char x,unsigned char y,unsigned char wide,unsigned char high,const unsigned char * bmp);

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
void Show_Image_Oled (unsigned short x, unsigned short y, const unsigned char *image, unsigned short width, unsigned short height, unsigned short show_width, unsigned short show_height, unsigned char threshold);

/**
*
* @brief    0.96��6��OLED��Ļд����
* @param    cmd         ����
* @return   void
* @notes    �ڲ�����
* Example:  OLED_WrByte(0xff);
*
**/
static void Write_Data_OLED(unsigned char cmd);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_OLED_H_ */
