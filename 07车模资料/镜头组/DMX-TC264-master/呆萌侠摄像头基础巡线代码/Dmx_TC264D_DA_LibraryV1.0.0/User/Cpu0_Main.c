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
 * @file       Cpu0_Main.c
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

#include "dmx_all.h"
#include "dmx_isr.h"

#pragma section all "cpu0_dsram"

void core0_main(void)
{
    // 初始化芯片
    init_chip();

    // 放置用户代码段
    // 初始化GPIO
    init_gpio(P20,8, OutputPUSHPULL,0);
    // 初始化舵机
    Init_Servos();
    // 初始化电机
    Init_Motor();
    // 初始化IPS114显示屏
    Init_IPS();
    // 初始化MT9V034摄像头
    Init_MT9V034();
//    // 初始化ICM42688陀螺仪
//    Init_ICM42688();
    // 初始化定时器5ms
    init_pit(CCU60, CH0, 5000);

    // 等待双核全部完成初始化
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // 中断使能
    IfxCpu_enableInterrupts();
    init_gpio(P21,5, OutputPUSHPULL,0);
    while(1)
    {
//        Show_Float_IPS(170,64,final_error,3,2,BLACK,WHITE,Show8x16);
//        Show_Int_IPS(170,16*5,left_rear_speed,4,BLACK,WHITE,Show8x16);
//        Show_Int_IPS(170,16*6,right_rear_speed,4,BLACK,WHITE,Show8x16);
//        Show_Image_Binary_IPS(0,0,Deal_Image_Binary[0],80,60,160,120);

        Show_Image_IPS(0,0,MT9V034_Image_Data[0],188,120,188,120,0);
    }
}

#pragma section all restore
