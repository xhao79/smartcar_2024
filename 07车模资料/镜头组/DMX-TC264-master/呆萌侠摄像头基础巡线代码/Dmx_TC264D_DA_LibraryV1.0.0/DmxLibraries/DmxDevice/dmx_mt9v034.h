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
 * @file       dmx_mt9v034.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_MT9V034_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_MT9V034_H_

// ͼ��ֱ�������,�˴������޸�
// ֻ��188X120�ķֱ�����������һ��ͼ��
// �����ֱ�������������ͼ���Ͻ��н�ȡ�ᶪʧ�ӽ�������ǹ̶���ԭʼͼ��ֱ���
#define MT9V034_IMAGEW                      188     // ��,����ͷͼ���
#define MT9V034_IMAGEH                      120     // ��,����ͷͼ���

// ͼ��֡������
#define CAMERA_FPS                          50
// �ع�ʱ��Խ��,ͼ��Խ��,֡�ʻ��½�
#define CAMERA_EXPOSURE_TIME                600
// �Աȶȸߵ�����0:�ͶԱȶ�,1:�߶Աȶ�
#define CAMERA_CONTRAST                     0
// ͼ��ģ����������,16~64,ͼ�������̶�
#define CAMERA_ANALOG_GAIN                  32

// �Զ��ع⿪��0:�ر��Զ��ع�,1:�����Զ��ع�
#define CAMERA_AUTO_EXPOSURE                0
// �Զ��ع�ģʽ�����ȵ��ڷ�Χ(1~64)
#define CAMERA_AUTO_EXPOSURE_BRIGHTNESS     52
// ����ع�ʱ��,�޸���������޸ıȽϰ�ʱ��ͼ����������
#define CAMERA_MAX_EXPOSURE_TIME            250
// ��С�ع�ʱ��,�޸���������޸�����ǿ��ʱ��ͼ����������
#define CAMERA_MIN_EXPOSURE_TIME            1

// ԭʼͼ���ά��������
extern unsigned char MT9V034_Image_Data[MT9V034_IMAGEH][MT9V034_IMAGEW];

/**
*
* @brief    MT9V034����ͷ��ʼ��
* @param
* @return
* @notes
* Example:  Init_MT9V034();
*
**/
void Init_MT9V034(void);

/**
*
* @brief    MT9V034����ͷ���������ع�ʱ��
* @param    time                    �ع�ʱ��
* @return   void
* @notes    ʹ��ǰ����ͷ��Ҫ��ʼ��
* Example:  Set_Exposure_Time_MT9V034(800);
*
**/
void Set_Exposure_Time_MT9V034(unsigned int time,unsigned int gain);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_MT9V034_H_ */
