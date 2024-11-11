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
 * @file       dmx_servos.h
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

#ifndef CODE_DMX_SERVOS_H_
#define CODE_DMX_SERVOS_H_

// ���PWM����
#define SERVOS_PWM          ATOM0_1_P33_9
// ���Ƶ��
#define SERVOS_FREQ         50
// �������λ
#define SERVOS_L_DUTY       645
// �����ֵ
#define SERVOS_M_DUTY       710
// �������λ
#define SERVOS_R_DUTY       770

/**
*
* @brief    �����ʼ��
* @param
* @return   void
* @notes
* Example:  Init_Servos();
*
**/
void Init_Servos(void);

/**
*
* @brief    ���Ͷ��ռ�ձ�
* @param    duty            ռ�ձȴ�С
* @return   void
* @notes
* Example:  Set_Servos_Duty(710);
*
**/
void Set_Servos_Duty(int duty);

/**
*
* @brief    ���PID
* @param    duty            ռ�ձȴ�С
* @return   int             PID���
* @notes
* Example:  PID_Servos(final_error);
*
**/
int PID_Servos(float error);

#endif /* CODE_DMX_SERVOS_H_ */
