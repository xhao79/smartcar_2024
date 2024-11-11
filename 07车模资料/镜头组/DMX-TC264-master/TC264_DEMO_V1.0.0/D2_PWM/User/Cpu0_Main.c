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
 * @file       Cpu0_Main.c
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

#include "dmx_all.h"
#include "dmx_isr.h"

#pragma section all "cpu0_dsram"

/** ！！！！！！！！
* PWM相关文件在该项目下的 -> DmxLibraries -> DmxDriver -> dmx_pwm.c和dmx_pwm.h中
* 该例程为PWM控制,具体体现为核心板上四个LED呈现呼吸灯效果
！！！！！！！！**/

int led_pwm = 0;
unsigned char led_dir = 0;

void core0_main(void)
{
    // 初始化芯片
    init_chip();
    // 放置用户代码段

    // 初始化P20_8引脚为PWM,频率为2KHZ,初始占空比为0
    init_pwm(ATOM2_7_P20_8, 2000, 0);
    // 初始化P20_9引脚为PWM,频率为2KHZ,初始占空比为0
    init_pwm(ATOM2_5_P20_9, 2000, 0);
    // 初始化P21_4引脚为PWM,频率为2KHZ,初始占空比为0
    init_pwm(ATOM1_2_P21_4, 2000, 0);
    // 初始化P21_5引脚为PWM,频率为2KHZ,初始占空比为0
    init_pwm(ATOM1_3_P21_5, 2000, 0);

    // 等待双核全部完成初始化
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // 中断使能
    IfxCpu_enableInterrupts();
    while(1)
    {
        // LED呼吸状态
        if(!led_dir)
        {
            // LED的PWM值,具体体现为亮度,PWM越大越接近于高电平即越暗(本核心板上LED为低电平点亮)
            led_pwm += 50;
            // 达到最大占空比,切换呼吸状态
            if(led_pwm >= 10000)
                led_dir =!led_dir;
        }
        else
        {
            // LED的PWM值,具体体现为亮度,PWM越小越接近于低电平即越亮(本核心板上LED为低电平点亮)
            led_pwm -= 50;
            // 达到最小占空比,切换呼吸状态
            if(led_pwm <= 0)
                led_dir =!led_dir;
        }

        // P20_8发送新的占空比led_pwm
        set_duty_pwm(ATOM2_7_P20_8, led_pwm);
        // P20_9发送新的占空比(10000 - led_pwm)
        set_duty_pwm(ATOM2_5_P20_9, 10000 - led_pwm);
        // P21_4发送新的占空比led_pwm
        set_duty_pwm(ATOM1_2_P21_4, led_pwm);
        // P21_5发送新的占空比(10000 - led_pwm)
        set_duty_pwm(ATOM1_3_P21_5, 10000 - led_pwm);

        // STM0模块延时10ms
        Delay_ms(STM0,10);
    }
}

#pragma section all restore
