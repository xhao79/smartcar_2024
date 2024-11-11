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
 * @file       dmx_delay.c
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

#include "dmx_delay.h"

static unsigned int systick_count[2];

/**
*
* @brief    systick��ʱ����
* @param    time            ��Ҫ��ʱ��ʱ��
* @return   void
* @notes    �ж��ﲻҪ������ʱ����
* Example:  ����ʾ����ʹ��dmx_delay.h�ļ��еĺ궨��
*
**/
void delay_systick(STM_module_enum stm, unsigned int time)
{
    unsigned long stm_clk;
    stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stm));
    IfxStm_waitTicks(IfxStm_getAddress((IfxStm_Index)stm), (unsigned long)((unsigned long long)stm_clk*time/1000000000));
}

/**
*
* @brief    systick��ʱ������
* @param    stmn        ѡ��ʹ�õ�STMģ��
* @return   void
* @notes
* Example:  start_systick(STM0);    // ��¼�µ�ǰSTMģ���ʱ��
*
**/
void start_systick(STM_module_enum stm)
{
    systick_count[stm] = IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stm));
}

/**
*
* @brief    ��ȡ��start_systick(STM0);���󵽴˴���ʱ��
* @param    stmn            ѡ��ʹ�õ�ģ��
* @return   unsigned int    ���ش�start_systick()������ʼִ�е����ڵ�ʱ��(��λΪ10ns)
* @notes
* Example:  unsigned int time = get_systick(STM0);  // ��timeΪstart_systick()�������˺�������ʱ����
*
**/
unsigned int get_systick(STM_module_enum stm)
{
    unsigned long stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stm));
    return (unsigned long)((unsigned long long)(IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stm)) - systick_count[stm]) * 100000000 / stm_clk);
}
