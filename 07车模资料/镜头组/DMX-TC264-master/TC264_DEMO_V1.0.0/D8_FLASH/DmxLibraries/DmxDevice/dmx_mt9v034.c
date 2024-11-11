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
 * @file       dmx_mt9v034.c
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

#include "dmx_mt9v034.h"
#include "dmx_gpio.h"
#include "dmx_eru.h"
#include "dmx_dma.h"
#include "dmx_sccb.h"

// 原始图像数据
unsigned char MT9V034_Image_Data[MT9V034_IMAGEH][MT9V034_IMAGEW];

// 写入到摄像头的数据,在dmx_mt9v034.h中已进行宏定义,此处不可修改
static unsigned int Config_MT9V034[10]=
{
    MT9V034_IMAGEW,                 // 列,摄像头图像宽
    MT9V034_IMAGEH,                 // 行,摄像头图像高
    CAMERA_FPS,                     // 图像帧率设置
    CAMERA_EXPOSURE_TIME,           // 曝光时间越长,图像越亮;时间过长,帧率会下降
    CAMERA_AUTO_EXPOSURE,           // 自动曝光开关0:关闭自动曝光,1:开启自动曝光
    CAMERA_AUTO_EXPOSURE_BRIGHTNESS,// 自动曝光模式下亮度调节范围(1~64)
    CAMERA_MAX_EXPOSURE_TIME,       // 最大曝光时间,修改这里可以修改比较暗时的图像整体亮度
    CAMERA_MIN_EXPOSURE_TIME,       // 最小曝光时间,修改这里可以修改遇到强光时的图像整体亮度
    CAMERA_CONTRAST,                // 对比度高低设置0:低对比度,1:高对比度
    CAMERA_ANALOG_GAIN,             // 图像模拟增益设置,16~64,图像亮暗程度
};

/**
*
* @brief    MT9V034摄像头初始化
* @param
* @return   void
* @notes
* Example:  Init_MT9V034();
*
**/
void Init_MT9V034(void)
{
    boolean interruptState = IfxCpu_disableInterrupts();

    // 初始化摄像头数据IO
    unsigned char i=0;
    for(i = 0; i < 8; i ++)
        init_gpio(P00 , i , InputPULLDOWN , 0);

    // 初始化摄像头通讯接口
    init_gpio(MT9V034_SCL_MODULE , MT9V034_SCL_PIN , OutputPUSHPULL , 1);
    init_gpio(MT9V034_SDA_MODULE, MT9V034_SDA_PIN, OutputPUSHPULL , 1);
    IfxPort_setPinPadDriver(MT9V034_SCL_MODULE, 3, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinPadDriver(MT9V034_SDA_MODULE, 2, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    // 读取摄像头ID
    unsigned short read;
    read = Set_Config_MT9V034(Config_MT9V034,0);
    if( read == 0XFFFF)
        while (1);          // SCCB通讯失败,停止运行
    else if(read != 0X1324)
        while (1);          // 芯片ID不正确,没有正确读取到数据,检查摄像头接线

    // 写命令到摄像头
    Set_Config_MT9V034(Config_MT9V034,1);

    // 场中断初始化
    init_eru(EruP02_0, FALLING);
    // CLK初始化
    init_eru(EruP02_1, RISING);
    // DMA初始化
    init_dma((unsigned int)(&MODULE_P00.IN.U), (unsigned int)MT9V034_Image_Data, ERU_CH2_6_INT_PRIORITY);

    IfxCpu_restoreInterrupts(interruptState);
}

/**
*
* @brief    MT9V034摄像头单独设置曝光时间
* @param    time                    曝光时间
* @param    gain                    图像增益
* @return   void
* @notes    使用前摄像头需要初始化
* Example:  Set_Exposure_Time_MT9V034(800);
*
**/
void Set_Exposure_Time_MT9V034(unsigned int time,unsigned int gain)
{
    Set_Exposure_Time(time,gain);
}
