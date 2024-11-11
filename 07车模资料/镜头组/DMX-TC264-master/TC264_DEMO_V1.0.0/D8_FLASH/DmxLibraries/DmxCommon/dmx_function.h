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
 * @file       dmx_function.h
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

#ifndef DMXLIBRARIES_DMX_COMMON_DMX_FUNCTION_H_
#define DMXLIBRARIES_DMX_COMMON_DMX_FUNCTION_H_

/**
*
* @brief    绝对值函数
* @param    int                 整数
* @return   int                 绝对值
* @notes
* Example:  abs_func(-2);
*
**/
int abs_func(int x);

/**
*
* @brief    限幅函数
* @param    x                   需要限幅的数据
* @param    min                 限幅的最小值
* @param    max                 限幅的最大值
* @return   int                 限幅值
* @notes
* Example:  limit_func(110,-100,100);   // 返回值为100
*
**/
int limit_func(int x,int min,int max);

/**
*
* @brief    字符串转整数
* @param    str                 字符串
* @return   int                 整数
* @notes
* Example:  str_to_int_func("-521");
*
**/
int str_to_int_func(char *str);

/**
*
* @brief    整数转字符串
* @param    str                     字符串指针
* @param    num                     数据
* @return   void
* @notes
* Example:  int_to_str_func(buffer,-521);
*
**/
void int_to_str_func(char *str, int num);

/**
*
* @brief    字符串转浮点数
* @param    str                     字符串指针
* @return   float                   浮点数
* @notes
* Example:  str_to_float_func("521.125");
*
**/
float str_to_float_func (char *str);

/**
*
* @brief    浮点数转字符串
* @param    str                     字符串指针
* @param    num                     数据
* @return   point                   小数点位数
* @notes
* Example:  float_to_str_func(buffer,521.21,2);
*
**/
void float_to_str_func (char *str, float num, unsigned char point);

#endif /* DMXLIBRARIES_DMX_COMMON_DMX_FUNCTION_H_ */
