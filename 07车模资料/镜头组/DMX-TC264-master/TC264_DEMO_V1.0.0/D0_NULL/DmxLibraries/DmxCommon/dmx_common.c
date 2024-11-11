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
 * @file       dmx_common.c
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

#include "dmx_common.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;   // �¼�ͬ������

App_Cpu0 g_AppCpu0; // Ƶ����Ϣ����

/**
*
* @brief    ��ʼ��оƬ
* @param
* @return   void
* @notes
* Example:  init_chip();
*
**/
void init_chip(void)
{
    // �ж�ʧ��
    IfxCpu_disableInterrupts();
    // �رտ��Ź�
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    // ��ȡʱ��Ƶ�ʣ����ڲ鿴��ǰϵͳ����Ƶ��
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();                       // ���໷
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());  // ������
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();                       // ϵͳ
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);
    // �ж�ʹ��
    IfxCpu_enableInterrupts();
}
