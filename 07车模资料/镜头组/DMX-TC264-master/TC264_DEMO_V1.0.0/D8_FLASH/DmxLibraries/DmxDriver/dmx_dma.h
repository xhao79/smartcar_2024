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
 * @file       dmx_dma.h
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

#ifndef DMXLIBRARIES_DMX_DRIVER_DMX_DMA_H_
#define DMXLIBRARIES_DMX_DRIVER_DMX_DMA_H_

#include "IfxDma_Dma.h"

// ERU����DMA�ж����ȼ�,���ȼ���Χ1~255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  DMA_PRIORITY    60
// ERU����DMA�жϷ���,���ж�����˭��Ӧ����,��Χ(CPU0 CPU1 DMA)��������Ϊ����ֵ
#define  DMA_VECTABNUM   IfxSrc_Tos_cpu0

typedef struct
{
    Ifx_DMA_CH linked_list[8];
    IfxDma_Dma_Channel channel;
}DMA_Link;

extern unsigned char mt9v034_success_flag;
extern unsigned char mt9v034_dma_init_flag;

/**
*
* @brief    ERU����DMA��ʼ��
* @param    srcAddr             ����Դ��ַ
* @param    dstAddr             ����Ŀ�ĵ�ַ
* @param    ch                  DMA����ͨ��(0~47)
* @return   void
* @notes    �ڲ�����
* Example:  init_dma((unsigned int)(&MODULE_P02.IN.U), (unsigned int)OriginalImageData, ERU_CH2_6_INT_PRIORITY);
*
**/
void init_dma(unsigned int srcAddr,unsigned int dstAddr,unsigned int ch);

/**
*
* @brief    DMA��ʼ
* @param    ch              ѡ��DMAͨ��
* @return   void
* @notes    �ڲ�����
* Example:
*
**/
void start_dma(unsigned int ch);

#endif /* DMXLIBRARIES_DMX_DRIVER_DMX_DMA_H_ */
