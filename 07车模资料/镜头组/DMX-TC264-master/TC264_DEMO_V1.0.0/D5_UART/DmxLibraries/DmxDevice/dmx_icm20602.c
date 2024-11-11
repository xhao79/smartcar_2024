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
 * @file       dmx_icm20602.c
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

#include "dmx_icm20602.h"
#include "dmx_gpio.h"
#include "dmx_hard_spi.h"
#include "dmx_soft_spi.h"

float icm20602_acc_x  = 0, icm20602_acc_y  = 0, icm20602_acc_z  = 0;    // ICM20602���ٶȼ�����
float icm20602_gyro_x = 0, icm20602_gyro_y = 0, icm20602_gyro_z = 0;    // ICM20602�Ǽ��ٶ�����

// SPIЭ���д�����궨��
#if ICM20602_HARD_SPI
#define ICM20602_Write_Reg(reg, data)       write_8bit_reg_hard_spi(ICM20602_SPI, reg, data);
#define ICM20602_Read_Regs(reg, data,num)   read_8bit_regs_hard_spi(ICM20602_SPI, reg | 0x80, data, num);
#else
static SOFT_SPI_struct ICM20602_SPI;
#define ICM20602_Write_Reg(reg, data)       write_8bitreg_soft_spi(&ICM20602_SPI, reg, data);
#define ICM20602_Read_Regs(reg, data,num)   read_8bitregs_soft_spi(&ICM20602_SPI, reg | 0x80, data, num);
#endif

static float icm20602_acc_inv = 1, icm20602_gyro_inv = 1;               // ����ת��Ϊʵ���������ݵ�ת��ϵ��

/**
*
* @brief    ICM20602�����ǳ�ʼ��
* @param
* @return   void
* @notes    �û�����
* Example:  Init_ICM20602();
*
**/
void Init_ICM20602(void)
{
        // SPI��ʼ��
        #if ICM20602_HARD_SPI
            init_hard_spi(ICM20602_SPI, SPI_MODE0, ICM20602_SPI_SPEED, ICM20602_SPC_PIN, ICM20602_SDI_PIN, ICM20602_SDO_PIN, SPI_CS_NULL);
        #else
            init_soft_spi (&ICM20602_SPI, 0,ICM20602_SPC_MODULE,ICM20602_SPC_PIN, ICM20602_SDI_MODULE,ICM20602_SDI_PIN,ICM20602_SDO_MODULE,ICM20602_SDO_PIN);
        #endif
        init_gpio(ICM20602_CS_MODULE, ICM20602_CS_PIN, OutputPUSHPULL, 1);
        // ��ȡ�������ͺ��������Լ�
        unsigned char model = 0xff;
        while(1)
        {
            unsigned char time = 50;
            Read_Datas_ICM20602(WHO_AM_I, &model, 1);
            if(model == 0x12)
            {
                // ICM20602
                break;
            }
            else
            {
                Delay_Ms_ICM20602(10);
                time--;
                if(time < 0)
                {
                    while(1);
                    // ��������ԭ�������¼���
                    // ICM20602����,������µĸ��ʼ���
                    // ���ߴ������û�нӺ�
                }
            }
        }
        Write_Data_ICM20602(PWR_MGMT_1, 0x80); // ��λ�豸
        Delay_Ms_ICM20602(10);

        Write_Data_ICM20602(PWR_MGMT_1, 0x01);
        Delay_Ms_ICM20602(10);
        Write_Data_ICM20602(PWR_MGMT_2, 0x00);
        Delay_Ms_ICM20602(10);

        Write_Data_ICM20602(SMPLRT_DIV, 0x07);

        // ����ICM20602�����ǵ�ͨ�˲������������,ICM20602��MPU6050��Ϊͬһ�Ҳ�Ʒǰ�߿ɿ������ߵ�������
        Set_LowpassFilter_Range_ICM20602(MPU_ABW_218, MPU_GBW_176, MPU_FS_4G, MPU_FS_2000DPS);
}

/**
*
* @brief    ���ICM20602�����Ǽ��ٶ�
* @param
* @return   void
* @notes    ��λ:g(m/s^2),�û�����
* Example:  Get_Acc_ICM20602();
*
**/
void Get_Acc_ICM20602(void)
{
    unsigned char data[6];
    Read_Datas_ICM20602(ACCEL_XOUT_H, data, 6);
    icm20602_acc_x = icm20602_acc_inv * (short int)(((short int)data[0] << 8) | data[1]);
    icm20602_acc_y = icm20602_acc_inv * (short int)(((short int)data[2] << 8) | data[3]);
    icm20602_acc_z = icm20602_acc_inv * (short int)(((short int)data[4] << 8) | data[5]);
}

/**
*
* @brief    ���ICM20602�����ǽǼ��ٶ�
* @param
* @return   void
* @notes    ��λΪ:��/s,�û�����
* Example:  Get_Gyro_ICM20602();
*
**/
void Get_Gyro_ICM20602(void)
{
    unsigned char data[6];
    Read_Datas_ICM20602(GYRO_XOUT_H, data, 6);
    icm20602_gyro_x = icm20602_gyro_inv * (short int)(((short int)data[0] << 8) | data[1]);
    icm20602_gyro_y = icm20602_gyro_inv * (short int)(((short int)data[2] << 8) | data[3]);
    icm20602_gyro_z = icm20602_gyro_inv * (short int)(((short int)data[4] << 8) | data[5]);
}

/**
*
* @brief    ����ICM20602�����ǵ�ͨ�˲������������
* @param    abw                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @param    gbw                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @param    afs                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @param    gfs                 // ����dmx_mpu.h�ļ���ö�ٶ����в鿴
* @return   void
* @notes    ICM20602.c�ļ��ڲ�����,�û�������ó���
* Example:  Set_LowpassFilter_Range_ICM20602(MPU_ABW_218, MPU_GBW_176,MPU_FS_4G, MPU_FS_2000DPS);
*
**/
void Set_LowpassFilter_Range_ICM20602(enum mpu_acc_bw abw, enum mpu_gyro_bw gbw, enum mpu_acc_fs afs, enum mpu_gyro_fs gfs)
{
    Write_Data_ICM20602(MPU6050_CONFIG, gbw);
    Write_Data_ICM20602(ACCEL_CONFIG_2, abw);
    Write_Data_ICM20602(GYRO_CONFIG, gfs << 3);
    Write_Data_ICM20602(ACCEL_CONFIG, afs << 3);
    switch(afs)
    {
    case MPU_FS_2G:
        icm20602_acc_inv = (float)2.0 * 9.8 / 32768.0;   // ���ٶȼ�����Ϊ:��2g
        break;
    case MPU_FS_4G:
        icm20602_acc_inv = (float)4.0 * 9.8 / 32768.0;   // ���ٶȼ�����Ϊ:��4g
        break;
    case MPU_FS_8G:
        icm20602_acc_inv = (float)8.0 * 9.8 / 32768.0;   // ���ٶȼ�����Ϊ:��8g
        break;
    case MPU_FS_16G:
        icm20602_acc_inv = (float)16.0 * 9.8 / 32768.0;  // ���ٶȼ�����Ϊ:��16g
        break;
    default:
        icm20602_acc_inv = 1;                            // ��ת��Ϊʵ������
        break;
    }
    switch(gfs)
    {
    case MPU_FS_250DPS:
        icm20602_gyro_inv = (float)250.0 / 32768.0;      // ����������Ϊ:��250dps
        break;
    case MPU_FS_500DPS:
        icm20602_gyro_inv = (float)500.0 / 32768.0;      // ����������Ϊ:��500dps
        break;
    case MPU_FS_1000DPS:
        icm20602_gyro_inv = (float)1000.0 / 32768.0;     // ����������Ϊ:��1000dps
        break;
    case MPU_FS_2000DPS:
        icm20602_gyro_inv = (float)2000.0 / 32768.0;     // ����������Ϊ:��2000dps
        break;
    default:
        icm20602_gyro_inv = 1;                           // ��ת��Ϊʵ������
        break;
    }
}

/**
*
* @brief    ��������ʱ
* @param    time            ��ʱʱ��
* @return   void
* @notes    ICM20602.c�ļ��ڲ�����,�û�������ó���
* Example:  Delay_Ms_ICM20602(1);   // ��ʱ1msʱ��
*
**/
void Delay_Ms_ICM20602(unsigned int ms)
{
    while (--ms)
    {
        unsigned int x = 2501;
        while (--x);
    }
}

/**
*
* @brief    ICM20602������д����
* @param    reg                 �Ĵ���
* @param    data                ��Ҫд���üĴ���������
* @return   void
* @notes    ICM20602.c�ļ��ڲ�����,�û�������ó���
* Example:  Write_Reg_ICM20602(0X00,0X00);
*
**/
static void Write_Data_ICM20602(unsigned char reg,unsigned char data)
{
    ICM20602_CS_LEVEL(0);
    ICM20602_Write_Reg(reg, data);
    ICM20602_CS_LEVEL(1);
}

/**
*
* @brief    ICM20602�����Ƕ�����
* @param    reg                 �Ĵ���
* @param    data                �Ѷ��������ݴ���data
* @param    num                 ���ݸ���
* @return   void
* @notes    ICM20602.c�ļ��ڲ�����,�û�������ó���
* Example:  ICM20602_Read_Datas(0X00,0X00,1);
*
**/
static void Read_Datas_ICM20602(unsigned char reg, unsigned char *data, unsigned int num)
{
    ICM20602_CS_LEVEL(0);
    ICM20602_Read_Regs(reg, data, num);
    ICM20602_CS_LEVEL(1);
}
