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
 * @file       dmx_encoder.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_ENCODER_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_ENCODER_H_

// ������ͨ��ö��
typedef enum
{
    ENCODEDR_T2,
    ENCODEDR_T3,
    ENCODEDR_T4,
    ENCODEDR_T5,
    ENCODEDR_T6
}ENCODER_GPT12_enum;

// ��������������ö��
typedef enum
{
    T2_COUNT_P00_7, // T2��ʱ��,�������ſ�ѡ��Χ
    T2_COUNT_P33_7,

    T3_COUNT_P02_6, // T3��ʱ��,�������ſ�ѡ��Χ
    CX0,// TC264�޴�����,�˴�ʹ��Ϊռλ���裡

    T4_COUNT_P02_8, // T4��ʱ��,�������ſ�ѡ��Χ
    CX1,// TC264�޴�����,�˴�ʹ��Ϊռλ���裡

    T5_COUNT_P21_7, // T5��ʱ��,�������ſ�ѡ��Χ
    T5_COUNT_P10_3,

    T6_COUNT_P20_3, // T6��ʱ��,�������ſ�ѡ��Χ
    T6_COUNT_P10_2,
}ENCODER_count_enum;

// ��������������ö��
typedef enum // ö�ٱ���������
{
    T2_DIR_P00_8,   // T2��ʱ��,�������ſ�ѡ��Χ
    T2_DIR_P33_6,

    T3_DIR_P02_7,   // T3��ʱ��,�������ſ�ѡ��Χ
    DX0,// TC264�޴�����,�˴�ʹ��Ϊռλ���裡

    T4_DIR_P00_9,   // T4��ʱ��,�������ſ�ѡ��Χ
    T4_DIR_P33_5,

    T5_DIR_P21_6,   // T5��ʱ��,�������ſ�ѡ��Χ
    T5_DIR_P10_1,

    T6_DIR_P20_0,   // T6��ʱ��,�������ſ�ѡ��Χ
    DX1,// TC264�޴�����,�˴�ʹ��Ϊռλ���裡
}ENCODER_dir_enum;

/**
*
* @brief    ��ʼ������������
* @param    gpt        ����ʹ�õļ�������
* @param    countpin   ��������
* @param    dirpin     ��������
* @return   void
* @notes    ���������������Լ���������ͷ�������Ӧ��Ӧͬһ����ʱ��
* Example:  Init_Encoder(ENCODEDR_T2, T2_COUNT_P33_7, T2_DIR_P33_6);
*
**/
void Init_Encoder(ENCODER_GPT12_enum gpt, ENCODER_count_enum countpin,ENCODER_dir_enum dirpin);

/**
*
* @brief    ��ȡ����������ֵ
* @param    gptn        ����ʹ�õļ�������
* @return   void
* @notes
* Example:  Get_Encoder(ENCODEDR_T2);
*
**/
short Get_Encoder(ENCODER_GPT12_enum gpt);//��ȡ����������ֵ

/**
*
* @brief    �������������ֵ
* @param    gptn        ����ʹ�õļ�������
* @return   void
* @notes
* Example:  Clear_Encoder(ENCODEDR_T2);
*
**/
void Clear_Encoder(ENCODER_GPT12_enum gpt);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_ENCODER_H_ */
