/****************************************************************************************
 *     COPYRIGHT NOTICE
 *     Copyright (C) 2023,AS DAIMXA
 *     copyright Copyright (C) ������DAIMXA,2023
 *     All rights reserved.
 *     ��������QQȺ��710026750
 *
 *     ��ע�������⣬�����������ݰ�Ȩ�������������ܿƼ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣�������������Ƽ��İ�Ȩ������
 *      ____    _    ___ __  ____  __    _
 *     |  _ \  / \  |_ _|  \/  \ \/ /   / \
 *     | | | |/ _ \  | || |\/| |\  /   / _ \
 *     | |_| / ___ \ | || |  | |/  \  / ___ \
 *     |____/_/   \_\___|_|  |_/_/\_\/_/   \_\
 *
 * @file       dmx_eru.c
 * @brief      ������TC264��Դ��
 * @company    �Ϸʴ��������ܿƼ����޹�˾
 * @author     �������Ƽ���QQ��2453520483��
 * @MCUcore    TC264
 * @Software   AURIX Development Stdio V1.8.0
 * @version    �鿴˵���ĵ���version�汾˵��
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
* @brief    gpio�ⲿ�жϳ�ʼ��
* @param    erupin      ����gpio�ⲿ�ж�����
* @param    mode        ���ô�����ʽ
* @return   void
* @notes    TC264ֻ��15���̶���GPIO����֧���ⲿ�ж�,��15�����ŷ�Ϊ8��ͨ��,����
*           ͨ��0��ͨ��4����һ���ж�,ͨ��1��ͨ��5����һ���ж�,ͨ��2��ͨ��6����һ���ж�,ͨ��3��ͨ��7����һ���ж�
* Example:  init_eru(P15_4, RISING);    // �ⲿ�ж�ͨ��0,ʹ��P15_4����,�����ش����ж�
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
* @brief    ����gpio�ⲿ�ж�
* @param    erupin     ����gpio�ⲿ�ж�����
* @return   void
* @notes
* Example:  enable_eru(P15_4);  // P15_4����gpio�ⲿ�жϿ���
*
**/
void enable_eru(ERU_pin_enum erupin)
{
    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)((IfxScuEru_OutputChannel)(erupin/3)) % 4];
    IfxSrc_enable(src);
}

/**
*
* @brief    �ر�gpio�ⲿ�ж�
* @param    erupin     ����gpio�ⲿ�ж�����
* @return   void
* @notes
* Example:  disable_eru(P15_4); // P15_4����gpio�ⲿ�жϹر�
*
**/
void disable_eru(ERU_pin_enum erupin)
{
    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)((IfxScuEru_OutputChannel)(erupin/3)) % 4];
    IfxSrc_disable(src);
}

/**
*
* @brief    GPIO�ⲿ�жϷ�����ʾ��
* @param
* @return
* @notes    һ��ͨ��ֻ��ѡ������һ��������Ϊ�ⲿ�жϵ�����
* Example:  ֱ��ʹ�����º�������
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

// MT9V034����ͷʹ��
void ERU_CH3_7_IRQ()
{
    IfxCpu_enableInterrupts();
    start_dma(ERU_CH2_6_INT_PRIORITY);
}
