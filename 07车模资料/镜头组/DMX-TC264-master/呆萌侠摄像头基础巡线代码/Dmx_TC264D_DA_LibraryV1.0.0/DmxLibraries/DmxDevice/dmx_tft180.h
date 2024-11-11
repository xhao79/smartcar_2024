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
 * @file       dmx_tft180.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_TFT18_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_TFT18_H_

#include "dmx_font.h"

// ͨ�ŷ�ʽѡ��,0:���SPI,1:Ӳ��SPI
#define TFT_HARD_SPI        1
// ������Ļ��ʾ����,0:����,1:����180��,2:����,3:����180��
#define TFT18_SHOW_DIR      3
// ����TFT��Ļ���,����ģʽ�¿��Ϊ128x160,����ģʽ�¿��Ϊ160x128
#define TFT18_WIDTH         160 // ����ģʽ�¿�Ϊ128,����ģʽ�¿�Ϊ160
#define TFT18_HEIGH         128 // ����ģʽ�¸�Ϊ160,����ģʽ�¸�Ϊ128

//TFT��Ļ�ܽź궨��
#if TFT_HARD_SPI
#define TFT_SPI_SPEED                   (30*1000*1000)      // Ӳ��SPI����
#define TFT_SPI                         (SPI_2)             // Ӳ��SPI��
#define TFT_SCL_PIN                     (SPI2_CLK_P15_3)    // Ӳ��SPI_SCK����
#define TFT_SDA_PIN                     (SPI2_MOSI_P15_5)   // Ӳ��SPI_MOSI ����
#define TFT_SDA_IN_PIN                  (SPI2_MISO_P15_4)   // ����SPI_MISO����
#else
// TFT,SCL�ܽŶ�ӦTC264����P15_3
#define TFT_SCL_MODULE  P15
#define TFT_SCL_PIN     3
// TFT,SDA�ܽŶ�ӦTC264����P15_5
#define TFT_SDA_MODULE  P15
#define TFT_SDA_PIN     5
#endif
// TFT,RES�ܽŶ�ӦTC264����P15_1
#define TFT_RES_MODULE  P15
#define TFT_RES_PIN     1
// TFT,DC�ܽŶ�ӦTC264����P15_0
#define TFT_DC_MODULE   P15
#define TFT_DC_PIN      0
// TFT,CS�ܽŶ�ӦTC264����P15_2
#define TFT_CS_MODULE   P15
#define TFT_CS_PIN      2

// ��TFT��Ļ�ܽŽ��иߵ͵�ƽ����
#define TFT_RES_LEVEL(level)    set_level_gpio(TFT_RES_MODULE ,TFT_RES_PIN , level);
#define TFT_DC_LEVEL(level)     set_level_gpio(TFT_DC_MODULE  ,TFT_DC_PIN  , level);
#define TFT_CS_LEVEL(level)     set_level_gpio(TFT_CS_MODULE  ,TFT_CS_PIN  , level);

/**
*
* @brief    TFT180��Ļ��ʼ��
* @param    void
* @return   void
* @notes    �޸ĹܽŶ������dmx_tft180.h�ļ���ĺ궨��ܽŽ����޸�
* Example:  IPS_Init();
*
**/
void TFT18_Init(void);

/**
*
* @brief    TFT��Ļ������ʼ�ͽ�������
* @param    x1                x������ʼ��
* @param    y1                y������ʼ��
* @param    x2                x���������
* @param    y2                y���������
* @return   void
* @notes
* Example:  Set_Pos_TFT18(0,0,0,0);
*
**/
void Set_Pos_TFT18(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

/**
*
* @brief    TFT��Ļ��ָ��λ�û���
* @param    x                   x��������
* @param    y                   y��������
* @param    color               �����ɫ(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Draw_Point_TFT(0,0,0,0);
*
**/
void Draw_Point_TFT(unsigned int x, unsigned int y, COLOR_enum color);

/**
*
* @brief    TFT��Ļ���ָ������
* @param    x1                  x������ʼ��
* @param    y1                  y������ʼ��
* @param    x2                  x���������
* @param    y2                  y���������
* @param    color               �����ɫ(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Fill_TFT18(0,0,128,160,WHITE);  // IPS114��Ļȫ��
*
**/
void Fill_TFT18(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, COLOR_enum color);

/**
*
* @brief    TFT��Ļ����
* @param    color               �����ɫ(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Clean_TFT(WHITE);   // TFT18��Ļȫ��
*
**/
void Clean_TFT(COLOR_enum color);

/**
*
* @brief    TFT��Ļ��ʾ�����ַ�
* @param    x                   x��������
* @param    y                   y��������
* @param    data                �ַ�
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    fontsize            ����ߴ�(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Show_Char_TFT18(0,0,'D',BLACK,WHITE,Show8X16);  // �����Ͻ���ʾ��ɫ������ɫ��8X16�ַ�'D'
*
**/
void Show_Char_TFT18(unsigned int x, unsigned int y, unsigned char data, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

/**
*
* @brief    TFT��Ļ��ʾ�ַ���
* @param    x                   x��������
* @param    y                   y��������
* @param    *p                  Ҫ��ʾ���ַ���
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    fontsize            ����ߴ�(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Show_String_TFT18(0,0,"DMX",BLACK,WHITE,Show8X16);  // �����Ͻ���ʾ��ɫ������ɫ��8X16�ַ���'DMX'
*
**/
void Show_String_TFT18(unsigned int x, unsigned int y, char *p, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

/**
*
* @brief    TFT��Ļ��ʾInt�ͱ���
* @param    x                   x��������
* @param    y                   y��������
* @param    data                Ҫ��ʾ��Int�ͱ���
* @param    num                 Ҫ��ʾ��Int�ͱ���λ��
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    fontsize            ����ߴ�(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Show_Int_TFT18(0,0,521,3,BLACK,WHITE,Show8X16);     // �����Ͻ���ʾ��ɫ������ɫ��8X16���֡�521��
*
**/
void Show_Int_TFT18 (unsigned short x, unsigned short y, const int data, unsigned char num, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

/**
*
* @brief    TFT��Ļ��ʾFloat�ͱ���
* @param    x                   x��������
* @param    y                   y��������
* @param    data                Ҫ��ʾ��Float�ͱ���
* @param    num                 Ҫ��ʾ��Float�ͱ�������λ��
* @param    pointnum            Ҫ��ʾ��Float�ͱ���С����λ��
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    fontsize            ����ߴ�(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Show_Float_TFT18(0,0,521.22,3,2,BLACK,WHITE,Show8X16); //�����Ͻ���ʾ��ɫ������ɫ��8X16���֡�521.22��
*
**/
void Show_Float_TFT18 (unsigned short x, unsigned short y, const float data, unsigned char num, unsigned char pointnum, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

/**
*
* @brief    TFT��Ļ��ʾ����
* @param    x                   x��������
* @param    y                   y��������
* @param    data                Ҫ��ʾ�ĺ�����������
* @param    startnumber         ��startnumber�����ֿ�ʼ
* @param    number              ��number�����ֽ���
* @param    fc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    bc                  ������ɫ(����dmx_font.h�ļ���鿴)
* @param    size                16
* @return   void
* @notes    ʹ��PCtoLCD2002���ȡģ,����,����ʽ,˳��,16*16
* Example:  Show_Chinese16x16_TFT(0,0,Chinese16x16[0],0,3,BLACK,WHITE,16);    //�����Ͻ���ʾChinese16x16�����еĵ�0~3�����ּ�����������
*
**/
void Show_Chinese16x16_TFT(unsigned int x, unsigned int y, const unsigned char *data, unsigned char startnumber,unsigned char number,COLOR_enum word_color,COLOR_enum back_color, unsigned char size);

/**
*
* @brief    TFT��Ļ��ʾ��ɫͼƬ
* @param    x                   x��������
* @param    y                   y��������
* @param    width               ͼƬ���
* @param    heigh               ͼƬ�߶�
* @param    pic                 ͼƬ����
* @return   void
* @notes
* Example:  Show_Picture_TFT(3,19,121,121,Earth121x121);     // ����Ļ�м���ʾ����ͼƬ
*
**/
void Show_Picture_TFT(unsigned int x, unsigned int y, unsigned int width, unsigned int heigh, const unsigned char pic[]);

/**
*
* @brief    TFT��Ļ��ʾ����ͷ�Ҷ�ͼ��
* @param    x                   x��������
* @param    y                   y��������
* @param    image               ͼ������
* @param    width               ͼ������ʵ�ʿ��
* @param    heigh               ͼ������ʵ�ʸ߶�
* @param    show_width          ͼ��������ʾ���
* @param    show_height         ͼ��������ʾ�߶�
* @param    threshold           ��ֵ����ֵΪ0ʱ�رն�ֵ��
* @return   void
* @notes
* Example:  Show_Image_TFT(0,0,OriginalImageData[0],188,120,188,120,0); // ��Ļ��ʾ����ͷ�Ҷ�ͼ��
*
**/
void Show_Image_TFT(unsigned short x, unsigned short y, unsigned char *image, unsigned short width, unsigned short height, unsigned short show_width, unsigned short show_height, unsigned char threshold);

/**
*
* @brief    TFT��Ļд����
* @param    com             ����
* @return   void
* @notes
* Example:  Write_Cmd_TFT18(0x21);
*
**/
static void Write_Cmd_TFT18(unsigned char cmd);

/**
*
* @brief    TFT��Ļд8bit����
* @param    data                8bit����
* @return   void
* @notes
* Example:  Write_8bit_TFT18(0x23);
*
**/
static void Write_8bit_TFT18(unsigned char data);

/**
*
* @brief    TFT��Ļд16bit����
* @param    data                16bit����
* @return   void
* @notes
* Example:  Write_16bit_TFT18(0x0000);
*
**/
static void Write_16bit_TFT18(unsigned short data);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_TFT18_H_ */
