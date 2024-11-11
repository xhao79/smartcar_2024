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
 * @file       Cpu1_Main.c
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

#include "dmx_all.h"
#include "Cpu0_Main.h"
#include "dmx_isr.h"

#pragma section all "cpu1_dsram"

/** ����������������
* ������ΪCPU1��ʹ��,CPU1ֱ��ʹ�ü���
* CPU1��main�����ļ��ڸ���Ŀ�µ� -> User -> Cpu1_Mian.c��
* ע��:CPU0��CPU1����ͬʱ����ͬһ����Դ(����ͱ���)����������������
����������������**/

void core1_main(void)
{
    // �رտ��Ź����ж�ʹ��
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    IfxCpu_enableInterrupts();
    // �����û������

    // ��ʼ��P20_8����,�������,�ߵ�ƽ,Ϩ��״̬
    init_gpio(P20 , 8 , OutputPUSHPULL , 1);
    // ��ʼ��P20_9����,�������,�ߵ�ƽ,Ϩ��״̬
    init_gpio(P20 , 9 , OutputPUSHPULL , 1);
    // ��ʼ��P21_4����,�������,�ߵ�ƽ,Ϩ��״̬
    init_gpio(P21 , 4 , OutputPUSHPULL , 1);
    // ��ʼ��P21_5����,�������,�ߵ�ƽ,Ϩ��״̬
    init_gpio(P21 , 5 , OutputPUSHPULL , 1);

    // �ȴ�˫��ȫ����ɳ�ʼ��
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);

    while(1)
    {
        // P20_8��������͵�ƽ,����״̬
        set_level_gpio(P20 ,8 , 0);
        // STM0ģ����ʱ100ms
        Delay_ms(STM0,100);
        // P20_8���ŵ�ƽ��ת,Ϩ��״̬
        toggle_level_gpio(P20 ,8);

        // P20_9��������͵�ƽ,����״̬
        set_level_gpio(P20 ,9 , 0);
        // STM0ģ����ʱ100ms
        Delay_ms(STM0,100);
        // P20_9���ŵ�ƽ��ת,Ϩ��״̬
        toggle_level_gpio(P20 ,9);

        // P21_4��������͵�ƽ,����״̬
        set_level_gpio(P21 ,4 , 0);
        // STM0ģ����ʱ100ms
        Delay_ms(STM0,100);
        // P20_9���ŵ�ƽ��ת,Ϩ��״̬
        toggle_level_gpio(P21 ,4);

        // P21_5��������͵�ƽ,����״̬
        set_level_gpio(P21 ,5 , 0);
        // STM0ģ����ʱ100ms
        Delay_ms(STM0,100);
        // P21_5���ŵ�ƽ��ת,Ϩ��״̬
        toggle_level_gpio(P21 ,5);
    }
}

#pragma section all restore
