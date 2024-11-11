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
 * @file       Cpu1_Main.c
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
#include "Cpu0_Main.h"
#include "dmx_isr.h"

#pragma section all "cpu1_dsram"

/** ！！！！！！！！
* 该例程为CPU1的使用,CPU1直接使用即可
* CPU1的main函数文件在该项目下的 -> User -> Cpu1_Mian.c中
* 注意:CPU0和CPU1不可同时调用同一个资源(外设和变量)！！！！！！！！
！！！！！！！！**/

void core1_main(void)
{
    // 关闭看门狗和中断使能
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    IfxCpu_enableInterrupts();
    // 放置用户代码段

    // 初始化P20_8引脚,推挽输出,高电平,熄灭状态
    init_gpio(P20 , 8 , OutputPUSHPULL , 1);
    // 初始化P20_9引脚,推挽输出,高电平,熄灭状态
    init_gpio(P20 , 9 , OutputPUSHPULL , 1);
    // 初始化P21_4引脚,推挽输出,高电平,熄灭状态
    init_gpio(P21 , 4 , OutputPUSHPULL , 1);
    // 初始化P21_5引脚,推挽输出,高电平,熄灭状态
    init_gpio(P21 , 5 , OutputPUSHPULL , 1);

    // 等待双核全部完成初始化
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);

    while(1)
    {
        // P20_8引脚输出低电平,点亮状态
        set_level_gpio(P20 ,8 , 0);
        // STM0模块延时100ms
        Delay_ms(STM0,100);
        // P20_8引脚电平反转,熄灭状态
        toggle_level_gpio(P20 ,8);

        // P20_9引脚输出低电平,点亮状态
        set_level_gpio(P20 ,9 , 0);
        // STM0模块延时100ms
        Delay_ms(STM0,100);
        // P20_9引脚电平反转,熄灭状态
        toggle_level_gpio(P20 ,9);

        // P21_4引脚输出低电平,点亮状态
        set_level_gpio(P21 ,4 , 0);
        // STM0模块延时100ms
        Delay_ms(STM0,100);
        // P20_9引脚电平反转,熄灭状态
        toggle_level_gpio(P21 ,4);

        // P21_5引脚输出低电平,点亮状态
        set_level_gpio(P21 ,5 , 0);
        // STM0模块延时100ms
        Delay_ms(STM0,100);
        // P21_5引脚电平反转,熄灭状态
        toggle_level_gpio(P21 ,5);
    }
}

#pragma section all restore
