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
 * @file       dmx_flash.c
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

#include "dmx_flash.h"
#include "IfxScuWdt.h"
#include "IfxFlash.h"

/**
*
* @brief    对指定页写入数据
* @param    sector      需要写入的扇区的编号,范围0~11
* @param    page        需要写入的页编号,参数范围0-1023
* @param    buf         需要写入的数据地址,数组类型必须为unsigned long
* @return   void
* @notes
* Example:  write_page(0,0, &buf,100);  // 在0扇区的第0页写入数据&buf,长度为100
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
* @brief    读取指定页数据
* @param    sector      需要读取的扇区的编号,范围0~11
* @param    page        需要读取的页编号,参数范围0-1023
* @param    buf         需要读取的数据存放地址,数组类型必须为unsigned long
* @return   void
* @notes
* Example:  read_page(0,0, &rbuf,100);  // 读取0扇区的第0页传入数组&rbuf,读取长度为100
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
* @brief    扇区擦除
* @param    sector      需要擦除扇区的编号,范围0~11
* @return   void
* @notes
* Example:  erase_sector(0);        // 擦除编号0的扇区
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
