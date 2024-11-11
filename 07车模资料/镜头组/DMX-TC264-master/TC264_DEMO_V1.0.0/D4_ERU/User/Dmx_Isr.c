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
 * @file       dmx_isr.c
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

// 定时器中断
void ccu60_ch0_irq(void)
{

}
void ccu60_ch1_irq(void)
{

}
void ccu61_ch0_irq(void)
{

}
void ccu61_ch1_irq(void)
{

}

// 外部中断
void eru_ch0_4_irq(void)
{
    // 初始化P20_8引脚,推挽输出,低电平,点亮状态
    init_gpio(P20 , 8 , OutputPUSHPULL , 0);
}

void eru_ch1_5_irq(void)
{

}

void eru_ch2_6_irq(void)
{

}

// 串口中断
void rx0_irq(void)
{
    set_char_uart(UART0, get_char_uart(UART0));
}
void tx0_irq(void)
{

}
void er0_irq(void)
{

}

void rx1_irq(void)
{
    set_char_uart(UART1, get_char_uart(UART1));
}
void tx1_irq(void)
{

}
void er1_irq(void)
{

}

void rx2_irq(void)
{
    set_char_uart(UART2, get_char_uart(UART2));
}
void tx2_irq(void)
{

}
void er2_irq(void)
{

}

void rx3_irq(void)
{
    set_char_uart(UART3, get_char_uart(UART3));
}
void tx3_irq(void)
{

}
void er3_irq(void)
{

}
