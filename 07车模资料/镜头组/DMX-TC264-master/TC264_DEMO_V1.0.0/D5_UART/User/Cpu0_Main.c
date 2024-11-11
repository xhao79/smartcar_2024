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
* UART相关文件在该项目下的 -> DmxLibraries -> DmxDriver -> dmx_uart.c和dmx_uart.h中
* UART中断调用文件在该项目下的 -> User -> Dmx_Isr.c和Dmx_Isr.h中
* 该例程为UART控制,具体体现为串口助手接收"串口0初始化完成"后发送变量uart_data每隔500ms加1
！！！！！！！！**/

int uart_data = 0;
char buff[4];

void core0_main(void)
{
    // 初始化芯片
    init_chip();
    // 放置用户代码段

    // 初始化串口0,TX引脚为P14_0,RX引脚为P14_1,波特率为115200
    init_uart(TX0_P14_0,RX0_P14_1, 115200);
    // 发送串口0初始化完成字符串
    set_string_uart(UART0,"串口0初始化完成！\r\n");

    // 等待双核全部完成初始化
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // 中断使能
    IfxCpu_enableInterrupts();
    while(1)
    {
        // UART中断调用在该项目下的 -> User -> Dmx_Isr.c中
        // 变量转字符串
        sprintf(buff,"uart_data:%d\r\n",uart_data++);
        // 串口发送该字符串
        set_string_uart(UART0,buff);
        // STM0模块延时500ms
        Delay_ms(STM0,500);
    }
}

#pragma section all restore
