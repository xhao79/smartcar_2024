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
 * @file       dmx_motor.h
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

#ifndef CODE_DMX_MOTOR_H_
#define CODE_DMX_MOTOR_H_

// ���PWM����
#define LEFT_MOTOR_PWM      ATOM1_4_P02_4
#define LEFT_MOTOR_DIR      ATOM1_5_P02_5
#define RIGHT_MOTOR_PWM     ATOM1_6_P02_6
#define RIGHT_MOTOR_DIR     ATOM1_7_P02_7
// ���Ƶ��
#define MOTOR_FREQ          13333
// ����޷�
#define MOTOR_A_DUTY        4000
// ����޷�
#define MOTOR_B_DUTY        4000

/**
*
* @brief    �����ʼ��
* @param
* @return   void
* @notes
* Example:  Init_Motor();
*
**/
void Init_Motor(void);

/**
*
* @brief    ��������ռ�ձ�
* @param    duty            ռ�ձȴ�С,��ֵ��ת
* @return   void
* @notes
* Example:  Set_Left_Motor_Duty(1500);
*
**/
void Set_Left_Motor_Duty(int duty);

/**
*
* @brief    �����ҵ��ռ�ձ�
* @param    duty            ռ�ձȴ�С,��ֵ��ת
* @return   void
* @notes
* Example:  Set_Right_Motor_Duty(1500);
*
**/
void Set_Right_Motor_Duty(int duty);

/**
*
* @brief    ��ȡ�����ٶ�
* @param
* @return   void
* @notes
* Example:  Get_Left_Motor_Speed();
*
**/
int Get_Left_Motor_Speed(void);

/**
*
* @brief    ��ȡ�ҵ���ٶ�
* @param
* @return   void
* @notes
* Example:  Get_Right_Motor_Speed();
*
**/
int Get_Right_Motor_Speed(void);

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
int Pid_Left_Motor(int hope_speed, int rear_speed);

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
int Pid_Right_Motor(int hope_speed, int rear_speed);

#endif /* CODE_DMX_MOTOR_H_ */
