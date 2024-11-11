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
 * @file       dmx_function.h
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

#ifndef DMXLIBRARIES_DMX_COMMON_DMX_FUNCTION_H_
#define DMXLIBRARIES_DMX_COMMON_DMX_FUNCTION_H_

/**
*
* @brief    ����ֵ����
* @param    int                 ����
* @return   int                 ����ֵ
* @notes
* Example:  abs_func(-2);
*
**/
int abs_func(int x);

/**
*
* @brief    �޷�����
* @param    x                   ��Ҫ�޷�������
* @param    min                 �޷�����Сֵ
* @param    max                 �޷������ֵ
* @return   int                 �޷�ֵ
* @notes
* Example:  limit_func(110,-100,100);   // ����ֵΪ100
*
**/
int limit_func(int x,int min,int max);

/**
*
* @brief    �ַ���ת����
* @param    str                 �ַ���
* @return   int                 ����
* @notes
* Example:  str_to_int_func("-521");
*
**/
int str_to_int_func(char *str);

/**
*
* @brief    ����ת�ַ���
* @param    str                     �ַ���ָ��
* @param    num                     ����
* @return   void
* @notes
* Example:  int_to_str_func(buffer,-521);
*
**/
void int_to_str_func(char *str, int num);

/**
*
* @brief    �ַ���ת������
* @param    str                     �ַ���ָ��
* @return   float                   ������
* @notes
* Example:  str_to_float_func("521.125");
*
**/
float str_to_float_func (char *str);

/**
*
* @brief    ������ת�ַ���
* @param    str                     �ַ���ָ��
* @param    num                     ����
* @return   point                   С����λ��
* @notes
* Example:  float_to_str_func(buffer,521.21,2);
*
**/
void float_to_str_func (char *str, float num, unsigned char point);

#endif /* DMXLIBRARIES_DMX_COMMON_DMX_FUNCTION_H_ */
