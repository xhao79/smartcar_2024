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
 * @file       dmx_pit.h
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

#ifndef DMXLIBRARIES_DMX_PIT_H_
#define DMXLIBRARIES_DMX_PIT_H_

// CCU6��ʱ��ģ��0ͨ��0�жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  CCU60_CH0_PIT_PRIORITY    30
// CCU6��ʱ��ģ��0ͨ��1�жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  CCU60_CH1_PIT_PRIORITY    31
// ����CCU6��ʱ��ģ��0���ĸ��ں˹���,���ж�����˭��Ӧ����,��Χ(CPU0 CPU1 DMA)��������Ϊ����ֵ
#define  CCU60_PIT_VECTABNUM       0

// CCU6��ʱ��ģ��1ͨ��0�жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  CCU61_CH0_PIT_PRIORITY    32
// CCU6��ʱ��ģ��1ͨ��1�жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  CCU61_CH1_PIT_PRIORITY    33
// ����CCU6��ʱ��ģ��1���ĸ��ں˹���,���ж�����˭��Ӧ����,��Χ(CPU0 CPU1 DMA)��������Ϊ����ֵ
#define  CCU61_PIT_VECTABNUM       0

// CCU6ģ��ö��
typedef enum
{
    CCU60,
    CCU61,
}CCU6_enum;

// CCU6ͨ��ö��
typedef enum
{
    CH0,
    CH1,
}CCU6_ch_enum;

/**
*
* @brief    ��ʱ���жϳ�ʼ��
* @param    ccu6        ѡ��CCU6ģ��(CCU60,CCU61)
* @param    channel     ѡ��ͨ��(CH0,CH1)
* @param    time        ����ʱ��
* @return   void
* @notes    ����ʱ�䵥λ:΢��
* Example:  init_pit(CCU60, CH0, 100);  // CCU60ģ��ͨ��0,100usִ��һ���ж�
*
**/
void init_pit(CCU6_enum ccu6, CCU6_ch_enum channel, unsigned long time);

/**
*
* @brief    ��ʱ���ж�ʹ��
* @param    ccu6        ѡ��CCU6ģ��(CCU60,CCU61)
* @param    channel     ѡ��ͨ��(CH0,CH1)
* @return   void
* @notes
* Example:  enable_pit(CCU60, CH0);     // ����CCU60ģ��ͨ��0���ж�
*
**/
void enable_pit(CCU6_enum ccu6, CCU6_ch_enum channel);

/**
*
* @brief    ��ʱ���жϽ�ֹ
* @param    ccu6        ѡ��CCU6ģ��(CCU60,CCU61)
* @param    channel     ѡ��ͨ��(CH0,CH1)
* @return   void
* @notes
* Example:  disable_pit(CCU60, CH0);    // �ر�CCU60ģ��ͨ��0���ж�
*
**/
void disable_pit(CCU6_enum ccu6, CCU6_ch_enum channel);

#endif /* DMXLIBRARIES_DMX_PIT_H_ */
