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
 * @file       dmx_eru.h
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

#ifndef DMXLIBRARIES_DMX_DRIVER_DMX_ERU_H_
#define DMXLIBRARIES_DMX_DRIVER_DMX_ERU_H_

// GPIO外部中断参数定义
// 定义ERU通道0和通道4中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define ERU_CH0_4_INT_PRIORITY      40
// 定义ERU通道0和通道4归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define ERU_CH0_4_INT_VECTABNUM     IfxSrc_Tos_cpu0

// 定义ERU通道1和通道5中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define ERU_CH1_5_INT_PRIORITY      41
// 定义ERU通道1和通道5归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define ERU_CH1_5_INT_VECTABNUM     IfxSrc_Tos_cpu0

// 定义ERU通道2和通道6中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define ERU_CH2_6_INT_PRIORITY      5
// 定义ERU通道2和通道6归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define ERU_CH2_6_INT_VECTABNUM     IfxSrc_Tos_dma

// 定义ERU通道3和通道7中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define ERU_CH3_7_INT_PRIORITY      43
// 定义ERU通道3和通道7归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define ERU_CH3_7_INT_VECTABNUM     IfxSrc_Tos_cpu0

// 触发方式枚举
typedef enum
{
    RISING,     // 上升沿触发
    FALLING,    // 下降沿触发
    BOTH,       // 双边沿触发
}ERU_mode_enum;

//ERU通道枚举
typedef enum
{
    // 通道0可选引脚
    EX0,        // ！！！！！TC264中无此引脚，此处使用为占位所需！！！！！
    EruP15_4,   // TC264的外部中断通道0的P15.4引脚
    EX1,        // ！！！！！TC264中无此引脚，此处使用为占位所需！！！！！
    // 通道1可选引脚
    EX2,        // ！！！！！TC264中无此引脚，此处使用为占位所需！！！！！
    EruP14_3,   // TC264的外部中断通道1的P14.3引脚
    EX3,        // ！！！！！TC264中无此引脚，此处使用为占位所需！！！！！
    // 通道2可选引脚
    EruP00_4,   // TC264的外部中断通道2的P00.4引脚
    EruP02_1,   // TC264的外部中断通道2的P02.1引脚
    EruP10_2,   // TC264的外部中断通道2的P10.2引脚
    // 通道3可选引脚
    EruP02_0,   // TC264的外部中断通道3的P02.0引脚
    EruP10_3,   // TC264的外部中断通道3的P10.3引脚
    EruP14_1,   // TC264的外部中断通道3的P14.1引脚
    // 通道4可选引脚
    EruP15_5,   // TC264的外部中断通道4的P15.5引脚
    EruP33_7,   // TC264的外部中断通道4的P33.7引脚
    EX4,        // ！！！！！TC264中无此引脚，此处使用为占位所需！！！！！
    // 通道5可选引脚
    EruP15_8,   // TC264的外部中断通道5的P15.8引脚
    EX5,        // ！！！！！TC264中无此引脚，此处使用为占位所需！！！！！
    EX6,        // ！！！！！TC264中无此引脚，此处使用为占位所需！！！！！
    // 通道6可选引脚
    EruP11_10,  // TC264的外部中断通道6的P11.10引脚
    EruP20_0,   // TC264的外部中断通道6的P20.0引脚
    EX7,        // ！！！！！TC264中无此引脚，此处使用为占位所需！！！！！
    // 通道7可选引脚
    EruP15_1,   // TC264的外部中断通道7的P15.1引脚
    EruP20_9,   // TC264的外部中断通道7的P20.9引脚
    EX8,        // ！！！！！TC264中无此引脚，此处使用为占位所需！！！！！
}ERU_pin_enum;

/**
*
* @brief    gpio外部中断初始化
* @param    erupin  设置gpio外部中断引脚
* @param    mode    设置触发方式
* @return   void
* @notes    TC264只有15个固定的GPIO引脚支持外部中断,这15个引脚分为8个通道,其中
*           通道0和通道4共用一个中断,通道1和通道5共用一个中断,通道2和通道6共用一个中断,通道3和通道7共用一个中断
* Example:  init_eru(P15_4, RISING);    // 外部中断通道0,使用P15_4引脚,上升沿触发中断
*
**/
void init_eru(ERU_pin_enum eru_pin, ERU_mode_enum trigger);

/**
*
* @brief    开启gpio外部中断
* @param    erupin     设置gpio外部中断引脚
* @return   void
* @notes
* Example:  enable_eru(P15_4);  // P15_4引脚gpio外部中断开启
*
**/
void enable_eru(ERU_pin_enum eru_pin);

/**
*
* @brief    关闭gpio外部中断
* @param    erupin     设置gpio外部中断引脚
* @return   void
* @notes
* Example:  disable_eru(P15_4); // P15_4引脚gpio外部中断关闭
*
**/
void disable_eru(ERU_pin_enum eru_pin);//eru中断关闭

#endif /* DMXLIBRARIES_DMX_DRIVER_DMX_ERU_H_ */
