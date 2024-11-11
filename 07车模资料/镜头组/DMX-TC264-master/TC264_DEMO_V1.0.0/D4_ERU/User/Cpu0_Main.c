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
* ERU相关文件在该项目下的 -> DmxLibraries -> DmxDriver -> dmx_eru.c和dmx_eru.h中
* ERU中断调用文件在该项目下的 -> User -> Dmx_Isr.c和Dmx_Isr.h中
* 该例程为ERU控制,具体体现为核心板通电后使外部中断通道0的P15_4引脚接GND(给下降沿信号),P20_8引脚LED点亮
！！！！！！！！**/

void core0_main(void)
{
    // 初始化芯片
    init_chip();
    // 放置用户代码段

    // 初始化外部中断通道0,使用P15_4引脚,下降沿触发中断
    init_eru(EruP15_4, FALLING);

    // 等待双核全部完成初始化
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // 中断使能
    IfxCpu_enableInterrupts();
    while(1)
    {
        // ERU中断调用在该项目下的 -> User -> Dmx_Isr.c中
    }
}

#pragma section all restore
