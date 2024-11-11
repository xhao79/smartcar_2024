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
 * @file       dmx_soft_spi.c
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

#include "dmx_soft_spi.h"

/**
*
* @brief    ���SPI���ų�ʼ��
* @param    soft_spi_obj        SPI�ṹ��
* @param    spi_delay           SPI��ʱ
* @param    sck_module          SCK�˿�
* @param    sck_pin             SCK����
* @param    mosi_module         MOSI�˿�
* @param    mosi_pin            MOSI����
* @param    miso_module         MISO�˿�
* @param    miso_pin            MISO����
* @return   void
* @notes
* Example:  init_soft_spi(&OLED_SPI, 0, OLED_D0_MODULE,OLED_D0_PIN, OLED_D1_MODULE,OLED_D1_PIN,0,0);
*
**/
void init_soft_spi(SOFT_SPI_struct *soft_spi_obj, unsigned int spi_delay, Ifx_P *sck_module, unsigned char sck_pin, Ifx_P *mosi_module, unsigned char mosi_pin, Ifx_P *miso_module, unsigned char miso_pin)
{
    soft_spi_obj->delay = spi_delay;
    soft_spi_obj->sck_module = sck_module;
    soft_spi_obj->sck_pin = sck_pin;
    soft_spi_obj->mosi_module = mosi_module;
    soft_spi_obj->mosi_pin = mosi_pin;
    soft_spi_obj->miso_module = miso_module;
    soft_spi_obj->miso_pin = miso_pin;

    init_gpio(sck_module, sck_pin, OutputPUSHPULL, 1);
    init_gpio(mosi_module, mosi_pin, OutputPUSHPULL, 1);
    if(miso_pin!=0)
    init_gpio(miso_module, miso_pin, OutputPUSHPULL, 1);
}

/**
*
* @brief    ���SPIд8bit����
* @param    soft_spi_obj        SPI�ṹ��
* @param    data                ����
* @return   void
* @notes
* Example:  write_8bitdata_soft_spi(&OLED_SPI, 0x00);
*
**/
void write_8bitdata_soft_spi(SOFT_SPI_struct *soft_spi_obj, unsigned char data)
{
    unsigned char temp = 0;
    for(temp = 8; temp > 0; temp --)
    {
        set_level_gpio(soft_spi_obj->sck_module, soft_spi_obj->sck_pin, 0);
        if(0x80 & data)
        {
            set_level_gpio(soft_spi_obj->mosi_module, soft_spi_obj->mosi_pin, 1);
        }
        else
        {
            set_level_gpio(soft_spi_obj->mosi_module, soft_spi_obj->mosi_pin, 0);
        }
        set_level_gpio(soft_spi_obj->sck_module, soft_spi_obj->sck_pin, 1);
        data <<= 1;
    }
}

/**
*
* @brief    ���SPIд8bit�Ĵ�������
* @param    soft_spi_obj        SPI�ṹ��
* @param    reg                 �Ĵ���
* @param    data                ����
* @return   void
* @notes
* Example:  write_8bitreg_soft_spi(&OLED_SPI,0x00,0x00);
*
**/
void write_8bitreg_soft_spi(SOFT_SPI_struct *soft_spi_obj, unsigned char reg,unsigned char data)
{
    write_8bitdata_soft_spi(soft_spi_obj,reg);
    write_8bitdata_soft_spi(soft_spi_obj,data);
}

/**
*
* @brief    ���SPI��8bit����
* @param    soft_spi_obj        SPI�ṹ��
* @param    data                ����
* @return   void
* @notes
* Example:  read_8bitdata_soft_spi(&OLED_SPI,data);
*
**/
void read_8bitdata_soft_spi(SOFT_SPI_struct *soft_spi_obj, unsigned char *data)
{
    unsigned char temp = 0;
    for(temp = 8; temp > 0; temp --)
    {
        set_level_gpio(soft_spi_obj->sck_module, soft_spi_obj->sck_pin, 0);
        *data = *data << 1;
        *data |= get_level_gpio(soft_spi_obj->miso_module, soft_spi_obj->miso_pin);
        set_level_gpio(soft_spi_obj->sck_module, soft_spi_obj->sck_pin, 1);
    }
}

/**
*
* @brief    ���SPI��8bit�Ĵ�������
* @param    soft_spi_obj        SPI�ṹ��
* @param    reg                 �Ĵ���
* @param    data                ����
* @param    len                 ��ȡ����
* @return   void
* @notes
* Example:  read_8bitregs_soft_spi(&OLED_SPI,0XFG,data,2);
*
**/
void read_8bitregs_soft_spi(SOFT_SPI_struct *soft_spi_obj, unsigned char reg,unsigned char *data,unsigned int len)
{
    write_8bitdata_soft_spi(soft_spi_obj,reg);
    while(len--)
        read_8bitdata_soft_spi(soft_spi_obj,data++);
}

/**
*
* @brief    ���SPIд16bit����
* @param    soft_spi_obj        SPI�ṹ��
* @param    data                ����
* @return   void
* @notes
* Example:  write_16bitdata_soft_spi(&OLED_SPI, 0x0000);
*
**/
void write_16bitdata_soft_spi(SOFT_SPI_struct *soft_spi_obj,  unsigned short data)
{
    unsigned char temp = 0;
    for(temp = 16; 0 < temp; temp --)
    {
        set_level_gpio(soft_spi_obj->sck_module, soft_spi_obj->sck_pin, 0);
        if(0x8000 & data)
        {
            set_level_gpio(soft_spi_obj->mosi_module, soft_spi_obj->mosi_pin, 1);
        }
        else
        {
            set_level_gpio(soft_spi_obj->mosi_module, soft_spi_obj->mosi_pin, 0);
        }
        set_level_gpio(soft_spi_obj->sck_module, soft_spi_obj->sck_pin, 1);
        data <<= 1;
    }
}

/**
*
* @brief    ���SPI��16bit����
* @param    soft_spi_obj        SPI�ṹ��
* @param    data                ����
* @return   void
* @notes
* Example:  read_16bitdata_soft_spi(&OLED_SPI,data);
*
**/
void read_16bitdata_soft_spi(SOFT_SPI_struct *soft_spi_obj, unsigned short *data)
{
    unsigned char temp = 0;
    for(temp = 16; temp > 0; temp --)
    {
        set_level_gpio(soft_spi_obj->sck_module, soft_spi_obj->sck_pin, 0);
        *data = *data << 1;
        *data |= get_level_gpio(soft_spi_obj->miso_module, soft_spi_obj->miso_pin);
        set_level_gpio(soft_spi_obj->sck_module, soft_spi_obj->sck_pin, 1);
    }
}
