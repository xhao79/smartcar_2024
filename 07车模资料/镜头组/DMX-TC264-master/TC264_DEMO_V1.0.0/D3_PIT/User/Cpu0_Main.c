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
 * @file       Cpu0_Main.c
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
#include "dmx_isr.h"

#pragma section all "cpu0_dsram"

/** ����������������
* PIT����ļ��ڸ���Ŀ�µ� -> DmxLibraries -> DmxDriver -> dmx_pwm.c��dmx_pwm.h��
* PIT�жϵ����ļ��ڸ���Ŀ�µ� -> User -> Dmx_Isr.c��Dmx_Isr.h��
* ������ΪPIT����,��������Ϊ���İ����ĸ�LED���100ms��˸
����������������**/

void core0_main(void)
{
    // ��ʼ��оƬ
    init_chip();
    // �����û������

    // ��ʼ��P20_8����,�������,�ߵ�ƽ,Ϩ��״̬
    init_gpio(P20 , 8 , OutputPUSHPULL , 1);
    // ��ʼ��P20_9����,�������,�ߵ�ƽ,����״̬
    init_gpio(P20 , 9 , OutputPUSHPULL , 0);
    // ��ʼ��P21_4����,�������,�ߵ�ƽ,Ϩ��״̬
    init_gpio(P21 , 4 , OutputPUSHPULL , 1);
    // ��ʼ��P21_5����,�������,�ߵ�ƽ,����״̬
    init_gpio(P21 , 5 , OutputPUSHPULL , 0);

    // ��ʼ��CCU60ģ��ͨ��0,200msִ��һ���ж�,����P20_8����LED��˸
    init_pit(CCU60, CH0, 200000);
    // ��ʼ��CCU60ģ��ͨ��1,200msִ��һ���ж�,����P20_9����LED��˸
    init_pit(CCU60, CH1, 200000);
    // ��ʼ��CCU61ģ��ͨ��0,200msִ��һ���ж�,����P21_4����LED��˸
    init_pit(CCU61, CH0, 200000);
    // ��ʼ��CCU61ģ��ͨ��1,200msִ��һ���ж�,����P21_5����LED��˸
    init_pit(CCU61, CH1, 200000);

    // �ȴ�˫��ȫ����ɳ�ʼ��
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // �ж�ʹ��
    IfxCpu_enableInterrupts();
    while(1)
    {
        // PIT�жϵ������ŷ�ת�����ڸ���Ŀ�µ� -> User -> Dmx_Isr.c��
    }
}

#pragma section all restore
