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
 * @file       dmx_hard_spi.c
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

#include "IFXQSPI_REGDEF.h"
#include "IfxQspi.h"
#include "dmx_gpio.h"
#include "dmx_delay.h"
#include "dmx_hard_spi.h"

Ifx_QSPI_BACON      bacon;
CS_pin_enum         spi_cs_pin;

/**
*
* @brief    硬件SPI初始化
* @param    spi_n           SPI模块
* @param    cs_pin          SPI CS引脚
* @param    sck_pin         SPI SCK引脚
* @param    mosi_pin        SPI MOSI引脚
* @param    miso_pin        选择SPI MISO引脚
* @param    mode            SPI模式
* @param    baud            波特率
* @return   void
* @notes
* Example:  init_hard_spi(SPI_2, SPI2_SCLK_P15_3, SPI2_MOSI_P15_5, SPI2_MISO_P15_4, SPI2_CS0_P15_2, 0, 1*1000*1000); // 硬件SPI初始,模式0,波特率为1Mhz
*
**/
void init_hard_spi (SPI_module_enum spi_n, SPI_mode_enum mode, unsigned int baud, SCK_pin_enum sck_pin, MOSI_pin_enum mosi_pin, MISO_pin_enum miso_pin, CS_pin_enum cs_pin)
{
    IfxQspi_SpiMaster_Config MasterConfig;
    IfxQspi_SpiMaster MasterHandle;
    IfxQspi_SpiMaster_Channel MasterChHandle;
    IfxQspi_SpiMaster_Pins MasterPins;
    IfxQspi_SpiMaster_Output SlsoPin;
    volatile Ifx_QSPI *moudle;

    spi_cs_pin  = cs_pin;

    moudle = IfxQspi_getAddress((IfxQspi_Index)spi_n);

    get_pin_addr_hard_spi(spi_n, sck_pin, mosi_pin, miso_pin, cs_pin, &MasterPins, &SlsoPin);

    IfxQspi_SpiMaster_initModuleConfig(&MasterConfig, moudle);
    MasterConfig.base.mode              = SpiIf_Mode_master;
    MasterConfig.base.maximumBaudrate   = MAX_BAUD;
    MasterConfig.base.isrProvider       = IfxSrc_Tos_cpu0;


    MasterConfig.pins = &MasterPins;
    IfxQspi_SpiMaster_initModule(&MasterHandle, &MasterConfig);

    IfxQspi_SpiMaster_ChannelConfig MasterChConfig;
    IfxQspi_SpiMaster_initChannelConfig(&MasterChConfig, &MasterHandle);


    MasterChConfig.base.baudrate = (float)baud;
    switch(mode)
    {
        case 0:
        {
            MasterChConfig.base.mode.clockPolarity = SpiIf_ClockPolarity_idleLow;
            MasterChConfig.base.mode.shiftClock    = SpiIf_ShiftClock_shiftTransmitDataOnTrailingEdge;
        }break;
        case 1:
        {
            MasterChConfig.base.mode.clockPolarity = SpiIf_ClockPolarity_idleLow;
            MasterChConfig.base.mode.shiftClock    = SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge;
        }break;
        case 2:
        {
            MasterChConfig.base.mode.clockPolarity = SpiIf_ClockPolarity_idleHigh;
            MasterChConfig.base.mode.shiftClock    = SpiIf_ShiftClock_shiftTransmitDataOnTrailingEdge;
        }break;
        case 3:
        {
            MasterChConfig.base.mode.clockPolarity = SpiIf_ClockPolarity_idleHigh;
            MasterChConfig.base.mode.shiftClock    = SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge;
        }break;
    }

    MasterChConfig.base.mode.dataHeading = SpiIf_DataHeading_msbFirst;
    MasterChConfig.base.mode.dataWidth   = 8;

    MasterChConfig.base.mode.csActiveLevel = Ifx_ActiveState_low;
    MasterChConfig.sls.output = SlsoPin;
    IfxQspi_SpiMaster_initChannel(&MasterChHandle, &MasterChConfig);

    if(SPI_CS_NULL == cs_pin)
    {
        IfxQspi_setSlaveSelectOutputControl(moudle, IfxQspi_ChannelId_0, FALSE, FALSE);
        spi_cs_pin      = SPI_CS_NULL;
        switch(spi_n)
        {
            case SPI_0: cs_pin = SPI0_CS0_P20_8; break;
            case SPI_1: cs_pin = SPI1_CS0_P20_8; break;
            case SPI_2: cs_pin = SPI2_CS0_P15_2; break;
            case SPI_3: cs_pin = SPI3_CS0_P02_4; break;
        }
    }

    IfxQspi_configPT1Event(moudle, IfxQspi_PhaseTransitionEvent_endOfFrame);

    bacon.U = moudle->BACON.U;
    bacon.B.DL      = 7;        // Data Length
    bacon.B.IDLE    = 1;        // Idle Delay Length
    bacon.B.IPRE    = 1;        // Prescaler for the Idle Delay
    bacon.B.LEAD    = 1;        // Leading Delay Length
    bacon.B.LPRE    = 1;        // Prescaler for the Leading Delay
    bacon.B.MSB     = 1;        // Shift MSB or LSB First
    bacon.B.PARTYP  = 0;        // Parity Type
    bacon.B.BYTE    = 0;        // Byte
    bacon.B.TRAIL   = 1;        // Trailing Delay Length
    bacon.B.TPRE    = 1;        // Prescaler for the Trailing Delay
    bacon.B.CS      = cs_pin%102/6-3;
}

/**
*
* @brief    硬件SPI清除接收缓存区数据
* @param    moudle          SPI模块
* @return   void
* @notes    内部调用
* Example:  clear_fifo_hard_spi(SPI_1);
*
**/
static void clear_fifo_hard_spi (Ifx_QSPI *moudle)
{
    unsigned int fifo_num;
    // 将之前fifo中的数据全读读取出来
    fifo_num = moudle->STATUS.B.RXFIFOLEVEL;
    while(fifo_num --)
    {
        (unsigned char)IfxQspi_readReceiveFifo(moudle);
    }
}

/**
*
* @brief    硬件SPI写8bit数据
* @param    spi_n           SPI模块
* @param    data            数据
* @return   void
* @notes
* Example:  write_8bit_hard_spi(SPI_1, 0x11);
*
**/
void write_8bit_hard_spi (SPI_module_enum spi_n, const unsigned char data)
{
    volatile Ifx_QSPI *moudle;                                  // 定义SPI模块对象
    moudle = IfxQspi_getAddress((IfxQspi_Index)spi_n);          // 获取模块地址
    IfxQspi_writeBasicConfigurationEndStream(moudle, bacon.U);  // 发送数据后CS拉高
    IfxQspi_writeTransmitFifo(moudle, data);                    // 将发送的数据写入缓冲区
    while(moudle->STATUS.B.TXFIFOLEVEL != 0);                   // 等待发送完毕
    while(moudle->STATUS.B.PT1F == 0);                          // 等待结束标志位
    IfxQspi_clearAllEventFlags(moudle);                         // 清除发送结束标志位
}

/**
*
* @brief    硬件SPI写16bit数据
* @param    spi_n           SPI模块
* @param    data            数据
* @return   void
* @notes
* Example:  write_16bit_hard_spi(SPI_1, 0x1111);
*
**/
void write_16bit_hard_spi (SPI_module_enum spi_n, const unsigned short data)
{
    volatile Ifx_QSPI *moudle;                                      // 定义SPI模块对象
    moudle = IfxQspi_getAddress((IfxQspi_Index)spi_n);              // 获取模块地址
    IfxQspi_writeBasicConfigurationBeginStream(moudle, bacon.U);    // 发送数据后CS继续保持为低
    IfxQspi_writeTransmitFifo(moudle, (unsigned char)((data & 0xFF00) >> 8)); // 将发送的数据写入缓冲区
    while(moudle->STATUS.B.TXFIFOLEVEL != 0);                       // 等待发送完毕
    IfxQspi_writeBasicConfigurationEndStream(moudle, bacon.U);      // 发送数据后CS拉高
    IfxQspi_writeTransmitFifo(moudle, (unsigned char)(data & 0x00FF));// 将发送的数据写入缓冲区
    while(moudle->STATUS.B.PT1F == 0);                              // 等待结束标志位
    IfxQspi_clearAllEventFlags(moudle);                             // 清除发送结束标志位
}

/**
*
* @brief    硬件SPI写8bit寄存器
* @param    spi_n           SPI模块
* @param    register_name   寄存器地址
* @param    data            数据
* @return   void
* @notes
* Example:  write_8bit_reg_hard_spi(SPI_1,0XFB,0x11);
*
**/
void write_8bit_reg_hard_spi (SPI_module_enum spi_n, const unsigned char register_name, const unsigned char data)
{
    volatile Ifx_QSPI *moudle;                                      // 定义SPI模块对象
    moudle = IfxQspi_getAddress((IfxQspi_Index)spi_n);              // 获取模块地址
    IfxQspi_writeBasicConfigurationBeginStream(moudle, bacon.U);    // 发送数据后CS继续保持为低
    clear_fifo_hard_spi(moudle);                                    // 清除接收缓存区
    IfxQspi_writeTransmitFifo(moudle, register_name);               // 将发送的数据写入缓冲区
    while(moudle->STATUS.B.TXFIFOLEVEL != 0);                       // 等待发送完毕
    IfxQspi_writeBasicConfigurationEndStream(moudle, bacon.U);      // 发送数据后CS拉高
    IfxQspi_writeTransmitFifo(moudle, data);                        // 将发送的数据写入缓冲区
    while(moudle->STATUS.B.TXFIFOLEVEL != 0);                       // 等待发送完毕
    while(moudle->STATUS.B.PT1F == 0);                              // 等待结束标志位
    IfxQspi_clearAllEventFlags(moudle);                             // 清除发送结束标志位
}

/**
*
* @brief    硬件SPI写8bit寄存器数组
* @param    spi_n           SPI模块
* @param    register_name   寄存器地址
* @param    data            数据
* @param    len             长度
* @return   void
* @notes
* Example:  write_8bit_regs_hard_spi(SPI_1, 0x11, data, 32);
*
**/
void write_8bit_regs_hard_spi (SPI_module_enum spi_n, const unsigned char register_name, const unsigned char *data, unsigned int len)
{
    volatile Ifx_QSPI *moudle;                                      // 定义SPI模块对象
    moudle = IfxQspi_getAddress((IfxQspi_Index)spi_n);              // 获取模块地址
    IfxQspi_writeBasicConfigurationBeginStream(moudle, bacon.U);    // 发送数据后CS继续保持为低
    IfxQspi_writeTransmitFifo(moudle, register_name);               // 将发送的数据写入缓冲区
    while(moudle->STATUS.B.TXFIFOLEVEL != 0);                       // 等待发送完毕
    do
    {
        if(len == 1)                                                // 最后一个数据
        {
            IfxQspi_writeBasicConfigurationEndStream(moudle, bacon.U);// 发送数据后CS拉高
        }
        IfxQspi_writeTransmitFifo(moudle, *data ++);                // 将发送的数据写入缓冲区
        while(moudle->STATUS.B.TXFIFOLEVEL != 0);                   // 等待发送完毕
    }while(-- len);
    while(moudle->STATUS.B.PT1F == 0);                              // 等待结束标志位
    IfxQspi_clearAllEventFlags(moudle);                             // 清除发送结束标志位
}

/**
*
* @brief    硬件SPI读8bit寄存器数据
* @param    spi_n           SPI模块
* @return   uint8           数据
* @notes
* Example:  read_8bit_hard_spi(SPI_1);
*
**/
unsigned char read_8bit_hard_spi (SPI_module_enum spi_n)
{
    volatile Ifx_QSPI *moudle;                                      // 定义SPI模块对象
    moudle = IfxQspi_getAddress((IfxQspi_Index)spi_n);              // 获取模块地址
    IfxQspi_writeBasicConfigurationEndStream(moudle, bacon.U);      // 发送数据后CS拉高
    clear_fifo_hard_spi(moudle);                                    // 清除接收缓存区
    IfxQspi_writeTransmitFifo(moudle, 0);                           // 将发送的数据写入缓冲区
    while(moudle->STATUS.B.RXFIFOLEVEL == 0);                       // 等待接收完毕
    while(moudle->STATUS.B.PT1F == 0);                              // 等待结束标志位
    IfxQspi_clearAllEventFlags(moudle);                             // 清除发送结束标志位
    return (uint8)IfxQspi_readReceiveFifo(moudle);                  // 返回接收到的数据
}

/**
*
* @brief    硬件SPI读8bit寄存器数组
* @param    spi_n           SPI模块
* @param    register_name   寄存器地址
* @param    data            数据
* @param    len             长度
* @return   void
* @notes
* Example:  read_8bit_regs_hard_spi(SPI_1, 0x11, data, 32);
*
**/
void read_8bit_regs_hard_spi (SPI_module_enum spi_n, const unsigned char register_name, unsigned char *data, unsigned int len)
{
    volatile Ifx_QSPI *moudle;                                      // 定义SPI模块对象
    moudle = IfxQspi_getAddress((IfxQspi_Index)spi_n);              // 获取模块地址
    clear_fifo_hard_spi(moudle);                                    // 清除接收缓存区
    IfxQspi_writeBasicConfigurationBeginStream(moudle, bacon.U);    // 发送数据后CS继续保持为低
    IfxQspi_writeTransmitFifo(moudle, register_name);               // 将发送的数据写入缓冲区
    while(moudle->STATUS.B.RXFIFOLEVEL == 0);                       // 等待接收完毕
    clear_fifo_hard_spi(moudle);                                    // 清除接收缓存区
    do
    {
        if(len == 1)
        {
            IfxQspi_writeBasicConfigurationEndStream(moudle, bacon.U);// 发送数据后CS拉高
        }
        IfxQspi_writeTransmitFifo(moudle, 0);                       // 将发送的数据写入缓冲区
        while(moudle->STATUS.B.RXFIFOLEVEL == 0);                   // 等待接收完毕
        *data ++ = (unsigned char)IfxQspi_readReceiveFifo(moudle);  // 保存接收到的数据
    }while(-- len);
    while(moudle->STATUS.B.PT1F == 0);                              // 等待结束标志位
    IfxQspi_clearAllEventFlags(moudle);                             // 清除发送结束标志位
}

/**
*
* @brief    硬件SPI引脚地址获取
* @param
* @return   void
* @notes    内部调用
* Example:
*
**/
void get_pin_addr_hard_spi (SPI_module_enum spi_n, SCK_pin_enum sck_pin, MOSI_pin_enum mosi_pin, MISO_pin_enum miso_pin, CS_pin_enum cs_pin, IfxQspi_SpiMaster_Pins *set_pin, IfxQspi_SpiMaster_Output *set_cs)
{
    set_pin->mrstMode  = IfxPort_InputMode_pullDown;
    set_pin->mtsrMode  = IfxPort_OutputMode_pushPull;
    set_pin->sclkMode  = IfxPort_OutputMode_pushPull;
    set_pin->pinDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1;
    set_cs->driver     = IfxPort_PadDriver_cmosAutomotiveSpeed1;
    set_cs->mode       = IfxPort_OutputMode_pushPull;
    switch(spi_n)
    {
        case SPI_0:
        {
            if      (SPI0_CLK_P20_11 == sck_pin)   set_pin->sclk = &IfxQspi0_SCLK_P20_11_OUT;
            else if (SPI0_CLK_P20_13 == sck_pin)   set_pin->sclk = &IfxQspi0_SCLK_P20_13_OUT;

            if      (SPI0_MOSI_P20_12 == mosi_pin)  set_pin->mtsr = &IfxQspi0_MTSR_P20_12_OUT;
            else if (SPI0_MOSI_P20_14 == mosi_pin)  set_pin->mtsr = &IfxQspi0_MTSR_P20_14_OUT;

            if      (SPI0_MISO_P20_12 == miso_pin)  set_pin->mrst = &IfxQspi0_MRSTA_P20_12_IN;

            if      (SPI0_CS0_P20_8   == cs_pin || SPI_CS_NULL == cs_pin) set_cs->pin = &IfxQspi0_SLSO0_P20_8_OUT;
            else if (SPI0_CS1_P20_9   == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO1_P20_9_OUT;
            else if (SPI0_CS2_P20_13  == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO2_P20_13_OUT;
            else if (SPI0_CS3_P11_10  == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO3_P11_10_OUT;
            else if (SPI0_CS4_P11_11  == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO4_P11_11_OUT;
            else if (SPI0_CS5_P11_2   == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO5_P11_2_OUT;
            else if (SPI0_CS6_P20_10  == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO6_P20_10_OUT;
            else if (SPI0_CS7_P33_5   == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO7_P33_5_OUT;
            else if (SPI0_CS8_P20_6   == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO8_P20_6_OUT;
            else if (SPI0_CS9_P20_3   == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO9_P20_3_OUT;
            else if (SPI0_CS13_P15_0  == cs_pin)    set_cs->pin   = &IfxQspi0_SLSO13_P15_0_OUT;

        }break;

        case SPI_1:
        {
            if      (SPI1_CLK_P10_2  == sck_pin)   set_pin->sclk = &IfxQspi1_SCLK_P10_2_OUT;
            else if (SPI1_CLK_P11_6  == sck_pin)   set_pin->sclk = &IfxQspi1_SCLK_P11_6_OUT;

            if      (SPI1_MOSI_P10_1  == mosi_pin)  set_pin->mtsr = &IfxQspi1_MTSR_P10_1_OUT;
            else if (SPI1_MOSI_P10_3  == mosi_pin)  set_pin->mtsr = &IfxQspi1_MTSR_P10_3_OUT;
            else if (SPI1_MOSI_P11_9  == mosi_pin)  set_pin->mtsr = &IfxQspi1_MTSR_P11_9_OUT;

            if      (SPI1_MISO_P10_1  == miso_pin)  set_pin->mrst = &IfxQspi1_MRSTA_P10_1_IN;
            else if (SPI1_MISO_P11_3  == miso_pin)  set_pin->mrst = &IfxQspi1_MRSTB_P11_3_IN;

            if      (SPI1_CS0_P20_8   == cs_pin  || SPI_CS_NULL  == cs_pin) set_cs->pin = &IfxQspi1_SLSO0_P20_8_OUT;
            else if (SPI1_CS1_P20_9   == cs_pin )   set_cs->pin   = &IfxQspi1_SLSO1_P20_9_OUT;
            else if (SPI1_CS2_P20_13  == cs_pin )   set_cs->pin   = &IfxQspi1_SLSO2_P20_13_OUT;
            else if (SPI1_CS3_P11_10  == cs_pin )   set_cs->pin   = &IfxQspi1_SLSO3_P11_10_OUT;
            else if (SPI1_CS4_P11_11  == cs_pin )   set_cs->pin   = &IfxQspi1_SLSO4_P11_11_OUT;
            else if (SPI1_CS5_P11_2   == cs_pin )   set_cs->pin   = &IfxQspi1_SLSO5_P11_2_OUT;
            else if (SPI1_CS6_P33_10  == cs_pin )   set_cs->pin   = &IfxQspi1_SLSO6_P33_10_OUT;
            else if (SPI1_CS7_P33_5   == cs_pin )   set_cs->pin   = &IfxQspi1_SLSO7_P33_5_OUT;
            else if (SPI1_CS8_P10_4   == cs_pin )   set_cs->pin   = &IfxQspi1_SLSO8_P10_4_OUT;
            else if (SPI1_CS9_P10_5   == cs_pin )   set_cs->pin   = &IfxQspi1_SLSO9_P10_5_OUT;
        }break;

        case SPI_2:
        {
            if      (SPI2_CLK_P13_0  == sck_pin)   set_pin->sclk = &IfxQspi2_SCLKN_P13_0_OUT;
            else if (SPI2_CLK_P13_1  == sck_pin)   set_pin->sclk = &IfxQspi2_SCLKP_P13_1_OUT;
            else if (SPI2_CLK_P15_3  == sck_pin)   set_pin->sclk = &IfxQspi2_SCLK_P15_3_OUT;
            else if (SPI2_CLK_P15_6  == sck_pin)   set_pin->sclk = &IfxQspi2_SCLK_P15_6_OUT;
            else if (SPI2_CLK_P15_8  == sck_pin)   set_pin->sclk = &IfxQspi2_SCLK_P15_8_OUT;

            if      (SPI2_MOSI_P13_3  == mosi_pin)  set_pin->mtsr = &IfxQspi2_MTSRP_P13_3_OUT;
            else if (SPI2_MOSI_P15_5  == mosi_pin)  set_pin->mtsr = &IfxQspi2_MTSR_P15_5_OUT;
            else if (SPI2_MOSI_P15_6  == mosi_pin)  set_pin->mtsr = &IfxQspi2_MTSR_P15_6_OUT;

            if      (SPI2_MISO_P15_2  == miso_pin)  set_pin->mrst = &IfxQspi2_MRSTE_P15_2_IN;
            else if (SPI2_MISO_P15_4  == miso_pin)  set_pin->mrst = &IfxQspi2_MRSTA_P15_4_IN;
            else if (SPI2_MISO_P15_7  == miso_pin)  set_pin->mrst = &IfxQspi2_MRSTB_P15_7_IN;
            else if (SPI2_MISO_P21_2  == miso_pin)  set_pin->mrst = &IfxQspi2_MRSTCN_P21_2_IN;
            else if (SPI2_MISO_P21_3  == miso_pin)  set_pin->mrst = &IfxQspi2_MRSTCP_P21_3_IN;

            if      (SPI2_CS0_P15_2   == cs_pin || SPI_CS_NULL == cs_pin) set_cs->pin = &IfxQspi2_SLSO0_P15_2_OUT;
            else if (SPI2_CS1_P14_2   == cs_pin)    set_cs->pin   = &IfxQspi2_SLSO1_P14_2_OUT;
            else if (SPI2_CS2_P14_6   == cs_pin)    set_cs->pin   = &IfxQspi2_SLSO2_P14_6_OUT;
            else if (SPI2_CS3_P14_3   == cs_pin)    set_cs->pin   = &IfxQspi2_SLSO3_P14_3_OUT;
            else if (SPI2_CS5_P15_1   == cs_pin)    set_cs->pin   = &IfxQspi2_SLSO5_P15_1_OUT;
            else if (SPI2_CS6_P33_13  == cs_pin)    set_cs->pin   = &IfxQspi2_SLSO6_P33_13_OUT;
            else if (SPI2_CS7_P20_10  == cs_pin)    set_cs->pin   = &IfxQspi2_SLSO7_P20_10_OUT;
            else if (SPI2_CS8_P20_6   == cs_pin)    set_cs->pin   = &IfxQspi2_SLSO8_P20_6_OUT;
            else if (SPI2_CS9_P20_3   == cs_pin)    set_cs->pin   = &IfxQspi2_SLSO9_P20_3_OUT;
        }break;

        case SPI_3:
        {
            if      (SPI3_CLK_P02_7  == sck_pin)   set_pin->sclk = &IfxQspi3_SCLK_P02_7_OUT;
            else if (SPI3_CLK_P22_0  == sck_pin)   set_pin->sclk = &IfxQspi3_SCLKN_P22_0_OUT;
            else if (SPI3_CLK_P22_1  == sck_pin)   set_pin->sclk = &IfxQspi3_SCLKP_P22_1_OUT;
            else if (SPI3_CLK_P22_3  == sck_pin)   set_pin->sclk = &IfxQspi3_SCLK_P22_3_OUT;
            else if (SPI3_CLK_P33_11 == sck_pin)   set_pin->sclk = &IfxQspi3_SCLK_P33_11_OUT;

            if      (SPI3_MOSI_P02_6  == mosi_pin)  set_pin->mtsr = &IfxQspi3_MTSR_P02_6_OUT;
            else if (SPI3_MOSI_P10_6  == mosi_pin)  set_pin->mtsr = &IfxQspi3_MTSR_P10_6_OUT;
            else if (SPI3_MOSI_P22_0  == mosi_pin)  set_pin->mtsr = &IfxQspi3_MTSR_P22_0_OUT;
            else if (SPI3_MOSI_P22_3  == mosi_pin)  set_pin->mtsr = &IfxQspi3_MTSRP_P22_3_OUT;
            else if (SPI3_MOSI_P33_12 == mosi_pin)  set_pin->mtsr = &IfxQspi3_MTSR_P33_12_OUT;

            if      (SPI3_MISO_P02_5  == miso_pin)  set_pin->mrst = &IfxQspi3_MRSTA_P02_5_IN;
            else if (SPI3_MISO_P22_1  == miso_pin)  set_pin->mrst = &IfxQspi3_MRSTE_P22_1_IN;
            else if (SPI3_MISO_P21_2  == miso_pin)  set_pin->mrst = &IfxQspi3_MRSTFN_P21_2_IN;
            else if (SPI3_MISO_P21_3  == miso_pin)  set_pin->mrst = &IfxQspi3_MRSTFP_P21_3_IN;
            else if (SPI3_MISO_P33_13 == miso_pin)  set_pin->mrst = &IfxQspi3_MRSTD_P33_13_IN;

            if      (SPI3_CS0_P02_4   == cs_pin || SPI_CS_NULL == cs_pin) set_cs->pin = &IfxQspi3_SLSO0_P02_4_OUT;
            else if (SPI3_CS1_P02_0   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO1_P02_0_OUT;
            else if (SPI3_CS1_P33_9   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO1_P33_9_OUT;
            else if (SPI3_CS2_P02_1   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO2_P02_1_OUT;
            else if (SPI3_CS2_P33_8   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO2_P33_8_OUT;
            else if (SPI3_CS3_P02_2   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO3_P02_2_OUT;
            else if (SPI3_CS4_P02_3   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO4_P02_3_OUT;
            else if (SPI3_CS5_P02_8   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO5_P02_8_OUT;
            else if (SPI3_CS6_P00_8   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO6_P00_8_OUT;
            else if (SPI3_CS7_P00_9   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO7_P00_9_OUT;
            else if (SPI3_CS7_P33_7   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO7_P33_7_OUT;
            else if (SPI3_CS8_P10_5   == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO8_P10_5_OUT;
            else if (SPI3_CS11_P33_10 == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO11_P33_10_OUT;
            else if (SPI3_CS12_P22_2  == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO12_P22_2_OUT;
            else if (SPI3_CS13_P23_1  == cs_pin)    set_cs->pin   = &IfxQspi3_SLSO13_P23_1_OUT;
        }break;
    }
}

