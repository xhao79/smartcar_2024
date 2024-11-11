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
 * @file       dmx_servos.h
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

#ifndef CODE_DMX_SERVOS_H_
#define CODE_DMX_SERVOS_H_

// 舵机PWM引脚
#define SERVOS_PWM          ATOM0_1_P33_9
// 舵机频率
#define SERVOS_FREQ         50
// 舵机左限位
#define SERVOS_L_DUTY       645
// 舵机中值
#define SERVOS_M_DUTY       710
// 舵机右限位
#define SERVOS_R_DUTY       770

/**
*
* @brief    舵机初始化
* @param
* @return   void
* @notes
* Example:  Init_Servos();
*
**/
void Init_Servos(void);

/**
*
* @brief    发送舵机占空比
* @param    duty            占空比大小
* @return   void
* @notes
* Example:  Set_Servos_Duty(710);
*
**/
void Set_Servos_Duty(int duty);

/**
*
* @brief    舵机PID
* @param    duty            占空比大小
* @return   int             PID结果
* @notes
* Example:  PID_Servos(final_error);
*
**/
int PID_Servos(float error);

#endif /* CODE_DMX_SERVOS_H_ */
