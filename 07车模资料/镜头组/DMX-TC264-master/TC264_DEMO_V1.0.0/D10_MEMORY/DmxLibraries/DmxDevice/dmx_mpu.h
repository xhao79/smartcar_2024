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
 * @file       dmx_mpu.h
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

#ifndef DMXLIBRARIES_DMX_DEVICE_DMX_MPU_H_
#define DMXLIBRARIES_DMX_DEVICE_DMX_MPU_H_

// ͨ�ŷ�ʽѡ��,0:���IIC,1:Ӳ��IIC
#define MPU_HARD_IIC    0

// MPU6050������ģ��ܽź궨��
// MPU,SCL�ܽŶ�ӦTC264����P20_11
#define MPU_SCL_MODULE  P20
#define MPU_SCL_PIN     11
// MPU,SDA�ܽŶ�ӦTC264����P20_14
#define MPU_SDA_MODULE  P20
#define MPU_SDA_PIN     14

// MPU6050���ٶȼ����ݺ���������������
extern float mpu_acc_x , mpu_acc_y , mpu_acc_z ;    // MPU6050���ٶȼ�����
extern float mpu_gyro_x, mpu_gyro_y, mpu_gyro_z;    // MPU6050����������

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
* @brief    MPU6050�����ǳ�ʼ��
* @param
* @return   void
* @notes    �û�����
* Example:  Init_MPU();
*
**/
void Init_MPU(void);

/**
*
* @brief    ���MPU6050�����Ǽ��ٶ�
* @param
* @return   void
* @notes    ��λ:g(m/s^2),�û�����
* Example:  Get_Acc_MPU();
*
**/
void Get_Acc_MPU(void);

/**
*
* @brief    ���MPU6050�����ǽǼ��ٶ�
* @param
* @return   void
* @notes    ��λΪ:��/s,�û�����
* Example:  Get_Gyro_MPU();
*
**/
void Get_Gyro_MPU(void);

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
void Set_LowpassFilter_Range_MPU(enum mpu_acc_bw abw, enum mpu_gyro_bw gbw, enum mpu_acc_fs afs, enum mpu_gyro_fs gfs);

/**
*
* @brief    ��������ʱ
* @param    time            ��ʱʱ��
* @return   void
* @notes    dmx_mpu.c�ļ��ڲ�����,�û�������ó���
* Example:  Delay_Ms_MPU(2);    // ��ʱ2msʱ��
*
**/
void Delay_Ms_MPU(unsigned int ms);

// MPU6050�ڲ���ַ
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
#define SMPLRT_DIV              0x19    //�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define MPU6050_CONFIG          0x1A    //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define GYRO_CONFIG             0x1B    //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define ACCEL_CONFIG            0x1C    //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define ACCEL_CONFIG_2          0x1D
#define LP_MODE_CFG             0x1E
#define ACCEL_WOM_X_THR         0x20
#define ACCEL_WOM_Y_THR         0x21
#define ACCEL_WOM_Z_THR         0x22
#define FIFO_EN                 0x23
#define FSYNC_INT               0x36
#define INT_PIN_CFG             0x37    //����6050����I2CΪֱͨģʽ�Ĵ���
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
#define USR_CONTROL             0x6A    //�ر�6050�Ը���I2C�豸�Ŀ���
#define PWR_MGMT_1              0x6B    //��Դ��������ֵ��0x00(��������)
#define PWR_MGMT_2              0x6C
#define I2C_IF                  0x70
#define FIFO_COUNTH             0x72
#define FIFO_COUNTL             0x73
#define FIFO_R_W                0x74
#define WHO_AM_I                0x75    //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define XA_OFFSET_H             0x77
#define XA_OFFSET_L             0x78
#define YA_OFFSET_H             0x7A
#define YA_OFFSET_L             0x7B
#define ZA_OFFSET_H             0x7D
#define ZA_OFFSET_L             0x7E

#endif /* DMXLIBRARIES_DMX_DEVICE_DMX_MPU_H_ */
