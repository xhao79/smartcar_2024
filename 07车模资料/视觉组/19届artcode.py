# Untitled - By: admin - 周三 4月 3 2024

import sensor, image, time, math
from pyb import LED
from machine import UART
import pyb,seekfree
uart = UART(2, baudrate=115200)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 500)
sensor.set_brightness(200)          # 设置摄像头亮度
sensor.set_auto_gain(True)
#角度定义
#       90
#180           0
#-180          -0
#       -90
clock = time.clock()
#设定的中心值
set_center_x = 175
set_center_y = 115
#卡片的中心值
card_x = 0
card_y = 0
recard_y=0
#卡片中心的和设定中心点的差值
derta_x=0;
derta_y=0;
#距离和角度
distance=0;
angle=0.0
#设置的roi区域
set_roi = [30,20,260,200]
test_tuple1 = [13, 58, -39, 108, -105, 11]#白色找蓝色
test_tuple2 = [35, 100, -114, 30, -21, 59]#蓝色找白色
#设置标志位
Flgstart_correct=0
jiaozheng_count=0#矫正次数
angle_tag=0
dis_tag=0
#blobs1=[]
#test_list = list(test_tuple)
LED(4).on()
#通过计算设定中心值和卡片中心值的误差来返回角度和距离

def uart_sent(data1,data2,data3,data4):
    FH = bytearray([0x2C,0x3a,data1,data2,data3,data4,0x5b])
    uart.write(FH)
    #print(FH)
    print("complete")


def  uart_sent1(data1,data2,data3,data4):
    FH = bytearray([0x2c,0x3a])
    uart.write(FH)
    pyb.mdelay(40)
    FH = bytearray([data1,data2,data3,data4])
    uart.write(FH)
    pyb.mdelay(40)
    FH = bytearray([0x5b])
    uart.write(FH)
    print("over")

def ReceiveData():
    global RxCounter1,RxBuffer1
    global Flgstart_correct
    if(uart.any()):
        #must print something to clean buf
        print('start transport data.')
        com_data=uart.read()
        print(com_data)
        if(b"\x00" and b"\xff" and b"\xf0" in com_data):
            print('this is a test')
            if(b"\xa0"  in com_data):
                print('this is a test2')
                Flgstart_correct=1#开始校正
            if(b"\xa1"  in com_data):
                print('this is a test3')
                Flgstart_correct=2#开始校正
            if(b"\xa2"  in com_data):
                print('this is a test4')
                Flgstart_correct=0#开始校正

def jiaozheng(flg):
    global angle_tag,dis_tag,test_tuple2,flg_confirmcorner
    blobs = img.find_blobs([tuple(test_tuple1)],x_stride=10,y_stride=10)
    for b in blobs:
        if(b.w()>100 and b.w()<240 and b.h()>100 and b.h()<240):
            #将找到的蓝色
            img.draw_rectangle(b.rect())
            roi_list=list(b.rect())
            #缩小roi区域为了减少误判
            roi_list[0]=roi_list[0]+10
            roi_list[1]=roi_list[1]+30
            roi_list[2]=roi_list[2]-30
            roi_list[3]=roi_list[3]-40
            cx1=b.x()+(b.w()/2)
            cy1=b.y()+(b.h()/2)
            recard_y_b = 240-1-cy1
            derta_x_blue=cx1 - set_center_x
            derta_y_blue=recard_y_b - (240-set_center_y)
            derta_y_b= derta_y_blue/240*55
            derta_x_b= derta_x_blue/320*67
            distance_b =math.sqrt( pow(abs(derta_x_b),2)+pow(abs(derta_y_b),2))
            angle_b=(math.atan2(derta_y_b,derta_x_b)*180/3.1415926)
            print(f"angle1={angle_b},distance_b")
            if(distance_b>255):
                dis_tag_b=1
            if(flg==1):
                uart_sent1(int(angle_b),0,int(distance_b),0)
                pyb.mdelay(5000)
                Flgstart_correct=0#数据发送完成
            #print(roi_list)
            blobs1 =img.find_blobs([tuple(test_tuple2)],roi=roi_list,x_stride=3,y_stride=3)
            if blobs1:
                #自适应阈值：再找到蓝色色块后用这个，可以滤除蓝色背景，再加腐蚀膨胀
                statistics=img.get_statistics(roi=roi_list)
                if(statistics.b_max()>=20):
                    test_tuple2[4]=int((statistics.b_mean()*0.5+statistics.b_max()*0.2))
                else:
                    test_tuple2[4]=int((statistics.b_mean()*0.8+statistics.b_max()*0.2))
                if(statistics.b_max()<=0):
                    test_tuple2[4]=20
                print('thre='+str(test_tuple2[4]))
                for b1 in blobs1:
                    if(b1.w()>40 and b1.w()<80 and b1.h()>40 and b1.h()<80):
                        cx2=b1.x()+(b1.w()/2)
                        cy2=b1.y()+(b1.h()/2)
                        if(abs(cx1-cx2)<60 and abs(cy1-cy2)<60):
                            img.draw_rectangle(b1.rect())
                            card_x = b1.x()+(b1.w()/2)
                            card_y = b1.y()+(b1.h()/2)
                            recard_y = 240-1-card_y
                            #print(f"x1:{cx1},y1:{cy1}")
                            img.draw_circle(int(card_x),int(card_y),5,color=(255,0,0),thickness=1,fill=1)
                            print(f"x2:{card_x},y2:{card_x}")
                            derta_x=card_x - set_center_x
                            derta_y=recard_y - (240-set_center_y)
                            derta_y = derta_y/240*55
                            derta_x = derta_x/320*67
                            distance =math.sqrt( pow(abs(derta_x),2)+pow(abs(derta_y),2))
                            img.draw_line((int(card_x),int(card_y),set_center_x,set_center_y),color = (255,255,0))
                            angle=(math.atan2(derta_y,derta_x)*180/3.1415926)
                            print(f"dis={distance}")
                            #art校正发送的角度和距离
                            if(distance>255):
                                dis_tag=1
                            if(angle<0):
                                angle_tag=1
                            print(f"d:{int(angle)},{angle_tag},{int(distance)},{dis_tag}")
                            distance=distance*0.9
                            if(jiaozheng_count==1):
                                distance=distance*0.45
                            if(flg==2):
                                if(distance<1):
                                    dis_tag=1
                                    distance=distance*100
                                uart_sent1(int(angle),angle_tag,int(distance),dis_tag)
                                pyb.mdelay(2000)
                                Flgstart_correct=0#数据发送完成
            else:
                print("error")

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_cross(set_center_x,set_center_y)
    print(f"jiaozheng:{Flgstart_correct}")
    ReceiveData();#接受1064数据，若收到0xa0则开始校正
    #jiaozheng(Flgstart_correct)#校正
    if(Flgstart_correct):
        jiaozheng(Flgstart_correct)#校正
    img1=img.copy(1,1)#显示二值化后的图像TypeError: function missing 1 required positional arguments
    img1.binary([tuple(test_tuple2)],invert=False)
    img1.erode(5,threshold=2)
    img1.dilate(5,threshold=15)
    img.draw_image(img1, 0, 0, x_scale=0.4, y_scale=0.4)#显示二值化的图像
