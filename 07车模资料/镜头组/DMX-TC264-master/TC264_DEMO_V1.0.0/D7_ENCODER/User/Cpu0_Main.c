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
* ENCODER����ļ��ڸ���Ŀ�µ� -> DmxLibraries -> DmxDriver -> dmx_encoder.c��dmx_encoder.h��
* ������Ϊ���������ݲɼ�,��������Ϊ���İ��������������ȷ��,��ת������,�������ַ��ͻ�ȡ�ı��������ݵ���λ��
����������������**/

char buff[4];

void core0_main(void)
{
    // ��ʼ��оƬ
    init_chip();
    // �����û������

    // ��ʼ��������(�����������;���ֵ����������),��������ΪP33_7,��������ΪP33_6
    Init_Encoder(ENCODEDR_T2, T2_COUNT_P33_7, T2_DIR_P33_6);
    // ��ʼ��CCU60ģ��ͨ��0,10msִ��һ���ж�,�ɼ�����������
    init_pit(CCU60, CH0, 10000);
    // ��ʼ������0,TX����ΪP14_0,RX����ΪP14_1,������Ϊ115200
    init_uart(TX0_P14_0,RX0_P14_1, 115200);
    // ���ʹ���0��ʼ������ַ���
    set_string_uart(UART0,"����0��ʼ����ɣ�\r\n");

    // �ȴ�˫��ȫ����ɳ�ʼ��
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // �ж�ʹ��
    IfxCpu_enableInterrupts();
    while(1)
    {
        // �������ٶ�rear_speed�ڸ���Ŀ�µ� -> User -> Dmx_Isr.c��Dmx_Isr.h���Ѿ����������
        // ����ת�ַ���
        sprintf(buff,"rear_speed:%d\r\n",rear_speed);
        // ���ڷ��͸��ַ���
        set_string_uart(UART0,buff);
        // STM0ģ����ʱ100ms
        Delay_ms(STM0,100);
    }
}

#pragma section all restore
