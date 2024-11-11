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
 * @file       dmx_dma.c
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

#include "dmx_dma.h"
#include "dmx_eru.h"
#include "dmx_mt9v034.h"
#include "IfxCpu_Irq.h"
#include "IfxScuEru.h"

unsigned char mt9v034_success_flag = 0;
unsigned char mt9v034_dma_init_flag = 0;
static unsigned char transfer_data_num = 0;

#if(DMA_VECTABNUM == 0)
#pragma section all "cpu0_dsram"
IFX_ALIGN(256) DMA_Link dma_link_list;
#elif(DMA_VECTABNUM == 1)
#pragma section all "cpu1_dsram"
IFX_ALIGN(256) DMA_Link dma_link_list;
#endif
#pragma section all restore

IFX_INTERRUPT(DMA_ISR, DMA_VECTABNUM, DMA_PRIORITY);

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
void init_dma(unsigned int srcAddr,unsigned int dstAddr,unsigned int ch)
{
    boolean interruptState = IfxCpu_disableInterrupts();

    IfxDma_Dma_Config        dmaConfig;
    IfxDma_Dma_initModuleConfig(&dmaConfig, &MODULE_DMA);

    IfxDma_Dma               dma;
    IfxDma_Dma_initModule(&dma, &dmaConfig);

    IfxDma_Dma_ChannelConfig cfg;
    IfxDma_Dma_initChannelConfig(&cfg, &dma);

    cfg.requestMode                     = IfxDma_ChannelRequestMode_oneTransferPerRequest;
    cfg.moveSize                        = IfxDma_ChannelMoveSize_8bit;

    cfg.shadowControl = IfxDma_ChannelShadow_none;
    cfg.operationMode = IfxDma_ChannelOperationMode_continuous;

    cfg.sourceAddress                   = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), srcAddr);
    cfg.sourceAddressCircularRange      = IfxDma_ChannelIncrementCircular_none;
    cfg.sourceCircularBufferEnabled     = TRUE;

    cfg.channelId                       = (IfxDma_ChannelId)ch;
    cfg.hardwareRequestEnabled          = TRUE;
    cfg.channelInterruptEnabled         = TRUE;
    cfg.channelInterruptPriority        = DMA_PRIORITY;
    cfg.channelInterruptTypeOfService   = DMA_VECTABNUM;

    cfg.destinationAddress              = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), dstAddr);

    cfg.shadowAddress = 0;

    cfg.transferCount                   = 11280;

    IfxDma_Dma_initChannel(&dma_link_list.channel, &cfg);

    IfxDma_Dma_initLinkedListEntry((void *)&dma_link_list.linked_list[0], &cfg);

    IfxCpu_Irq_installInterruptHandler((void*)DMA_ISR, DMA_PRIORITY);

    IfxDma_Dma_getSrcPointer(&dma_link_list.channel)->B.CLRR = 1;

    IfxDma_clearChannelInterrupt(&MODULE_DMA, ch);

    IfxDma_disableChannelTransaction(&MODULE_DMA, ch);

    IfxCpu_restoreInterrupts(interruptState);
}

/**
*
* @brief    DMA开始
* @param    ch              选择DMA通道
* @return   void
* @notes    内部调用
* Example:
*
**/
void start_dma(unsigned int ch)
{
    IfxScuEru_getEventFlagStatus((IfxScuEru_InputChannel)(EruP02_0/3));
    if(mt9v034_dma_init_flag)
    {
        mt9v034_dma_init_flag = 0;
        IfxDma_resetChannel(&MODULE_DMA, ch);
        init_dma((unsigned int)(&MODULE_P00.IN.U), (unsigned int)MT9V034_Image_Data, ch);
        IfxDma_enableChannelTransaction(&MODULE_DMA, ch);
    }
    else
    {
        IfxDma_setChannelDestinationAddress(&MODULE_DMA, ch,(void *) IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), MT9V034_Image_Data));
        IfxDma_enableChannelTransaction(&MODULE_DMA, ch);
    }
}

/**
*
* @brief    DMA中断服务函数示例
* @param
* @return
* @notes    摄像头中断服务函数
* Example:  直接使用以下函数即可
*
**/
void DMA_ISR(void)
{
    IfxCpu_enableInterrupts();
    IfxDma_clearChannelInterrupt(&MODULE_DMA, ERU_CH2_6_INT_PRIORITY);
    if(IfxDma_getChannelTransactionRequestLost(&MODULE_DMA, ERU_CH2_6_INT_PRIORITY))
    {
        mt9v034_success_flag = 0;
        IfxDma_disableChannelTransaction(&MODULE_DMA, ERU_CH2_6_INT_PRIORITY);
        IfxDma_clearChannelTransactionRequestLost(&MODULE_DMA, ERU_CH2_6_INT_PRIORITY);
        mt9v034_dma_init_flag = 1;
    }
    else
    {
        transfer_data_num++;
        if (transfer_data_num == 2)
        {
            transfer_data_num=0;
            mt9v034_success_flag=1;
            IfxDma_disableChannelTransaction(&MODULE_DMA, ERU_CH2_6_INT_PRIORITY);
        }
    }
}
