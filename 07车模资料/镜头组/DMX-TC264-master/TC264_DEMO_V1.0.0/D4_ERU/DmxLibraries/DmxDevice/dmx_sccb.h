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
 * @file       dmx_sccb.h
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

#ifndef DMXLIBRARIES_DMXDEVICE_DMX_SCCB_H_
#define DMXLIBRARIES_DMXDEVICE_DMX_SCCB_H_

#include "dmx_gpio.h"

// 摄像头使用SCCB通信,SCCB和IIC基本类似
#define MT9V034_SCL_MODULE      P02   // SCCB,SCL管脚
#define MT9V034_SCL_PIN         3
#define MT9V034_SDA_MODULE      P02   // SCCB,SDA管脚
#define MT9V034_SDA_PIN         2

// SCCB接口管脚控制
#define MT9V034_SCL_MODE(dir)       set_dir_gpio(MT9V034_SCL_MODULE , MT9V034_SCL_PIN , dir);
#define MT9V034_SDA_MODE(dir)       set_dir_gpio(MT9V034_SDA_MODULE , MT9V034_SDA_PIN , dir);
#define MT9V034_SCL_LEVEL(level)    set_level_gpio(MT9V034_SCL_MODULE , MT9V034_SCL_PIN , level);
#define MT9V034_SDA_LEVEL(level)    set_level_gpio(MT9V034_SDA_MODULE , MT9V034_SDA_PIN , level);
#define MT9V034_SDA_GET             get_level_gpio(MT9V034_SDA_MODULE , MT9V034_SDA_PIN );

// 用户无需调用和更改
#define SCCB_Delay()     {int count=500;while(--count){__asm("NOP");}}

void Set_Exposure_Time(unsigned int exposure,unsigned int analog_gain);
unsigned short Set_Config_MT9V034(unsigned int config[], unsigned char mode);

#endif /* DMXLIBRARIES_DMXDEVICE_DMX_SCCB_H_ */
