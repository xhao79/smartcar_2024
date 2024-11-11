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
 * @file       dmx_eru.c
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

#include "dmx_eru.h"
#include "dmx_dma.h"
#include "dmx_gpio.h"
#include "dmx_mt9v034.h"
#include "dmx_isr.h"
#include "Bsp.h"
#include "IfxScuEru.h"
#include "IfxCpu_Irq.h"

IFX_INTERRUPT(ERU_CH0_4_IRQ, ERU_CH0_4_INT_VECTABNUM, ERU_CH0_4_INT_PRIORITY);
IFX_INTERRUPT(ERU_CH1_5_IRQ, ERU_CH1_5_INT_VECTABNUM, ERU_CH1_5_INT_PRIORITY);
IFX_INTERRUPT(ERU_CH2_6_IRQ, ERU_CH2_6_INT_VECTABNUM, ERU_CH2_6_INT_PRIORITY);
IFX_INTERRUPT(ERU_CH3_7_IRQ, ERU_CH3_7_INT_VECTABNUM, ERU_CH3_7_INT_PRIORITY);

/**
*
* @brief    gpio外部中断初始化
* @param    erupin      设置gpio外部中断引脚
* @param    mode        设置触发方式
* @return   void
* @notes    TC264只有15个固定的GPIO引脚支持外部中断,这15个引脚分为8个通道,其中
*           通道0和通道4共用一个中断,通道1和通道5共用一个中断,通道2和通道6共用一个中断,通道3和通道7共用一个中断
* Example:  init_eru(P15_4, RISING);    // 外部中断通道0,使用P15_4引脚,上升沿触发中断
*
**/
void init_eru(ERU_pin_enum erupin, ERU_mode_enum mode)
{
    boolean interruptState = IfxCpu_disableInterrupts();

    IfxScu_Req_In *reqPin;

    switch(erupin)
    {
        case EruP15_4: reqPin= &IfxScu_REQ0_P15_4_IN;break;

        case EruP14_3: reqPin= &IfxScu_REQ10_P14_3_IN;break;

        case EruP00_4: reqPin= &IfxScu_REQ7_P00_4_IN;break;
        case EruP02_1: reqPin= &IfxScu_REQ14_P02_1_IN;break;
        case EruP10_2: reqPin= &IfxScu_REQ2_P10_2_IN;break;

        case EruP02_0:  reqPin= &IfxScu_REQ6_P02_0_IN;break;
        case EruP10_3:  reqPin= &IfxScu_REQ3_P10_3_IN;break;
        case EruP14_1: reqPin= &IfxScu_REQ15_P14_1_IN;break;

        case EruP15_5: reqPin= &IfxScu_REQ13_P15_5_IN;break;
        case EruP33_7: reqPin= &IfxScu_REQ8_P33_7_IN;break;

        case EruP15_8: reqPin= &IfxScu_REQ1_P15_8_IN;break;

        case EruP11_10: reqPin= &IfxScu_REQ12_P11_10_IN;break;
        case EruP20_0: reqPin= &IfxScu_REQ9_P20_0_IN;break;

        case EruP15_1: reqPin= &IfxScu_REQ16_P15_1_IN;break;
        case EruP20_9: reqPin= &IfxScu_REQ11_P20_9_IN;break;

        default:break;
    }

    IfxScuEru_initReqPin(reqPin, IfxPort_InputMode_pullUp);

    IfxScuEru_InputChannel inputChannel = (IfxScuEru_InputChannel)reqPin->channelId;

    switch (mode)
    {
        case RISING:
            {
                IfxScuEru_disableFallingEdgeDetection(inputChannel);
                IfxScuEru_enableRisingEdgeDetection(inputChannel);
            }
            break;

        case FALLING:
            {
                IfxScuEru_enableFallingEdgeDetection(inputChannel);
                IfxScuEru_disableRisingEdgeDetection(inputChannel);
            }
            break;

        case BOTH:
            {
                IfxScuEru_enableFallingEdgeDetection(inputChannel);
                IfxScuEru_enableRisingEdgeDetection(inputChannel);
            }
            break;
    }
    IfxScuEru_enableAutoClear(inputChannel);

    IfxScuEru_InputNodePointer triggerSelect = (IfxScuEru_InputNodePointer)(erupin/3);
    IfxScuEru_OutputChannel    outputChannel = (IfxScuEru_OutputChannel)(erupin/3);

    IfxScuEru_enableTriggerPulse(inputChannel);
    IfxScuEru_connectTrigger(inputChannel, triggerSelect);

    IfxScuEru_setFlagPatternDetection(outputChannel, inputChannel, FALSE);
    IfxScuEru_enablePatternDetectionTrigger(outputChannel);
    IfxScuEru_setInterruptGatingPattern(outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);

    IfxSrc_Tos vectabNum;
    unsigned char Priority;
    switch((erupin/3)%4)
    {
        case 0:
            vectabNum   = ERU_CH0_4_INT_VECTABNUM;
            Priority    = ERU_CH0_4_INT_PRIORITY;

            IfxCpu_Irq_installInterruptHandler(ERU_CH0_4_IRQ, Priority);
            break;

        case 1:
            vectabNum   = ERU_CH1_5_INT_VECTABNUM;
            Priority    = ERU_CH1_5_INT_PRIORITY;

            IfxCpu_Irq_installInterruptHandler(ERU_CH1_5_IRQ, Priority);
            break;

        case 2:
            vectabNum   = ERU_CH2_6_INT_VECTABNUM;
            Priority    = ERU_CH2_6_INT_PRIORITY;

            IfxCpu_Irq_installInterruptHandler(ERU_CH2_6_IRQ, Priority);
            break;

        case 3:
            vectabNum   = ERU_CH3_7_INT_VECTABNUM;
            Priority    = ERU_CH3_7_INT_PRIORITY;

            IfxCpu_Irq_installInterruptHandler(ERU_CH3_7_IRQ, Priority);
            break;
    }

    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)(outputChannel)%4];
    IfxSrc_init(src, vectabNum, Priority);
    IfxSrc_enable(src);

    IfxCpu_restoreInterrupts(interruptState);
}

/**
*
* @brief    开启gpio外部中断
* @param    erupin     设置gpio外部中断引脚
* @return   void
* @notes
* Example:  enable_eru(P15_4);  // P15_4引脚gpio外部中断开启
*
**/
void enable_eru(ERU_pin_enum erupin)
{
    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)((IfxScuEru_OutputChannel)(erupin/3)) % 4];
    IfxSrc_enable(src);
}

/**
*
* @brief    关闭gpio外部中断
* @param    erupin     设置gpio外部中断引脚
* @return   void
* @notes
* Example:  disable_eru(P15_4); // P15_4引脚gpio外部中断关闭
*
**/
void disable_eru(ERU_pin_enum erupin)
{
    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)((IfxScuEru_OutputChannel)(erupin/3)) % 4];
    IfxSrc_disable(src);
}

/**
*
* @brief    GPIO外部中断服务函数示例
* @param
* @return
* @notes    一个通道只能选择其中一个引脚作为外部中断的输入
* Example:  直接使用以下函数即可
*
**/
void ERU_CH0_4_IRQ()
{
    IfxCpu_enableInterrupts();
    eru_ch0_4_irq();
}

void ERU_CH1_5_IRQ()
{
    IfxCpu_enableInterrupts();
    eru_ch1_5_irq();
}

void ERU_CH2_6_IRQ()
{
    IfxCpu_enableInterrupts();
    eru_ch2_6_irq();
}

// MT9V034摄像头使用
void ERU_CH3_7_IRQ()
{
    IfxCpu_enableInterrupts();
    start_dma(ERU_CH2_6_INT_PRIORITY);
}
