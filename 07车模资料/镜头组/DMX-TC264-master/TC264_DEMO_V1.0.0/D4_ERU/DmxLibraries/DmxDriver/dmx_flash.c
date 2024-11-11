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
 * @file       dmx_flash.c
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

#include "dmx_flash.h"
#include "IfxScuWdt.h"
#include "IfxFlash.h"

/**
*
* @brief    ��ָ��ҳд������
* @param    sector      ��Ҫд��������ı��,��Χ0~11
* @param    page        ��Ҫд���ҳ���,������Χ0-1023
* @param    buf         ��Ҫд������ݵ�ַ,�������ͱ���Ϊunsigned long
* @return   void
* @notes
* Example:  write_page(0,0, &buf,100);  // ��0�����ĵ�0ҳд������&buf,����Ϊ100
*
**/
void write_page(unsigned char sector, unsigned short page, unsigned long *buf,unsigned short len)
{
    unsigned long sectorAddr = IfxFlash_dFlashTableEepLog[sector].start;
    unsigned short endInitSafetyPassword = IfxScuWdt_getSafetyWatchdogPassword();
    unsigned short i;
    for (i = 0; i < len / 2; i++)
    {
        unsigned long pageAddr = sectorAddr + (page + i) * IFXFLASH_DFLASH_PAGE_LENGTH;
        IfxFlash_enterPageMode(pageAddr);
        IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);

        IfxFlash_loadPage2X32(pageAddr, buf[2 * i], buf[2 * i + 1]);

        IfxScuWdt_clearSafetyEndinit(endInitSafetyPassword);
        IfxFlash_writePage(pageAddr);
        IfxScuWdt_setSafetyEndinit(endInitSafetyPassword);

        IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
    }
    if (len % 2)
    {
        unsigned int pageAddr = sectorAddr + (page + len / 2) * IFXFLASH_DFLASH_PAGE_LENGTH;
        IfxFlash_enterPageMode(pageAddr);
        IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);

        IfxFlash_loadPage2X32(pageAddr, buf[len], 0);

        IfxScuWdt_clearSafetyEndinit(endInitSafetyPassword);
        IfxFlash_writePage(pageAddr);
        IfxScuWdt_setSafetyEndinit(endInitSafetyPassword);

        IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
    }
}

/**
*
* @brief    ��ȡָ��ҳ����
* @param    sector      ��Ҫ��ȡ�������ı��,��Χ0~11
* @param    page        ��Ҫ��ȡ��ҳ���,������Χ0-1023
* @param    buf         ��Ҫ��ȡ�����ݴ�ŵ�ַ,�������ͱ���Ϊunsigned long
* @return   void
* @notes
* Example:  read_page(0,0, &rbuf,100);  // ��ȡ0�����ĵ�0ҳ��������&rbuf,��ȡ����Ϊ100
*
**/
void read_page(unsigned char sector, unsigned short page, unsigned long *rbuf, unsigned short len)
{
    unsigned long sectorAddr = IfxFlash_dFlashTableEepLog[sector].start;
    volatile unsigned long* pageAddr = (unsigned long*)(sectorAddr + page * IFXFLASH_DFLASH_PAGE_LENGTH);
    unsigned short i;
    for (i = 0; i < len; i++)
        rbuf[i] = *(pageAddr++);
}

/**
*
* @brief    ��������
* @param    sector      ��Ҫ���������ı��,��Χ0~11
* @return   void
* @notes
* Example:  erase_sector(0);        // �������0������
*
**/
void erase_sector(unsigned char sector)
{
    unsigned long sectorAddr = IfxFlash_dFlashTableEepLog[sector].start;
    unsigned short endInitSafetyPassword = IfxScuWdt_getSafetyWatchdogPassword();

    IfxScuWdt_clearSafetyEndinit(endInitSafetyPassword);
    IfxFlash_eraseSector(sectorAddr);
    IfxScuWdt_setSafetyEndinit(endInitSafetyPassword);

    IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
}
