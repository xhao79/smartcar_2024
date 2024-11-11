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
 * @file       dmx_motor.c
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

// �����ٶȱջ���ر���
int left_motor_error,left_motor_next_error,left_motor_last_error;
float left_motor_increment,left_motor_actual;
float left_motor_p,left_motor_i,left_motor_d;
// �ҵ���ٶȱջ���ر���
int right_motor_error,right_motor_next_error,right_motor_last_error;
float right_motor_increment,right_motor_actual;
float right_motor_p,right_motor_i,right_motor_d;

/**
*
* @brief    �����ʼ��
* @param
* @return   void
* @notes
* Example:  Init_Motor();
*
**/
void Init_Motor(void)
{
    // ������������
    init_pwm(LEFT_MOTOR_PWM, MOTOR_FREQ, 0);
    init_pwm(LEFT_MOTOR_DIR, MOTOR_FREQ, 0);
    // �ҵ����������
    init_pwm(RIGHT_MOTOR_PWM, MOTOR_FREQ, 0);
    init_pwm(RIGHT_MOTOR_DIR, MOTOR_FREQ, 0);
    // �������
    Init_Encoder(ENCODEDR_T4, T4_COUNT_P02_8, T4_DIR_P00_9);
    // �ұ�����
    Init_Encoder(ENCODEDR_T2, T2_COUNT_P33_7, T2_DIR_P33_6);
    // �����ٶȱջ�����
    left_motor_p = 120;
    left_motor_i = 15;
    left_motor_d = 76;
    // �ҵ���ٶȱջ�����
    right_motor_p = 120;
    right_motor_i = 15;
    right_motor_d = 76;
}

/**
*
* @brief    ��������ռ�ձ�
* @param    duty            ռ�ձȴ�С,��ֵ��ת
* @return   void
* @notes
* Example:  Set_Left_Motor_Duty(1500);
*
**/
void Set_Left_Motor_Duty(int duty)
{
    if(duty >=0)
    {
        if(duty > MOTOR_A_DUTY)
            duty = MOTOR_A_DUTY;

        set_duty_pwm(LEFT_MOTOR_PWM, duty);
        set_duty_pwm(LEFT_MOTOR_DIR, 0);
    }
    else
    {
        if(duty < -MOTOR_B_DUTY)
            duty = -MOTOR_B_DUTY;

        set_duty_pwm(LEFT_MOTOR_PWM, -duty);
        set_duty_pwm(LEFT_MOTOR_DIR, 10000);
    }
}

/**
*
* @brief    �����ҵ��ռ�ձ�
* @param    duty            ռ�ձȴ�С,��ֵ��ת
* @return   void
* @notes
* Example:  Set_Right_Motor_Duty(1500);
*
**/
void Set_Right_Motor_Duty(int duty)
{
    if(duty >=0)
    {
        if(duty > MOTOR_A_DUTY)
            duty = MOTOR_A_DUTY;

        set_duty_pwm(RIGHT_MOTOR_PWM, duty);
        set_duty_pwm(RIGHT_MOTOR_DIR, 0);
    }
    else
    {
        if(duty < -MOTOR_B_DUTY)
            duty = -MOTOR_B_DUTY;

        set_duty_pwm(RIGHT_MOTOR_PWM, -duty);
        set_duty_pwm(RIGHT_MOTOR_DIR, 10000);
    }
}

/**
*
* @brief    ��ȡ�����ٶ�
* @param
* @return   void
* @notes
* Example:  Get_Left_Motor_Speed();
*
**/
int Get_Left_Motor_Speed(void)
{
    int left_speed;
    left_speed = -(int)Get_Encoder(ENCODEDR_T4);
    Clear_Encoder(ENCODEDR_T4);
    return left_speed;
}

/**
*
* @brief    ��ȡ�ҵ���ٶ�
* @param
* @return   void
* @notes
* Example:  Get_Right_Motor_Speed();
*
**/
int Get_Right_Motor_Speed(void)
{
    int right_speed;
    right_speed = (int)Get_Encoder(ENCODEDR_T2);
    Clear_Encoder(ENCODEDR_T2);
    return right_speed;
}

/**
*
* @brief    �����ٶȱջ�PID
* @param    hope_speed              �����ٶ�
* @param    rear_speed              ʵ���ٶ�
* @return   int                     ����ռ�ձ�
* @notes
* Example:  Pid_Left_Motor(hope_speed,rear_speed);
*
**/
int Pid_Left_Motor(int hope_speed, int rear_speed)
{
    // �ٶ����
    left_motor_error = hope_speed - rear_speed;
    // ��������
    left_motor_increment = left_motor_p * (left_motor_error) + left_motor_i * (left_motor_error - left_motor_next_error) + left_motor_d * (left_motor_error - 2 * left_motor_next_error + left_motor_last_error);
    left_motor_actual += left_motor_increment;
    // ����޷�
    if(left_motor_actual > 10000)
        left_motor_actual = 10000;
    else if(left_motor_actual < -10000)
        left_motor_actual = -10000;
    // ������
    left_motor_last_error = left_motor_next_error;
    left_motor_next_error = left_motor_error;
    return (int)left_motor_actual;
}

/**
*
* @brief    �ҵ���ٶȱջ�PID
* @param    hope_speed              �����ٶ�
* @param    rear_speed              ʵ���ٶ�
* @return   int                     ����ռ�ձ�
* @notes
* Example:  Pid_Right_Motor(hope_speed,rear_speed);
*
**/
int Pid_Right_Motor(int hope_speed, int rear_speed)
{
    // �ٶ����
    right_motor_error = hope_speed - rear_speed;
    // ��������
    right_motor_increment = right_motor_p * (right_motor_error) + right_motor_i * (right_motor_error - right_motor_next_error) + right_motor_d * (right_motor_error - 2 * right_motor_next_error + right_motor_last_error);
    right_motor_actual += right_motor_increment;
    // ����޷�
    if(right_motor_actual > 10000)
        right_motor_actual = 10000;
    else if(right_motor_actual < -10000)
        right_motor_actual = -10000;
    // ������
    right_motor_last_error = right_motor_next_error;
    right_motor_next_error = right_motor_error;
    return (int)right_motor_actual;
}

