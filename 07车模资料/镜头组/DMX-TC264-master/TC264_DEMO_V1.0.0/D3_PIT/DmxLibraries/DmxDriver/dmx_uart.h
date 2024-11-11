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
 * @file       dmx_uart.h
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

#ifndef DMXLIBRARIES_DMX_UART_H_
#define DMXLIBRARIES_DMX_UART_H_

//发送和接收缓冲区大小
#define ASC_TX_BUFFER_SIZE 256
#define ASC_RX_BUFFER_SIZE 256

//UART中断参数定义
//定义UART0接收中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  RX0_PRIORITY       10
//定义UART0发送中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  TX0_PRIORITY       11
//定义UART0错误中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  ER0_PRIORITY       12
//定义UART0中断服务函数归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define  UART0_VECTABNUM    0

//定义UART1接收中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  RX1_PRIORITY       14
//定义UART1发送中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  TX1_PRIORITY       13
//定义UART1错误中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  ER1_PRIORITY       15
//定义UART1中断服务函数归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define  UART1_VECTABNUM    0

//定义UART2接收中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  RX2_PRIORITY       17
//定义UART2发送中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  TX2_PRIORITY       16
//定义UART2错误中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  ER2_PRIORITY       18
//定义UART2中断服务函数归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define  UART2_VECTABNUM    0

//定义UART3接收中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  RX3_PRIORITY       20
//定义UART3发送中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  TX3_PRIORITY       19
//定义UART3错误中断服务函数优先级,优先级范围1-255,数字越大优先级越高,优先级不可重复
#define  ER3_PRIORITY       21
//定义UART3中断服务函数归哪个内核管理,即中断是由谁响应处理,范围(CPU0 CPU1 DMA)不可设置为其他值
#define  UART3_VECTABNUM    0

//串口号枚举
typedef enum
{
    UART0,
    UART1,
    UART2,
    UART3,
}UART_enum;

//串口TX引脚枚举
typedef enum
{
    //串口0发送引脚
    TX0_P14_0,
    TX0_P14_1,
    TX0_P15_2,
    TX0_P15_3,
    //串口1发送引脚
    TX1_P02_2,
    TX1_P11_12,
    TX1_P15_0,
    TX1_P15_1,
    TX1_P15_4,
    TX1_P15_5,
    TX1_P20_10,
    TX1_P33_12,
    TX1_P33_13,
    //串口2发送引脚
    TX2_P02_0,
    TX2_P10_5,
    TX2_P14_2,
    TX2_P14_3,
    TX2_P33_8,
    TX2_P33_9,
    //串口3发送引脚
    TX3_P00_0,
    TX3_P00_1,
    TX3_P15_6,
    TX3_P15_7,
    TX3_P20_0,
    TX3_P20_3,
    TX3_P21_7,
}UART_tx_enum;

//串口RX引脚枚举
typedef enum
{
    //串口0接收引脚
    RX0_P14_1,
    RX0_P15_3,
    //串口1接收引脚
    RX1_P02_3,
    RX1_P11_10,
    RX1_P15_1,
    RX1_P15_5,
    RX1_P20_9,
    RX1_P33_13,
    //串口2接收引脚
    RX2_P02_0,
    RX2_P02_1,
    RX2_P10_6,
    RX2_P14_3,
    RX2_P33_8,
    //串口3接收引脚
    RX3_P00_1,
    RX3_P15_7,
    RX3_P20_3,
    RX3_P21_6,
}UART_rx_enum;

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
void init_uart(UART_tx_enum TxPin, UART_rx_enum RxPin, unsigned int baudrate);

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
void set_char_uart(UART_enum  uart, char ch);

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
void set_string_uart(UART_enum  uart, char *str);

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
void set_buff_uart(UART_enum  uart, unsigned char *buf, unsigned int len);

/**
*
* @brief    获取串口缓冲区接收数据的个数
* @param    uart        UART0~UART3
* @return   uint8
* @notes    使用前请先初始化对应串口
* Example:  get_count_uart(UART0);          // 获取串口0缓冲区接收数据的个数
*
**/
unsigned char get_count_uart(UART_enum  uart);

/**
*
* @brief    串口接收字节
* @param    uart        UART0~UART3
* @return   char
* @notes    使用前请先初始化对应串口
* Example:  get_char_uart(UART0);           // 接收一个字符
*
**/
char get_char_uart(UART_enum  uart);

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
char get_buff_uart(UART_enum  uart, unsigned char *data, unsigned char len);

#endif /* DMXLIBRARIES_DMX_UART_H_ */
