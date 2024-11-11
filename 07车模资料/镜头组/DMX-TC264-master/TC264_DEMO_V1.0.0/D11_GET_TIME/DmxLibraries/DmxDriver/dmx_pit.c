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
 * @file       dmx_pit.c
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

#include "dmx_pit.h"
#include "dmx_isr.h"
#include <Bsp.h>
#include <IfxCcu6.h>
#include <IfxCcu6_Timer.h>
#include <IfxCpu.h>
#include <IfxCpu_Irq.h>

IFX_INTERRUPT(CCU60_CH0_PIT_IRQ, CCU60_PIT_VECTABNUM, CCU60_CH0_PIT_PRIORITY);
IFX_INTERRUPT(CCU60_CH1_PIT_IRQ, CCU60_PIT_VECTABNUM, CCU60_CH1_PIT_PRIORITY);
IFX_INTERRUPT(CCU61_CH0_PIT_IRQ, CCU61_PIT_VECTABNUM, CCU61_CH0_PIT_PRIORITY);
IFX_INTERRUPT(CCU61_CH1_PIT_IRQ, CCU61_PIT_VECTABNUM, CCU61_CH1_PIT_PRIORITY);

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
void init_pit(CCU6_enum ccu6, CCU6_ch_enum channel, unsigned long time)
{
    boolean interruptState = IfxCpu_disableInterrupts();
    Ifx_CCU6 * module = IfxCcu6_getAddress((IfxCcu6_Index) ccu6);
    IfxCcu6_Timer_Config timerConfig;
    IfxCcu6_Timer_initModuleConfig(&timerConfig, module);

    unsigned long long clk = IfxScuCcu_getSpbFrequency();
    unsigned long period = 0;
    for(unsigned char i = 0;i < 16;i++)
    {
        period = (unsigned long) (clk * time / 1000000);
        if (period < 0xffff)
            break;
        else
            clk /= 2;
    }

    switch(ccu6 * 2 + channel)
    {
        case 0:
            timerConfig.interrupt1.typeOfService = CCU60_PIT_VECTABNUM;
            timerConfig.interrupt1.priority = CCU60_CH0_PIT_PRIORITY;
            IfxCpu_Irq_installInterruptHandler(CCU60_CH0_PIT_IRQ, CCU60_CH0_PIT_PRIORITY);
            break;
        case 1:
            timerConfig.interrupt2.typeOfService = CCU60_PIT_VECTABNUM;
            timerConfig.interrupt2.priority = CCU60_CH1_PIT_PRIORITY;
            IfxCpu_Irq_installInterruptHandler(CCU60_CH1_PIT_IRQ, CCU60_CH1_PIT_PRIORITY);
            break;
        case 2:
            timerConfig.interrupt1.typeOfService = CCU61_PIT_VECTABNUM;
            timerConfig.interrupt1.priority = CCU61_CH0_PIT_PRIORITY;
            IfxCpu_Irq_installInterruptHandler(CCU61_CH0_PIT_IRQ, CCU61_CH0_PIT_PRIORITY);
            break;
        case 3:
            timerConfig.interrupt2.typeOfService = CCU61_PIT_VECTABNUM;
            timerConfig.interrupt2.priority = CCU61_CH1_PIT_PRIORITY;
            IfxCpu_Irq_installInterruptHandler(CCU61_CH1_PIT_IRQ, CCU61_CH1_PIT_PRIORITY);
            break;
    }

    switch (channel)
    {
        case CH0 :
            timerConfig.timer = IfxCcu6_TimerId_t12;
            timerConfig.interrupt1.source = IfxCcu6_InterruptSource_t12PeriodMatch;
            timerConfig.interrupt1.serviceRequest = IfxCcu6_ServiceRequest_1;
            timerConfig.base.t12Frequency = (float) clk;
            timerConfig.base.t12Period = period;
            timerConfig.clock.t12countingInputMode = IfxCcu6_CountingInputMode_internal;
            timerConfig.timer12.counterValue = 0;
            break;
        case CH1 :
            timerConfig.timer = IfxCcu6_TimerId_t13;
            timerConfig.interrupt2.source = IfxCcu6_InterruptSource_t13PeriodMatch;
            timerConfig.interrupt2.serviceRequest = IfxCcu6_ServiceRequest_2;
            timerConfig.base.t13Frequency = (float) clk;
            timerConfig.base.t13Period = period;
            timerConfig.clock.t13countingInputMode = IfxCcu6_CountingInputMode_internal;
            timerConfig.timer13.counterValue = 0;
            break;
    }
    timerConfig.trigger.t13InSyncWithT12 = FALSE;

    IfxCcu6_Timer g_Ccu6Timer;
    IfxCcu6_Timer_initModule(&g_Ccu6Timer, &timerConfig);
    IfxCpu_restoreInterrupts(interruptState);

    IfxCcu6_Timer_start(&g_Ccu6Timer);
}

/**
*
* @brief    定时器中断使能
* @param    ccu6        选择CCU6模块(CCU60,CCU61)
* @param    channel     选择通道(CH0,CH1)
* @return   void
* @notes
* Example:  enable_pit(CCU60, CH0); // 开启CCU60模块通道0的中断
*
**/
void enable_pit(CCU6_enum ccu6, CCU6_ch_enum channel)
{
    Ifx_CCU6 * module = IfxCcu6_getAddress((IfxCcu6_Index) ccu6);
    IfxCcu6_clearInterruptStatusFlag(module, (IfxCcu6_InterruptSource) (7 + channel * 2));
    IfxCcu6_enableInterrupt(module, (IfxCcu6_InterruptSource) (7 + channel * 2));
}

/**
*
* @brief    定时器中断禁止
* @param    ccu6        选择CCU6模块(CCU60,CCU61)
* @param    channel     选择通道(CH0,CH1)
* @return   void
* @notes
* Example:  disable_pit(CCU60, CH0);    //关闭CCU60模块通道0的中断
*
**/
void disable_pit(CCU6_enum ccu6, CCU6_ch_enum channel)
{
    Ifx_CCU6 * module = IfxCcu6_getAddress((IfxCcu6_Index) ccu6);
    IfxCcu6_clearInterruptStatusFlag(module, (IfxCcu6_InterruptSource) (7 + channel * 2));
    IfxCcu6_disableInterrupt(module, (IfxCcu6_InterruptSource) (7 + channel * 2));
}

/**
*
* @brief    CCU6中断服务函数示例
* @param
* @return
* @notes
* Example:
*
**/
void CCU60_CH0_PIT_IRQ (void)
{
    IfxCpu_enableInterrupts();
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU60, IfxCcu6_InterruptSource_t12PeriodMatch);
    ccu60_ch0_irq();
}

void CCU60_CH1_PIT_IRQ (void)
{
    IfxCpu_enableInterrupts();
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU60, IfxCcu6_InterruptSource_t13PeriodMatch);
    ccu60_ch1_irq();
}

void CCU61_CH0_PIT_IRQ (void)
{
    IfxCpu_enableInterrupts();
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU61, IfxCcu6_InterruptSource_t12PeriodMatch);
    ccu61_ch0_irq();
}

void CCU61_CH1_PIT_IRQ (void)
{
    IfxCpu_enableInterrupts();
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU61, IfxCcu6_InterruptSource_t13PeriodMatch);
    ccu61_ch1_irq();
}
