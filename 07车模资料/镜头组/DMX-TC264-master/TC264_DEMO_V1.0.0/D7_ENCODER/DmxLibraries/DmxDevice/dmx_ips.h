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
 * @file       dmx_ips.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_IPS_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_IPS_H_

#include "dmx_font.h"

// ͨ�ŷ�ʽѡ��,0:���SPI,1:Ӳ��SPI
#define IPS_HARD_SPI    1
// ��Ļ�ͺ�ѡ��,0:IPS114,1:IPS130,2:IPS154,3:IPS200
#define IPS_MODEL       0
// ������Ļ��ʾ����,0:����,1:����180��,2:����,3:����180��
#define IPS_SHOW_DIR    2

// IPS��Ļ�ܽź궨��
#if IPS_HARD_SPI
#define IPS114_SPI_SPEED                (60*1000*1000)                          // Ӳ�� SPI ����
#define IPS_SPI                         (SPI_2)                                 // Ӳ�� SPI ��
#define IPS114_SCL_PIN                  (SPI2_CLK_P15_3)                        // Ӳ�� SPI SCK ����
#define IPS114_SDA_PIN                  (SPI2_MOSI_P15_5)                       // Ӳ�� SPI MOSI ����
#define IPS114_SDA_IN_PIN               (SPI2_MISO_P15_4)                       // ����SPI_MISO����  IPSû��MISO���ţ�����������Ȼ��Ҫ���壬��spi�ĳ�ʼ��ʱ��Ҫʹ��
#else
// IPS,SCL�ܽŶ�ӦTC264����P15_3
#define IPS_SCL_MODULE  P15
#define IPS_SCL_PIN     3
// IPS,SDA�ܽŶ�ӦTC264����P15_5
#define IPS_SDA_MODULE  P15
#define IPS_SDA_PIN     5
#endif
// IPS,RES�ܽŶ�ӦTC264����P15_1
#define IPS_RES_MODULE  P15
#define IPS_RES_PIN     1
// IPS,DC�ܽŶ�ӦTC264����P15_0
#define IPS_DC_MODULE   P15
#define IPS_DC_PIN      0
// IPS,CS�ܽŶ�ӦTC264����P15_2
#define IPS_CS_MODULE   P15
#define IPS_CS_PIN      2
// IPS,BLK�ܽŶ�ӦTC264����P15_4
#define IPS_BLK_MODULE  P15
#define IPS_BLK_PIN     4

// ��IPS��Ļ�ܽŽ��иߵ͵�ƽ����
#define IPS_RES_LEVEL(level)    set_level_gpio(IPS_RES_MODULE,IPS_RES_PIN,level);
#define IPS_DC_LEVEL(level)     set_level_gpio(IPS_DC_MODULE ,IPS_DC_PIN ,level);
#define IPS_CS_LEVEL(level)     set_level_gpio(IPS_CS_MODULE ,IPS_CS_PIN ,level);
#define IPS_BLK_LEVEL(level)    set_level_gpio(IPS_BLK_MODULE,IPS_BLK_PIN,level);

/**
*
* @brief    ��ʼ��IPS��Ļ
* @param    void
* @return   void
* @notes    �޸ĹܽŶ������dmx_ips.h�ļ���ĺ궨��ܽŽ����޸�
* Example:  Init_IPS();
*
**/
void Init_IPS(void);

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
void Set_Pos_IPS(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

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
void Draw_Point_IPS(unsigned int x, unsigned int y, COLOR_enum color);

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
void Fill_IPS(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, COLOR_enum color);

/**
*
* @brief    IPS��Ļ����
* @param    color               �����ɫ(����dmx_font.h�ļ���鿴)
* @return   void
* @notes
* Example:  Clean_IPS(WHITE);   // IPS114��Ļȫ��
*
**/
void Clean_IPS(COLOR_enum color);

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
void Show_Char_IPS(unsigned int x, unsigned int y, unsigned char data, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

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
void Show_String_IPS(unsigned int x, unsigned int y, char *p, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

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
void Show_Int_IPS (unsigned short x, unsigned short y, const int data, unsigned char num, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

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
void Show_Float_IPS (unsigned short x, unsigned short y, const float data, unsigned char num, unsigned char pointnum, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

/**
*
* @brief    IPS��Ļ��ʾ����
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    data                Ҫ��ʾ�ĺ�����������
* @param    startnumber         ��startnumber�����ֿ�ʼ
* @param    number              ��number�����ֽ���
* @param    fc                  ������ɫ(����Dmx_FONT.h�ļ���鿴)
* @param    bc                  ������ɫ(����Dmx_FONT.h�ļ���鿴)
* @param    size                16
* @return   void
* @notes    ʹ��PCtoLCD2002���ȡģ,����,����ʽ,˳��,16*16
* Example:  Show_Chinese16x16_IPS(0,0,IPSChinese16x16[0],0,3,BLACK,WHITE,16);   // �����Ͻ���ʾIPSChinese16x16�����еĵ�0~3�����ּ�����������
*
**/
void Show_Chinese16x16_IPS(unsigned int x, unsigned int y,  const unsigned char *data, unsigned char startnumber,unsigned char number,COLOR_enum word_color,COLOR_enum back_color, unsigned char size);

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
void Show_Picture_IPS(unsigned int x, unsigned int y, unsigned int width, unsigned int heigh, const unsigned char pic[]);

/**
*
* @brief    IPS��Ļ��ʾ����ͷ�Ҷ�ͼ��
* @param    x                   x��������(0~240)
* @param    y                   y��������(0~135)
* @param    image               ͼ������
* @param    width               ͼ������ʵ�ʿ��
* @param    heigh               ͼ������ʵ�ʸ߶�
* @param    dis_width           ͼ��������ʾ���
* @param    dis_height          ͼ��������ʾ�߶�
* @param    threshold           Ϊ0ʱ�رն�ֵ��
* @return   void
* @notes
* Example:  Show_Image_IPS(0,0,OriginalImageData[0],188,120,188,135,0);
*
**/
void Show_Image_IPS(unsigned short x, unsigned short y, unsigned char *image, unsigned short width, unsigned short height, unsigned short show_width, unsigned short show_height, unsigned char threshold);

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
 void Show_Image_Binary_IPS(unsigned short x, unsigned short y, unsigned char *image, unsigned short width, unsigned short height, unsigned short show_width, unsigned short show_height);

/**
*
* @brief    IPS��Ļд����
* @param    command         ����
* @return   void
* @notes    IPS.c�ļ��ڲ�����,�û�������ó���
* Example:  Write_Cmd_IPS(0x21);
*
**/
static void Write_Cmd_IPS(unsigned char cmd);

/**
*
* @brief    IPS��Ļд8bit����
* @param    data                8bit����
* @return   void
* @notes    IPS.c�ļ��ڲ�����,�û�������ó���
* Example:  Write_8bit_IPS(0x23);
*
**/
static void Write_8bit_IPS(unsigned char data);

/**
*
* @brief    IPS��Ļд16bit����
* @param    data                16bit����
* @return   void
* @notes    IPS.c�ļ��ڲ�����,�û�������ó���
* Example:  Write_16bit_IPS(0x0000);
*
**/
static void Write_16bit_IPS(unsigned short data);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_IPS_H_ */
