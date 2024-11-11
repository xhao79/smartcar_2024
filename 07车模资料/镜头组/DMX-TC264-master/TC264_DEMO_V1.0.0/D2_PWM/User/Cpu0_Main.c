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

/** ����������������
* PWM����ļ��ڸ���Ŀ�µ� -> DmxLibraries -> DmxDriver -> dmx_pwm.c��dmx_pwm.h��
* ������ΪPWM����,��������Ϊ���İ����ĸ�LED���ֺ�����Ч��
����������������**/

int led_pwm = 0;
unsigned char led_dir = 0;

void core0_main(void)
{
    // ��ʼ��оƬ
    init_chip();
    // �����û������

    // ��ʼ��P20_8����ΪPWM,Ƶ��Ϊ2KHZ,��ʼռ�ձ�Ϊ0
    init_pwm(ATOM2_7_P20_8, 2000, 0);
    // ��ʼ��P20_9����ΪPWM,Ƶ��Ϊ2KHZ,��ʼռ�ձ�Ϊ0
    init_pwm(ATOM2_5_P20_9, 2000, 0);
    // ��ʼ��P21_4����ΪPWM,Ƶ��Ϊ2KHZ,��ʼռ�ձ�Ϊ0
    init_pwm(ATOM1_2_P21_4, 2000, 0);
    // ��ʼ��P21_5����ΪPWM,Ƶ��Ϊ2KHZ,��ʼռ�ձ�Ϊ0
    init_pwm(ATOM1_3_P21_5, 2000, 0);

    // �ȴ�˫��ȫ����ɳ�ʼ��
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // �ж�ʹ��
    IfxCpu_enableInterrupts();
    while(1)
    {
        // LED����״̬
        if(!led_dir)
        {
            // LED��PWMֵ,��������Ϊ����,PWMԽ��Խ�ӽ��ڸߵ�ƽ��Խ��(�����İ���LEDΪ�͵�ƽ����)
            led_pwm += 50;
            // �ﵽ���ռ�ձ�,�л�����״̬
            if(led_pwm >= 10000)
                led_dir =!led_dir;
        }
        else
        {
            // LED��PWMֵ,��������Ϊ����,PWMԽСԽ�ӽ��ڵ͵�ƽ��Խ��(�����İ���LEDΪ�͵�ƽ����)
            led_pwm -= 50;
            // �ﵽ��Сռ�ձ�,�л�����״̬
            if(led_pwm <= 0)
                led_dir =!led_dir;
        }

        // P20_8�����µ�ռ�ձ�led_pwm
        set_duty_pwm(ATOM2_7_P20_8, led_pwm);
        // P20_9�����µ�ռ�ձ�(10000 - led_pwm)
        set_duty_pwm(ATOM2_5_P20_9, 10000 - led_pwm);
        // P21_4�����µ�ռ�ձ�led_pwm
        set_duty_pwm(ATOM1_2_P21_4, led_pwm);
        // P21_5�����µ�ռ�ձ�(10000 - led_pwm)
        set_duty_pwm(ATOM1_3_P21_5, 10000 - led_pwm);

        // STM0ģ����ʱ10ms
        Delay_ms(STM0,10);
    }
}

#pragma section all restore
