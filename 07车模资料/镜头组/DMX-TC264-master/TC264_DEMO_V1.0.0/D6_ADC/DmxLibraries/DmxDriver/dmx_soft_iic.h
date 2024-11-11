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
 * @file       dmx_soft_iic.h
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

#ifndef DMXLIBRARIES_DMX_SOFT_IIC_H_
#define DMXLIBRARIES_DMX_SOFT_IIC_H_

#include "dmx_gpio.h"

#define ACK     1   // ��Ӧ��
#define NACK    0   // ��Ӧ��

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
* @brief    ���IIC���ų�ʼ��
* @param    soft_iic_obj        IIC�ṹ��
* @param    scl_module          SCL�˿�
* @param    scl_pin             SCL����
* @param    sda_module          SCL�˿�
* @param    sda_pin             SCL����
* @param    iic_delay           IIC��ʱ
* @return   void
* @notes
* Example:  init_soft_iic(&MPU, MPU_SCL_MODULE, MPU_SCL_PIN, MPU_SDA_MODULE, MPU_SDA_PIN, 200);
*
**/
void init_soft_iic(SOFT_IIC_struct *soft_iic_obj,Ifx_P * scl_module,unsigned char scl_pin,Ifx_P * sda_module,unsigned char sda_pin,unsigned int iic_delay);

/**
*
* @brief    д���ݵ��豸�Ĵ�����
* @param    soft_iic_obj        IIC�ṹ��
* @param    device_addr         �豸��ַ
* @param    reg_addr            �豸�Ĵ�����ַ
* @param    data                ����
* @return   void
* @notes
* Example:  write_data_soft_iic(&MPU,addr,reg,data)
*
**/
void write_data_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char device_addr, unsigned char reg_addr, unsigned char data);

/**
*
* @brief    ���豸�Ĵ���������
* @param    soft_iic_obj        IIC�ṹ��
* @param    device_addr         �豸��ַ
* @param    reg_addr            �豸�Ĵ�����ַ
* @return   unsigned char
* @notes
* Example:  read_data_soft_iic(&MPU,addr,reg,data)
*
**/
unsigned char read_data_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char device_addr, unsigned char reg_addr);

/**
*
* @brief    ���豸�Ĵ�����ȡ���ֽ�����
* @param    soft_iic_obj        IIC�ṹ��
* @param    device_addr         �豸��ַ
* @param    reg_addr            �豸�Ĵ�����ַ
* @param    data_addr           ���ݵ�ַ
* @param    num                 ���ݳ���
* @return   void
* @notes
* Example:  read_datas_soft_iic(&MPU,addr,reg,data,num)
*
**/
void read_datas_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char device_addr, unsigned char reg_addr, unsigned char* data_addr, unsigned char num);

/**
*
* @brief    ���IIC��ʱ����
* @param    soft_iic_obj        IIC�ṹ��
* @return   void
* @notes    �ڲ�����
* Example:  delay_soft_iic(&MPU);
*
**/
static void delay_soft_iic(SOFT_IIC_struct *soft_iic_obj);

/**
*
* @brief    ���IIC��ʼ
* @param    soft_iic_obj        IIC�ṹ��
* @return   void
* @notes    �ڲ�����
* Example:  start_soft_iic(&MPU);
*
**/
static void start_soft_iic(SOFT_IIC_struct *soft_iic_obj);

/**
*
* @brief    ���IICֹͣ
* @param    soft_iic_obj        IIC�ṹ��
* @return   void
* @notes    �ڲ�����
* Example:  stop_soft_iic(&MPU);
*
**/
static void stop_soft_iic(SOFT_IIC_struct *soft_iic_obj);

/**
*
* @brief    ��������豸����Ӧ��/��Ӧ���ź� 1/0
* @param    soft_iic_obj        IIC�ṹ��
* @param    ack_data            �����ź�
* @return   void
* @notes    �ڲ�����
* Example:  sendack_soft_iic(&MPU,NACK);
*
**/
static void sendack_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char ack_data);

/**
*
* @brief    �����ȴ����豸Ӧ���ź�
* @param    soft_iic_obj        IIC�ṹ��
* @return   int
* @notes    �ڲ�����
* Example:  waitack_soft_iic(&MPU);
*
**/
static int waitack_soft_iic(SOFT_IIC_struct *soft_iic_obj);

/**
*
* @brief    ���͵����ֽ�
* @param    soft_iic_obj        IIC�ṹ��
* @param    ch                  �ֽ�
* @return   void
* @notes    �ڲ�����
* Example:  send_char_soft_iic(&MPU,0X66);
*
**/
static void send_char_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char ch);

/**
*
* @brief    ����һ���ֽ�����
* @param    soft_iic_obj        IIC�ṹ��
* @param    ack_x               Ӧ���ź�
* @return   unsigned char       �����ֽ�
* @notes    �ڲ�����
* Example:  read_char_soft_iic(&MPU,NACK);
*
**/
static unsigned char read_char_soft_iic(SOFT_IIC_struct *soft_iic_obj,unsigned char ack_x);

#endif /* DMXLIBRARIES_DMX_SOFT_IIC_H_ */
