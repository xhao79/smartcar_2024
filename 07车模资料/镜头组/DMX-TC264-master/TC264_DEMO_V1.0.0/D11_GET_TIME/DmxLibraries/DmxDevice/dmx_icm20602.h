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
 * @file       dmx_icm20602.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_ICM20602_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_ICM20602_H_

#include "dmx_mpu.h"
#include "dmx_ips.h"

// ͨ�ŷ�ʽѡ��,0:���SPI,1:Ӳ��SPI
#define ICM20602_HARD_SPI       1

// IPS��Ļ�ܽź궨��
#if ICM20602_HARD_SPI
#define ICM20602_SPI_SPEED                  (10*1000*1000)                          // Ӳ�� SPI ����
#define ICM20602_SPI                        (SPI_0)                                 // Ӳ�� SPI ��
#define ICM20602_SPC_PIN                    (SPI0_CLK_P20_11)                       // Ӳ�� SPI SCK ����
#define ICM20602_SDI_PIN                    (SPI0_MOSI_P20_14)                      // Ӳ�� SPI MOSI ����
#define ICM20602_SDO_PIN                    (SPI0_MISO_P20_12)                      // ����SPI_MISO����  IPSû��MISO���ţ�����������Ȼ��Ҫ���壬��spi�ĳ�ʼ��ʱ��Ҫʹ��
#else
// ICM20602,SPC�ܽŶ�ӦTC264����P20_11
#define ICM20602_SPC_MODULE     P20
#define ICM20602_SPC_PIN        11
// ICM20602,SD1�ܽŶ�ӦTC264����P20_14
#define ICM20602_SDI_MODULE     P20
#define ICM20602_SDI_PIN        14
// ICM20602,SD0�ܽŶ�ӦTC264����P20_12
#define ICM20602_SDO_MODULE     P20
#define ICM20602_SDO_PIN        12
#endif
// ICM20602,CS�ܽŶ�ӦTC264����P20_13
#define ICM20602_CS_MODULE      P20
#define ICM20602_CS_PIN         13

// ��ICM20602��ĻCS�ܽŽ��иߵ͵�ƽ����
#define ICM20602_CS_LEVEL(level)    set_level_gpio(ICM20602_CS_MODULE  ,ICM20602_CS_PIN  , level);

extern float icm20602_acc_x  , icm20602_acc_y  , icm20602_acc_z  ;   // ����ICM20602���ٶȼ�����
extern float icm20602_gyro_x , icm20602_gyro_y , icm20602_gyro_z ;   // ����ICM20602�Ǽ��ٶ�����

/**
*
* @brief    ICM20602�����ǳ�ʼ��
* @param
* @return   void
* @notes    �û�����
* Example:  Init_ICM20602();
*
**/
void Init_ICM20602(void);

/**
*
* @brief    ���ICM20602�����Ǽ��ٶ�
* @param
* @return   void
* @notes    ��λ:g(m/s^2),�û�����
* Example:  Get_Acc_ICM20602();
*
**/
void Get_Acc_ICM20602(void);

/**
*
* @brief    ���ICM20602�����ǽǼ��ٶ�
* @param
* @return   void
* @notes    ��λΪ:��/s,�û�����
* Example:  Get_Gyro_ICM20602();
*
**/
void Get_Gyro_ICM20602(void);

/**
*
* @brief    ����ICM20602�����ǵ�ͨ�˲������������
* @param    abw                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @param    gbw                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @param    afs                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @param    gfs                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @return   void
* @notes    ICM20602.c�ļ��ڲ�����,�û�������ó���
* Example:  Set_LowpassFilter_Range_ICM20602(MPU_ABW_218, MPU_GBW_176,MPU_FS_4G, MPU_FS_2000DPS);
*
**/
void Set_LowpassFilter_Range_ICM20602(enum mpu_acc_bw abw, enum mpu_gyro_bw gbw, enum mpu_acc_fs afs, enum mpu_gyro_fs gfs);

/**
*
* @brief    ��������ʱ
* @param    time            ��ʱʱ��
* @return   void
* @notes    ICM20602.c�ļ��ڲ�����,�û�������ó���
* Example:  ICM20602_Delay_Ms(2);    // ��ʱ2msʱ��
*
**/
void Delay_Ms_ICM20602(unsigned int ms);

/**
 *
 * @brief    ICM20602������д����
 * @param    reg                 �Ĵ���
 * @param    data                ��Ҫд���üĴ���������
 * @return   void
 * @notes    ICM20602.c�ļ��ڲ�����,�û�������ó���
 * Example:  Write_Data_ICM20602(0X00,0X00);
 *
 **/
 static void Write_Data_ICM20602(unsigned char reg,unsigned char data);

 /**
 *
 * @brief    ICM20602�����Ƕ�����
 * @param    reg                 �Ĵ���
 * @param    data                �Ѷ��������ݴ���data
 * @param    num                 ���ݸ���
 * @return   void
 * @notes    ICM20602.c�ļ��ڲ�����,�û�������ó���
 * Example:  Read_Datas_ICM20602(0X00,0X00,1);
 *
 **/
 static void Read_Datas_ICM20602(unsigned char reg, unsigned char *data, unsigned int num);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_ICM20602_H_ */
