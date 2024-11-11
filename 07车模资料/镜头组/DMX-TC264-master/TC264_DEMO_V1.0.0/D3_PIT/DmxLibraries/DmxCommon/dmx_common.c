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
 * @file       dmx_common.c
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

#include "dmx_common.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;   // 事件同步变量

App_Cpu0 g_AppCpu0; // 频率信息变量

/**
*
* @brief    初始化芯片
* @param
* @return   void
* @notes
* Example:  init_chip();
*
**/
void init_chip(void)
{
    // 中断失能
    IfxCpu_disableInterrupts();
    // 关闭看门狗
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    // 获取时钟频率，便于查看当前系统运行频率
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();                       // 锁相环
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());  // 处理器
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();                       // 系统
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);
    // 中断使能
    IfxCpu_enableInterrupts();
}
