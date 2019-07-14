
/**
 * 目前目标：实现两轮车
 * 目标功能：能检测物体并转向它
 * 目标要求：快、稳、准
 * 
 * 一旦5个传感器中一个检测到物体，立刻下指令，向那个方向转向
 * 当任意非正前方检测到物体时，向特定方向以特定角度原地旋转，同时时刻监视正前方是否检测到，一旦检测到立刻停止
 * 注意：默认M1为左，M2为右
 */

/**
 * 所需的库
 */
#include <SoftwareSerial.h>
#include <RoboClaw.h>


/**
 * 设定一些和传输命令有关的参数
 */
#define address 0x80
//新建一个模拟串口
SoftwareSerial serial = SoftwareSerial(10,11);
//设置超时值
#define timeout 10000
//利用刚才新建的串口和通信超时值来新建一个对象
RoboClaw roboclaw = RoboClaw(&serial,timeout);

/**
 * 定义传感器
 */
#define detector1 9
#define detector2 8
#define detector3 7
#define detector4 6
#define detector5 5

/**
 * 定义检测到物体没有
 */
#define yes 1
#define no 0

/**
 * 定义默认速度，应该是最高速了
 */
#define speed 8000

//物体位置，角度位置
flaot position = 0;

//用于储存探测器收集到的数据
int infrared[5] = {no,no,no,no,no};

//定义日志地址
int addr = 0;

//定义日志格式
struct MyObject {
    long time_record;
    int status;
};

//存储日志函数
void record(int choice){
    if(addr>1000){

    }else{
        MyObject jilu;
        jilu.time_record = millis();
        jilu.status = choice;
        EEPROM.put(addr,jilu);
        addr += sizeof(MyObject);
    }
}

//动作组以下-----------------------------------------------------------------------------------------------
//停止
void stop(){
    roboclaw.ForwardM1(address, 0);
    //roboclaw.BackwardM1(address,speed);
    roboclaw.ForwardM2(address, 0);
}
//左转，直到车头正对，在这之中可以被打断
void turnLeft(){
    //roboclaw.ForwardM1(address, speed);
    roboclaw.BackwardM1(address,speed);
    roboclaw.ForwardM2(address, speed);
    //roboclaw.BackwardM2(address,speed);
}
//右转，直到车头正对，在这之中可以被打断
void turnRight(){
    roboclaw.ForwardM1(address, speed);
    //roboclaw.BackwardM1(address,speed);
    //roboclaw.ForwardM2(address, speed);
    roboclaw.BackwardM2(address,speed);
}
//动作组以上--------------------------------------------------------------------------------------------------

//状态组以下----------------------------------------------------------------------------------------------------
void forward(){
    //停止
    stop();
}

void left_front(){
    //向左旋转
    turnLeft();
}

void right_front(){
    //向右旋转
    turnRight();
}

void left(){
    //向左旋转
    turnLeft();
}

void right(){
    //向右旋转
    turnRight();
}
//状态组以上---------------------------------------------------------------------------------------------------

//原始函数：
void setup(){
    //定义模拟串口
    roboclaw.begin(38400);
    //设置传感器引脚
    pinMode(detector1,INPUT);
    pinMode(detector2,INPUT);
    pinMode(detector3,INPUT);
    pinMode(detector4,INPUT);
    pinMode(detector5,INPUT);
    //roboclaw.SetEncM1(address,0);
    //turn_round(900);
}

void loop(){
    //turn_round(900);
    //delay(4000);
    /**
     * 开始启动
     * 通过检测传感器的数据来决定位置
     */
    switch (infrared){
    case {yes,no,no,no,no}:
        //状态1
        record(1);
        //在正左方
        left();
        break;
    case {no,yes,no,no,no}:
        //状态2
        record(2);
        //在左前方
        left_front();
        break;
    case {no,no,yes,no,no}:
        //状态3
        record(3);
        //在前方
        forward();
        break;
    case {no,no,no,yes,no}:
        //状态4
        record(4);
        //在右前方
        right_front();
        break;
    case {no,no,no,no,yes}:
        //状态5
        record(5);
        //在正右方
        right();
        break;
    case {no,no,no,no,no}:
        //状态6
        record(6);
        //暂时没有检测到
        //如果没有检测到，可能是真的没有检测到，也有可能是在转弯过程中刚刚好转到了一个中间的位置-
        //所以不作为
        break;
    default:
        //状态7
        record(7);
        //其他情况
        break;
    }
}







void turn_round(long value){
    //这两个是设定编码器的值，val是一个32-bit的参数
    roboclaw.SetEncM1(address,0);
    //roboclaw.SetEncM2(address,0);
    roboclaw.SpeedAccelDeccelPositionM1(address, 655360, speed, 655360, value, 1);
    //roboclaw.peedAccelDeccelPositionM2(address, 655360, speed, 655360, value, 1);
    //roboclaw.SpeedAccelDeccelPositionM1M2(address, 655360, speed, 655360, value, 655360, speed, 655360, value, 1);
    //delay(3000);
}