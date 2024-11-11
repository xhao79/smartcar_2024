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
 * @file       Cpu0_Main.c
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

#include "dmx_all.h"
#include "dmx_isr.h"

#pragma section all "cpu0_dsram"

void core0_main(void)
{
    // ��ʼ��оƬ
    init_chip();

    // �����û������
    // ��ʼ��GPIO
    init_gpio(P20,8, OutputPUSHPULL,0);
    // ��ʼ�����
    Init_Servos();
    // ��ʼ�����
    Init_Motor();
    // ��ʼ��IPS114��ʾ��
    Init_IPS();
    // ��ʼ��MT9V034����ͷ
    Init_MT9V034();
//    // ��ʼ��ICM42688������
//    Init_ICM42688();
    // ��ʼ����ʱ��5ms
    init_pit(CCU60, CH0, 5000);

    // �ȴ�˫��ȫ����ɳ�ʼ��
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // �ж�ʹ��
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
