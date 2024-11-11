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
* ERU����ļ��ڸ���Ŀ�µ� -> DmxLibraries -> DmxDriver -> dmx_eru.c��dmx_eru.h��
* ERU�жϵ����ļ��ڸ���Ŀ�µ� -> User -> Dmx_Isr.c��Dmx_Isr.h��
* ������ΪERU����,��������Ϊ���İ�ͨ���ʹ�ⲿ�ж�ͨ��0��P15_4���Ž�GND(���½����ź�),P20_8����LED����
����������������**/

void core0_main(void)
{
    // ��ʼ��оƬ
    init_chip();
    // �����û������

    // ��ʼ���ⲿ�ж�ͨ��0,ʹ��P15_4����,�½��ش����ж�
    init_eru(EruP15_4, FALLING);

    // �ȴ�˫��ȫ����ɳ�ʼ��
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // �ж�ʹ��
    IfxCpu_enableInterrupts();
    while(1)
    {
        // ERU�жϵ����ڸ���Ŀ�µ� -> User -> Dmx_Isr.c��
    }
}

#pragma section all restore
