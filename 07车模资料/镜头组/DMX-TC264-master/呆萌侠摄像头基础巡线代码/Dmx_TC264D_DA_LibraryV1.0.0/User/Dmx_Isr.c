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

// �����������
float final_error;
// ���ұ�����ֵ
int left_rear_speed,right_rear_speed;
// ���������ٶ�
int final_hope_speed = 90;

// ��ʱ���ж�
void ccu60_ch0_irq(void)
{
    // ���ұ������ٶȲɼ�
    left_rear_speed = Get_Left_Motor_Speed();
    right_rear_speed = Get_Right_Motor_Speed();
    // ������״̬
    if(Car_State)
    {
        Set_Servos_Duty(PID_Servos(-final_error));
        Set_Left_Motor_Duty (Pid_Left_Motor(final_hope_speed + final_error*0.3,left_rear_speed));
        Set_Right_Motor_Duty(Pid_Right_Motor(final_hope_speed - final_error*0.3 ,right_rear_speed));
    }
    // �����籣��
    else
    {
        Set_Servos_Duty(PID_Servos(0));
        Set_Left_Motor_Duty (Pid_Left_Motor(0,left_rear_speed));
        Set_Right_Motor_Duty(Pid_Right_Motor(0,right_rear_speed));
    }

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
