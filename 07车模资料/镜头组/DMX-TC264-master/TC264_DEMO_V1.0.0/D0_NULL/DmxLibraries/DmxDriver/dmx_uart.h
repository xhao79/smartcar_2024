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
 * @file       dmx_uart.h
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

#ifndef DMXLIBRARIES_DMX_UART_H_
#define DMXLIBRARIES_DMX_UART_H_

//���ͺͽ��ջ�������С
#define ASC_TX_BUFFER_SIZE 256
#define ASC_RX_BUFFER_SIZE 256

//UART�жϲ�������
//����UART0�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  RX0_PRIORITY       10
//����UART0�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  TX0_PRIORITY       11
//����UART0�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  ER0_PRIORITY       12
//����UART0�жϷ��������ĸ��ں˹���,���ж�����˭��Ӧ����,��Χ(CPU0 CPU1 DMA)��������Ϊ����ֵ
#define  UART0_VECTABNUM    0

//����UART1�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  RX1_PRIORITY       14
//����UART1�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  TX1_PRIORITY       13
//����UART1�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  ER1_PRIORITY       15
//����UART1�жϷ��������ĸ��ں˹���,���ж�����˭��Ӧ����,��Χ(CPU0 CPU1 DMA)��������Ϊ����ֵ
#define  UART1_VECTABNUM    0

//����UART2�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  RX2_PRIORITY       17
//����UART2�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  TX2_PRIORITY       16
//����UART2�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  ER2_PRIORITY       18
//����UART2�жϷ��������ĸ��ں˹���,���ж�����˭��Ӧ����,��Χ(CPU0 CPU1 DMA)��������Ϊ����ֵ
#define  UART2_VECTABNUM    0

//����UART3�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  RX3_PRIORITY       20
//����UART3�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  TX3_PRIORITY       19
//����UART3�����жϷ��������ȼ�,���ȼ���Χ1-255,����Խ�����ȼ�Խ��,���ȼ������ظ�
#define  ER3_PRIORITY       21
//����UART3�жϷ��������ĸ��ں˹���,���ж�����˭��Ӧ����,��Χ(CPU0 CPU1 DMA)��������Ϊ����ֵ
#define  UART3_VECTABNUM    0

//���ں�ö��
typedef enum
{
    UART0,
    UART1,
    UART2,
    UART3,
}UART_enum;

//����TX����ö��
typedef enum
{
    //����0��������
    TX0_P14_0,
    TX0_P14_1,
    TX0_P15_2,
    TX0_P15_3,
    //����1��������
    TX1_P02_2,
    TX1_P11_12,
    TX1_P15_0,
    TX1_P15_1,
    TX1_P15_4,
    TX1_P15_5,
    TX1_P20_10,
    TX1_P33_12,
    TX1_P33_13,
    //����2��������
    TX2_P02_0,
    TX2_P10_5,
    TX2_P14_2,
    TX2_P14_3,
    TX2_P33_8,
    TX2_P33_9,
    //����3��������
    TX3_P00_0,
    TX3_P00_1,
    TX3_P15_6,
    TX3_P15_7,
    TX3_P20_0,
    TX3_P20_3,
    TX3_P21_7,
}UART_tx_enum;

//����RX����ö��
typedef enum
{
    //����0��������
    RX0_P14_1,
    RX0_P15_3,
    //����1��������
    RX1_P02_3,
    RX1_P11_10,
    RX1_P15_1,
    RX1_P15_5,
    RX1_P20_9,
    RX1_P33_13,
    //����2��������
    RX2_P02_0,
    RX2_P02_1,
    RX2_P10_6,
    RX2_P14_3,
    RX2_P33_8,
    //����3��������
    RX3_P00_1,
    RX3_P15_7,
    RX3_P20_3,
    RX3_P21_6,
}UART_rx_enum;

/**
*
* @brief    ����ģ���ʼ��
* @param    TxPin       ���ڷ��͹ܽ�
* @param    RxPin       ���ڽ��չܽ�
* @param    baudrate    ������
* @return   void
* @notes    TX���ź�RX���Ŵ��ں����Ӧ
* Example:  init_uart(TX0_P14_0,RX0_P14_1, 115200); // ��ʼ������0,����Ϊ(P14_0,P14_1)������115200,����żУ��,1ֹͣλ
*
**/
void init_uart(UART_tx_enum TxPin, UART_rx_enum RxPin, unsigned int baudrate);

/**
*
* @brief    ���ڷ����ֽ�
* @param    uart        UART0~UART3
* @param    ch          Ҫ���͵��ַ�
* @return   void
* @notes    ʹ��ǰ���ȳ�ʼ����Ӧ����
* Example:  set_char_uart(UART0,'A');       // ͨ������0�����ַ���A��
*
**/
void set_char_uart(UART_enum  uart, char ch);

/**
*
* @brief    ���ڷ����ַ�������
* @param    uart        UART0~UART3
* @param    str         Ҫ���͵��ַ����׵�ַ
* @return   void
* @notes    ��nullֹͣ����,ʹ��ǰ���ȳ�ʼ����Ӧ����
* Example:  set_string_uart(UART0,"1234");  // ͨ������0����4���ֽڡ�1234��
*
**/
void set_string_uart(UART_enum  uart, char *str);

/**
*
* @brief    ���ڷ����ֽں���
* @param    uart        UART0~UART3
* @param    buf         Ҫ���͵��ַ����׵�ַ
* @param    len         Ҫ���͵��ַ�������
* @return   void
* @notes    ʹ��ǰ���ȳ�ʼ����Ӧ����
* Example:  set_buff_uart(UART0,"1234",3);   // ͨ������0����3���ֽ�'1''2''3'
*
**/
void set_buff_uart(UART_enum  uart, unsigned char *buf, unsigned int len);

/**
*
* @brief    ��ȡ���ڻ������������ݵĸ���
* @param    uart        UART0~UART3
* @return   uint8
* @notes    ʹ��ǰ���ȳ�ʼ����Ӧ����
* Example:  get_count_uart(UART0);          // ��ȡ����0�������������ݵĸ���
*
**/
unsigned char get_count_uart(UART_enum  uart);

/**
*
* @brief    ���ڽ����ֽ�
* @param    uart        UART0~UART3
* @return   char
* @notes    ʹ��ǰ���ȳ�ʼ����Ӧ����
* Example:  get_char_uart(UART0);           // ����һ���ַ�
*
**/
char get_char_uart(UART_enum  uart);

/**
*
* @brief    ���ڽ���һ�������ַ�
* @param    uart        UART0~UART3
* @param    buf         �洢���������׵�ַ
* @param    len         ���ճ���
* @return   0
* @notes    ʹ��ǰ���ȳ�ʼ����Ӧ����
* Example:  get_buff_uart(UART0, data, 10); // ����10���ַ�
*
**/
char get_buff_uart(UART_enum  uart, unsigned char *data, unsigned char len);

#endif /* DMXLIBRARIES_DMX_UART_H_ */
