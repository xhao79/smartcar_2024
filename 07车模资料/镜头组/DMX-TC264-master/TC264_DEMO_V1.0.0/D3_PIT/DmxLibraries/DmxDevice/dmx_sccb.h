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
 * @file       dmx_sccb.h
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

#ifndef DMXLIBRARIES_DMXDEVICE_DMX_SCCB_H_
#define DMXLIBRARIES_DMXDEVICE_DMX_SCCB_H_

#include "dmx_gpio.h"

// ����ͷʹ��SCCBͨ��,SCCB��IIC��������
#define MT9V034_SCL_MODULE      P02   // SCCB,SCL�ܽ�
#define MT9V034_SCL_PIN         3
#define MT9V034_SDA_MODULE      P02   // SCCB,SDA�ܽ�
#define MT9V034_SDA_PIN         2

// SCCB�ӿڹܽſ���
#define MT9V034_SCL_MODE(dir)       set_dir_gpio(MT9V034_SCL_MODULE , MT9V034_SCL_PIN , dir);
#define MT9V034_SDA_MODE(dir)       set_dir_gpio(MT9V034_SDA_MODULE , MT9V034_SDA_PIN , dir);
#define MT9V034_SCL_LEVEL(level)    set_level_gpio(MT9V034_SCL_MODULE , MT9V034_SCL_PIN , level);
#define MT9V034_SDA_LEVEL(level)    set_level_gpio(MT9V034_SDA_MODULE , MT9V034_SDA_PIN , level);
#define MT9V034_SDA_GET             get_level_gpio(MT9V034_SDA_MODULE , MT9V034_SDA_PIN );

// �û�������ú͸���
#define SCCB_Delay()     {int count=500;while(--count){__asm("NOP");}}

void Set_Exposure_Time(unsigned int exposure,unsigned int analog_gain);
unsigned short Set_Config_MT9V034(unsigned int config[], unsigned char mode);

#endif /* DMXLIBRARIES_DMXDEVICE_DMX_SCCB_H_ */
