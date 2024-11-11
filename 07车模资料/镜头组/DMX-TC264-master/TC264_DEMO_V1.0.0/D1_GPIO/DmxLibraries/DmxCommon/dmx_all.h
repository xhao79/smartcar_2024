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
 * @file       dmx_all.h
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

#ifndef DMXLIBRARIES_DMX_COMMON_DMX_ALL_H_
#define DMXLIBRARIES_DMX_COMMON_DMX_ALL_H_

//基本库文件
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"

//英飞凌官方头文件
#include "ifxAsclin_reg.h"
#include "Bsp.h"
#include "IfxCcu6_Timer.h"
#include "IfxScuEru.h"
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "ifxCpu_Irq.h"
#include "CompilerTasking.h"
#include "IfxFft.h"

//呆萌侠二次封装驱动头文件
#include "dmx_common.h"
#include "dmx_adc.h"
#include "dmx_assert.h"
#include "dmx_delay.h"
#include "dmx_dma.h"
#include "dmx_encoder.h"
#include "dmx_eru.h"
#include "dmx_flash.h"
#include "dmx_gpio.h"
#include "dmx_hard_spi.h"
#include "dmx_pit.h"
#include "dmx_pwm.h"
#include "dmx_soft_iic.h"
#include "dmx_soft_spi.h"
#include "dmx_uart.h"

//呆萌侠外围设备头文件
#include "dmx_font.h"
#include "dmx_function.h"
#include "dmx_icm20602.h"
#include "dmx_ips.h"
#include "dmx_mpu.h"
#include "dmx_mt9v034.h"
#include "dmx_oled.h"
#include "dmx_tft180.h"
#include "dmx_icm42688.h"

//CODE头文件

#endif /* DMXLIBRARIES_DMX_COMMON_DMX_ALL_H_ */
