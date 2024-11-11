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
* FLASH����ļ��ڸ���Ŀ�µ� -> DmxLibraries -> DmxDriver -> dmx_flash.c��dmx_flash.h��
* ������ΪFLASH��д����
* ע��:��д���ݵ����鳤����СΪ2������
����������������**/

char buff[100];

float write_data[2];
float read_data[2];

void core0_main(void)
{
    // ��ʼ��оƬ
    init_chip();
    // �����û������

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
        // ��ֵ
        write_data[0] = 1.234567;
        write_data[1] = 3;

        // ����ת�ַ���
        sprintf(buff,"ԭ ʼ �� ��write_data[0]:%f write_data[1]:%f\r\n\r\n",write_data[0],write_data[1]);
        // ���ڷ��͸��ַ���
        set_string_uart(UART0,buff);

        // ����
        erase_sector(0);
        // д��
        write_page(0,0, (unsigned long*)write_data,2);
        // ��ȡ
        read_page(0,0, (unsigned long*)read_data,2);

        // ����ת�ַ���
        sprintf(buff,"��ȡд�������read_data[0]:%f read_data[1]:%f\r\n",read_data[0],read_data[1]);
        // ���ڷ��͸��ַ���
        set_string_uart(UART0,buff);

        // ����
        erase_sector(0);
        // ��ȡ
        read_page(0,0, (unsigned long*)read_data,2);

        // ����ת�ַ���
        sprintf(buff,"�������ȡ����read_data[0]:%f read_data[1]:%f\r\n\r\n",read_data[0],read_data[1]);
        // ���ڷ��͸��ַ���
        set_string_uart(UART0,buff);

        // STM0ģ����ʱ6s,ʱ����6s����۲�
        Delay_ms(STM0,3000);
        Delay_ms(STM0,3000);
    }
}

#pragma section all restore
