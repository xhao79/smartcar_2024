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
 * @file       dmx_uart.c
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

#include "dmx_uart.h"
#include "dmx_isr.h"
#include <ifxCpu_Irq.h>
#include <ifxAsclin_Asc.h>

IfxAsclin_Asc g_asc[4];
static unsigned char g_ascTxBuffer[4][ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static unsigned char g_ascRxBuffer[4][ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

// UART中断
IFX_INTERRUPT(RX0_IRQ, UART0_VECTABNUM, RX0_PRIORITY);
IFX_INTERRUPT(TX0_IRQ, UART0_VECTABNUM, TX0_PRIORITY);
IFX_INTERRUPT(ER0_IRQ, UART0_VECTABNUM, ER0_PRIORITY);
IFX_INTERRUPT(RX1_IRQ, UART1_VECTABNUM, RX1_PRIORITY);
IFX_INTERRUPT(TX1_IRQ, UART1_VECTABNUM, TX1_PRIORITY);
IFX_INTERRUPT(ER1_IRQ, UART1_VECTABNUM, ER1_PRIORITY);
IFX_INTERRUPT(RX2_IRQ, UART2_VECTABNUM, RX2_PRIORITY);
IFX_INTERRUPT(TX2_IRQ, UART2_VECTABNUM, TX2_PRIORITY);
IFX_INTERRUPT(ER2_IRQ, UART2_VECTABNUM, ER2_PRIORITY);
IFX_INTERRUPT(RX3_IRQ, UART3_VECTABNUM, RX3_PRIORITY);
IFX_INTERRUPT(TX3_IRQ, UART3_VECTABNUM, TX3_PRIORITY);
IFX_INTERRUPT(ER3_IRQ, UART3_VECTABNUM, ER3_PRIORITY);

const unsigned char uart_vectabnum[4] = {UART0_VECTABNUM, UART1_VECTABNUM, UART2_VECTABNUM, UART3_VECTABNUM};
const unsigned char uart_priority[12] = {RX0_PRIORITY, TX0_PRIORITY, ER0_PRIORITY, RX1_PRIORITY, TX1_PRIORITY, ER1_PRIORITY,RX2_PRIORITY, TX2_PRIORITY, ER2_PRIORITY, RX3_PRIORITY, TX3_PRIORITY, ER3_PRIORITY};
const void *uart_func_pointer[12] = {&RX0_IRQ, &TX0_IRQ, &ER0_IRQ,&RX1_IRQ, &TX1_IRQ, &ER1_IRQ,&RX2_IRQ, &TX2_IRQ, &ER2_IRQ,&RX3_IRQ, &TX3_IRQ, &ER3_IRQ,};

/**
*
* @brief    串口模块初始化
* @param    TxPin       串口发送管脚
* @param    RxPin       串口接收管脚
* @param    baudrate    波特率
* @return   void
* @notes    TX引脚和RX引脚串口号需对应
* Example:  init_uart(TX0_P14_0,RX0_P14_1, 115200); // 初始化串口0,引脚为(P14_0,P14_1)波特率115200,无奇偶校验,1停止位
*
**/
void init_uart(UART_tx_enum TxPin, UART_rx_enum RxPin, unsigned int baudrate)
{
    boolean interruptState = IfxCpu_disableInterrupts();

    IfxAsclin_Tx_Out * Tx_Pin = 0;
    IfxAsclin_Rx_In  * Rx_Pin = 0;

    switch(TxPin)
    {
        case TX0_P14_0:Tx_Pin=&IfxAsclin0_TX_P14_0_OUT;break;
        case TX0_P14_1:Tx_Pin=&IfxAsclin0_TX_P14_1_OUT;break;
        case TX0_P15_2:Tx_Pin=&IfxAsclin0_TX_P15_2_OUT;break;
        case TX0_P15_3:Tx_Pin=&IfxAsclin0_TX_P15_3_OUT;break;

        case TX1_P02_2:Tx_Pin=&IfxAsclin1_TX_P02_2_OUT;break;
        case TX1_P11_12:Tx_Pin=&IfxAsclin1_TX_P11_12_OUT;break;
        case TX1_P15_0:Tx_Pin=&IfxAsclin1_TX_P15_0_OUT;break;
        case TX1_P15_1:Tx_Pin=&IfxAsclin1_TX_P15_1_OUT;break;
        case TX1_P15_4:Tx_Pin=&IfxAsclin1_TX_P15_4_OUT;break;
        case TX1_P15_5:Tx_Pin=&IfxAsclin1_TX_P15_5_OUT;break;
        case TX1_P20_10:Tx_Pin=&IfxAsclin1_TX_P20_10_OUT;break;
        case TX1_P33_12:Tx_Pin=&IfxAsclin1_TX_P33_12_OUT;break;
        case TX1_P33_13:Tx_Pin=&IfxAsclin1_TX_P33_13_OUT;break;

        case TX2_P02_0:Tx_Pin=&IfxAsclin2_TX_P02_0_OUT;break;
        case TX2_P10_5:Tx_Pin=&IfxAsclin2_TX_P10_5_OUT;break;
        case TX2_P14_2:Tx_Pin=&IfxAsclin2_TX_P14_2_OUT;break;
        case TX2_P14_3:Tx_Pin=&IfxAsclin2_TX_P14_3_OUT;break;
        case TX2_P33_8:Tx_Pin=&IfxAsclin2_TX_P33_8_OUT;break;
        case TX2_P33_9:Tx_Pin=&IfxAsclin2_TX_P33_9_OUT;break;

        case TX3_P00_0:Tx_Pin=&IfxAsclin3_TX_P00_0_OUT;break;
        case TX3_P00_1:Tx_Pin=&IfxAsclin3_TX_P00_1_OUT;break;
        case TX3_P15_6:Tx_Pin=&IfxAsclin3_TX_P15_6_OUT;break;
        case TX3_P15_7:Tx_Pin=&IfxAsclin3_TX_P15_7_OUT;break;
        case TX3_P20_0:Tx_Pin=&IfxAsclin3_TX_P20_0_OUT;break;
        case TX3_P20_3:Tx_Pin=&IfxAsclin3_TX_P20_3_OUT;break;
        case TX3_P21_7:Tx_Pin=&IfxAsclin3_TX_P21_7_OUT;break;
    }

    switch(RxPin)
    {
        case RX0_P14_1:Rx_Pin=&IfxAsclin0_RXA_P14_1_IN;break;
        case RX0_P15_3:Rx_Pin=&IfxAsclin0_RXB_P15_3_IN;break;

        case RX1_P15_1:Rx_Pin=&IfxAsclin1_RXA_P15_1_IN;break;
        case RX1_P15_5:Rx_Pin=&IfxAsclin1_RXB_P15_5_IN;break;
        case RX1_P20_9:Rx_Pin=&IfxAsclin1_RXC_P20_9_IN;break;
        case RX1_P11_10:Rx_Pin=&IfxAsclin1_RXE_P11_10_IN;break;
        case RX1_P33_13:Rx_Pin=&IfxAsclin1_RXF_P33_13_IN;break;
        case RX1_P02_3:Rx_Pin=&IfxAsclin1_RXG_P02_3_IN;break;

        case RX2_P14_3:Rx_Pin=&IfxAsclin2_RXA_P14_3_IN;break;
        case RX2_P02_1:Rx_Pin=&IfxAsclin2_RXB_P02_1_IN;break;
        case RX2_P10_6:Rx_Pin=&IfxAsclin2_RXD_P10_6_IN;break;
        case RX2_P33_8:Rx_Pin=&IfxAsclin2_RXE_P33_8_IN;break;
        case RX2_P02_0:Rx_Pin=&IfxAsclin2_RXG_P02_0_IN;break;

        case RX3_P15_7:Rx_Pin=&IfxAsclin3_RXA_P15_7_IN;break;
        case RX3_P20_3:Rx_Pin=&IfxAsclin3_RXC_P20_3_IN;break;
        case RX3_P00_1:Rx_Pin=&IfxAsclin3_RXE_P00_1_IN;break;
        case RX3_P21_6:Rx_Pin=&IfxAsclin3_RXF_P21_6_IN;break;
    }

    IfxAsclin_Asc_Config ascConfig;
    IfxAsclin_Asc_initModuleConfig(&ascConfig, Tx_Pin->module);

    ascConfig.baudrate.baudrate  = (float)baudrate;
    ascConfig.frame.frameMode    = IfxAsclin_FrameMode_asc;
    ascConfig.frame.dataLength   = IfxAsclin_DataLength_8;
    ascConfig.frame.stopBit      = IfxAsclin_StopBit_1;
    ascConfig.frame.shiftDir     = IfxAsclin_ShiftDirection_lsbFirst;
    ascConfig.frame.parityBit    = FALSE;

    unsigned char uartNum = IfxAsclin_getIndex(Tx_Pin->module);

    ascConfig.interrupt.rxPriority = uart_priority[uartNum * 3 + 0];
    ascConfig.interrupt.txPriority = uart_priority[uartNum * 3 + 1];
    ascConfig.interrupt.erPriority = uart_priority[uartNum * 3 + 2];
    ascConfig.interrupt.typeOfService = uart_vectabnum[uartNum];

    ascConfig.txBuffer     = &g_ascTxBuffer[uartNum][0];
    ascConfig.txBufferSize = ASC_TX_BUFFER_SIZE;
    ascConfig.rxBuffer     = &g_ascRxBuffer[uartNum][0];
    ascConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;

    IfxAsclin_Asc_Pins pins =
    {
        NULL,                       IfxPort_InputMode_pullUp,
        Rx_Pin,                     IfxPort_InputMode_pullUp,
        NULL,                       IfxPort_OutputMode_pushPull,
        Tx_Pin,                     IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConfig.pins = &pins;

    IfxAsclin_Asc_initModule(&g_asc[uartNum], &ascConfig);

    IfxCpu_Irq_installInterruptHandler((void*)uart_func_pointer[uartNum * 3 + 0], uart_priority[uartNum * 3 + 0]);
    IfxCpu_Irq_installInterruptHandler((void*)uart_func_pointer[uartNum * 3 + 1], uart_priority[uartNum * 3 + 1]);
    IfxCpu_Irq_installInterruptHandler((void*)uart_func_pointer[uartNum * 3 + 2], uart_priority[uartNum * 3 + 2]);

    IfxCpu_restoreInterrupts(interruptState);
}

/**
*
* @brief    串口发送字节
* @param    uart        UART0~UART3
* @param    ch          要发送的字符
* @return   void
* @notes    使用前请先初始化对应串口
* Example:  set_char_uart(UART0,'A');       // 通过串口0发送字符‘A’
*
**/
void set_char_uart(UART_enum  uart, char ch)
{
    IfxAsclin_Asc_blockingWrite(&g_asc[uart], ch);
}

/**
*
* @brief    串口发送字符串函数
* @param    uart        UART0~UART3
* @param    str         要发送的字符串首地址
* @return   void
* @notes    遇null停止发送,使用前请先初始化对应串口
* Example:  set_string_uart(UART0,"1234");  // 通过串口0发送4个字节“1234”
*
**/
void set_string_uart(UART_enum  uart, char *str)
{
   while(*str)
    {
       set_char_uart(uart, *str++);
    }
}

/**
*
* @brief    串口发送字节函数
* @param    uart        UART0~UART3
* @param    buf         要发送的字符串首地址
* @param    len         要发送的字符串长度
* @return   void
* @notes    使用前请先初始化对应串口
* Example:  set_buff_uart(UART0,"1234",3);   // 通过串口0发送3个字节'1''2''3'
*
**/
void set_buff_uart(UART_enum  uart, unsigned char *buf, unsigned int len)
{
    while(len--)
    {
        set_char_uart(uart, *buf);
        buf++;
    }
}

/**
*
* @brief    获取串口缓冲区接收数据的个数
* @param    uart        UART0~UART3
* @return   uint8
* @notes    使用前请先初始化对应串口
* Example:  get_count_uart(UART0);          // 获取串口0缓冲区接收数据的个数
*
**/
unsigned char get_count_uart(UART_enum  uart)
{
    return (unsigned char)IfxAsclin_Asc_getReadCount(&g_asc[uart]);
}

/**
*
* @brief    串口接收字节
* @param    uart        UART0~UART3
* @return   char
* @notes    使用前请先初始化对应串口
* Example:  get_char_uart(UART0);           // 接收一个字符
*
**/
char get_char_uart(UART_enum  uart)
{
    unsigned char data=0;
    Ifx_SizeT count = 1;
    // 获取接收到的一个字节数据没有接收到则会一直等待
    IfxAsclin_Asc_read(&g_asc[uart], &data, &count, TIME_INFINITE);
    return  data;
}

/**
*
* @brief    串口接收一定长度字符
* @param    uart        UART0~UART3
* @param    buf         存储接收数据首地址
* @param    len         接收长度
* @return   0
* @notes    使用前请先初始化对应串口
* Example:  get_buff_uart(UART0, data, 10); // 接收10个字符
*
**/
char get_buff_uart(UART_enum  uart, unsigned char *data, unsigned char len)
{
    Ifx_SizeT count = len;
    // 判断当前接收到的数据数量如不够读取长度则返回1
    if(get_count_uart(uart) < len)
        return 1;
    IfxAsclin_Asc_read(&g_asc[uart], data, &count, TIME_INFINITE);
    return  0;
}

/**
*
* @brief    UART中断服务函数示例
* @param
* @return
* @notes
* Example:  直接使用以下函数即可
*
**/
void RX0_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrReceive(&g_asc[0]);
    rx0_irq();
}
void TX0_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&g_asc[0]);
    tx0_irq();
}
void ER0_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrError(&g_asc[0]);
    er0_irq();
}


void RX1_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrReceive(&g_asc[1]);
    rx1_irq();
}
void TX1_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&g_asc[1]);
    tx1_irq();
}
void ER1_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrError(&g_asc[1]);
    er1_irq();
}


void RX2_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrReceive(&g_asc[2]);
    rx2_irq();
}
void TX2_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&g_asc[2]);
    tx2_irq();
}
void ER2_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrError(&g_asc[2]);
    er2_irq();
}


void RX3_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrReceive(&g_asc[3]);
    rx3_irq();
}
void TX3_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&g_asc[3]);
    tx3_irq();
}
void ER3_IRQ(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrError(&g_asc[3]);
    er3_irq();
}
