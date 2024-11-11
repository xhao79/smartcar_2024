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
 * @file       dmx_isr.c
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

// ��ʱ���ж�
void ccu60_ch0_irq(void)
{

}
void ccu60_ch1_irq(void)
{

}
void ccu61_ch0_irq(void)
{

}
void ccu61_ch1_irq(void)
{

}

// �ⲿ�ж�
void eru_ch0_4_irq(void)
{
    // ��ʼ��P20_8����,�������,�͵�ƽ,����״̬
    init_gpio(P20 , 8 , OutputPUSHPULL , 0);
}

void eru_ch1_5_irq(void)
{

}

void eru_ch2_6_irq(void)
{

}

// �����ж�
void rx0_irq(void)
{
    set_char_uart(UART0, get_char_uart(UART0));
}
void tx0_irq(void)
{

}
void er0_irq(void)
{

}

void rx1_irq(void)
{
    set_char_uart(UART1, get_char_uart(UART1));
}
void tx1_irq(void)
{

}
void er1_irq(void)
{

}

void rx2_irq(void)
{
    set_char_uart(UART2, get_char_uart(UART2));
}
void tx2_irq(void)
{

}
void er2_irq(void)
{

}

void rx3_irq(void)
{
    set_char_uart(UART3, get_char_uart(UART3));
}
void tx3_irq(void)
{

}
void er3_irq(void)
{

}
