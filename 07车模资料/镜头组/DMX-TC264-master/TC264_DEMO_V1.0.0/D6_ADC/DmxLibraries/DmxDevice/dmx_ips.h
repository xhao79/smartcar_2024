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
 * @file       dmx_ips.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_IPS_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_IPS_H_

#include "dmx_font.h"

// 通信方式选择,0:软件SPI,1:硬件SPI
#define IPS_HARD_SPI    1
// 屏幕型号选择,0:IPS114,1:IPS130,2:IPS154,3:IPS200
#define IPS_MODEL       0
// 设置屏幕显示方向,0:竖屏,1:竖屏180度,2:横屏,3:横屏180度
#define IPS_SHOW_DIR    2

// IPS屏幕管脚宏定义
#if IPS_HARD_SPI
#define IPS114_SPI_SPEED                (60*1000*1000)                          // 硬件 SPI 速率
#define IPS_SPI                         (SPI_2)                                 // 硬件 SPI 号
#define IPS114_SCL_PIN                  (SPI2_CLK_P15_3)                        // 硬件 SPI SCK 引脚
#define IPS114_SDA_PIN                  (SPI2_MOSI_P15_5)                       // 硬件 SPI MOSI 引脚
#define IPS114_SDA_IN_PIN               (SPI2_MISO_P15_4)                       // 定义SPI_MISO引脚  IPS没有MISO引脚，但是这里任然需要定义，在spi的初始化时需要使用
#else
// IPS,SCL管脚对应TC264引脚P15_3
#define IPS_SCL_MODULE  P15
#define IPS_SCL_PIN     3
// IPS,SDA管脚对应TC264引脚P15_5
#define IPS_SDA_MODULE  P15
#define IPS_SDA_PIN     5
#endif
// IPS,RES管脚对应TC264引脚P15_1
#define IPS_RES_MODULE  P15
#define IPS_RES_PIN     1
// IPS,DC管脚对应TC264引脚P15_0
#define IPS_DC_MODULE   P15
#define IPS_DC_PIN      0
// IPS,CS管脚对应TC264引脚P15_2
#define IPS_CS_MODULE   P15
#define IPS_CS_PIN      2
// IPS,BLK管脚对应TC264引脚P15_4
#define IPS_BLK_MODULE  P15
#define IPS_BLK_PIN     4

// 对IPS屏幕管脚进行高低电平操作
#define IPS_RES_LEVEL(level)    set_level_gpio(IPS_RES_MODULE,IPS_RES_PIN,level);
#define IPS_DC_LEVEL(level)     set_level_gpio(IPS_DC_MODULE ,IPS_DC_PIN ,level);
#define IPS_CS_LEVEL(level)     set_level_gpio(IPS_CS_MODULE ,IPS_CS_PIN ,level);
#define IPS_BLK_LEVEL(level)    set_level_gpio(IPS_BLK_MODULE,IPS_BLK_PIN,level);

/**
*
* @brief    初始化IPS屏幕
* @param    void
* @return   void
* @notes    修改管脚定义可在dmx_ips.h文件里的宏定义管脚进行修改
* Example:  Init_IPS();
*
**/
void Init_IPS(void);

/**
*
* @brief    IPS屏幕设置起始和结束坐标
* @param    x1                x方向起始点(0~240)
* @param    y1                y方向起始点(0~135)
* @param    x2                x方向结束点(0~240)
* @param    y2                y方向结束点(0~135)
* @return   void
* @notes
* Example:  Set_Pos_IPS(0,0,0,0);
*
**/
void Set_Pos_IPS(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

/**
*
* @brief    IPS屏幕在指定位置画点
* @param    x                   x方向坐标(0~240)
* @param    y                   y方向坐标(0~135)
* @param    color               点的颜色(可在dmx_font.h文件里查看)
* @return   void
* @notes
* Example:  Draw_Point_IPS(0,0,BLACK);
*
**/
void Draw_Point_IPS(unsigned int x, unsigned int y, COLOR_enum color);

/**
*
* @brief    IPS屏幕填充指定区域
* @param    x1                  x方向起始点(0~240)
* @param    y1                  y方向起始点(0~135)
* @param    x2                  x方向结束点(0~240)
* @param    y2                  y方向结束点(0~135)
* @param    color               填充颜色(可在dmx_font.h文件里查看)
* @return   void
* @notes
* Example:  Fill_IPS(0,0,240,135,WHITE);    // IPS114屏幕全白
*
**/
void Fill_IPS(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, COLOR_enum color);

/**
*
* @brief    IPS屏幕清屏
* @param    color               填充颜色(可在dmx_font.h文件里查看)
* @return   void
* @notes
* Example:  Clean_IPS(WHITE);   // IPS114屏幕全白
*
**/
void Clean_IPS(COLOR_enum color);

/**
*
* @brief    IPS屏幕显示单个字符
* @param    x                   x方向坐标(0~240)
* @param    y                   y方向坐标(0~135)
* @param    data                字符
* @param    fc                  字体颜色(可在dmx_font.h文件里查看)
* @param    bc                  背景颜色(可在dmx_font.h文件里查看)
* @param    fontsize            字体尺寸(可在dmx_font.h文件里查看)
* @return   void
* @notes
* Example:  Show_Char_IPS(0,0,'D',BLACK,WHITE,Show8X16);    // 在左上角显示白色背景黑色的8X16字符'D'
*
**/
void Show_Char_IPS(unsigned int x, unsigned int y, unsigned char data, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

/**
*
* @brief    IPS屏幕显示字符串
* @param    x                   x方向坐标(0~240)
* @param    y                   y方向坐标(0~135)
* @param    *p                  要显示的字符串
* @param    fc                  字体颜色(可在dmx_font.h文件里查看)
* @param    bc                  背景颜色(可在dmx_font.h文件里查看)
* @param    fontsize            字体尺寸(可在dmx_font.h文件里查看)
* @return   void
* @notes
* Example:  Show_String_IPS(0,0,"DMX",BLACK,WHITE,Show8X16);    // 在左上角显示白色背景黑色的8X16字符串'DMX'
*
**/
void Show_String_IPS(unsigned int x, unsigned int y, char *p, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

/**
*
* @brief    IPS屏幕显示Int型变量
* @param    x                   x方向坐标(0~240)
* @param    y                   y方向坐标(0~135)
* @param    data                要显示的Int型变量
* @param    num                 要显示的Int型变量位数
* @param    fc                  字体颜色(可在dmx_font.h文件里查看)
* @param    bc                  背景颜色(可在dmx_font.h文件里查看)
* @param    fontsize            字体尺寸(可在dmx_font.h文件里查看)
* @return   void
* @notes
* Example:  Show_Int_IPS(0,0,521,3,BLACK,WHITE,Show8X16);   // 在左上角显示白色背景黑色的8X16数字“521”
*
**/
void Show_Int_IPS (unsigned short x, unsigned short y, const int data, unsigned char num, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

/**
*
* @brief    IPS屏幕显示Float型变量
* @param    x                   x方向坐标(0~240)
* @param    y                   y方向坐标(0~135)
* @param    data                要显示的Float型变量
* @param    num                 要显示的Float型变量整数位数
* @param    pointnum            要显示的Float型变量小数点位数
* @param    fc                  字体颜色(可在dmx_font.h文件里查看)
* @param    bc                  背景颜色(可在dmx_font.h文件里查看)
* @param    fontsize            字体尺寸(可在dmx_font.h文件里查看)
* @return   void
* @notes
* Example:  Show_Float_IPS(0,0,521.22,3,2,BLACK,WHITE,Show8X16);    // 在左上角显示白色背景黑色的8X16数字“521.22”
*
**/
void Show_Float_IPS (unsigned short x, unsigned short y, const float data, unsigned char num, unsigned char pointnum, COLOR_enum fc, COLOR_enum bc, SHOW_size_enum fontsize);

/**
*
* @brief    IPS屏幕显示汉字
* @param    x                   x方向坐标(0~240)
* @param    y                   y方向坐标(0~135)
* @param    data                要显示的汉字所在数组
* @param    startnumber         第startnumber个汉字开始
* @param    number              第number个汉字结束
* @param    fc                  字体颜色(可在Dmx_FONT.h文件里查看)
* @param    bc                  背景颜色(可在Dmx_FONT.h文件里查看)
* @param    size                16
* @return   void
* @notes    使用PCtoLCD2002软件取模,阴码,逐行式,顺向,16*16
* Example:  Show_Chinese16x16_IPS(0,0,IPSChinese16x16[0],0,3,BLACK,WHITE,16);   // 在左上角显示IPSChinese16x16数组中的第0~3个汉字即“呆萌侠”
*
**/
void Show_Chinese16x16_IPS(unsigned int x, unsigned int y,  const unsigned char *data, unsigned char startnumber,unsigned char number,COLOR_enum word_color,COLOR_enum back_color, unsigned char size);

/**
*
* @brief    IPS屏幕显示彩色图片
* @param    x                   x方向坐标(0~240)
* @param    y                   y方向坐标(0~135)
* @param    width               图片宽度
* @param    heigh               图片高度
* @param    pic                 图片数组
* @return   void
* @notes
* Example:  Show_Picture_IPS(60,7,121,121,IPSEarth121x121); // 在屏幕中间显示地球图片
*
**/
void Show_Picture_IPS(unsigned int x, unsigned int y, unsigned int width, unsigned int heigh, const unsigned char pic[]);

/**
*
* @brief    IPS屏幕显示摄像头灰度图像
* @param    x                   x方向坐标(0~240)
* @param    y                   y方向坐标(0~135)
* @param    image               图像数组
* @param    width               图像数组实际宽度
* @param    heigh               图像数组实际高度
* @param    dis_width           图像数组显示宽度
* @param    dis_height          图像数组显示高度
* @param    threshold           为0时关闭二值化
* @return   void
* @notes
* Example:  Show_Image_IPS(0,0,OriginalImageData[0],188,120,188,135,0);
*
**/
void Show_Image_IPS(unsigned short x, unsigned short y, unsigned char *image, unsigned short width, unsigned short height, unsigned short show_width, unsigned short show_height, unsigned char threshold);

/**
 *
 * @brief    IPS屏幕显示摄像头二值化图像
 * @param    x                   x方向坐标(0~240)
 * @param    y                   y方向坐标(0~135)
 * @param    image               图像数组
 * @param    width               图像数组实际宽度
 * @param    heigh               图像数组实际高度
 * @param    show_width          图像数组显示宽度
 * @param    show_height         图像数组显示高度
 * @return   void
 * @notes
 * Example:  Show_Image_Binary_IPS(0,0,Deal_Image_Binary[0],80,60,160,120);
 *
 **/
 void Show_Image_Binary_IPS(unsigned short x, unsigned short y, unsigned char *image, unsigned short width, unsigned short height, unsigned short show_width, unsigned short show_height);

/**
*
* @brief    IPS屏幕写命令
* @param    command         命令
* @return   void
* @notes    IPS.c文件内部调用,用户无需调用尝试
* Example:  Write_Cmd_IPS(0x21);
*
**/
static void Write_Cmd_IPS(unsigned char cmd);

/**
*
* @brief    IPS屏幕写8bit数据
* @param    data                8bit数据
* @return   void
* @notes    IPS.c文件内部调用,用户无需调用尝试
* Example:  Write_8bit_IPS(0x23);
*
**/
static void Write_8bit_IPS(unsigned char data);

/**
*
* @brief    IPS屏幕写16bit数据
* @param    data                16bit数据
* @return   void
* @notes    IPS.c文件内部调用,用户无需调用尝试
* Example:  Write_16bit_IPS(0x0000);
*
**/
static void Write_16bit_IPS(unsigned short data);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_IPS_H_ */
