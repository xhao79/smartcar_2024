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
 * @file       dmx_delay.h
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

#ifndef DMXLIBRARIES_DMX_DELAY_H_
#define DMXLIBRARIES_DMX_DELAY_H_

#include "IfxStm.h"
#include "IFXSTM_CFG.h"
#include "dmx_common.h"

// STMģ���ö��
typedef enum
{
    STM0,
    STM1,
}STM_module_enum;

/**
*
* @brief    systick��ʱ����
* @param    time        ��Ҫ��ʱ��ʱ��
* @return   void
* @notes    �ж��ﲻҪ������ʱ����
* Example:  ����ʾ����ʹ��dmx_delay.h�ļ��еĺ궨��
*
**/
void delay_systick(STM_module_enum stm, unsigned int time);

/**
*
* @brief    systick��ʱ������
* @param    stmn        ѡ��ʹ�õ�STMģ��
* @return   void
* @notes
* Example:  start_systick(STM0);    // ��¼�µ�ǰSTMģ���ʱ��
*
**/
void start_systick(STM_module_enum stm);

/**
*
* @brief    ��ȡ��start_systick(STM0);���󵽴˴���ʱ��
* @param    stmn            ѡ��ʹ�õ�ģ��
* @return   unsigned int    ���ش�start_systick()������ʼִ�е����ڵ�ʱ��(��λΪ10ns)
* @notes
* Example:  unsigned int time = get_systick(STM0);  // ��timeΪstart_systick()�������˺�������ʱ����
*
**/
unsigned int get_systick(STM_module_enum stm);

// ���º궨��������ʱ
#define Delay_ms(stm, time)    delay_systick(stm, time*1000000)   // ������ʱʱ��/��λms
#define Delay_us(stm, time)    delay_systick(stm, time*1000)      // ������ʱʱ��/��λus
#define Delay_ns(stm, time)    delay_systick(stm, time)           // ������ʱʱ��/��λns

// ���º궨�����ڻ�ȡ��ǰʱ��
#define GetTime_ms(stm)        get_systick(stm)/100000            // ��ȡ��ǰ��ʱʱ��/��λms
#define GetTime_us(stm)        get_systick(stm)/100               // ��ȡ��ǰ��ʱʱ��/��λus
#define GetTime_ns(stm)        get_systick(stm)*10                // ��ȡ��ǰ��ʱʱ��/��λns

#endif /* DMXLIBRARIES_DMX_DELAY_H_ */
