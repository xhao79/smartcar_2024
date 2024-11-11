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
 * @file       dmx_dma.h
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

#ifndef DMXLIBRARIES_DMX_DRIVER_DMX_DMA_H_
#define DMXLIBRARIES_DMX_DRIVER_DMX_DMA_H_

#include "IfxDma_Dma.h"

// ERU触发DMA中断优先级,优先级范围1~255,数字越大优先级越高,优先级不可重复
#define  DMA_PRIORITY    60
// ERU触发DMA中断服务,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
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
* @brief    ERU触发DMA初始化
* @param    srcAddr             设置源地址
* @param    dstAddr             设置目的地址
* @param    ch                  DMA传输通道(0~47)
* @return   void
* @notes    内部调用
* Example:  init_dma((unsigned int)(&MODULE_P02.IN.U), (unsigned int)OriginalImageData, ERU_CH2_6_INT_PRIORITY);
*
**/
void init_dma(unsigned int srcAddr,unsigned int dstAddr,unsigned int ch);

/**
*
* @brief    DMA开始
* @param    ch              选择DMA通道
* @return   void
* @notes    内部调用
* Example:
*
**/
void start_dma(unsigned int ch);

#endif /* DMXLIBRARIES_DMX_DRIVER_DMX_DMA_H_ */
