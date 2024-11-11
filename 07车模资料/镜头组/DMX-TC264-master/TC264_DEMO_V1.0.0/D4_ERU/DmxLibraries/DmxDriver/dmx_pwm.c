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
 * @file       dmx_pwm.c
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

#include "dmx_pwm.h"
#include "IfxGtm_Atom_Pwm.h"

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
void init_pwm(PWM_pin_enum pwmpin, unsigned int frequency, unsigned int duty)
{
    static boolean GtmInitFlag=0;

    IfxGtm_Atom_Pwm_Config g_atomConfig;
    IfxGtm_Atom_Pwm_Driver g_atomDriver;

    IfxGtm_Atom_ToutMap* pwm_channel_pin;

    switch(pwmpin)
    {
        case ATOM0_0_P00_0: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT9_P00_0_OUT; break;
        case ATOM0_0_P02_0: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT0_P02_0_OUT; break;
        case ATOM0_0_P02_8: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT8_P02_8_OUT; break;
        case ATOM0_0_P14_5: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT85_P14_5_OUT; break;
        case ATOM0_0_P21_2: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT53_P21_2_OUT; break;
        case ATOM0_0_P22_1: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT48_P22_1_OUT; break;

        case ATOM0_1_P00_1: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT10_P00_1_OUT; break;
        case ATOM0_1_P00_2: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT11_P00_2_OUT; break;
        case ATOM0_1_P02_1: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT1_P02_1_OUT; break;
        case ATOM0_1_P10_1: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT103_P10_1_OUT; break;
        case ATOM0_1_P14_4: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT84_P14_4_OUT; break;
        case ATOM0_1_P21_3: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT54_P21_3_OUT; break;
        case ATOM0_1_P22_0: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT47_P22_0_OUT; break;
        case ATOM0_1_P33_9: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT31_P33_9_OUT; break;

        case ATOM0_2_P00_3: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT12_P00_3_OUT; break;
        case ATOM0_2_P02_2: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT2_P02_2_OUT; break;
        case ATOM0_2_P10_2: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT104_P10_2_OUT; break;
        case ATOM0_2_P10_5: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT107_P10_5_OUT; break;
        case ATOM0_2_P14_3: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT83_P14_3_OUT; break;
        case ATOM0_2_P21_4: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT55_P21_4_OUT; break;
        case ATOM0_2_P33_11:pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT33_P33_11_OUT; break;

        case ATOM0_3_P00_4: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT13_P00_4_OUT; break;
        case ATOM0_3_P02_3: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT3_P02_3_OUT; break;
        case ATOM0_3_P10_3: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT105_P10_3_OUT; break;
        case ATOM0_3_P10_6: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT108_P10_6_OUT; break;
        case ATOM0_3_P14_2: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT82_P14_2_OUT; break;
        case ATOM0_3_P21_5: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT56_P21_5_OUT; break;
        case ATOM0_3_P22_2: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT49_P22_2_OUT; break;

        case ATOM0_4_P00_5: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT14_P00_5_OUT; break;
        case ATOM0_4_P02_4: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT4_P02_4_OUT; break;
        case ATOM0_4_P14_1: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT81_P14_1_OUT; break;
        case ATOM0_4_P20_3: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT61_P20_3_OUT; break;
        case ATOM0_4_P21_6: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT57_P21_6_OUT; break;
        case ATOM0_4_P22_3: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT50_P22_3_OUT; break;

        case ATOM0_5_P00_6: pwm_channel_pin = &IfxGtm_ATOM0_5_TOUT15_P00_6_OUT; break;
        case ATOM0_5_P02_5: pwm_channel_pin = &IfxGtm_ATOM0_5_TOUT5_P02_5_OUT; break;
        case ATOM0_5_P21_7: pwm_channel_pin = &IfxGtm_ATOM0_5_TOUT58_P21_7_OUT; break;
        case ATOM0_5_P32_4: pwm_channel_pin = &IfxGtm_ATOM0_5_TOUT40_P32_4_OUT; break;

        case ATOM0_6_P00_7: pwm_channel_pin = &IfxGtm_ATOM0_6_TOUT16_P00_7_OUT; break;
        case ATOM0_6_P02_6: pwm_channel_pin = &IfxGtm_ATOM0_6_TOUT6_P02_6_OUT; break;
        case ATOM0_6_P20_0: pwm_channel_pin = &IfxGtm_ATOM0_6_TOUT59_P20_0_OUT; break;
        case ATOM0_6_P23_1: pwm_channel_pin = &IfxGtm_ATOM0_6_TOUT42_P23_1_OUT; break;

        case ATOM0_7_P00_8: pwm_channel_pin = &IfxGtm_ATOM0_7_TOUT17_P00_8_OUT; break;
        case ATOM0_7_P02_7: pwm_channel_pin = &IfxGtm_ATOM0_7_TOUT7_P02_7_OUT; break;
        case ATOM0_7_P20_8: pwm_channel_pin = &IfxGtm_ATOM0_7_TOUT64_P20_8_OUT; break;

        case ATOM1_0_P00_0: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT9_P00_0_OUT; break;
        case ATOM1_0_P02_0: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT0_P02_0_OUT; break;
        case ATOM1_0_P02_8: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT8_P02_8_OUT; break;
        case ATOM1_0_P15_5: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT76_P15_5_OUT; break;
        case ATOM1_0_P15_6: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT77_P15_6_OUT; break;
        case ATOM1_0_P20_12:pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT68_P20_12_OUT; break;
        case ATOM1_0_P21_2: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT53_P21_2_OUT; break;
        case ATOM1_0_P22_1: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT48_P22_1_OUT; break;

        case ATOM1_1_P00_1: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT10_P00_1_OUT; break;
        case ATOM1_1_P00_2: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT11_P00_2_OUT; break;
        case ATOM1_1_P02_1: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT1_P02_1_OUT; break;
        case ATOM1_1_P10_1: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT103_P10_1_OUT; break;
        case ATOM1_1_P14_6: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT86_P14_6_OUT; break;
        case ATOM1_1_P15_7: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT78_P15_7_OUT; break;
        case ATOM1_1_P15_8: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT79_P15_8_OUT; break;
        case ATOM1_1_P20_13:pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT69_P20_13_OUT; break;
        case ATOM1_1_P21_3: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT54_P21_3_OUT; break;
        case ATOM1_1_P22_0: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT47_P22_0_OUT; break;
        case ATOM1_1_P33_9: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT31_P33_9_OUT; break;

        case ATOM1_2_P00_3: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT12_P00_3_OUT; break;
        case ATOM1_2_P02_2: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT2_P02_2_OUT; break;
        case ATOM1_2_P10_2: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT104_P10_2_OUT; break;
        case ATOM1_2_P10_5: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT107_P10_5_OUT; break;
        case ATOM1_2_P14_0: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT80_P14_0_OUT; break;
        case ATOM1_2_P20_14:pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT70_P20_14_OUT; break;
        case ATOM1_2_P21_4: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT55_P21_4_OUT; break;
        case ATOM1_2_P33_11:pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT33_P33_11_OUT; break;

        case ATOM1_3_P00_4: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT13_P00_4_OUT; break;
        case ATOM1_3_P02_3: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT3_P02_3_OUT; break;
        case ATOM1_3_P10_3: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT105_P10_3_OUT; break;
        case ATOM1_3_P10_6: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT108_P10_6_OUT; break;
        case ATOM1_3_P15_0: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT71_P15_0_OUT; break;
        case ATOM1_3_P21_5: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT56_P21_5_OUT; break;
        case ATOM1_3_P22_2: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT49_P22_2_OUT; break;

        case ATOM1_4_P00_5: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT14_P00_5_OUT; break;
        case ATOM1_4_P02_4: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT4_P02_4_OUT; break;
        case ATOM1_4_P15_1: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT72_P15_1_OUT; break;
        case ATOM1_4_P20_3: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT61_P20_3_OUT; break;
        case ATOM1_4_P21_6: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT57_P21_6_OUT; break;
        case ATOM1_4_P22_3: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT50_P22_3_OUT; break;

        case ATOM1_5_P00_6: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT15_P00_6_OUT; break;
        case ATOM1_5_P02_5: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT5_P02_5_OUT; break;
        case ATOM1_5_P15_2: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT73_P15_2_OUT; break;
        case ATOM1_5_P20_9: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT65_P20_9_OUT; break;
        case ATOM1_5_P21_7: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT58_P21_7_OUT; break;
        case ATOM1_5_P32_4: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT40_P32_4_OUT; break;

        case ATOM1_6_P00_7: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT16_P00_7_OUT; break;
        case ATOM1_6_P02_6: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT6_P02_6_OUT; break;
        case ATOM1_6_P15_3: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT74_P15_3_OUT; break;
        case ATOM1_6_P20_0: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT59_P20_0_OUT; break;
        case ATOM1_6_P20_10:pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT66_P20_10_OUT; break;
        case ATOM1_6_P23_1: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT42_P23_1_OUT; break;

        case ATOM1_7_P00_8: pwm_channel_pin = &IfxGtm_ATOM1_7_TOUT17_P00_8_OUT; break;
        case ATOM1_7_P02_7: pwm_channel_pin = &IfxGtm_ATOM1_7_TOUT7_P02_7_OUT; break;
        case ATOM1_7_P15_4: pwm_channel_pin = &IfxGtm_ATOM1_7_TOUT75_P15_4_OUT; break;
        case ATOM1_7_P20_11:pwm_channel_pin = &IfxGtm_ATOM1_7_TOUT67_P20_11_OUT; break;

        case ATOM2_0_P00_9: pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT18_P00_9_OUT; break;
        case ATOM2_0_P13_3: pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT94_P13_3_OUT; break;
        case ATOM2_0_P20_12:pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT68_P20_12_OUT; break;
        case ATOM2_0_P33_4: pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT26_P33_4_OUT; break;
        case ATOM2_0_P33_10:pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT32_P33_10_OUT; break;

        case ATOM2_1_P11_2: pwm_channel_pin = &IfxGtm_ATOM2_1_TOUT95_P11_2_OUT; break;
        case ATOM2_1_P20_13:pwm_channel_pin = &IfxGtm_ATOM2_1_TOUT69_P20_13_OUT; break;
        case ATOM2_1_P33_5: pwm_channel_pin = &IfxGtm_ATOM2_1_TOUT27_P33_5_OUT; break;

        case ATOM2_2_P11_3: pwm_channel_pin = &IfxGtm_ATOM2_2_TOUT96_P11_3_OUT; break;
        case ATOM2_2_P20_14:pwm_channel_pin = &IfxGtm_ATOM2_2_TOUT70_P20_14_OUT; break;
        case ATOM2_2_P33_6: pwm_channel_pin = &IfxGtm_ATOM2_2_TOUT28_P33_6_OUT; break;

        case ATOM2_3_P00_12:pwm_channel_pin = &IfxGtm_ATOM2_3_TOUT21_P00_12_OUT; break;
        case ATOM2_3_P11_6: pwm_channel_pin = &IfxGtm_ATOM2_3_TOUT97_P11_6_OUT; break;
        case ATOM2_3_P15_0: pwm_channel_pin = &IfxGtm_ATOM2_3_TOUT71_P15_0_OUT; break;
        case ATOM2_3_P33_7: pwm_channel_pin = &IfxGtm_ATOM2_3_TOUT29_P33_7_OUT; break;

        case ATOM2_4_P11_9: pwm_channel_pin = &IfxGtm_ATOM2_4_TOUT98_P11_9_OUT; break;
        case ATOM2_4_P15_1: pwm_channel_pin = &IfxGtm_ATOM2_4_TOUT72_P15_1_OUT; break;
        case ATOM2_4_P33_8: pwm_channel_pin = &IfxGtm_ATOM2_4_TOUT30_P33_8_OUT; break;
        case ATOM2_4_P33_12:pwm_channel_pin = &IfxGtm_ATOM2_4_TOUT34_P33_12_OUT; break;

        case ATOM2_5_P11_10:pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT99_P11_10_OUT; break;
        case ATOM2_5_P13_0: pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT91_P13_0_OUT; break;
        case ATOM2_5_P15_2: pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT73_P15_2_OUT; break;
        case ATOM2_5_P20_9: pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT65_P20_9_OUT; break;
        case ATOM2_5_P33_13:pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT35_P33_13_OUT; break;

        case ATOM2_6_P11_11:pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT100_P11_11_OUT; break;
        case ATOM2_6_P13_1: pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT92_P13_1_OUT; break;
        case ATOM2_6_P15_3: pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT74_P15_3_OUT; break;
        case ATOM2_6_P20_6: pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT62_P20_6_OUT; break;
        case ATOM2_6_P20_10:pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT66_P20_10_OUT; break;
        case ATOM2_6_P32_0: pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT36_P32_0_OUT; break;

        case ATOM2_7_P11_12:pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT101_P11_12_OUT; break;
        case ATOM2_7_P13_2: pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT93_P13_2_OUT; break;
        case ATOM2_7_P15_4: pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT75_P15_4_OUT; break;
        case ATOM2_7_P20_7: pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT63_P20_7_OUT; break;
        case ATOM2_7_P20_8: pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT64_P20_8_OUT; break;
        case ATOM2_7_P20_11:pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT67_P20_11_OUT; break;

        case ATOM3_0_P00_9: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT18_P00_9_OUT; break;
        case ATOM3_0_P13_3: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT94_P13_3_OUT; break;
        case ATOM3_0_P14_5: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT85_P14_5_OUT; break;
        case ATOM3_0_P15_5: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT76_P15_5_OUT; break;
        case ATOM3_0_P15_6: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT77_P15_6_OUT; break;
        case ATOM3_0_P33_4: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT26_P33_4_OUT; break;
        case ATOM3_0_P33_10:pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT32_P33_10_OUT; break;

        case ATOM3_1_P11_2: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT95_P11_2_OUT; break;
        case ATOM3_1_P14_4: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT84_P14_4_OUT; break;
        case ATOM3_1_P14_6: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT86_P14_6_OUT; break;
        case ATOM3_1_P15_7: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT78_P15_7_OUT; break;
        case ATOM3_1_P15_8: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT79_P15_8_OUT; break;
        case ATOM3_1_P33_5: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT27_P33_5_OUT; break;

        case ATOM3_2_P11_3: pwm_channel_pin = &IfxGtm_ATOM3_2_TOUT96_P11_3_OUT; break;
        case ATOM3_2_P14_0: pwm_channel_pin = &IfxGtm_ATOM3_2_TOUT80_P14_0_OUT; break;
        case ATOM3_2_P14_3: pwm_channel_pin = &IfxGtm_ATOM3_2_TOUT83_P14_3_OUT; break;
        case ATOM3_2_P33_6: pwm_channel_pin = &IfxGtm_ATOM3_2_TOUT28_P33_6_OUT; break;

        case ATOM3_3_P00_12:pwm_channel_pin = &IfxGtm_ATOM3_3_TOUT21_P00_12_OUT; break;
        case ATOM3_3_P11_6: pwm_channel_pin = &IfxGtm_ATOM3_3_TOUT97_P11_6_OUT; break;
        case ATOM3_3_P14_2: pwm_channel_pin = &IfxGtm_ATOM3_3_TOUT82_P14_2_OUT; break;
        case ATOM3_3_P33_7: pwm_channel_pin = &IfxGtm_ATOM3_3_TOUT29_P33_7_OUT; break;

        case ATOM3_4_P11_9: pwm_channel_pin = &IfxGtm_ATOM3_4_TOUT98_P11_9_OUT; break;
        case ATOM3_4_P14_1: pwm_channel_pin = &IfxGtm_ATOM3_4_TOUT81_P14_1_OUT; break;
        case ATOM3_4_P33_8: pwm_channel_pin = &IfxGtm_ATOM3_4_TOUT30_P33_8_OUT; break;
        case ATOM3_4_P33_12:pwm_channel_pin = &IfxGtm_ATOM3_4_TOUT34_P33_12_OUT; break;

        case ATOM3_5_P11_10:pwm_channel_pin = &IfxGtm_ATOM3_5_TOUT99_P11_10_OUT; break;
        case ATOM3_5_P13_0: pwm_channel_pin = &IfxGtm_ATOM3_5_TOUT91_P13_0_OUT; break;
        case ATOM3_5_P33_13: pwm_channel_pin = &IfxGtm_ATOM3_5_TOUT35_P33_13_OUT; break;

        case ATOM3_6_P11_11:pwm_channel_pin = &IfxGtm_ATOM3_6_TOUT100_P11_11_OUT; break;
        case ATOM3_6_P13_1: pwm_channel_pin = &IfxGtm_ATOM3_6_TOUT92_P13_1_OUT; break;
        case ATOM3_6_P20_6: pwm_channel_pin = &IfxGtm_ATOM3_6_TOUT62_P20_6_OUT; break;
        case ATOM3_6_P32_0: pwm_channel_pin = &IfxGtm_ATOM3_6_TOUT36_P32_0_OUT; break;

        case ATOM3_7_P11_12:pwm_channel_pin = &IfxGtm_ATOM3_7_TOUT101_P11_12_OUT; break;
        case ATOM3_7_P13_2: pwm_channel_pin = &IfxGtm_ATOM3_7_TOUT93_P13_2_OUT; break;
        case ATOM3_7_P20_7: pwm_channel_pin = &IfxGtm_ATOM3_7_TOUT63_P20_7_OUT; break;
    }

    switch(pwm_channel_pin->atom)
    {
        case 0: IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, duty <= PWM_DUTY_MAX); break;
        case 1: IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, duty <= PWM_DUTY_MAX); break;
        case 2: IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, duty <= PWM_DUTY_MAX); break;
        case 3: IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, duty <= PWM_DUTY_MAX); break;
    }

    if(!GtmInitFlag)
    {
        GtmInitFlag=1;
        IfxGtm_enable(&MODULE_GTM);
        IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, CLK_FREQ);
        IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);
    }

    IfxGtm_Atom_Pwm_initConfig(&g_atomConfig, &MODULE_GTM);
    g_atomConfig.atom = pwm_channel_pin->atom;
    g_atomConfig.atomChannel = pwm_channel_pin->channel;
    g_atomConfig.period = CLK_FREQ/frequency;
    g_atomConfig.pin.outputPin = pwm_channel_pin;
    g_atomConfig.dutyCycle = (unsigned int)((unsigned long)duty * g_atomConfig.period / MAX_DUTY);
    g_atomConfig.synchronousUpdateEnabled = TRUE;

    IfxGtm_Atom_Pwm_init(&g_atomDriver, &g_atomConfig);
    IfxGtm_Atom_Pwm_start(&g_atomDriver, TRUE);
}

/**
*
* @brief    设置输出占空比
* @param    PWM_pin_enum        PWM引脚
* @param    duty                PWM占空比
* @return   void
* @notes    duty最大值为10000即占空比100%
* Example:  set_duty_pwm(ATOM0_7_P20_8, 2000);  // 使引脚P20_8占空比变为20%(2000/MAX_DUTY)
*
**/
void set_duty_pwm(PWM_pin_enum pwmpin, unsigned int duty)
{
    IfxGtm_Atom_ToutMap* pwm_channel_pin;

    switch(pwmpin)
    {
        case ATOM0_0_P00_0: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT9_P00_0_OUT; break;
        case ATOM0_0_P02_0: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT0_P02_0_OUT; break;
        case ATOM0_0_P02_8: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT8_P02_8_OUT; break;
        case ATOM0_0_P14_5: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT85_P14_5_OUT; break;
        case ATOM0_0_P21_2: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT53_P21_2_OUT; break;
        case ATOM0_0_P22_1: pwm_channel_pin = &IfxGtm_ATOM0_0_TOUT48_P22_1_OUT; break;

        case ATOM0_1_P00_1: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT10_P00_1_OUT; break;
        case ATOM0_1_P00_2: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT11_P00_2_OUT; break;
        case ATOM0_1_P02_1: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT1_P02_1_OUT; break;
        case ATOM0_1_P10_1: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT103_P10_1_OUT; break;
        case ATOM0_1_P14_4: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT84_P14_4_OUT; break;
        case ATOM0_1_P21_3: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT54_P21_3_OUT; break;
        case ATOM0_1_P22_0: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT47_P22_0_OUT; break;
        case ATOM0_1_P33_9: pwm_channel_pin = &IfxGtm_ATOM0_1_TOUT31_P33_9_OUT; break;

        case ATOM0_2_P00_3: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT12_P00_3_OUT; break;
        case ATOM0_2_P02_2: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT2_P02_2_OUT; break;
        case ATOM0_2_P10_2: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT104_P10_2_OUT; break;
        case ATOM0_2_P10_5: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT107_P10_5_OUT; break;
        case ATOM0_2_P14_3: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT83_P14_3_OUT; break;
        case ATOM0_2_P21_4: pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT55_P21_4_OUT; break;
        case ATOM0_2_P33_11:pwm_channel_pin = &IfxGtm_ATOM0_2_TOUT33_P33_11_OUT; break;

        case ATOM0_3_P00_4: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT13_P00_4_OUT; break;
        case ATOM0_3_P02_3: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT3_P02_3_OUT; break;
        case ATOM0_3_P10_3: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT105_P10_3_OUT; break;
        case ATOM0_3_P10_6: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT108_P10_6_OUT; break;
        case ATOM0_3_P14_2: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT82_P14_2_OUT; break;
        case ATOM0_3_P21_5: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT56_P21_5_OUT; break;
        case ATOM0_3_P22_2: pwm_channel_pin = &IfxGtm_ATOM0_3_TOUT49_P22_2_OUT; break;

        case ATOM0_4_P00_5: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT14_P00_5_OUT; break;
        case ATOM0_4_P02_4: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT4_P02_4_OUT; break;
        case ATOM0_4_P14_1: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT81_P14_1_OUT; break;
        case ATOM0_4_P20_3: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT61_P20_3_OUT; break;
        case ATOM0_4_P21_6: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT57_P21_6_OUT; break;
        case ATOM0_4_P22_3: pwm_channel_pin = &IfxGtm_ATOM0_4_TOUT50_P22_3_OUT; break;

        case ATOM0_5_P00_6: pwm_channel_pin = &IfxGtm_ATOM0_5_TOUT15_P00_6_OUT; break;
        case ATOM0_5_P02_5: pwm_channel_pin = &IfxGtm_ATOM0_5_TOUT5_P02_5_OUT; break;
        case ATOM0_5_P21_7: pwm_channel_pin = &IfxGtm_ATOM0_5_TOUT58_P21_7_OUT; break;
        case ATOM0_5_P32_4: pwm_channel_pin = &IfxGtm_ATOM0_5_TOUT40_P32_4_OUT; break;

        case ATOM0_6_P00_7: pwm_channel_pin = &IfxGtm_ATOM0_6_TOUT16_P00_7_OUT; break;
        case ATOM0_6_P02_6: pwm_channel_pin = &IfxGtm_ATOM0_6_TOUT6_P02_6_OUT; break;
        case ATOM0_6_P20_0: pwm_channel_pin = &IfxGtm_ATOM0_6_TOUT59_P20_0_OUT; break;
        case ATOM0_6_P23_1: pwm_channel_pin = &IfxGtm_ATOM0_6_TOUT42_P23_1_OUT; break;

        case ATOM0_7_P00_8: pwm_channel_pin = &IfxGtm_ATOM0_7_TOUT17_P00_8_OUT; break;
        case ATOM0_7_P02_7: pwm_channel_pin = &IfxGtm_ATOM0_7_TOUT7_P02_7_OUT; break;
        case ATOM0_7_P20_8: pwm_channel_pin = &IfxGtm_ATOM0_7_TOUT64_P20_8_OUT; break;

        case ATOM1_0_P00_0: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT9_P00_0_OUT; break;
        case ATOM1_0_P02_0: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT0_P02_0_OUT; break;
        case ATOM1_0_P02_8: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT8_P02_8_OUT; break;
        case ATOM1_0_P15_5: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT76_P15_5_OUT; break;
        case ATOM1_0_P15_6: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT77_P15_6_OUT; break;
        case ATOM1_0_P20_12:pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT68_P20_12_OUT; break;
        case ATOM1_0_P21_2: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT53_P21_2_OUT; break;
        case ATOM1_0_P22_1: pwm_channel_pin = &IfxGtm_ATOM1_0_TOUT48_P22_1_OUT; break;

        case ATOM1_1_P00_1: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT10_P00_1_OUT; break;
        case ATOM1_1_P00_2: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT11_P00_2_OUT; break;
        case ATOM1_1_P02_1: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT1_P02_1_OUT; break;
        case ATOM1_1_P10_1: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT103_P10_1_OUT; break;
        case ATOM1_1_P14_6: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT86_P14_6_OUT; break;
        case ATOM1_1_P15_7: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT78_P15_7_OUT; break;
        case ATOM1_1_P15_8: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT79_P15_8_OUT; break;
        case ATOM1_1_P20_13:pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT69_P20_13_OUT; break;
        case ATOM1_1_P21_3: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT54_P21_3_OUT; break;
        case ATOM1_1_P22_0: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT47_P22_0_OUT; break;
        case ATOM1_1_P33_9: pwm_channel_pin = &IfxGtm_ATOM1_1_TOUT31_P33_9_OUT; break;

        case ATOM1_2_P00_3: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT12_P00_3_OUT; break;
        case ATOM1_2_P02_2: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT2_P02_2_OUT; break;
        case ATOM1_2_P10_2: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT104_P10_2_OUT; break;
        case ATOM1_2_P10_5: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT107_P10_5_OUT; break;
        case ATOM1_2_P14_0: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT80_P14_0_OUT; break;
        case ATOM1_2_P20_14:pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT70_P20_14_OUT; break;
        case ATOM1_2_P21_4: pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT55_P21_4_OUT; break;
        case ATOM1_2_P33_11:pwm_channel_pin = &IfxGtm_ATOM1_2_TOUT33_P33_11_OUT; break;

        case ATOM1_3_P00_4: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT13_P00_4_OUT; break;
        case ATOM1_3_P02_3: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT3_P02_3_OUT; break;
        case ATOM1_3_P10_3: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT105_P10_3_OUT; break;
        case ATOM1_3_P10_6: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT108_P10_6_OUT; break;
        case ATOM1_3_P15_0: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT71_P15_0_OUT; break;
        case ATOM1_3_P21_5: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT56_P21_5_OUT; break;
        case ATOM1_3_P22_2: pwm_channel_pin = &IfxGtm_ATOM1_3_TOUT49_P22_2_OUT; break;

        case ATOM1_4_P00_5: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT14_P00_5_OUT; break;
        case ATOM1_4_P02_4: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT4_P02_4_OUT; break;
        case ATOM1_4_P15_1: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT72_P15_1_OUT; break;
        case ATOM1_4_P20_3: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT61_P20_3_OUT; break;
        case ATOM1_4_P21_6: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT57_P21_6_OUT; break;
        case ATOM1_4_P22_3: pwm_channel_pin = &IfxGtm_ATOM1_4_TOUT50_P22_3_OUT; break;

        case ATOM1_5_P00_6: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT15_P00_6_OUT; break;
        case ATOM1_5_P02_5: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT5_P02_5_OUT; break;
        case ATOM1_5_P15_2: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT73_P15_2_OUT; break;
        case ATOM1_5_P20_9: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT65_P20_9_OUT; break;
        case ATOM1_5_P21_7: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT58_P21_7_OUT; break;
        case ATOM1_5_P32_4: pwm_channel_pin = &IfxGtm_ATOM1_5_TOUT40_P32_4_OUT; break;

        case ATOM1_6_P00_7: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT16_P00_7_OUT; break;
        case ATOM1_6_P02_6: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT6_P02_6_OUT; break;
        case ATOM1_6_P15_3: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT74_P15_3_OUT; break;
        case ATOM1_6_P20_0: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT59_P20_0_OUT; break;
        case ATOM1_6_P20_10:pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT66_P20_10_OUT; break;
        case ATOM1_6_P23_1: pwm_channel_pin = &IfxGtm_ATOM1_6_TOUT42_P23_1_OUT; break;

        case ATOM1_7_P00_8: pwm_channel_pin = &IfxGtm_ATOM1_7_TOUT17_P00_8_OUT; break;
        case ATOM1_7_P02_7: pwm_channel_pin = &IfxGtm_ATOM1_7_TOUT7_P02_7_OUT; break;
        case ATOM1_7_P15_4: pwm_channel_pin = &IfxGtm_ATOM1_7_TOUT75_P15_4_OUT; break;
        case ATOM1_7_P20_11:pwm_channel_pin = &IfxGtm_ATOM1_7_TOUT67_P20_11_OUT; break;

        case ATOM2_0_P00_9: pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT18_P00_9_OUT; break;
        case ATOM2_0_P13_3: pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT94_P13_3_OUT; break;
        case ATOM2_0_P20_12:pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT68_P20_12_OUT; break;
        case ATOM2_0_P33_4: pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT26_P33_4_OUT; break;
        case ATOM2_0_P33_10:pwm_channel_pin = &IfxGtm_ATOM2_0_TOUT32_P33_10_OUT; break;

        case ATOM2_1_P11_2: pwm_channel_pin = &IfxGtm_ATOM2_1_TOUT95_P11_2_OUT; break;
        case ATOM2_1_P20_13:pwm_channel_pin = &IfxGtm_ATOM2_1_TOUT69_P20_13_OUT; break;
        case ATOM2_1_P33_5: pwm_channel_pin = &IfxGtm_ATOM2_1_TOUT27_P33_5_OUT; break;

        case ATOM2_2_P11_3: pwm_channel_pin = &IfxGtm_ATOM2_2_TOUT96_P11_3_OUT; break;
        case ATOM2_2_P20_14:pwm_channel_pin = &IfxGtm_ATOM2_2_TOUT70_P20_14_OUT; break;
        case ATOM2_2_P33_6: pwm_channel_pin = &IfxGtm_ATOM2_2_TOUT28_P33_6_OUT; break;

        case ATOM2_3_P00_12:pwm_channel_pin = &IfxGtm_ATOM2_3_TOUT21_P00_12_OUT; break;
        case ATOM2_3_P11_6: pwm_channel_pin = &IfxGtm_ATOM2_3_TOUT97_P11_6_OUT; break;
        case ATOM2_3_P15_0: pwm_channel_pin = &IfxGtm_ATOM2_3_TOUT71_P15_0_OUT; break;
        case ATOM2_3_P33_7: pwm_channel_pin = &IfxGtm_ATOM2_3_TOUT29_P33_7_OUT; break;

        case ATOM2_4_P11_9: pwm_channel_pin = &IfxGtm_ATOM2_4_TOUT98_P11_9_OUT; break;
        case ATOM2_4_P15_1: pwm_channel_pin = &IfxGtm_ATOM2_4_TOUT72_P15_1_OUT; break;
        case ATOM2_4_P33_8: pwm_channel_pin = &IfxGtm_ATOM2_4_TOUT30_P33_8_OUT; break;
        case ATOM2_4_P33_12:pwm_channel_pin = &IfxGtm_ATOM2_4_TOUT34_P33_12_OUT; break;

        case ATOM2_5_P11_10:pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT99_P11_10_OUT; break;
        case ATOM2_5_P13_0: pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT91_P13_0_OUT; break;
        case ATOM2_5_P15_2: pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT73_P15_2_OUT; break;
        case ATOM2_5_P20_9: pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT65_P20_9_OUT; break;
        case ATOM2_5_P33_13:pwm_channel_pin = &IfxGtm_ATOM2_5_TOUT35_P33_13_OUT; break;

        case ATOM2_6_P11_11:pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT100_P11_11_OUT; break;
        case ATOM2_6_P13_1: pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT92_P13_1_OUT; break;
        case ATOM2_6_P15_3: pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT74_P15_3_OUT; break;
        case ATOM2_6_P20_6: pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT62_P20_6_OUT; break;
        case ATOM2_6_P20_10:pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT66_P20_10_OUT; break;
        case ATOM2_6_P32_0: pwm_channel_pin = &IfxGtm_ATOM2_6_TOUT36_P32_0_OUT; break;

        case ATOM2_7_P11_12:pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT101_P11_12_OUT; break;
        case ATOM2_7_P13_2: pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT93_P13_2_OUT; break;
        case ATOM2_7_P15_4: pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT75_P15_4_OUT; break;
        case ATOM2_7_P20_7: pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT63_P20_7_OUT; break;
        case ATOM2_7_P20_8: pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT64_P20_8_OUT; break;
        case ATOM2_7_P20_11:pwm_channel_pin = &IfxGtm_ATOM2_7_TOUT67_P20_11_OUT; break;

        case ATOM3_0_P00_9: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT18_P00_9_OUT; break;
        case ATOM3_0_P13_3: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT94_P13_3_OUT; break;
        case ATOM3_0_P14_5: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT85_P14_5_OUT; break;
        case ATOM3_0_P15_5: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT76_P15_5_OUT; break;
        case ATOM3_0_P15_6: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT77_P15_6_OUT; break;
        case ATOM3_0_P33_4: pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT26_P33_4_OUT; break;
        case ATOM3_0_P33_10:pwm_channel_pin = &IfxGtm_ATOM3_0_TOUT32_P33_10_OUT; break;

        case ATOM3_1_P11_2: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT95_P11_2_OUT; break;
        case ATOM3_1_P14_4: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT84_P14_4_OUT; break;
        case ATOM3_1_P14_6: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT86_P14_6_OUT; break;
        case ATOM3_1_P15_7: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT78_P15_7_OUT; break;
        case ATOM3_1_P15_8: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT79_P15_8_OUT; break;
        case ATOM3_1_P33_5: pwm_channel_pin = &IfxGtm_ATOM3_1_TOUT27_P33_5_OUT; break;

        case ATOM3_2_P11_3: pwm_channel_pin = &IfxGtm_ATOM3_2_TOUT96_P11_3_OUT; break;
        case ATOM3_2_P14_0: pwm_channel_pin = &IfxGtm_ATOM3_2_TOUT80_P14_0_OUT; break;
        case ATOM3_2_P14_3: pwm_channel_pin = &IfxGtm_ATOM3_2_TOUT83_P14_3_OUT; break;
        case ATOM3_2_P33_6: pwm_channel_pin = &IfxGtm_ATOM3_2_TOUT28_P33_6_OUT; break;

        case ATOM3_3_P00_12:pwm_channel_pin = &IfxGtm_ATOM3_3_TOUT21_P00_12_OUT; break;
        case ATOM3_3_P11_6: pwm_channel_pin = &IfxGtm_ATOM3_3_TOUT97_P11_6_OUT; break;
        case ATOM3_3_P14_2: pwm_channel_pin = &IfxGtm_ATOM3_3_TOUT82_P14_2_OUT; break;
        case ATOM3_3_P33_7: pwm_channel_pin = &IfxGtm_ATOM3_3_TOUT29_P33_7_OUT; break;

        case ATOM3_4_P11_9: pwm_channel_pin = &IfxGtm_ATOM3_4_TOUT98_P11_9_OUT; break;
        case ATOM3_4_P14_1: pwm_channel_pin = &IfxGtm_ATOM3_4_TOUT81_P14_1_OUT; break;
        case ATOM3_4_P33_8: pwm_channel_pin = &IfxGtm_ATOM3_4_TOUT30_P33_8_OUT; break;
        case ATOM3_4_P33_12:pwm_channel_pin = &IfxGtm_ATOM3_4_TOUT34_P33_12_OUT; break;

        case ATOM3_5_P11_10:pwm_channel_pin = &IfxGtm_ATOM3_5_TOUT99_P11_10_OUT; break;
        case ATOM3_5_P13_0: pwm_channel_pin = &IfxGtm_ATOM3_5_TOUT91_P13_0_OUT; break;
        case ATOM3_5_P33_13:pwm_channel_pin = &IfxGtm_ATOM3_5_TOUT35_P33_13_OUT; break;

        case ATOM3_6_P11_11:pwm_channel_pin = &IfxGtm_ATOM3_6_TOUT100_P11_11_OUT; break;
        case ATOM3_6_P13_1: pwm_channel_pin = &IfxGtm_ATOM3_6_TOUT92_P13_1_OUT; break;
        case ATOM3_6_P20_6: pwm_channel_pin = &IfxGtm_ATOM3_6_TOUT62_P20_6_OUT; break;
        case ATOM3_6_P32_0: pwm_channel_pin = &IfxGtm_ATOM3_6_TOUT36_P32_0_OUT; break;

        case ATOM3_7_P11_12:pwm_channel_pin = &IfxGtm_ATOM3_7_TOUT101_P11_12_OUT; break;
        case ATOM3_7_P13_2: pwm_channel_pin = &IfxGtm_ATOM3_7_TOUT93_P13_2_OUT; break;
        case ATOM3_7_P20_7: pwm_channel_pin = &IfxGtm_ATOM3_7_TOUT63_P20_7_OUT; break;
    }
    unsigned int period = IfxGtm_Atom_Ch_getCompareZero(&MODULE_GTM.ATOM[pwm_channel_pin->atom], pwm_channel_pin->channel);
    duty = (unsigned int)((unsigned long)duty * period / MAX_DUTY);
    IfxGtm_Atom_Ch_setCompareOneShadow(&MODULE_GTM.ATOM[pwm_channel_pin->atom], pwm_channel_pin->channel, duty);
}
