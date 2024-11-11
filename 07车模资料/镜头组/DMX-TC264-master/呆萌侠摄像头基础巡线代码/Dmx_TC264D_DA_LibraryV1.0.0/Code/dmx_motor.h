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
 * @file       dmx_motor.h
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

#ifndef CODE_DMX_MOTOR_H_
#define CODE_DMX_MOTOR_H_

// 电机PWM引脚
#define LEFT_MOTOR_PWM      ATOM1_4_P02_4
#define LEFT_MOTOR_DIR      ATOM1_5_P02_5
#define RIGHT_MOTOR_PWM     ATOM1_6_P02_6
#define RIGHT_MOTOR_DIR     ATOM1_7_P02_7
// 电机频率
#define MOTOR_FREQ          13333
// 电机限幅
#define MOTOR_A_DUTY        4000
// 电机限幅
#define MOTOR_B_DUTY        4000

/**
*
* @brief    电机初始化
* @param
* @return   void
* @notes
* Example:  Init_Motor();
*
**/
void Init_Motor(void);

/**
*
* @brief    发送左电机占空比
* @param    duty            占空比大小,负值反转
* @return   void
* @notes
* Example:  Set_Left_Motor_Duty(1500);
*
**/
void Set_Left_Motor_Duty(int duty);

/**
*
* @brief    发送右电机占空比
* @param    duty            占空比大小,负值反转
* @return   void
* @notes
* Example:  Set_Right_Motor_Duty(1500);
*
**/
void Set_Right_Motor_Duty(int duty);

/**
*
* @brief    获取左电机速度
* @param
* @return   void
* @notes
* Example:  Get_Left_Motor_Speed();
*
**/
int Get_Left_Motor_Speed(void);

/**
*
* @brief    获取右电机速度
* @param
* @return   void
* @notes
* Example:  Get_Right_Motor_Speed();
*
**/
int Get_Right_Motor_Speed(void);

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
int Pid_Left_Motor(int hope_speed, int rear_speed);

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
int Pid_Right_Motor(int hope_speed, int rear_speed);

#endif /* CODE_DMX_MOTOR_H_ */
