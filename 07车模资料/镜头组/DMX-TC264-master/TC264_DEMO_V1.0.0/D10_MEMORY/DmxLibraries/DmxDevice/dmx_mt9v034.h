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
 * @file       dmx_mt9v034.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_MT9V034_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_MT9V034_H_

// 图像分辨率设置,此处不可修改
// 只有188X120的分辨率是完整的一幅图像
// 其他分辨率是在完整的图像上进行截取会丢失视角因此我们固定了原始图像分辨率
#define MT9V034_IMAGEW                      188     // 列,摄像头图像宽
#define MT9V034_IMAGEH                      120     // 行,摄像头图像高

// 图像帧率设置
#define CAMERA_FPS                          50
// 曝光时间越长,图像越亮,帧率会下降
#define CAMERA_EXPOSURE_TIME                600
// 对比度高低设置0:低对比度,1:高对比度
#define CAMERA_CONTRAST                     0
// 图像模拟增益设置,16~64,图像亮暗程度
#define CAMERA_ANALOG_GAIN                  32

// 自动曝光开关0:关闭自动曝光,1:开启自动曝光
#define CAMERA_AUTO_EXPOSURE                0
// 自动曝光模式下亮度调节范围(1~64)
#define CAMERA_AUTO_EXPOSURE_BRIGHTNESS     52
// 最大曝光时间,修改这里可以修改比较暗时的图像整体亮度
#define CAMERA_MAX_EXPOSURE_TIME            250
// 最小曝光时间,修改这里可以修改遇到强光时的图像整体亮度
#define CAMERA_MIN_EXPOSURE_TIME            1

// 原始图像二维数组声明
extern unsigned char MT9V034_Image_Data[MT9V034_IMAGEH][MT9V034_IMAGEW];

/**
*
* @brief    MT9V034摄像头初始化
* @param
* @return
* @notes
* Example:  Init_MT9V034();
*
**/
void Init_MT9V034(void);

/**
*
* @brief    MT9V034摄像头单独设置曝光时间
* @param    time                    曝光时间
* @return   void
* @notes    使用前摄像头需要初始化
* Example:  Set_Exposure_Time_MT9V034(800);
*
**/
void Set_Exposure_Time_MT9V034(unsigned int time,unsigned int gain);

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_MT9V034_H_ */
