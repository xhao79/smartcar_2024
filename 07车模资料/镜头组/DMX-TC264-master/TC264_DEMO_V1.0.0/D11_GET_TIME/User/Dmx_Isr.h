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
 * @file       dmx_isr.h
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
