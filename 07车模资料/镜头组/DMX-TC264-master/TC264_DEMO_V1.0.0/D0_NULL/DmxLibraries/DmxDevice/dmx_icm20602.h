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
 * @file       dmx_icm20602.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_ICM20602_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_ICM20602_H_

#include "dmx_mpu.h"
#include "dmx_ips.h"

// 通信方式选择,0:软件SPI,1:硬件SPI
#define ICM20602_HARD_SPI       1

// IPS屏幕管脚宏定义
#if ICM20602_HARD_SPI
#define ICM20602_SPI_SPEED                  (10*1000*1000)                          // 硬件 SPI 速率
#define ICM20602_SPI                        (SPI_0)                                 // 硬件 SPI 号
#define ICM20602_SPC_PIN                    (SPI0_CLK_P20_11)                       // 硬件 SPI SCK 引脚
#define ICM20602_SDI_PIN                    (SPI0_MOSI_P20_14)                      // 硬件 SPI MOSI 引脚
#define ICM20602_SDO_PIN                    (SPI0_MISO_P20_12)                      // 定义SPI_MISO引脚  IPS没有MISO引脚，但是这里任然需要定义，在spi的初始化时需要使用
#else
// ICM20602,SPC管脚对应TC264引脚P20_11
#define ICM20602_SPC_MODULE     P20
#define ICM20602_SPC_PIN        11
// ICM20602,SD1管脚对应TC264引脚P20_14
#define ICM20602_SDI_MODULE     P20
#define ICM20602_SDI_PIN        14
// ICM20602,SD0管脚对应TC264引脚P20_12
#define ICM20602_SDO_MODULE     P20
#define ICM20602_SDO_PIN        12
#endif
// ICM20602,CS管脚对应TC264引脚P20_13
#define ICM20602_CS_MODULE      P20
#define ICM20602_CS_PIN         13

// 对ICM20602屏幕CS管脚进行高低电平操作
#define ICM20602_CS_LEVEL(level)    set_level_gpio(ICM20602_CS_MODULE  ,ICM20602_CS_PIN  , level);

extern float icm20602_acc_x  , icm20602_acc_y  , icm20602_acc_z  ;   // 声明ICM20602加速度计数据
extern float icm20602_gyro_x , icm20602_gyro_y , icm20602_gyro_z ;   // 声明ICM20602角加速度数据

/**
*
* @brief    ICM20602陀螺仪初始化
* @param
* @return   void
* @notes    用户调用
* Example:  Init_ICM20602();
*
**/
void Init_ICM20602(void);

/**
*
* @brief    获得ICM20602陀螺仪加速度
* @param
* @return   void
* @notes    单位:g(m/s^2),用户调用
* Example:  Get_Acc_ICM20602();
*
**/
void Get_Acc_ICM20602(void);

/**
*
* @brief    获得ICM20602陀螺仪角加速度
* @param
* @return   void
* @notes    单位为:°/s,用户调用
* Example:  Get_Gyro_ICM20602();
*
**/
void Get_Gyro_ICM20602(void);

/**
*
* @brief    设置ICM20602陀螺仪低通滤波器带宽和量程
* @param    abw                 // 可在dmx_mpu.h文件里枚举定义中查看
* @param    gbw                 // 可在dmx_mpu.h文件里枚举定义中查看
* @param    afs                 // 可在dmx_mpu.h文件里枚举定义中查看
* @param    gfs                 // 可在dmx_mpu.h文件里枚举定义中查看
* @return   void
* @notes    ICM20602.c文件内部调用,用户无需调用尝试
* Example:  Set_LowpassFilter_Range_ICM20602(MPU_ABW_218, MPU_GBW_176,MPU_FS_4G, MPU_FS_2000DPS);
*
**/
void Set_LowpassFilter_Range_ICM20602(enum mpu_acc_bw abw, enum mpu_gyro_bw gbw, enum mpu_acc_fs afs, enum mpu_gyro_fs gfs);

/**
*
* @brief    陀螺仪延时
* @param    time            延时时间
* @return   void
* @notes    ICM20602.c文件内部调用,用户无需调用尝试
* Example:  ICM20602_Delay_Ms(2);    // 延时2ms时间
*
**/
void Delay_Ms_ICM20602(unsigned int ms);

/**
 *
 * @brief    ICM20602陀螺仪写数据
 * @param    reg                 寄存器
 * @param    data                需要写进该寄存器的数据
 * @return   void
 * @notes    ICM20602.c文件内部调用,用户无需调用尝试
 * Example:  Write_Data_ICM20602(0X00,0X00);
 *
 **/
 static void Write_Data_ICM20602(unsigned char reg,unsigned char data);

 /**
 *
 * @brief    ICM20602陀螺仪读数据
 * @param    reg                 寄存器
 * @param    data                把读出的数据存入data
 * @param    num                 数据个数
 * @return   void
 * @notes    ICM20602.c文件内部调用,用户无需调用尝试
 * Example:  Read_Datas_ICM20602(0X00,0X00,1);
 *
 **/
 static void Read_Datas_ICM20602(unsigned char reg, unsigned char *data, unsigned int num);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_ICM20602_H_ */
