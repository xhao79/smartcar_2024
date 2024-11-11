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
 * @file       dmx_pwm.h
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

#ifndef DMXLIBRARIES_DMX_PWM_H_
#define DMXLIBRARIES_DMX_PWM_H_

#define MAX_DUTY    10000
#define CLK_FREQ    20000000.0f

typedef enum
{
    // ATOM0
    ATOM0_0_P00_0,  ATOM0_0_P02_0,  ATOM0_0_P02_8,  ATOM0_0_P14_5,  ATOM0_0_P21_2,  ATOM0_0_P22_1,                                  // ATOM0_CHANNEL0
    ATOM0_1_P00_1,  ATOM0_1_P00_2,  ATOM0_1_P02_1,  ATOM0_1_P10_1,  ATOM0_1_P14_4,  ATOM0_1_P21_3,  ATOM0_1_P22_0,  ATOM0_1_P33_9,  // ATOM0_CHANNEL1
    ATOM0_2_P00_3,  ATOM0_2_P02_2,  ATOM0_2_P10_2,  ATOM0_2_P10_5,  ATOM0_2_P14_3,  ATOM0_2_P21_4,  ATOM0_2_P33_11,                 // ATOM0_CHANNEL2
    ATOM0_3_P00_4,  ATOM0_3_P02_3,  ATOM0_3_P10_3,  ATOM0_3_P10_6,  ATOM0_3_P14_2,  ATOM0_3_P21_5,  ATOM0_3_P22_2,                  // ATOM0_CHANNEL3
    ATOM0_4_P00_5,  ATOM0_4_P02_4,  ATOM0_4_P14_1,  ATOM0_4_P20_3,  ATOM0_4_P21_6,  ATOM0_4_P22_3,                                  // ATOM0_CHANNEL4
    ATOM0_5_P00_6,  ATOM0_5_P02_5,  ATOM0_5_P21_7,  ATOM0_5_P32_4,                                                                  // ATOM0_CHANNEL5
    ATOM0_6_P00_7,  ATOM0_6_P02_6,  ATOM0_6_P20_0,  ATOM0_6_P23_1,                                                                  // ATOM0_CHANNEL6
    ATOM0_7_P00_8,  ATOM0_7_P02_7,  ATOM0_7_P20_8,                                                                                  // ATOM0_CHANNEL7
    // ATOM1
    ATOM1_0_P00_0,  ATOM1_0_P02_0,  ATOM1_0_P02_8,  ATOM1_0_P15_5,  ATOM1_0_P15_6,  ATOM1_0_P20_12, ATOM1_0_P21_2, ATOM1_0_P22_1,                                               // ATOM1_CHANNEL0
    ATOM1_1_P00_1,  ATOM1_1_P00_2,  ATOM1_1_P02_1,  ATOM1_1_P10_1,  ATOM1_1_P14_6,  ATOM1_1_P15_7,  ATOM1_1_P15_8, ATOM1_1_P20_13, ATOM1_1_P21_3, ATOM1_1_P22_0, ATOM1_1_P33_9, // ATOM1_CHANNEL1
    ATOM1_2_P00_3,  ATOM1_2_P02_2,  ATOM1_2_P10_2,  ATOM1_2_P10_5,  ATOM1_2_P14_0,  ATOM1_2_P20_14, ATOM1_2_P21_4, ATOM1_2_P33_11,                                              // ATOM1_CHANNEL2
    ATOM1_3_P00_4,  ATOM1_3_P02_3,  ATOM1_3_P10_3,  ATOM1_3_P10_6,  ATOM1_3_P15_0,  ATOM1_3_P21_5,  ATOM1_3_P22_2,                                                              // ATOM1_CHANNEL3
    ATOM1_4_P00_5,  ATOM1_4_P02_4,  ATOM1_4_P15_1,  ATOM1_4_P20_3,  ATOM1_4_P21_6,  ATOM1_4_P22_3,                                                                              // ATOM1_CHANNEL4
    ATOM1_5_P00_6,  ATOM1_5_P02_5,  ATOM1_5_P15_2,  ATOM1_5_P20_9,  ATOM1_5_P21_7,  ATOM1_5_P32_4,                                                                              // ATOM1_CHANNEL5
    ATOM1_6_P00_7,  ATOM1_6_P02_6,  ATOM1_6_P15_3,  ATOM1_6_P20_0,  ATOM1_6_P20_10, ATOM1_6_P23_1,                                                                              // ATOM1_CHANNEL6
    ATOM1_7_P00_8,  ATOM1_7_P02_7,  ATOM1_7_P15_4,  ATOM1_7_P20_11,                                                                                                             // ATOM1_CHANNEL7
    // ATOM2
    ATOM2_0_P00_9,  ATOM2_0_P13_3,  ATOM2_0_P20_12, ATOM2_0_P33_4,  ATOM2_0_P33_10,                 // ATOM2_CHANNEL0
    ATOM2_1_P11_2,  ATOM2_1_P20_13, ATOM2_1_P33_5,                                                  // ATOM2_CHANNEL1
    ATOM2_2_P11_3,  ATOM2_2_P20_14, ATOM2_2_P33_6,                                                  // ATOM2_CHANNEL2
    ATOM2_3_P00_12, ATOM2_3_P11_6,  ATOM2_3_P15_0,  ATOM2_3_P33_7,                                  // ATOM2_CHANNEL3
    ATOM2_4_P11_9,  ATOM2_4_P15_1,  ATOM2_4_P33_8,  ATOM2_4_P33_12,                                 // ATOM2_CHANNEL4
    ATOM2_5_P11_10, ATOM2_5_P13_0,  ATOM2_5_P15_2,  ATOM2_5_P20_9,  ATOM2_5_P33_13,                 // ATOM2_CHANNEL5
    ATOM2_6_P11_11, ATOM2_6_P13_1,  ATOM2_6_P15_3,  ATOM2_6_P20_6,  ATOM2_6_P20_10, ATOM2_6_P32_0,  // ATOM2_CHANNEL6
    ATOM2_7_P11_12, ATOM2_7_P13_2,  ATOM2_7_P15_4,  ATOM2_7_P20_7,  ATOM2_7_P20_8,  ATOM2_7_P20_11, // ATOM2_CHANNEL7
    // ATOM3
    ATOM3_0_P00_9,  ATOM3_0_P13_3,  ATOM3_0_P14_5,  ATOM3_0_P15_5,  ATOM3_0_P15_6,  ATOM3_0_P33_4,  ATOM3_0_P33_10, // ATOM3_CHANNEL0
    ATOM3_1_P11_2,  ATOM3_1_P14_4,  ATOM3_1_P14_6,  ATOM3_1_P15_7,  ATOM3_1_P15_8,  ATOM3_1_P33_5,                  // ATOM3_CHANNEL1
    ATOM3_2_P11_3,  ATOM3_2_P14_0,  ATOM3_2_P14_3,  ATOM3_2_P33_6,                                                  // ATOM3_CHANNEL2
    ATOM3_3_P00_12, ATOM3_3_P11_6,  ATOM3_3_P14_2,  ATOM3_3_P33_7,                                                  // ATOM3_CHANNEL3
    ATOM3_4_P11_9,  ATOM3_4_P14_1,  ATOM3_4_P33_8,  ATOM3_4_P33_12,                                                 // ATOM3_CHANNEL4
    ATOM3_5_P11_10, ATOM3_5_P13_0,  ATOM3_5_P33_13,                                                                 // ATOM3_CHANNEL5
    ATOM3_6_P11_11, ATOM3_6_P13_1,  ATOM3_6_P20_6,  ATOM3_6_P32_0,                                                  // ATOM3_CHANNEL6
    ATOM3_7_P11_12, ATOM3_7_P13_2,  ATOM3_7_P20_7,                                                                  // ATOM3_CHANNEL7
}PWM_pin_enum;

/**
*
* @brief    初始化引脚作为pwm输出引脚，并设定其初始频率及初始占空比
* @param    PWM_pin_enum        PWM引脚
* @param    frequency           PWM频率
* @param    duty                PWM占空比
* @return   void
* @notes    同一个ATOM模块下的相同通道不能设置不同频率。如在同一个模块同一个通道不同引脚负责电机驱动和舵机驱动，这样是不可行的。
* Example:  init_pwm(ATOM0_7_P20_8, 13333, 1000);   // 初始化引脚P20_8频率为13333占空比为10%(1000/MAX_DUTY)
*
**/
void init_pwm(PWM_pin_enum pwmpin, unsigned int freq, unsigned int duty);

/**
*
* @brief    设置输出占空比
* @param    PWM_pin_enum        PWM引脚
* @param    duty                PWM占空比
* @return   void
* @notes    duty最大值为10000即占空比100%
* Example:  set_duty_pwm(ATOM0_7_P20_8, 2000);      // 使引脚P20_8占空比变为20%(2000/MAX_DUTY)
*
**/
void set_duty_pwm(PWM_pin_enum pwmpin, unsigned int duty);

#endif /* DMXLIBRARIES_DMX_PWM_H_ */
