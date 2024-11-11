/****************************************************************************************
 *     COPYRIGHT NOTICE
 *     Copyright (C) 2023,AS DAIMXA
 *     copyright Copyright (C) 呆萌侠DAIMXA,2023
 *     All rights reserved.
 *     技术讨论QQ群：710026750
 *
 *     除注明出处外，以下所有内容版权均属呆萌侠智能科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留呆萌智能侠科技的版权声明。
 *      ____    _    ___ __  ____  __    _
 *     |  _ \  / \  |_ _|  \/  \ \/ /   / \
 *     | | | |/ _ \  | || |\/| |\  /   / _ \
 *     | |_| / ___ \ | || |  | |/  \  / ___ \
 *     |____/_/   \_\___|_|  |_/_/\_\/_/   \_\
 *
 * @file       dmx_motor.c
 * @brief      呆萌侠TC264开源库
 * @company    合肥呆萌侠智能科技有限公司
 * @author     呆萌侠科技（QQ：2453520483）
 * @MCUcore    TC264
 * @Software   AURIX Development Stdio V1.8.0
 * @version    查看说明文档内version版本说明
 * @Taobao     https://daimxa.taobao.com/
 * @Openlib    https://gitee.com/daimxa
 * @date       2023-11-10
****************************************************************************************/

#include "dmx_all.h"

// 左电机速度闭环相关变量
int left_motor_error,left_motor_next_error,left_motor_last_error;
float left_motor_increment,left_motor_actual;
float left_motor_p,left_motor_i,left_motor_d;
// 右电机速度闭环相关变量
int right_motor_error,right_motor_next_error,right_motor_last_error;
float right_motor_increment,right_motor_actual;
float right_motor_p,right_motor_i,right_motor_d;

/**
*
* @brief    电机初始化
* @param
* @return   void
* @notes
* Example:  Init_Motor();
*
**/
void Init_Motor(void)
{
    // 左电机控制引脚
    init_pwm(LEFT_MOTOR_PWM, MOTOR_FREQ, 0);
    init_pwm(LEFT_MOTOR_DIR, MOTOR_FREQ, 0);
    // 右电机控制引脚
    init_pwm(RIGHT_MOTOR_PWM, MOTOR_FREQ, 0);
    init_pwm(RIGHT_MOTOR_DIR, MOTOR_FREQ, 0);
    // 左编码器
    Init_Encoder(ENCODEDR_T4, T4_COUNT_P02_8, T4_DIR_P00_9);
    // 右编码器
    Init_Encoder(ENCODEDR_T2, T2_COUNT_P33_7, T2_DIR_P33_6);
    // 左电机速度闭环参数
    left_motor_p = 120;
    left_motor_i = 15;
    left_motor_d = 76;
    // 右电机速度闭环参数
    right_motor_p = 120;
    right_motor_i = 15;
    right_motor_d = 76;
}

/**
*
* @brief    发送左电机占空比
* @param    duty            占空比大小,负值反转
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
* @brief    发送右电机占空比
* @param    duty            占空比大小,负值反转
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
* @brief    获取左电机速度
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
* @brief    获取右电机速度
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
* @brief    左电机速度闭环PID
* @param    hope_speed              期望速度
* @param    rear_speed              实际速度
* @return   int                     期望占空比
* @notes
* Example:  Pid_Left_Motor(hope_speed,rear_speed);
*
**/
int Pid_Left_Motor(int hope_speed, int rear_speed)
{
    // 速度误差
    left_motor_error = hope_speed - rear_speed;
    // 增量计算
    left_motor_increment = left_motor_p * (left_motor_error) + left_motor_i * (left_motor_error - left_motor_next_error) + left_motor_d * (left_motor_error - 2 * left_motor_next_error + left_motor_last_error);
    left_motor_actual += left_motor_increment;
    // 结果限幅
    if(left_motor_actual > 10000)
        left_motor_actual = 10000;
    else if(left_motor_actual < -10000)
        left_motor_actual = -10000;
    // 误差迭代
    left_motor_last_error = left_motor_next_error;
    left_motor_next_error = left_motor_error;
    return (int)left_motor_actual;
}

/**
*
* @brief    右电机速度闭环PID
* @param    hope_speed              期望速度
* @param    rear_speed              实际速度
* @return   int                     期望占空比
* @notes
* Example:  Pid_Right_Motor(hope_speed,rear_speed);
*
**/
int Pid_Right_Motor(int hope_speed, int rear_speed)
{
    // 速度误差
    right_motor_error = hope_speed - rear_speed;
    // 增量计算
    right_motor_increment = right_motor_p * (right_motor_error) + right_motor_i * (right_motor_error - right_motor_next_error) + right_motor_d * (right_motor_error - 2 * right_motor_next_error + right_motor_last_error);
    right_motor_actual += right_motor_increment;
    // 结果限幅
    if(right_motor_actual > 10000)
        right_motor_actual = 10000;
    else if(right_motor_actual < -10000)
        right_motor_actual = -10000;
    // 误差迭代
    right_motor_last_error = right_motor_next_error;
    right_motor_next_error = right_motor_error;
    return (int)right_motor_actual;
}

