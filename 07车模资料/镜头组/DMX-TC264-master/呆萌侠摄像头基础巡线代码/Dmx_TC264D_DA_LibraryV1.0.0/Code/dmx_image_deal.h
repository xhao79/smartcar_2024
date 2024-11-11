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
 * @file       dmx_image_deal.h
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

#ifndef CODE_DMX_IMAGE_DEAL_H_
#define CODE_DMX_IMAGE_DEAL_H_

#define DEAL_IMAGE_W    80  // 压缩图像的图像宽
#define DEAL_IMAGE_H    60  // 压缩图像的图像高

extern unsigned char Deal_Image_Gray[DEAL_IMAGE_H][DEAL_IMAGE_W];       // 压缩后的灰度图像
extern unsigned char Deal_Image_Binary[DEAL_IMAGE_H][DEAL_IMAGE_W];     // 二值化图像
extern unsigned char Car_State;                                         // 车状态,0:停车,1:正常

/**
*
* @brief    图像压缩
* @param    *in_image       原始图像
* @param    *out_image      压缩后的图像
* @return   void
* @notes
* Example:  Image_Compress(MT9V034_Image_Data[0],Deal_Image_Gray[0]);
*
**/
void Image_Compress(unsigned char *in_image,unsigned char *out_image);

/**
*
* @brief    大津法计算按图像二值化阈值
* @param    *image          需要计算阈值的图像
* @param    width           图像宽
* @param    height          图像高
* @param    pixel_threshold 图像阈值
* @return   unsigned char   大津法阈值
* @notes
* Example:  Image_Threshold(Deal_Image_Gray[0],DEAL_IMAGE_W,DEAL_IMAGE_H,150);
*
**/
unsigned char Image_Threshold(unsigned char *image, unsigned short width, unsigned short height, unsigned int image_max_threshold);

/**
 *
 * @brief    图像二值化
 * @param    *in_image       压缩后的图像
 * @param    *out_image      二值化后的图像
 * @return   void
 * @notes
 * Example:  Image_Binary(Deal_Image_Gray[0],Deal_Image_Binary[0],150);
 *
 **/

void Image_Binary(unsigned char *in_image,unsigned char *out_image, unsigned int image_max_threshold);

/**
*
* @brief    图像Sobel二值化
* @param    *in_image       压缩后的图像
* @param    *out_image      Sobel二值化后的图像
* @return   void
* @notes
* Example:  Image_Sobel(Deal_Image_Gray, Deal_Image_Binary, 120);
*
**/
void Image_Sobel(unsigned char in_image[DEAL_IMAGE_H][DEAL_IMAGE_W], unsigned char out_image[DEAL_IMAGE_H][DEAL_IMAGE_W], unsigned int threshold);

 /**
  *
  * @brief    图像滤波
  * @param    *in_image       需要滤波的图像
  * @return   void
  * @notes
  * Example:  Image_Filter(Deal_Image_Binary[0]);
  *
  **/
 void Image_Filter(unsigned char *in_image);

 /**
 *
 * @brief    图像扫线
 * @param    *in_image       需要处理的图像
 * @return   void
 * @notes
 * Example:  Image_Find_Line(Deal_Image_Binary[0]);
 *
 **/
 void Image_Find_Line(unsigned char *in_image);

 /**
  *
  * @brief    图像处理
  * @param    prospect            计算偏差的前瞻
  * @param    error_offset        偏差补偿
  * @return   void
  * @notes
  * Example:  Image_Deal(30,12.5);
  *
  **/
  float Image_Deal(unsigned char prospect, float error_offset);

#endif /* CODE_DMX_IMAGE_DEAL_H_ */
