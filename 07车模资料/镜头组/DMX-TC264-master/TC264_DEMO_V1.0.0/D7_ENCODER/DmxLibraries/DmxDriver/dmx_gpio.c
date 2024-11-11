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
 * @file       dmx_gpio.c
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

#include "dmx_gpio.h"

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
void init_gpio(Ifx_P *port, unsigned char pinIndex,GPIO_mode_enum pinmode,unsigned char level)
{
    IfxPort_Mode port_mode;

    switch(pinmode)
    {
        case InputNOPULL:       port_mode = IfxPort_Mode_inputNoPullDevice;      break;
        case InputPULLUP:       port_mode = IfxPort_Mode_inputPullUp;            break;
        case InputPULLDOWN:     port_mode = IfxPort_Mode_inputPullDown;          break;
        case OutputOPENDRAIN:   port_mode = IfxPort_Mode_outputOpenDrainGeneral; break;
        case OutputPUSHPULL:    port_mode = IfxPort_Mode_outputPushPullGeneral;  break;
        default:                port_mode = IfxPort_Mode_outputPushPullGeneral;  break;
    }

    IfxPort_setPinMode(port, pinIndex, port_mode);
    IfxPort_setPinPadDriver(port, pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    if(pinmode == OutputPUSHPULL || pinmode == OutputOPENDRAIN)
    {
        if(level) IfxPort_setPinHigh(port, pinIndex);
        else    IfxPort_setPinLow(port, pinIndex);
    }
}

/**
*
* @brief    GPIO�������ת��
* @param    port        ѡ��Ķ˿�,����dmx_gpio.h�ж˿ڵ�ַ�ĺ궨��
* @param    pinIndex    �ö˿ڵĶ�Ӧ���ź�
* @param    dir         ����:0 ���:1
* @return   void
* @notes
* Example:  set_dir_gpio(P20 ,8 , 1);   // ʹTC264��P20.8��������ߵ�ƽ
*
**/
void set_dir_gpio(Ifx_P *port, unsigned char pinIndex, unsigned char dir)
{
    if(!dir) IfxPort_setPinMode(port, pinIndex, IfxPort_Mode_inputNoPullDevice);
    else    IfxPort_setPinMode(port, pinIndex, IfxPort_Mode_outputPushPullGeneral);
}

/**
*
* @brief    GPIO�������
* @param    port        ѡ��Ķ˿�,����dmx_gpio.h�ж˿ڵ�ַ�ĺ궨��
* @param    pinIndex    �ö˿ڵĶ�Ӧ���ź�
* @param    level       ���ų�ʼ��ʱ���õĵ�ƽ״̬(���ģʽʱ��Ч)�͵�ƽ:0 �ߵ�ƽ:1
* @return   void
* @notes
* Example:  set_level_gpio(P20 ,8 , 1);   // ʹTC264��P20.8��������ߵ�ƽ
*
**/
void set_level_gpio(Ifx_P *port, unsigned char pinIndex, unsigned char level)
{
    if(level) IfxPort_setPinHigh(port, pinIndex);
    else    IfxPort_setPinLow(port, pinIndex);
}

/**
*
* @brief    GPIO״̬��ȡ
* @param    port        ѡ��Ķ˿�,����dmx_gpio.h�ж˿ڵ�ַ�ĺ궨��
* @param    pinIndex    �ö˿ڵĶ�Ӧ���ź�
* @param    level       ���ų�ʼ��ʱ���õĵ�ƽ״̬(���ģʽʱ��Ч)�͵�ƽ:0 �ߵ�ƽ:1
* @notes
* Example:  unsigned char status = get_level_gpio(P20 ,8);    // ��ȡTC264��P20.8���ŵ�ƽ��ֵ���������status����
*
**/
unsigned char get_level_gpio(Ifx_P *port, unsigned char pinIndex)
{
    return IfxPort_getPinState(port, pinIndex);
}

/**
*
* @brief    GPIO״̬��ת
* @param    port        ѡ��Ķ˿�,����dmx_gpio.h�ж˿ڵ�ַ�ĺ궨��
* @param    pinIndex    �ö˿ڵĶ�Ӧ���ź�
* @return   void
* @notes
* Example:  toggle_level_gpio(P20 ,8);    // TC264��P20.8���ŵ�ƽ��ת
*
**/
void toggle_level_gpio(Ifx_P *port, unsigned char pinIndex)
{
    IfxPort_togglePin(port, pinIndex);
}
