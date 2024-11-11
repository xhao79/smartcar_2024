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
 * @file       dmx_servos.c
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

// ���PID
float Steer_P  = 2.9, Steer_D  = 1;
float Steer_Error,Last_Steer_Error;

/**
*
* @brief    �����ʼ��
* @param
* @return   void
* @notes
* Example:  Init_Servos();
*
**/
void Init_Servos(void)
{
    init_pwm(SERVOS_PWM, SERVOS_FREQ, SERVOS_M_DUTY);
}

/**
*
* @brief    ���Ͷ��ռ�ձ�
* @param    duty            ռ�ձȴ�С
* @return   void
* @notes
* Example:  Set_Servos_Duty(710);
*
**/
void Set_Servos_Duty(int duty)
{
    if(duty < SERVOS_L_DUTY)
        duty = SERVOS_L_DUTY;
    if(duty > SERVOS_R_DUTY)
        duty = SERVOS_R_DUTY;
    set_duty_pwm(SERVOS_PWM, duty);
}

/**
*
* @brief    ���PID
* @param    duty            ռ�ձȴ�С
* @return   int             PID���
* @notes
* Example:  PID_Servos(final_error);
*
**/
int PID_Servos(float error)
{
    Steer_Error = (Steer_P * error + Steer_D * (error - Last_Steer_Error));
    Last_Steer_Error = error;
    if(Steer_Error > 60)
        Steer_Error = 60;
    if(Steer_Error < -60)
        Steer_Error = -60;
    return (Steer_Error + SERVOS_M_DUTY);
}

