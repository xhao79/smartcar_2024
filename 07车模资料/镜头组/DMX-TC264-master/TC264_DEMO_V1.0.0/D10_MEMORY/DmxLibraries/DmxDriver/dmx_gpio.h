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
 * @file       dmx_gpio.h
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

#ifndef DMXLIBRARIES_DMX_GPIO_H_
#define DMXLIBRARIES_DMX_GPIO_H_

#include "IFXPORT.h"

// �˿ڵ�ַ
#define  P00    &MODULE_P00
#define  P02    &MODULE_P02
#define  P10    &MODULE_P10
#define  P11    &MODULE_P11
#define  P13    &MODULE_P13
#define  P14    &MODULE_P14
#define  P15    &MODULE_P15
#define  P20    &MODULE_P20
#define  P21    &MODULE_P21
#define  P22    &MODULE_P22
#define  P23    &MODULE_P23
#define  P33    &MODULE_P33

// GPIO����ģʽö��
typedef enum
{
    InputNOPULL     ,     // ������������
    InputPULLDOWN   ,     // ��������
    InputPULLUP     ,     // ��������
    OutputPUSHPULL  ,     // �������
    OutputOPENDRAIN ,     // ��©���
}GPIO_mode_enum;

/**
*
* @brief    GPIO��ʼ��
* @param    port        ѡ��Ķ˿�,����dmx_gpio.h�ж˿ڵ�ַ�ĺ궨��
* @param    pinIndex    �ö˿ڵĶ�Ӧ���ź�
* @param    pinmode     ����ģʽ����(�����ò�����dmx_gpio.h��GPIO����ģʽö��ֵȷ��)
* @param    level       ���ų�ʼ��ʱ���õĵ�ƽ״̬(���ģʽʱ��Ч)�͵�ƽ:0 �ߵ�ƽ:1
* @return   void
* @notes    TC264��P20.2�����ǲ������������,�������빦�ܡ�TC264DAоƬ��21.6�޷�����ʹ�á�
* Example:  init_gpio(P20 , 8 , OutputPUSHPULL , 0);    // TC264��P20.8���ų�ʼ��Ϊ�������ģʽ,��ʼ����͵�ƽ
*
**/
void init_gpio(Ifx_P *port, unsigned char pinIndex,GPIO_mode_enum pinmode,unsigned char level);

/**
*
* @brief    GPIO�������ת��
* @param    port        ѡ��Ķ˿�,����Dmx_Gpio.h�ж˿ڵ�ַ�ĺ궨��
* @param    pinIndex    �ö˿ڵĶ�Ӧ���ź�
* @param    dir         ����:0 ���:1
* @return   void
* @notes
* Example:  set_dir_gpio(P20 ,8 , 1);   //ʹTC264��P20.8��������ߵ�ƽ
*
**/
void set_dir_gpio(Ifx_P *port, unsigned char pinIndex, unsigned char dir);

/**
*
* @brief    GPIO�������
* @param    port        ѡ��Ķ˿�,����Dmx_Gpio.h�ж˿ڵ�ַ�ĺ궨��
* @param    pinIndex    �ö˿ڵĶ�Ӧ���ź�
* @param    level       ���ų�ʼ��ʱ���õĵ�ƽ״̬(���ģʽʱ��Ч)�͵�ƽ:0 �ߵ�ƽ:1
* @return   void
* @notes
* Example:  set_level_gpio(P20 ,8 , 1);   //ʹTC264��P20.8��������ߵ�ƽ
*
**/
void set_level_gpio(Ifx_P *port, unsigned char pinIndex, unsigned char level);

/**
*
* @brief    GPIO״̬��ȡ
* @param    port        ѡ��Ķ˿�,����Dmx_Gpio.h�ж˿ڵ�ַ�ĺ궨��
* @param    pinIndex    �ö˿ڵĶ�Ӧ���ź�
* @param    level       ���ų�ʼ��ʱ���õĵ�ƽ״̬(���ģʽʱ��Ч)�͵�ƽ:0 �ߵ�ƽ:1
* @notes
* Example:  unsigned char status = get_level_gpio(P20 ,8);  // ��ȡTC264��P20.8���ŵ�ƽ��ֵ���������status����
*
**/
unsigned char get_level_gpio(Ifx_P *port, unsigned char pinIndex);

/**
*
* @brief    GPIO״̬��ת
* @param    port        ѡ��Ķ˿�,����Dmx_Gpio.h�ж˿ڵ�ַ�ĺ궨��
* @param    pinIndex    �ö˿ڵĶ�Ӧ���ź�
* @return   void
* @notes
* Example:  toggle_level_gpio(P20 ,8);  // TC264��P20.8���ŵ�ƽ��ת
*
**/
void toggle_level_gpio(Ifx_P *port, unsigned char pinIndex);

#endif /* DMXLIBRARIES_DMX_GPIO_H_ */
