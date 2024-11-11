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
 * @file       dmx_adc.c
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

#include "dmx_adc.h"

/**
*
* @brief    adc初始化
* @param    adc_pin     选择需要初始化adc引脚(dmx_adc.h文件里已枚举定义)
* @return   void
* @notes    调用此函数前可查看dmx_adc.h文件里枚举的可用引脚
* Example:  init_adc(A0);   // 初始化A0引脚
*
**/
void init_adc(ADC_pin_enum adc_pin)
{
    IfxVadc_Adc g_vadc;
    IfxVadc_Adc_Group g_vadcGroup;
    IfxVadc_Adc_Channel g_vadcChannel;

    // 初始化ADC模块
    IfxVadc_Adc_Config adcConf;
    IfxVadc_Adc_initModuleConfig(&adcConf, &MODULE_VADC);
    IfxVadc_Adc_initModule(&g_vadc, &adcConf);

    // 初始化ADC组
    IfxVadc_Adc_GroupConfig adcGroupConf;
    IfxVadc_Adc_initGroupConfig(&adcGroupConf, &g_vadc);

    adcGroupConf.inputClass[0].sampleTime = (1.0f/ADC_SAMPLE_FREQ);
    adcGroupConf.inputClass[1].sampleTime = (1.0f/ADC_SAMPLE_FREQ);
    adcGroupConf.inputClass[0].resolution = IfxVadc_ChannelResolution_12bit;
    adcGroupConf.inputClass[1].resolution = IfxVadc_ChannelResolution_12bit;

    adcGroupConf.groupId = (IfxVadc_GroupId)(adc_pin/ADC_CHANNEL_SUM);
    adcGroupConf.master  = adcGroupConf.groupId;
    adcGroupConf.arbiter.requestSlotBackgroundScanEnabled = TRUE;
    adcGroupConf.backgroundScanRequest.autoBackgroundScanEnabled = TRUE;
    adcGroupConf.backgroundScanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;
    IfxVadc_Adc_initGroup(&g_vadcGroup, &adcGroupConf);

    // 初始化ADC通道
    IfxVadc_Adc_ChannelConfig adcChannelConf;
    IfxVadc_Adc_initChannelConfig(&adcChannelConf, &g_vadcGroup);
    adcChannelConf.channelId         = (IfxVadc_ChannelId)(adc_pin%ADC_CHANNEL_SUM);
    adcChannelConf.resultRegister    = (IfxVadc_ChannelResult)(adc_pin%ADC_CHANNEL_SUM);
    adcChannelConf.backgroundChannel = TRUE;
    IfxVadc_Adc_initChannel(&g_vadcChannel, &adcChannelConf);
    unsigned chnEnableBit = (1 << adcChannelConf.channelId);
    unsigned mask = chnEnableBit;
    IfxVadc_Adc_setBackgroundScan(&g_vadc, &g_vadcGroup, chnEnableBit, mask);

    // 开始扫描
    IfxVadc_Adc_startBackgroundScan(&g_vadc);
}

/**
*
* @brief    adc转换一次即获取一次ad值
* @param    adc_pin     选择需要读取的adc引脚(dmx_adc.h文件里已枚举定义)
* @param    adc_res     选择adc精度(8bit,10bit,12bit)
* @return   void
* @notes
* Example:  get_adc(A0, ADC12BIT);  // 获取一次A0引脚的ad值,精度为12bit即该函数返回值最大为2的十二次方
*
**/
unsigned short get_adc(ADC_pin_enum adc_pin, ADC_res_enum adc_res)
{
    Ifx_VADC_RES conversionResult;
    do
    {
        conversionResult = IfxVadc_getResult(&MODULE_VADC.G[adc_pin/ADC_CHANNEL_SUM], adc_pin%ADC_CHANNEL_SUM);
    }while (!conversionResult.B.VF);
    unsigned char precision = 4 - (adc_res * 2);
    return ((conversionResult.U&0x0fff)>>precision);
}
