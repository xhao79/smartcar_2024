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
 * @file       dmx_mpu.c
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

#include "dmx_mpu.h"
#include "dmx_gpio.h"
#include "dmx_soft_iic.h"

float mpu_acc_x  = 0, mpu_acc_y  = 0, mpu_acc_z  = 0;   // MPU6050���ٶȼ�����
float mpu_gyro_x = 0, mpu_gyro_y = 0, mpu_gyro_z = 0;   // MPU6050����������

static float mpu_acc_inv = 1, mpu_gyro_inv = 1;         // ����ת��Ϊʵ���������ݵ�ת��ϵ��

static unsigned char GYROSCOPE_DEV_ADDR;                // �����ǵ�ַ

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
* @brief    MPU6050�����ǳ�ʼ��
* @param
* @return   void
* @notes    �û�����
* Example:  Init_MPU();
*
**/
void Init_MPU(void)
{
    // IIC��ʼ��
    #if MPU_HARD_IIC
        i2cdev_handle.deviceAddress = device_addr << 1;
        HardwareI2c_Init(IfxI2c0_SCL_P02_5_INOUT, IfxI2c0_SDA_P02_4_INOUT, 400 * 1000);
    #else
        init_soft_iic(&MPU, MPU_SCL_MODULE, MPU_SCL_PIN, MPU_SDA_MODULE, MPU_SDA_PIN, 200);
    #endif

    // ��ȡ�������ͺ��������Լ�
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
            slave_addr = slave_addr ^ 0x01; // ��ת�����ǵ�ַ���λ(0x69,0x68)
            Delay_Ms_MPU(10);
            time--;
            if(time < 0)
            {
                while(1);
                // ��������ԭ�������¼���
                // MPU6050����ICM20602����,������µĸ��ʼ���
                // ���ߴ������û�нӺ�
                // ������Ҫ�����������,������3.3V
            }
        }
    }
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, PWR_MGMT_1, 0x80);
    Delay_Ms_MPU(10);

    MPU_Write_Data(GYROSCOPE_DEV_ADDR, PWR_MGMT_1, 0x00);                 // �������״̬
    Delay_Ms_MPU(10);
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, PWR_MGMT_2, 0x00);
    Delay_Ms_MPU(10);

    MPU_Write_Data(GYROSCOPE_DEV_ADDR, SMPLRT_DIV, 0x07);                 // 125HZ������

    // ���������ǵ�ͨ�˲������������
    Set_LowpassFilter_Range_MPU(MPU_ABW_218, MPU_GBW_176, MPU_FS_4G, MPU_FS_2000DPS);

    MPU_Write_Data(GYROSCOPE_DEV_ADDR, USR_CONTROL, 0x00);                // �ر�MPU6050�Ը���IIC�豸�Ŀ���
    MPU_Write_Data(GYROSCOPE_DEV_ADDR, INT_PIN_CFG, 0x02);
}

/**
*
* @brief    ���MPU6050�����Ǽ��ٶ�
* @param
* @return   void
* @notes    ��λ:g(m/s^2),�û�����
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
* @brief    ���MPU6050�����ǽǼ��ٶ�
* @param
* @return   void
* @notes    ��λΪ:��/s,�û�����
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
* @brief    ����MPU6050�����ǵ�ͨ�˲������������
* @param    abw                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @param    gbw                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @param    afs                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @param    gfs                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @return   void
* @notes    dmx_mpu.c�ļ��ڲ�����,�û�������ó���
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
        mpu_acc_inv = (float)2.0 * 9.8 / 32768.0;       // ���ٶȼ�����Ϊ:��2g
        break;
    case MPU_FS_4G:
        mpu_acc_inv = (float)4.0 * 9.8 / 32768.0;       // ���ٶȼ�����Ϊ:��4g
        break;
    case MPU_FS_8G:
        mpu_acc_inv = (float)8.0 * 9.8 / 32768.0;       // ���ٶȼ�����Ϊ:��8g
        break;
    case MPU_FS_16G:
        mpu_acc_inv = (float)16.0 * 9.8 / 32768.0;      // ���ٶȼ�����Ϊ:��16g
        break;
    default:
        mpu_acc_inv = 1;                                // ��ת��Ϊʵ������
        break;
    }
    switch(gfs)
    {
    case MPU_FS_250DPS:
        mpu_gyro_inv = (float)250.0 / 32768.0;          // ����������Ϊ:��250dps
        break;
    case MPU_FS_500DPS:
        mpu_gyro_inv = (float)500.0 / 32768.0;          // ����������Ϊ:��500dps
        break;
    case MPU_FS_1000DPS:
        mpu_gyro_inv = (float)1000.0 / 32768.0;         // ����������Ϊ:��1000dps
        break;
    case MPU_FS_2000DPS:
        mpu_gyro_inv = (float)2000.0 / 32768.0;         // ����������Ϊ:��2000dps
        break;
    default:
        mpu_gyro_inv = 1;                               // ��ת��Ϊʵ������
        break;
    }
}

/**
*
* @brief    ��������ʱ
* @param    time            ��ʱʱ��
* @return   void
* @notes    dmx_mpu.c�ļ��ڲ�����,�û�������ó���
* Example:  Delay_Ms_MPU(2);    // ��ʱ2msʱ��
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
