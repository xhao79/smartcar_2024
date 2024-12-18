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
 * @file       dmx_mpu.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_MPU_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_MPU_H_

// 通信方式选择,0:软件IIC,1:硬件IIC
#define MPU_HARD_IIC    0

// MPU6050陀螺仪模块管脚宏定义
// MPU,SCL管脚对应TC264引脚P20_11
#define MPU_SCL_MODULE  P20
#define MPU_SCL_PIN     11
// MPU,SDA管脚对应TC264引脚P20_14
#define MPU_SDA_MODULE  P20
#define MPU_SDA_PIN     14

// MPU6050加速度计数据和陀螺仪数据声明
extern float mpu_acc_x , mpu_acc_y , mpu_acc_z ;    // MPU6050加速度计数据
extern float mpu_gyro_x, mpu_gyro_y, mpu_gyro_z;    // MPU6050陀螺仪数据

enum mpu_acc_fs
{
    MPU_FS_2G,
    MPU_FS_4G,
    MPU_FS_8G,
    MPU_FS_16G,
    NUM_MPU_AFS
};
enum mpu_gyro_fs
{
    MPU_FS_250DPS,
    MPU_FS_500DPS,
    MPU_FS_1000DPS,
    MPU_FS_2000DPS,
    NUM_MPU_GFS
};
enum mpu_acc_bw
{
    MPU_ABW_XXX,
    MPU_ABW_218,
    MPU_ABW_99,
    MPU_ABW_45,
    MPU_ABW_21,
    MPU_ABW_10,
    MPU_ABW_5,
    MPU_ABW_420,
    NUM_MPU_ABW
};
enum mpu_gyro_bw
{
    MPU_GBW_250,
    MPU_GBW_176,
    MPU_GBW_92,
    MPU_GBW_41,
    MPU_GBW_20,
    MPU_GBW_10,
    MPU_GBW_5,
    NUM_MPU_GBW
};

/**
*
* @brief    MPU6050陀螺仪初始化
* @param
* @return   void
* @notes    用户调用
* Example:  Init_MPU();
*
**/
void Init_MPU(void);

/**
*
* @brief    获得MPU6050陀螺仪加速度
* @param
* @return   void
* @notes    单位:g(m/s^2),用户调用
* Example:  Get_Acc_MPU();
*
**/
void Get_Acc_MPU(void);

/**
*
* @brief    获得MPU6050陀螺仪角加速度
* @param
* @return   void
* @notes    单位为:°/s,用户调用
* Example:  Get_Gyro_MPU();
*
**/
void Get_Gyro_MPU(void);

/**
*
* @brief    设置MPU6050陀螺仪低通滤波器带宽和量程
* @param    abw                 // 可在dmx_mpu.h文件里枚举定义中查看
* @param    gbw                 // 可在dmx_mpu.h文件里枚举定义中查看
* @param    afs                 // 可在dmx_mpu.h文件里枚举定义中查看
* @param    gfs                 // 可在dmx_mpu.h文件里枚举定义中查看
* @return   void
* @notes    dmx_mpu.c文件内部调用,用户无需调用尝试
* Example:  Set_LowpassFilter_Range_MPU(MPU_ABW_218, MPU_GBW_176,MPU_FS_4G, MPU_FS_2000DPS);
*
**/
void Set_LowpassFilter_Range_MPU(enum mpu_acc_bw abw, enum mpu_gyro_bw gbw, enum mpu_acc_fs afs, enum mpu_gyro_fs gfs);

/**
*
* @brief    陀螺仪延时
* @param    time            延时时间
* @return   void
* @notes    dmx_mpu.c文件内部调用,用户无需调用尝试
* Example:  Delay_Ms_MPU(2);    // 延时2ms时间
*
**/
void Delay_Ms_MPU(unsigned int ms);

// MPU6050内部地址
#define XG_OFFS_TC_H            0x04
#define XG_OFFS_TC_L            0x05
#define YG_OFFS_TC_H            0x07
#define YG_OFFS_TC_L            0x08
#define ZG_OFFS_TC_H            0x0A
#define ZG_OFFS_TC_L            0x0B
#define SELF_TEST_X_ACCEL       0x0D
#define SELF_TEST_Y_ACCEL       0x0E
#define SELF_TEST_Z_ACCEL       0x0F
#define XG_OFFS_USRH            0x13
#define XG_OFFS_USRL            0x14
#define YG_OFFS_USRH            0x15
#define YG_OFFS_USRL            0x16
#define ZG_OFFS_USRH            0x17
#define ZG_OFFS_USRL            0x18
#define SMPLRT_DIV              0x19    //陀螺仪采样率，典型值：0x07(125Hz)
#define MPU6050_CONFIG          0x1A    //低通滤波频率，典型值：0x06(5Hz)
#define GYRO_CONFIG             0x1B    //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define ACCEL_CONFIG            0x1C    //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define ACCEL_CONFIG_2          0x1D
#define LP_MODE_CFG             0x1E
#define ACCEL_WOM_X_THR         0x20
#define ACCEL_WOM_Y_THR         0x21
#define ACCEL_WOM_Z_THR         0x22
#define FIFO_EN                 0x23
#define FSYNC_INT               0x36
#define INT_PIN_CFG             0x37    //设置6050辅助I2C为直通模式寄存器
#define INT_ENABLE              0x38
#define FIFO_WM_INT_STATUS      0x39
#define INT_STATUS              0x3A
#define ACCEL_XOUT_H            0x3B
#define ACCEL_XOUT_L            0x3C
#define ACCEL_YOUT_H            0x3D
#define ACCEL_YOUT_L            0x3E
#define ACCEL_ZOUT_H            0x3F
#define ACCEL_ZOUT_L            0x40
#define TEMP_OUT_H              0x41
#define TEMP_OUT_L              0x42
#define GYRO_XOUT_H             0x43
#define GYRO_XOUT_L             0x44
#define GYRO_YOUT_H             0x45
#define GYRO_YOUT_L             0x46
#define GYRO_ZOUT_H             0x47
#define GYRO_ZOUT_L             0x48
#define SELF_TEST_X_GYRO        0x50
#define SELF_TEST_Y_GYRO        0x51
#define SELF_TEST_Z_GYRO        0x52
#define FIFO_WM_TH1             0x60
#define FIFO_WM_TH2             0x61
#define SIGNAL_PATH_RESET       0x68
#define ACCEL_INTEL_CTRL        0x69
#define USR_CONTROL             0x6A    //关闭6050对辅助I2C设备的控制
#define PWR_MGMT_1              0x6B    //电源管理，典型值：0x00(正常启用)
#define PWR_MGMT_2              0x6C
#define I2C_IF                  0x70
#define FIFO_COUNTH             0x72
#define FIFO_COUNTL             0x73
#define FIFO_R_W                0x74
#define WHO_AM_I                0x75    //IIC地址寄存器(默认数值0x68，只读)
#define XA_OFFSET_H             0x77
#define XA_OFFSET_L             0x78
#define YA_OFFSET_H             0x7A
#define YA_OFFSET_L             0x7B
#define ZA_OFFSET_H             0x7D
#define ZA_OFFSET_L             0x7E

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_MPU_H_ */
