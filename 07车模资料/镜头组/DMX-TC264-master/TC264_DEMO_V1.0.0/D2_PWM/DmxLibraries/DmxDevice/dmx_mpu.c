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
 * @file       dmx_mpu.c
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

#include "dmx_mpu.h"
#include "dmx_gpio.h"
#include "dmx_soft_iic.h"

float mpu_acc_x  = 0, mpu_acc_y  = 0, mpu_acc_z  = 0;   // MPU6050加速度计数据
float mpu_gyro_x = 0, mpu_gyro_y = 0, mpu_gyro_z = 0;   // MPU6050陀螺仪数据

static float mpu_acc_inv = 1, mpu_gyro_inv = 1;         // 数据转换为实际物理数据的转换系数

static unsigned char GYROSCOPE_DEV_ADDR;                // 陀螺仪地址

#if MPU_HARD_IIC
#define MPU_Write_Data(addr,reg,data)      HardwareI2c_Writereg(reg, data, 1)
#define MPU_Read_Datas(addr,reg,data,num)  HardwareI2c_Readreg(reg, data,num)
#else
static SOFT_IIC_struct MPU;
#define MPU_Write_Data(addr,reg,data)      write_data_soft_iic(&MPU,addr,reg,data)
#define MPU_Read_Datas(addr,reg,data,num)  read_datas_soft_iic(&MPU,addr,reg,data,num)
#endif

/**
*
* @brief    MPU6050陀螺仪初始化
* @param
* @return   void
* @notes    用户调用
* Example:  Init_MPU();
*
**/
void Init_MPU(void)
{
    // IIC初始化
    #if MPU_HARD_IIC
        i2cdev_handle.deviceAddress = device_addr << 1;
        HardwareI2c_Init(IfxI2c0_SCL_P02_5_INOUT, IfxI2c0_SDA_P02_4_INOUT, 400 * 1000);
    #else
        init_soft_iic(&MPU, MPU_SCL_MODULE, MPU_SCL_PIN, MPU_SDA_MODULE, MPU_SDA_PIN, 200);
    #endif

    // 读取陀螺仪型号陀螺仪自检
    unsigned char model = 0xff;
    unsigned char slave_addr = 0x68;
    while(1)
    {
        unsigned char time = 50;
        MPU_Read_Datas(slave_addr, WHO_AM_I, &model, 1);
        if(model == 0x68)
        {
            // MPU6050,104
            GYROSCOPE_DEV_ADDR=0x68;
            break;
        }
        else if(model == 0x12)
        {
            // ICM20602
            GYROSCOPE_DEV_ADDR=0x69;
            break;
        }
        else
        {
            slave_addr = slave_addr ^ 0x01; // 反转陀螺仪地址最低位(0x69,0x68)
            Delay_Ms_MPU(10);
            time--;
            if(time < 0)
            {
                while(1);
                // 卡在这里原因有以下几点
                // MPU6050或者ICM20602坏了,如果是新的概率极低
                // 接线错误或者没有接好
                // 可能需要外接上拉电阻,上拉到3.3V
            }
        }
    }
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, PWR_MGMT_1, 0x80);
    Delay_Ms_MPU(10);

    MPU_Write_Data(GYROSCOPE_DEV_ADDR, PWR_MGMT_1, 0x00);                 // 解除休眠状态
    Delay_Ms_MPU(10);
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, PWR_MGMT_2, 0x00);
    Delay_Ms_MPU(10);

    MPU_Write_Data(GYROSCOPE_DEV_ADDR, SMPLRT_DIV, 0x07);                 // 125HZ采样率

    // 设置陀螺仪低通滤波器带宽和量程
    Set_LowpassFilter_Range_MPU(MPU_ABW_218, MPU_GBW_176, MPU_FS_4G, MPU_FS_2000DPS);

    MPU_Write_Data(GYROSCOPE_DEV_ADDR, USR_CONTROL, 0x00);                // 关闭MPU6050对辅助IIC设备的控制
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, INT_PIN_CFG, 0x02);
}

/**
*
* @brief    获得MPU6050陀螺仪加速度
* @param
* @return   void
* @notes    单位:g(m/s^2),用户调用
* Example:  Get_Acc_MPU();
*
**/
void Get_Acc_MPU(void)
{
    unsigned char data[6];
    MPU_Read_Datas(GYROSCOPE_DEV_ADDR, ACCEL_XOUT_H, data, 6);
    mpu_acc_x = mpu_acc_inv * (short int)(((short int)data[0] << 8) | data[1]);
    mpu_acc_y = mpu_acc_inv * (short int)(((short int)data[2] << 8) | data[3]);
    mpu_acc_z = mpu_acc_inv * (short int)(((short int)data[4] << 8) | data[5]);
}

/**
*
* @brief    获得MPU6050陀螺仪角加速度
* @param
* @return   void
* @notes    单位为:°/s,用户调用
* Example:  Get_Gyro_MPU();
*
**/
void Get_Gyro_MPU(void)
{
    unsigned char data[6];
    MPU_Read_Datas(GYROSCOPE_DEV_ADDR, GYRO_XOUT_H, data, 6);
    mpu_gyro_x = mpu_gyro_inv * (short int)(((short int)data[0] << 8) | data[1]);
    mpu_gyro_y = mpu_gyro_inv * (short int)(((short int)data[2] << 8) | data[3]);
    mpu_gyro_z = mpu_gyro_inv * (short int)(((short int)data[4] << 8) | data[5]);
}

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
void Set_LowpassFilter_Range_MPU(enum mpu_acc_bw abw, enum mpu_gyro_bw gbw, enum mpu_acc_fs afs, enum mpu_gyro_fs gfs)
{
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, MPU6050_CONFIG, gbw);
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, ACCEL_CONFIG_2, abw);
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, GYRO_CONFIG, gfs << 3);
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, ACCEL_CONFIG, afs << 3);
    switch(afs)
    {
    case MPU_FS_2G:
        mpu_acc_inv = (float)2.0 * 9.8 / 32768.0;       // 加速度计量程为:±2g
        break;
    case MPU_FS_4G:
        mpu_acc_inv = (float)4.0 * 9.8 / 32768.0;       // 加速度计量程为:±4g
        break;
    case MPU_FS_8G:
        mpu_acc_inv = (float)8.0 * 9.8 / 32768.0;       // 加速度计量程为:±8g
        break;
    case MPU_FS_16G:
        mpu_acc_inv = (float)16.0 * 9.8 / 32768.0;      // 加速度计量程为:±16g
        break;
    default:
        mpu_acc_inv = 1;                                // 不转化为实际数据
        break;
    }
    switch(gfs)
    {
    case MPU_FS_250DPS:
        mpu_gyro_inv = (float)250.0 / 32768.0;          // 陀螺仪量程为:±250dps
        break;
    case MPU_FS_500DPS:
        mpu_gyro_inv = (float)500.0 / 32768.0;          // 陀螺仪量程为:±500dps
        break;
    case MPU_FS_1000DPS:
        mpu_gyro_inv = (float)1000.0 / 32768.0;         // 陀螺仪量程为:±1000dps
        break;
    case MPU_FS_2000DPS:
        mpu_gyro_inv = (float)2000.0 / 32768.0;         // 陀螺仪量程为:±2000dps
        break;
    default:
        mpu_gyro_inv = 1;                               // 不转化为实际数据
        break;
    }
}

/**
*
* @brief    陀螺仪延时
* @param    time            延时时间
* @return   void
* @notes    dmx_mpu.c文件内部调用,用户无需调用尝试
* Example:  Delay_Ms_MPU(2);    // 延时2ms时间
*
**/
void Delay_Ms_MPU(unsigned int ms)
{
    while (--ms)
    {
        unsigned int x = 2501;
        while (--x);
    }
}
