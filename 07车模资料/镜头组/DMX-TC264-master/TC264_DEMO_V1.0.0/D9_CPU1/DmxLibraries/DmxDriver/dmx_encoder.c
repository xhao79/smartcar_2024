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
 * @file       dmx_encoder.c
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

#include "dmx_encoder.h"
#include "IfxGpt12_IncrEnc.h"

/**
*
* @brief    初始化编码器引脚
* @param    gpt        引脚使用的计数器号
* @param    countpin   计数引脚
* @param    dirpin     方向引脚
* @return   void
* @notes    编码器计数器号以及脉冲输入和方向输入应对应同一个定时器
* Example:  Init_Encoder(ENCODEDR_T2, T2_COUNT_P33_7, T2_DIR_P33_6);
*
**/
void Init_Encoder(ENCODER_GPT12_enum gpt, ENCODER_count_enum countpin,ENCODER_dir_enum dirpin)
{
    if((countpin/2!=dirpin/2)||(gpt!=countpin/2))
    {
        // 编码器脉冲输入和方向输入以及计数器号应对应同一个定时器
        while(1);
    }

    IfxGpt12_enableModule(&MODULE_GPT120);
    IfxGpt12_setGpt1BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt1BlockPrescaler_4);
    IfxGpt12_setGpt2BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt2BlockPrescaler_4);

    IfxGpt12_TxIn_In *count_pin;
    IfxGpt12_TxEud_In *dir_pin;
    switch(gpt)
    {
        case ENCODEDR_T2:
        {
            if (countpin==T2_COUNT_P00_7) count_pin = &IfxGpt120_T2INA_P00_7_IN;
            else count_pin = &IfxGpt120_T2INB_P33_7_IN;

            if (dirpin==T2_DIR_P00_8) dir_pin = &IfxGpt120_T2EUDA_P00_8_IN;
            else dir_pin = &IfxGpt120_T2EUDB_P33_6_IN;
        }
        break;
        case ENCODEDR_T3:
        {
            count_pin = &IfxGpt120_T3INA_P02_6_IN;

            dir_pin = &IfxGpt120_T3EUDA_P02_7_IN;
        }
        break;
        case ENCODEDR_T4:
        {
            count_pin = &IfxGpt120_T4INA_P02_8_IN;

            if (dirpin==T4_DIR_P00_9) dir_pin = &IfxGpt120_T4EUDA_P00_9_IN;
            else dir_pin = &IfxGpt120_T4EUDB_P33_5_IN;
        }
        break;
        case ENCODEDR_T5:
        {
            if (countpin==T5_COUNT_P21_7) count_pin = &IfxGpt120_T5INA_P21_7_IN;
            else count_pin = &IfxGpt120_T5INB_P10_3_IN;

            if (dirpin==T5_DIR_P21_6) dir_pin = &IfxGpt120_T5EUDA_P21_6_IN;
            else dir_pin = &IfxGpt120_T5EUDB_P10_1_IN;
        }
        break;

        case ENCODEDR_T6:
        {
            if (countpin==T6_COUNT_P20_3) count_pin = &IfxGpt120_T6INA_P20_3_IN;
            else count_pin = &IfxGpt120_T6INB_P10_2_IN;

            dir_pin = &IfxGpt120_T6EUDA_P20_0_IN;
        }
        break;
    }
    IfxGpt12_initTxInPinWithPadLevel(count_pin, IfxPort_InputMode_pullUp, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxGpt12_initTxEudInPinWithPadLevel(dir_pin, IfxPort_InputMode_pullUp, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    switch(gpt)
    {
        case  ENCODEDR_T2:
        {
            IfxGpt12_T2_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T2_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T2_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T2_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }
        break;
        case  ENCODEDR_T3:
        {
            IfxGpt12_T3_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T3_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T3_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T3_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }
        break;
        case  ENCODEDR_T4:
        {
            IfxGpt12_T4_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T4_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T4_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T4_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }break;

        case  ENCODEDR_T5:
        {
            IfxGpt12_T5_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T5_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T5_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T5_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }
        break;
        case ENCODEDR_T6:
        {
            IfxGpt12_T6_setCounterInputMode(&MODULE_GPT120, IfxGpt12_CounterInputMode_risingEdgeTxIN);
            IfxGpt12_T6_setDirectionSource(&MODULE_GPT120, IfxGpt12_TimerDirectionSource_external);
            IfxGpt12_T6_setMode(&MODULE_GPT120, IfxGpt12_Mode_counter);
            IfxGpt12_T6_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
        }
        break;
    }
}

/**
*
* @brief    获取编码器计数值
* @param    gptn        引脚使用的计数器号
* @return   void
* @notes
* Example:  Get_Encoder(ENCODEDR_T2);
*
**/
short Get_Encoder(ENCODER_GPT12_enum gpt)
{
    switch(gpt)
    {
        case ENCODEDR_T2: return (short)IfxGpt12_T2_getTimerValue(&MODULE_GPT120);
        case ENCODEDR_T3: return (short)IfxGpt12_T3_getTimerValue(&MODULE_GPT120);
        case ENCODEDR_T4: return (short)IfxGpt12_T4_getTimerValue(&MODULE_GPT120);
        case ENCODEDR_T5: return (short)IfxGpt12_T5_getTimerValue(&MODULE_GPT120);
        case ENCODEDR_T6: return (short)IfxGpt12_T6_getTimerValue(&MODULE_GPT120);
        default: return 0;
    }
}

/**
*
* @brief    清除编码器计数值
* @param    gptn        引脚使用的计数器号
* @return   void
* @notes
* Example:  Clear_Encoder(ENCODEDR_T2);
*
**/
void Clear_Encoder(ENCODER_GPT12_enum gpt)
{
    switch(gpt)
    {
        case ENCODEDR_T2: IfxGpt12_T2_setTimerValue(&MODULE_GPT120, 0); break;
        case ENCODEDR_T3: IfxGpt12_T3_setTimerValue(&MODULE_GPT120, 0); break;
        case ENCODEDR_T4: IfxGpt12_T4_setTimerValue(&MODULE_GPT120, 0); break;
        case ENCODEDR_T5: IfxGpt12_T5_setTimerValue(&MODULE_GPT120, 0); break;
        case ENCODEDR_T6: IfxGpt12_T6_setTimerValue(&MODULE_GPT120, 0); break;
    }
}
