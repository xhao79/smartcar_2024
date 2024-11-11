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
 * @file       dmx_soft_iic.h
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

#ifndef DMXLIBRARIES_DMX_SOFT_IIC_H_
#define DMXLIBRARIES_DMX_SOFT_IIC_H_

#include "dmx_gpio.h"

#define ACK     1   // 主应答
#define NACK    0   // 从应答

typedef struct
{
    Ifx_P *             scl_module;
    unsigned char       scl_pin;
    Ifx_P *             sda_module;
    unsigned char       sda_pin;
    unsigned int        delay;
}SOFT_IIC_struct;

/**
*
* @brief    软件IIC引脚初始化
* @param    soft_iic_obj        IIC结构体
* @param    scl_module          SCL端口
* @param    scl_pin             SCL引脚
* @param    sda_module          SCL端口
* @param    sda_pin             SCL引脚
* @param    iic_delay           IIC延时
* @return   void
* @notes
* Example:  init_soft_iic(&MPU, MPU_SCL_MODULE, MPU_SCL_PIN, MPU_SDA_MODULE, MPU_SDA_PIN, 200);
*
**/
void init_soft_iic(SOFT_IIC_struct *soft_iic_obj,Ifx_P * scl_module,unsigned char scl_pin,Ifx_P * sda_module,unsigned char sda_pin,unsigned int iic_delay);

/**
*
* @brief    写数据到设备寄存器中
* @param    soft_iic_obj        IIC结构体
* @param    device_addr         设备地址
* @param    reg_addr            设备寄存器地址
* @param    data                数据
* @return   void
* @notes
* Example:  write_data_soft_iic(&MPU,addr,reg,data)
*
**/
void write_data_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char device_addr, unsigned char reg_addr, unsigned char data);

/**
*
* @brief    从设备寄存器读数据
* @param    soft_iic_obj        IIC结构体
* @param    device_addr         设备地址
* @param    reg_addr            设备寄存器地址
* @return   unsigned char
* @notes
* Example:  read_data_soft_iic(&MPU,addr,reg,data)
*
**/
unsigned char read_data_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char device_addr, unsigned char reg_addr);

/**
*
* @brief    从设备寄存器读取多字节数据
* @param    soft_iic_obj        IIC结构体
* @param    device_addr         设备地址
* @param    reg_addr            设备寄存器地址
* @param    data_addr           数据地址
* @param    num                 数据长度
* @return   void
* @notes
* Example:  read_datas_soft_iic(&MPU,addr,reg,data,num)
*
**/
void read_datas_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char device_addr, unsigned char reg_addr, unsigned char* data_addr, unsigned char num);

/**
*
* @brief    软件IIC延时函数
* @param    soft_iic_obj        IIC结构体
* @return   void
* @notes    内部调用
* Example:  delay_soft_iic(&MPU);
*
**/
static void delay_soft_iic(SOFT_IIC_struct *soft_iic_obj);

/**
*
* @brief    软件IIC开始
* @param    soft_iic_obj        IIC结构体
* @return   void
* @notes    内部调用
* Example:  start_soft_iic(&MPU);
*
**/
static void start_soft_iic(SOFT_IIC_struct *soft_iic_obj);

/**
*
* @brief    软件IIC停止
* @param    soft_iic_obj        IIC结构体
* @return   void
* @notes    内部调用
* Example:  stop_soft_iic(&MPU);
*
**/
static void stop_soft_iic(SOFT_IIC_struct *soft_iic_obj);

/**
*
* @brief    主机向从设备发送应答/非应答信号 1/0
* @param    soft_iic_obj        IIC结构体
* @param    ack_data            发送信号
* @return   void
* @notes    内部调用
* Example:  sendack_soft_iic(&MPU,NACK);
*
**/
static void sendack_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char ack_data);

/**
*
* @brief    主机等待从设备应答信号
* @param    soft_iic_obj        IIC结构体
* @return   int
* @notes    内部调用
* Example:  waitack_soft_iic(&MPU);
*
**/
static int waitack_soft_iic(SOFT_IIC_struct *soft_iic_obj);

/**
*
* @brief    发送单个字节
* @param    soft_iic_obj        IIC结构体
* @param    ch                  字节
* @return   void
* @notes    内部调用
* Example:  send_char_soft_iic(&MPU,0X66);
*
**/
static void send_char_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char ch);

/**
*
* @brief    接受一个字节数据
* @param    soft_iic_obj        IIC结构体
* @param    ack_x               应答信号
* @return   unsigned char       接受字节
* @notes    内部调用
* Example:  read_char_soft_iic(&MPU,NACK);
*
**/
static unsigned char read_char_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char ack_x);

#endif /* DMXLIBRARIES_DMX_SOFT_IIC_H_ */
