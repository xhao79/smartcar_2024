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
 * @file       dmx_hard_spi.h
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

#ifndef DMXLIBRARIES_DMX_DRIVER_DMX_HARD_SPI_H_
#define DMXLIBRARIES_DMX_DRIVER_DMX_HARD_SPI_H_

#include "IfxQspi_SpiMaster.h"

#define MAX_BAUD    50000000

// SPIģ���
typedef enum
{
    SPI_0,
    SPI_1,
    SPI_2,
    SPI_3,
}SPI_module_enum;

// SPIģʽ
typedef enum
{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3,
}SPI_mode_enum;

// SPI CLK����
typedef enum
{
    // SPI0 CLK��ѡ����
    SPI0_CLK_P20_11 = 0  ,
    SPI0_CLK_P20_13,
    // SPI1 CLK��ѡ����
    SPI1_CLK_P10_2  = 102,
    SPI1_CLK_P11_6,
    // SPI2 CLK��ѡ����
    SPI2_CLK_P13_0,
    SPI2_CLK_P13_1,
    SPI2_CLK_P15_3,
    SPI2_CLK_P15_6,
    SPI2_CLK_P15_8,
    // SPI3 CLK��ѡ����
    SPI3_CLK_P02_7  = 306,
    SPI3_CLK_P22_0,
    SPI3_CLK_P22_1,
    SPI3_CLK_P22_3,
    SPI3_CLK_P33_11,
}SCK_pin_enum;

// SPI MOSI����
typedef enum
{
    // SPI0 MOSI��ѡ����
    SPI0_MOSI_P20_12 = 6,
    SPI0_MOSI_P20_14,
    // SPI1 MOSI��ѡ����
    SPI1_MOSI_P10_1 ,
    SPI1_MOSI_P10_3 ,
    SPI1_MOSI_P11_9 ,
    // SPI2 MOSI��ѡ����
    SPI2_MOSI_P13_3 = 210,
    SPI2_MOSI_P15_5 ,
    SPI2_MOSI_P15_6 ,
    // SPI3 MOSI��ѡ����
    SPI3_MOSI_P02_6 = 312,
    SPI3_MOSI_P10_6 ,
    SPI3_MOSI_P22_0 ,
    SPI3_MOSI_P22_3 ,
    SPI3_MOSI_P33_12,
}MOSI_pin_enum;

// SPI MISO����
typedef enum
{
    // SPI0 MISO��ѡ����
    SPI0_MISO_P20_12 = 12,
    // SPI1 MISO��ѡ����
    SPI1_MISO_P10_1 = 114,
    SPI1_MISO_P11_3,
    // SPI2 MISO��ѡ����
    SPI2_MISO_P15_2 = 216,
    SPI2_MISO_P15_4,
    SPI2_MISO_P15_7,
    SPI2_MISO_P21_2,
    SPI2_MISO_P21_3,
    // SPI3 MISO��ѡ����
    SPI3_MISO_P02_5 = 318,
    SPI3_MISO_P22_1,
    SPI3_MISO_P21_2,
    SPI3_MISO_P21_3,
    SPI3_MISO_P33_13,
}MISO_pin_enum;

// SPI CS����
typedef enum
{
    // SPI0 CS��ѡ����
    SPI0_CS0_P20_8   = 3*6 ,
    SPI0_CS1_P20_9   = 4*6 ,
    SPI0_CS2_P20_13  = 5*6 ,
    SPI0_CS3_P11_10  = 6*6 ,
    SPI0_CS4_P11_11  = 7*6 ,
    SPI0_CS5_P11_2   = 8*6 ,
    SPI0_CS6_P20_10  = 9*6 ,
    SPI0_CS7_P33_5   = 10*6,
    SPI0_CS8_P20_6   = 11*6,
    SPI0_CS9_P20_3   = 12*6,
    SPI0_CS13_P15_0  = 16*6,
    // SPI1 CS��ѡ����
    SPI1_CS0_P20_8   = 1*102+3*6 ,
    SPI1_CS1_P20_9   = 1*102+4*6 ,
    SPI1_CS2_P20_13  = 1*102+5*6 ,
    SPI1_CS3_P11_10  = 1*102+6*6 ,
    SPI1_CS4_P11_11  = 1*102+7*6 ,
    SPI1_CS5_P11_2   = 1*102+8*6 ,
    SPI1_CS6_P33_10  = 1*102+9*6 ,
    SPI1_CS7_P33_5   = 1*102+10*6,
    SPI1_CS8_P10_4   = 1*102+11*6,
    SPI1_CS9_P10_5   = 1*102+12*6,
    // SPI2 CS��ѡ����
    SPI2_CS0_P15_2   = 2*102+3*6 ,
    SPI2_CS1_P14_2   = 2*102+4*6 ,
    SPI2_CS2_P14_6   = 2*102+5*6 ,
    SPI2_CS3_P14_3   = 2*102+6*6 ,
    SPI2_CS5_P15_1   = 2*102+8*6 ,
    SPI2_CS6_P33_13  = 2*102+9*6 ,
    SPI2_CS7_P20_10  = 2*102+10*6,
    SPI2_CS8_P20_6   = 2*102+11*6,
    SPI2_CS9_P20_3   = 2*102+12*6,
    // SPI3 CS��ѡ����
    SPI3_CS0_P02_4   = 3*102+3*6 ,
    SPI3_CS1_P02_0   = 3*102+4*6 , SPI3_CS1_P33_9,
    SPI3_CS2_P02_1   = 3*102+5*6 , SPI3_CS2_P33_8,
    SPI3_CS3_P02_2   = 3*102+6*6 ,
    SPI3_CS4_P02_3   = 3*102+7*6 ,
    SPI3_CS5_P02_8   = 3*102+8*6 ,
    SPI3_CS6_P00_8   = 3*102+9*6 ,
    SPI3_CS7_P00_9   = 3*102+10*6, SPI3_CS7_P33_7,
    SPI3_CS8_P10_5   = 3*102+11*6,
    SPI3_CS11_P33_10 = 3*102+14*6,
    SPI3_CS12_P22_2  = 3*102+15*6,
    SPI3_CS13_P23_1  = 3*102+16*6,
    SPI_CS_NULL,
}CS_pin_enum;

/**
*
* @brief    Ӳ��SPI��ʼ��
* @param    spi_n           SPIģ��
* @param    cs_pin          SPI CS����
* @param    sck_pin         SPI SCK����
* @param    mosi_pin        SPI MOSI����
* @param    miso_pin        ѡ��SPI MISO����
* @param    mode            SPIģʽ
* @param    baud            ������
* @return   void
* @notes
* Example:  init_hard_spi(SPI_2, SPI2_SCLK_P15_3, SPI2_MOSI_P15_5, SPI2_MISO_P15_4, SPI2_CS0_P15_2, 0, 1*1000*1000); // Ӳ��SPI��ʼ,ģʽ0,������Ϊ1Mhz
*
**/
void init_hard_spi (SPI_module_enum spi_n, SPI_mode_enum mode, unsigned int baud, SCK_pin_enum sck_pin, MOSI_pin_enum mosi_pin, MISO_pin_enum miso_pin, CS_pin_enum cs_pin);

/**
*
* @brief    Ӳ��SPI������ջ���������
* @param    spi_n           SPIģ��
* @return   void
* @notes    �ڲ�����
* Example:  clear_fifo_hard_spi(SPI_1);
*
**/
static void clear_fifo_hard_spi (Ifx_QSPI *moudle);

/**
*
* @brief    Ӳ��SPIд8bit����
* @param    spi_n           SPIģ��
* @param    data            ����
* @return   void
* @notes
* Example:  write_8bit_hard_spi(SPI_1, 0x11);
*
**/
void write_8bit_hard_spi (SPI_module_enum spi_n, const unsigned char data);

/**
*
* @brief    Ӳ��SPIд16bit����
* @param    spi_n           SPIģ��
* @param    data            ����
* @return   void
* @notes
* Example:  write_16bit_hard_spi(SPI_1, 0x1111);
*
**/
void write_16bit_hard_spi (SPI_module_enum spi_n, const unsigned short data);

/**
*
* @brief    Ӳ��SPIд8bit�Ĵ���
* @param    spi_n           SPIģ��
* @param    register_name   �Ĵ�����ַ
* @param    data            ����
* @return   void
* @notes
* Example:  write_8bit_reg_hard_spi(SPI_1,0XFB,0x11);
*
**/
void write_8bit_reg_hard_spi (SPI_module_enum spi_n, const unsigned char register_name, const unsigned char data);

/**
*
* @brief    Ӳ��SPIд8bit�Ĵ�������
* @param    spi_n           SPIģ��
* @param    register_name   �Ĵ�����ַ
* @param    data            ����
* @param    len             ����
* @return   void
* @notes
* Example:  write_8bit_regs_hard_spi(SPI_1, 0x11, data, 32);
*
**/
void write_8bit_regs_hard_spi (SPI_module_enum spi_n, const unsigned char register_name, const unsigned char *data, unsigned int len);

/**
*
* @brief    Ӳ��SPI��8bit�Ĵ�������
* @param    spi_n           SPIģ��
* @return   uint8           ����
* @notes
* Example:  read_8bit_hard_spi(SPI_1);
*
**/
unsigned char read_8bit_hard_spi (SPI_module_enum spi_n);

/**
*
* @brief    Ӳ��SPI��8bit�Ĵ�������
* @param    spi_n           SPIģ��
* @param    register_name   �Ĵ�����ַ
* @param    data            ����
* @param    len             ����
* @return   void
* @notes
* Example:  read_8bit_regs_hard_spi(SPI_1, 0x11, data, 32);
*
**/
void read_8bit_regs_hard_spi (SPI_module_enum spi_n, const unsigned char register_name, unsigned char *data, unsigned int len);

/**
*
* @brief    Ӳ��SPI���ŵ�ַ��ȡ
* @param
* @return   void
* @notes    �ڲ�����
* Example:
*
**/
void get_pin_addr_hard_spi (SPI_module_enum spi_n, SCK_pin_enum sck_pin, MOSI_pin_enum mosi_pin, MISO_pin_enum miso_pin, CS_pin_enum cs_pin, IfxQspi_SpiMaster_Pins *set_pin, IfxQspi_SpiMaster_Output *set_cs);

#endif /* DMXLIBRARIES_DMX_DRIVER_DMX_HARD_SPI_H_ */
