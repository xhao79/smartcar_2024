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
 * @file       dmx_font.h
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

#ifndef DMXLIBRARIES_DMX_COMMON_DMX_FONT_H_
#define DMXLIBRARIES_DMX_COMMON_DMX_FONT_H_

//����ߴ�ѡ��
typedef enum
{
    Show6x8,
    Show8x16,
}SHOW_size_enum;

//������ɫѡ��
typedef enum
{
    WHITE    = (0xFFFF),                                                     // ��ɫ
    BLACK    = (0x0000),                                                     // ��ɫ
    BLUE     = (0x001F),                                                     // ��ɫ
    PURPLE   = (0xF81F),                                                     // ��ɫ
    PINK     = (0xFE19),                                                     // ��ɫ
    RED      = (0xF800),                                                     // ��ɫ
    MAGENTA  = (0xF81F),                                                     // Ʒ��
    GREEN    = (0x07E0),                                                     // ��ɫ
    CYAN     = (0x07FF),                                                     // ��ɫ
    YELLOW   = (0xFFE0),                                                     // ��ɫ
    BROWN    = (0xBC40),                                                     // ��ɫ
    GRAY     = (0x8430),                                                     // ��ɫ

}COLOR_enum;

extern const unsigned char Char6x8[][6];
extern const unsigned char Char8x16[][16];
extern const unsigned char OledChinese16x16[];
extern const unsigned char OledDMXLOGO128X54[896];
extern const unsigned char Chinese16x16[8][16];
extern const unsigned char Earth121x121[29282];

#endif /* DMXLIBRARIES_DMX_COMMON_DMX_FONT_H_ */
