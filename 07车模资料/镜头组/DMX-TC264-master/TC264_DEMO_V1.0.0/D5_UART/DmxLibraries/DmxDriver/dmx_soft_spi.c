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
 * @file       dmx_soft_spi.c
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

#include "dmx_soft_spi.h"

/**
*
* @brief    软件SPI引脚初始化
* @param    soft_spi_obj        SPI结构体
* @param    spi_delay           SPI延时
* @param    sck_module          SCK端口
* @param    sck_pin             SCK引脚
* @param    mosi_module         MOSI端口
* @param    mosi_pin            MOSI引脚
* @param    miso_module         MISO端口
* @param    miso_pin            MISO引脚
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
* @brief    软件SPI写8bit数据
* @param    soft_spi_obj        SPI结构体
* @param    data                数据
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
* @brief    软件SPI写8bit寄存器数据
* @param    soft_spi_obj        SPI结构体
* @param    reg                 寄存器
* @param    data                数据
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
* @brief    软件SPI读8bit数据
* @param    soft_spi_obj        SPI结构体
* @param    data                数据
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
* @brief    软件SPI读8bit寄存器数据
* @param    soft_spi_obj        SPI结构体
* @param    reg                 寄存器
* @param    data                数据
* @param    len                 读取长度
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
* @brief    软件SPI写16bit数据
* @param    soft_spi_obj        SPI结构体
* @param    data                数据
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
* @brief    软件SPI读16bit数据
* @param    soft_spi_obj        SPI结构体
* @param    data                数据
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
