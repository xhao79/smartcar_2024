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

/** ！！！！！！！！
* 该例程为变量或函数体定义存放位置
* CPU1速度比CPU0快
* 建议程序由哪个CPU执行,则所用到的变量和函数放置在哪个CPU内
* 不指定变量定义位置则默认存放在CPU1,不指定函数加载位置默认从flash加载
！！！！！！！！**/

////////////////////////////////
// 数据定义在CPU0中
#pragma section all "cpu0_dsram"
// 数据在此语句体内定义则被分配到CPU0中
float test;
#pragma section all restore
// 定义结束

////////////////////////////////
// 函数定义在CPU0中
#pragma section all "cpu0_psram"
// 函数在此语句体内定义则被分配到CPU0中
void test_function(void)
{

}
#pragma section all restore
// 定义结束

////////////////////////////////
// 数据定义在CPU1中
#pragma section all "cpu1_dsram"
// 数据在此语句体内定义则被分配到CPU1中
float test1;
#pragma section all restore
// 定义结束

////////////////////////////////
// 函数定义在CPU1中
#pragma section all "cpu1_psram"
// 函数在此语句体内定义则被分配到CPU1中
void test_function1(void)
{

}
#pragma section all restore
// 定义结束

/** ！！！！！！！！
* 此段注释以上为变量或函数体定义存放位置的演示
！！！！！！！！**/

#pragma section all "cpu0_dsram"
void core0_main(void)
{
    // 初始化芯片
    init_chip();
    // 放置用户代码段


    // 等待双核全部完成初始化
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xffff);
    // 中断使能
    IfxCpu_enableInterrupts();
    while(1)
    {

    }
}
#pragma section all restore
