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
 * @file       dmx_pit.h
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

#ifndef DMXLIBRARIES_DMX_PIT_H_
#define DMXLIBRARIES_DMX_PIT_H_

// CCU6定时器模块0通道0中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  CCU60_CH0_PIT_PRIORITY    30
// CCU6定时器模块0通道1中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  CCU60_CH1_PIT_PRIORITY    31
// 定义CCU6定时器模块0归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define  CCU60_PIT_VECTABNUM       0

// CCU6定时器模块1通道0中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  CCU61_CH0_PIT_PRIORITY    32
// CCU6定时器模块1通道1中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  CCU61_CH1_PIT_PRIORITY    33
// 定义CCU6定时器模块1归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define  CCU61_PIT_VECTABNUM       0

// CCU6模块枚举
typedef enum
{
    CCU60,
    CCU61,
}CCU6_enum;

// CCU6通道枚举
typedef enum
{
    CH0,
    CH1,
}CCU6_ch_enum;

/**
*
* @brief    定时器中断初始化
* @param    ccu6        选择CCU6模块(CCU60,CCU61)
* @param    channel     选择通道(CH0,CH1)
* @param    time        周期时间
* @return   void
* @notes    周期时间单位:微秒
* Example:  init_pit(CCU60, CH0, 100);  // CCU60模块通道0,100us执行一次中断
*
**/
void init_pit(CCU6_enum ccu6, CCU6_ch_enum channel, unsigned long time);

/**
*
* @brief    定时器中断使能
* @param    ccu6        选择CCU6模块(CCU60,CCU61)
* @param    channel     选择通道(CH0,CH1)
* @return   void
* @notes
* Example:  enable_pit(CCU60, CH0);     // 开启CCU60模块通道0的中断
*
**/
void enable_pit(CCU6_enum ccu6, CCU6_ch_enum channel);

/**
*
* @brief    定时器中断禁止
* @param    ccu6        选择CCU6模块(CCU60,CCU61)
* @param    channel     选择通道(CH0,CH1)
* @return   void
* @notes
* Example:  disable_pit(CCU60, CH0);    // 关闭CCU60模块通道0的中断
*
**/
void disable_pit(CCU6_enum ccu6, CCU6_ch_enum channel);

#endif /* DMXLIBRARIES_DMX_PIT_H_ */
