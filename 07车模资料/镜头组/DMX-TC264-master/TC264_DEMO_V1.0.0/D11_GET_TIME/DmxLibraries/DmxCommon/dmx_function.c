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
 * @file       dmx_function.c
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

#include "dmx_function.h"
#include "math.h"
#include "string.h"
#include "stdint.h"
#include "ctype.h"
#include "errno.h"
#include "stdbool.h"

/**
*
* @brief    绝对值函数
* @param    int                 整数
* @return   int                 绝对值
* @notes
* Example:  abs_func(-2);
*
**/
int abs_func(int x)
{
    return (x >= 0) ? x : -x;
}

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
int limit_func(int x,int min,int max)
{
    return ((x) > (max) ? (max) : ((x) < -(min) ? -(min) : (x)));
}

/**
*
* @brief    字符串转整数
* @param    str                 字符串
* @return   int                 整数
* @notes
* Example:  str_to_int_func("-521");
*
**/
int str_to_int_func(char *str)
{
    if (str == NULL)
    {
        return 0;
    }

    long num = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-')
    {
        sign = -1;
        i = 1;
    }

    while (str[i] != '\0')
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
        num = num * 10 + (str[i] - '0');
        i++;
    }

    return sign * num;
}

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
void int_to_str_func(char *str, int num)
{
    uint8_t data_temp[16];
    size_t bit = 0;
    if (str == NULL)
    {
        return;
    }
    if (num < 0)
    {
        *str++ = '-';
        num = -num;
    }
    else if (num == 0)
    {
        *str++ = '0';
        return;
    }
    while (num != 0)
    {
        data_temp[bit++] = (unsigned char)abs_func(num % 10);
        num /= 10;
    }
    while (bit != 0)
    {
        *str++ = (data_temp[--bit] + '0');
    }
}

/**
*
* @brief    字符串转浮点数
* @param    str                     字符串指针
* @return   float                   浮点数
* @notes
* Example:  str_to_float_func("521.125");
*
**/
float str_to_float_func (char *str)
{
    uint8_t sign = 0;
    float temp = 0.0;
    float factor = 1.0;
    bool is_point_seen = false;
    bool is_number = false;
    int errno = 0;

    while (*str != '\0')
    {
        if (*str == '-')
        {
            sign = 1;
            str++;
        }
        else if (*str == '+')
        {
            str++;
        }
        else if (*str >= '0' && *str <= '9')
        {
            if (!is_number)
            {
                is_number = true;
                temp = (uint8_t)(*str - '0');
            }
            else
            {
                temp = temp * 10.0f + (uint8_t)(*str - '0');
            }
            str++;
        }
        else if (*str == '.')
        {
            if (is_point_seen || !is_number)
            {
                errno = EINVAL;
                break;
            }
            is_point_seen = true;
            str++;
            while (*str >= '0' && *str <= '9')
            {
                temp += (uint8_t)(*str - '0') / factor;
                factor *= 10.0f;
                str++;
            }
        }
        else
        {
            break;
        }
    }
    if (errno == EINVAL || !is_number)
    {
        return NAN;
    }
    return sign ? -temp : temp;
}

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
void float_to_str_func (char *str, float num, unsigned char point)
{
    int data_int = 0;
    int data_float = 0.0;
    int data_temp[8];
    int data_temp_point[6];
    unsigned char bit = point;
    if(NULL == str)
    {
        return;
    }
    data_int = (int)num;
    if(0 > num)
    {
        *str ++ = '-';
    }
    else if(0.0 == num)
    {
        *str ++ = '0';
        *str ++ = '.';
        *str = '0';
        return;
    }
    num = num - data_int;
    while(bit --)
        num = num * 10;

    data_float = (int)num;

    bit = 0;
    do
    {
        data_temp[bit ++] = data_int % 10;
        data_int /= 10;
    }
    while(0 != data_int);
    while(0 != bit)
    {
        *str ++ = (abs_func(data_temp[bit - 1]) + 0x30);
        bit --;
    }

    if(point != 0)
    {
        bit = 0;
        *str ++ = '.';
        if(0 == data_float)
        {
            *str = '0';
        }
        else
        {
            while(0 != point)
            {
                data_temp_point[bit ++] = data_float % 10;
                data_float /= 10;
                point --;
            }
            while(0 != bit)
            {
                *str ++ = (abs_func(data_temp_point[bit - 1]) + 0x30);
                bit --;
            }
        }
    }
}
