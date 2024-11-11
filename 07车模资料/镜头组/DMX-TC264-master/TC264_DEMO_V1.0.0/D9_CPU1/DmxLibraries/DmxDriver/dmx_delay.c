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
 * @file       dmx_delay.c
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

#include "dmx_delay.h"

static unsigned int systick_count[2];

/**
*
* @brief    systick延时函数
* @param    time            需要延时的时间
* @return   void
* @notes    中断里不要调用延时函数
* Example:  调用示例请使用dmx_delay.h文件中的宏定义
*
**/
void delay_systick(STM_module_enum stm, unsigned int time)
{
    unsigned long stm_clk;
    stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stm));
    IfxStm_waitTicks(IfxStm_getAddress((IfxStm_Index)stm), (unsigned long)((unsigned long long)stm_clk*time/1000000000));
}

/**
*
* @brief    systick定时器启动
* @param    stmn        选择使用的STM模块
* @return   void
* @notes
* Example:  start_systick(STM0);    // 记录下当前STM模块的时间
*
**/
void start_systick(STM_module_enum stm)
{
    systick_count[stm] = IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stm));
}

/**
*
* @brief    获取从start_systick(STM0);语句后到此处的时间
* @param    stmn            选择使用的模块
* @return   unsigned int    返回从start_systick()函数开始执行到现在的时间(单位为10ns)
* @notes
* Example:  unsigned int time = get_systick(STM0);  // 此time为start_systick()函数到此函数处的时间间隔
*
**/
unsigned int get_systick(STM_module_enum stm)
{
    unsigned long stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stm));
    return (unsigned long)((unsigned long long)(IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stm)) - systick_count[stm]) * 100000000 / stm_clk);
}
