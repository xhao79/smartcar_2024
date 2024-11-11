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
 * @file       dmx_image_deal.h
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

#ifndef CODE_DMX_IMAGE_DEAL_H_
#define CODE_DMX_IMAGE_DEAL_H_

#define DEAL_IMAGE_W    80  // ѹ��ͼ���ͼ���
#define DEAL_IMAGE_H    60  // ѹ��ͼ���ͼ���

extern unsigned char Deal_Image_Gray[DEAL_IMAGE_H][DEAL_IMAGE_W];       // ѹ����ĻҶ�ͼ��
extern unsigned char Deal_Image_Binary[DEAL_IMAGE_H][DEAL_IMAGE_W];     // ��ֵ��ͼ��
extern unsigned char Car_State;                                         // ��״̬,0:ͣ��,1:����

/**
*
* @brief    ͼ��ѹ��
* @param    *in_image       ԭʼͼ��
* @param    *out_image      ѹ�����ͼ��
* @return   void
* @notes
* Example:  Image_Compress(MT9V034_Image_Data[0],Deal_Image_Gray[0]);
*
**/
void Image_Compress(unsigned char *in_image,unsigned char *out_image);

/**
*
* @brief    ��򷨼��㰴ͼ���ֵ����ֵ
* @param    *image          ��Ҫ������ֵ��ͼ��
* @param    width           ͼ���
* @param    height          ͼ���
* @param    pixel_threshold ͼ����ֵ
* @return   unsigned char   �����ֵ
* @notes
* Example:  Image_Threshold(Deal_Image_Gray[0],DEAL_IMAGE_W,DEAL_IMAGE_H,150);
*
**/
unsigned char Image_Threshold(unsigned char *image, unsigned short width, unsigned short height, unsigned int image_max_threshold);

/**
 *
 * @brief    ͼ���ֵ��
 * @param    *in_image       ѹ�����ͼ��
 * @param    *out_image      ��ֵ�����ͼ��
 * @return   void
 * @notes
 * Example:  Image_Binary(Deal_Image_Gray[0],Deal_Image_Binary[0],150);
 *
 **/

void Image_Binary(unsigned char *in_image,unsigned char *out_image, unsigned int image_max_threshold);

/**
*
* @brief    ͼ��Sobel��ֵ��
* @param    *in_image       ѹ�����ͼ��
* @param    *out_image      Sobel��ֵ�����ͼ��
* @return   void
* @notes
* Example:  Image_Sobel(Deal_Image_Gray, Deal_Image_Binary, 120);
*
**/
void Image_Sobel(unsigned char in_image[DEAL_IMAGE_H][DEAL_IMAGE_W], unsigned char out_image[DEAL_IMAGE_H][DEAL_IMAGE_W], unsigned int threshold);

 /**
  *
  * @brief    ͼ���˲�
  * @param    *in_image       ��Ҫ�˲���ͼ��
  * @return   void
  * @notes
  * Example:  Image_Filter(Deal_Image_Binary[0]);
  *
  **/
 void Image_Filter(unsigned char *in_image);

 /**
 *
 * @brief    ͼ��ɨ��
 * @param    *in_image       ��Ҫ�����ͼ��
 * @return   void
 * @notes
 * Example:  Image_Find_Line(Deal_Image_Binary[0]);
 *
 **/
 void Image_Find_Line(unsigned char *in_image);

 /**
  *
  * @brief    ͼ����
  * @param    prospect            ����ƫ���ǰհ
  * @param    error_offset        ƫ���
  * @return   void
  * @notes
  * Example:  Image_Deal(30,12.5);
  *
  **/
  float Image_Deal(unsigned char prospect, float error_offset);

#endif /* CODE_DMX_IMAGE_DEAL_H_ */
