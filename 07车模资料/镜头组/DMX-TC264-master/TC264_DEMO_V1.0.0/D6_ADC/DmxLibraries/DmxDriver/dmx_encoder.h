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
 * @file       dmx_encoder.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_ENCODER_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_ENCODER_H_

// 编码器通道枚举
typedef enum
{
    ENCODEDR_T2,
    ENCODEDR_T3,
    ENCODEDR_T4,
    ENCODEDR_T5,
    ENCODEDR_T6
}ENCODER_GPT12_enum;

// 编码器计数引脚枚举
typedef enum
{
    T2_COUNT_P00_7, // T2定时器,计数引脚可选范围
    T2_COUNT_P33_7,

    T3_COUNT_P02_6, // T3定时器,计数引脚可选范围
    CX0,// TC264无此引脚,此处使用为占位所需！

    T4_COUNT_P02_8, // T4定时器,计数引脚可选范围
    CX1,// TC264无此引脚,此处使用为占位所需！

    T5_COUNT_P21_7, // T5定时器,计数引脚可选范围
    T5_COUNT_P10_3,

    T6_COUNT_P20_3, // T6定时器,计数引脚可选范围
    T6_COUNT_P10_2,
}ENCODER_count_enum;

// 编码器方向引脚枚举
typedef enum // 枚举编码器引脚
{
    T2_DIR_P00_8,   // T2定时器,方向引脚可选范围
    T2_DIR_P33_6,

    T3_DIR_P02_7,   // T3定时器,方向引脚可选范围
    DX0,// TC264无此引脚,此处使用为占位所需！

    T4_DIR_P00_9,   // T4定时器,方向引脚可选范围
    T4_DIR_P33_5,

    T5_DIR_P21_6,   // T5定时器,方向引脚可选范围
    T5_DIR_P10_1,

    T6_DIR_P20_0,   // T6定时器,方向引脚可选范围
    DX1,// TC264无此引脚,此处使用为占位所需！
}ENCODER_dir_enum;

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
void Init_Encoder(ENCODER_GPT12_enum gpt, ENCODER_count_enum countpin,ENCODER_dir_enum dirpin);

/**
*
* @brief    获取编码器计数值
* @param    gptn        引脚使用的计数器号
* @return   void
* @notes
* Example:  Get_Encoder(ENCODEDR_T2);
*
**/
short Get_Encoder(ENCODER_GPT12_enum gpt);//获取编码器计数值

/**
*
* @brief    清除编码器计数值
* @param    gptn        引脚使用的计数器号
* @return   void
* @notes
* Example:  Clear_Encoder(ENCODEDR_T2);
*
**/
void Clear_Encoder(ENCODER_GPT12_enum gpt);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_ENCODER_H_ */
