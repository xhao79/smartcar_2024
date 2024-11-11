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
 * @file       dmx_gpio.h
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

#ifndef DMXLIBRARIES_DMX_GPIO_H_
#define DMXLIBRARIES_DMX_GPIO_H_

#include "IFXPORT.h"

// 端口地址
#define  P00    &MODULE_P00
#define  P02    &MODULE_P02
#define  P10    &MODULE_P10
#define  P11    &MODULE_P11
#define  P13    &MODULE_P13
#define  P14    &MODULE_P14
#define  P15    &MODULE_P15
#define  P20    &MODULE_P20
#define  P21    &MODULE_P21
#define  P22    &MODULE_P22
#define  P23    &MODULE_P23
#define  P33    &MODULE_P33

// GPIO引脚模式枚举
typedef enum
{
    InputNOPULL     ,     // 无输入上下拉
    InputPULLDOWN   ,     // 输入下拉
    InputPULLUP     ,     // 输入上拉
    OutputPUSHPULL  ,     // 推挽输出
    OutputOPENDRAIN ,     // 开漏输出
}GPIO_mode_enum;

/**
*
* @brief    GPIO初始化
* @param    port        选择的端口,根据dmx_gpio.h中端口地址的宏定义
* @param    pinIndex    该端口的对应引脚号
* @param    pinmode     引脚模式配置(可设置参数由dmx_gpio.h中GPIO引脚模式枚举值确定)
* @param    level       引脚初始化时设置的电平状态(输出模式时有效)低电平:0 高电平:1
* @return   void
* @notes    TC264的P20.2引脚是不能用于输出的,仅有输入功能。TC264DA芯片的21.6无法正常使用。
* Example:  init_gpio(P20 , 8 , OutputPUSHPULL , 0);    // TC264的P20.8引脚初始化为推挽输出模式,初始输出低电平
*
**/
void init_gpio(Ifx_P *port, unsigned char pinIndex,GPIO_mode_enum pinmode,unsigned char level);

/**
*
* @brief    GPIO输入输出转换
* @param    port        选择的端口,根据Dmx_Gpio.h中端口地址的宏定义
* @param    pinIndex    该端口的对应引脚号
* @param    dir         输入:0 输出:1
* @return   void
* @notes
* Example:  set_dir_gpio(P20 ,8 , 1);   //使TC264的P20.8引脚输出高电平
*
**/
void set_dir_gpio(Ifx_P *port, unsigned char pinIndex, unsigned char dir);

/**
*
* @brief    GPIO输出设置
* @param    port        选择的端口,根据Dmx_Gpio.h中端口地址的宏定义
* @param    pinIndex    该端口的对应引脚号
* @param    level       引脚初始化时设置的电平状态(输出模式时有效)低电平:0 高电平:1
* @return   void
* @notes
* Example:  set_level_gpio(P20 ,8 , 1);   //使TC264的P20.8引脚输出高电平
*
**/
void set_level_gpio(Ifx_P *port, unsigned char pinIndex, unsigned char level);

/**
*
* @brief    GPIO状态获取
* @param    port        选择的端口,根据Dmx_Gpio.h中端口地址的宏定义
* @param    pinIndex    该端口的对应引脚号
* @param    level       引脚初始化时设置的电平状态(输出模式时有效)低电平:0 高电平:1
* @notes
* Example:  unsigned char status = get_level_gpio(P20 ,8);  // 获取TC264的P20.8引脚电平赋值到所定义的status变量
*
**/
unsigned char get_level_gpio(Ifx_P *port, unsigned char pinIndex);

/**
*
* @brief    GPIO状态翻转
* @param    port        选择的端口,根据Dmx_Gpio.h中端口地址的宏定义
* @param    pinIndex    该端口的对应引脚号
* @return   void
* @notes
* Example:  toggle_level_gpio(P20 ,8);  // TC264的P20.8引脚电平翻转
*
**/
void toggle_level_gpio(Ifx_P *port, unsigned char pinIndex);

#endif /* DMXLIBRARIES_DMX_GPIO_H_ */
