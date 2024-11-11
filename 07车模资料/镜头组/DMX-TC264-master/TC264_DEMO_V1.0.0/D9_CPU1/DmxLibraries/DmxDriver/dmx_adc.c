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
 * @file       dmx_adc.c
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

#include "dmx_adc.h"

/**
*
* @brief    adc��ʼ��
* @param    adc_pin     ѡ����Ҫ��ʼ��adc����(dmx_adc.h�ļ�����ö�ٶ���)
* @return   void
* @notes    ���ô˺���ǰ�ɲ鿴dmx_adc.h�ļ���ö�ٵĿ�������
* Example:  init_adc(A0);   // ��ʼ��A0����
*
**/
void init_adc(ADC_pin_enum adc_pin)
{
    IfxVadc_Adc g_vadc;
    IfxVadc_Adc_Group g_vadcGroup;
    IfxVadc_Adc_Channel g_vadcChannel;

    // ��ʼ��ADCģ��
    IfxVadc_Adc_Config adcConf;
    IfxVadc_Adc_initModuleConfig(&adcConf, &MODULE_VADC);
    IfxVadc_Adc_initModule(&g_vadc, &adcConf);

    // ��ʼ��ADC��
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

    // ��ʼ��ADCͨ��
    IfxVadc_Adc_ChannelConfig adcChannelConf;
    IfxVadc_Adc_initChannelConfig(&adcChannelConf, &g_vadcGroup);
    adcChannelConf.channelId         = (IfxVadc_ChannelId)(adc_pin%ADC_CHANNEL_SUM);
    adcChannelConf.resultRegister    = (IfxVadc_ChannelResult)(adc_pin%ADC_CHANNEL_SUM);
    adcChannelConf.backgroundChannel = TRUE;
    IfxVadc_Adc_initChannel(&g_vadcChannel, &adcChannelConf);
    unsigned chnEnableBit = (1 << adcChannelConf.channelId);
    unsigned mask = chnEnableBit;
    IfxVadc_Adc_setBackgroundScan(&g_vadc, &g_vadcGroup, chnEnableBit, mask);

    // ��ʼɨ��
    IfxVadc_Adc_startBackgroundScan(&g_vadc);
}

/**
*
* @brief    adcת��һ�μ���ȡһ��adֵ
* @param    adc_pin     ѡ����Ҫ��ȡ��adc����(dmx_adc.h�ļ�����ö�ٶ���)
* @param    adc_res     ѡ��adc����(8bit,10bit,12bit)
* @return   void
* @notes
* Example:  get_adc(A0, ADC12BIT);  // ��ȡһ��A0���ŵ�adֵ,����Ϊ12bit���ú�������ֵ���Ϊ2��ʮ���η�
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
