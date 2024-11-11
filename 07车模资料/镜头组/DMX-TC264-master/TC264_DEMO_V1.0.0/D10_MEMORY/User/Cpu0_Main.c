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

/** ����������������
* ������Ϊ���������嶨����λ��
* CPU1�ٶȱ�CPU0��
* ����������ĸ�CPUִ��,�����õ��ı����ͺ����������ĸ�CPU��
* ��ָ����������λ����Ĭ�ϴ����CPU1,��ָ����������λ��Ĭ�ϴ�flash����
����������������**/

////////////////////////////////
// ���ݶ�����CPU0��
#pragma section all "cpu0_dsram"
// �����ڴ�������ڶ����򱻷��䵽CPU0��
float test;
#pragma section all restore
// �������

////////////////////////////////
// ����������CPU0��
#pragma section all "cpu0_psram"
// �����ڴ�������ڶ����򱻷��䵽CPU0��
void test_function(void)
{

}
#pragma section all restore
// �������

////////////////////////////////
// ���ݶ�����CPU1��
#pragma section all "cpu1_dsram"
// �����ڴ�������ڶ����򱻷��䵽CPU1��
float test1;
#pragma section all restore
// �������

////////////////////////////////
// ����������CPU1��
#pragma section all "cpu1_psram"
// �����ڴ�������ڶ����򱻷��䵽CPU1��
void test_function1(void)
{

}
#pragma section all restore
// �������

/** ����������������
* �˶�ע������Ϊ���������嶨����λ�õ���ʾ
����������������**/

#pragma section all "cpu0_dsram"
void core0_main(void)
{
    // ��ʼ��оƬ
    init_chip();
    // �����û������


    // �ȴ�˫��ȫ����ɳ�ʼ��
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // �ж�ʹ��
    IfxCpu_enableInterrupts();
    while(1)
    {

    }
}
#pragma section all restore
