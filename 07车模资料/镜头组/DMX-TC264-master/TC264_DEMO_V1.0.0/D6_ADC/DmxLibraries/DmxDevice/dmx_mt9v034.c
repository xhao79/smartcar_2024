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
 * @file       dmx_mt9v034.c
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

#include "dmx_mt9v034.h"
#include "dmx_gpio.h"
#include "dmx_eru.h"
#include "dmx_dma.h"
#include "dmx_sccb.h"

// ԭʼͼ������
unsigned char MT9V034_Image_Data[MT9V034_IMAGEH][MT9V034_IMAGEW];

// д�뵽����ͷ������,��dmx_mt9v034.h���ѽ��к궨��,�˴������޸�
static unsigned int Config_MT9V034[10]=
{
    MT9V034_IMAGEW,                 // ��,����ͷͼ���
    MT9V034_IMAGEH,                 // ��,����ͷͼ���
    CAMERA_FPS,                     // ͼ��֡������
    CAMERA_EXPOSURE_TIME,           // �ع�ʱ��Խ��,ͼ��Խ��;ʱ�����,֡�ʻ��½�
    CAMERA_AUTO_EXPOSURE,           // �Զ��ع⿪��0:�ر��Զ��ع�,1:�����Զ��ع�
    CAMERA_AUTO_EXPOSURE_BRIGHTNESS,// �Զ��ع�ģʽ�����ȵ��ڷ�Χ(1~64)
    CAMERA_MAX_EXPOSURE_TIME,       // ����ع�ʱ��,�޸���������޸ıȽϰ�ʱ��ͼ����������
    CAMERA_MIN_EXPOSURE_TIME,       // ��С�ع�ʱ��,�޸���������޸�����ǿ��ʱ��ͼ����������
    CAMERA_CONTRAST,                // �Աȶȸߵ�����0:�ͶԱȶ�,1:�߶Աȶ�
    CAMERA_ANALOG_GAIN,             // ͼ��ģ����������,16~64,ͼ�������̶�
};

/**
*
* @brief    MT9V034����ͷ��ʼ��
* @param
* @return   void
* @notes
* Example:  Init_MT9V034();
*
**/
void Init_MT9V034(void)
{
    boolean interruptState = IfxCpu_disableInterrupts();

    // ��ʼ������ͷ����IO
    unsigned char i=0;
    for(i = 0; i < 8; i ++)
        init_gpio(P00 , i , InputPULLDOWN , 0);

    // ��ʼ������ͷͨѶ�ӿ�
    init_gpio(MT9V034_SCL_MODULE , MT9V034_SCL_PIN , OutputPUSHPULL , 1);
    init_gpio(MT9V034_SDA_MODULE, MT9V034_SDA_PIN, OutputPUSHPULL , 1);
    IfxPort_setPinPadDriver(MT9V034_SCL_MODULE, 3, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinPadDriver(MT9V034_SDA_MODULE, 2, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    // ��ȡ����ͷID
    unsigned short read;
    read = Set_Config_MT9V034(Config_MT9V034,0);
    if( read == 0XFFFF)
        while (1);          // SCCBͨѶʧ��,ֹͣ����
    else if(read != 0X1324)
        while (1);          // оƬID����ȷ,û����ȷ��ȡ������,�������ͷ����

    // д�������ͷ
    Set_Config_MT9V034(Config_MT9V034,1);

    // ���жϳ�ʼ��
    init_eru(EruP02_0, FALLING);
    // CLK��ʼ��
    init_eru(EruP02_1, RISING);
    // DMA��ʼ��
    init_dma((unsigned int)(&MODULE_P00.IN.U), (unsigned int)MT9V034_Image_Data, ERU_CH2_6_INT_PRIORITY);

    IfxCpu_restoreInterrupts(interruptState);
}

/**
*
* @brief    MT9V034����ͷ���������ع�ʱ��
* @param    time                    �ع�ʱ��
* @param    gain                    ͼ������
* @return   void
* @notes    ʹ��ǰ����ͷ��Ҫ��ʼ��
* Example:  Set_Exposure_Time_MT9V034(800);
*
**/
void Set_Exposure_Time_MT9V034(unsigned int time,unsigned int gain)
{
    Set_Exposure_Time(time,gain);
}
