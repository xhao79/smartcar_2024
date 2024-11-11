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
 * @file       dmx_isr.h
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

#ifndef USER_DMX_ISR_H_
#define USER_DMX_ISR_H_

extern void ccu60_ch0_irq(void);
extern void ccu60_ch1_irq(void);
extern void ccu61_ch0_irq(void);
extern void ccu61_ch1_irq(void);

extern void eru_ch0_4_irq(void);
extern void eru_ch1_5_irq(void);
extern void eru_ch2_6_irq(void);

extern void rx0_irq(void);
extern void tx0_irq(void);
extern void er0_irq(void);

extern void rx1_irq(void);
extern void tx1_irq(void);
extern void er1_irq(void);

extern void rx2_irq(void);
extern void tx2_irq(void);
extern void er2_irq(void);

extern void rx3_irq(void);
extern void tx3_irq(void);
extern void er3_irq(void);

#endif /* USER_DMX_ISR_H_ */
