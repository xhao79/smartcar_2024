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
 * @file       dmx_servos.c
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

// 舵机PID
float Steer_P  = 2.9, Steer_D  = 1;
float Steer_Error,Last_Steer_Error;

/**
*
* @brief    舵机初始化
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
* @brief    发送舵机占空比
* @param    duty            占空比大小
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
* @brief    舵机PID
* @param    duty            占空比大小
* @return   int             PID结果
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

