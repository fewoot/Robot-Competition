/**
 * 这是第三阶段
 * 目前目标未知，待第二阶段完成后在执行
 */

/**
 * 30速度，5s，3.75圈，30*5：3.75=40：1圈，0.25圈=10(即速度×时间/ms为10)
 */

/**
 * 所需的库
 */
#include <SoftwareSerial.h>
#include <RoboClaw.h>
#include <EEPROM.h>

//定义后视探测器引脚
#define backdetector1 A0
#define backdetector2 A1

//定义日志是否已经开始
#define timeyes 1
#define timeno 0

//定义电机驱动模块引脚
#define driver_S1 11
#define driver_S2 10

/**
 * 设定一些和传输命令有关的参数
 */
#define address 0x80

//设置超时值
#define timeout 10000

//加速度设置，默认
#define accel 655360
#define deccel 655360
#define accel1 655360
#define accel2 655360
#define deccel1 655360
#define deccel2 655360

//经测试，900左右END值是一圈
#define oneround 900

#define onleft 1
#define onleftfront 2
#define onfront 3
#define onrightfront 4
#define onright 5
#define onleftfrontmore 7
#define onrightfrontmore 8
#define onnothing 6

#define goSpeedFast 25
#define goSpeedSlow 10

/**
 * 定义传感器
 */
#define detector1 12
#define detector2 8
#define detector3 6
#define detector4 7
#define detector5 9
#define detector6 9
#define detector7 10

/**
 * 定义检测到物体没有
 */
#define yes 0
#define no 1

/**
 * 定义默认速度
 */
#define speed 40


//用于储存探测器收集到的数据
//int infrared[5] = {no,no,no,no,no};

//定义日志地址
int addr = 0;

//定义上一次的转向移动状态
int last_move_status = 0;

//定义日志记录次数
int log_times = 0;

//定义时间起始处
long time_start = 0;

//定义是否已经开始计时，1为已经开始，0为未开始
int time_temp = 0;

//定义日志状态
int time_status = 0;

//新建一个模拟串口,S1=P11,S2=P10
SoftwareSerial serial = SoftwareSerial(driver_S2,driver_S1);

//利用刚才新建的串口和通信超时值来新建一个对象
RoboClaw roboclaw = RoboClaw(&serial,timeout);

//定义日志格式
struct MyObject {
    //执行次数
    int times;
    //记录状态
    /**
     * 状态规定：左-1，左前-2，右前-4，右-5
     */
    int statue;
    //记录时间，应该是一次完整转向所用的时间
    long time;
};

//动作组以下-----------------------------------------------------------------------------------------------
//停止
void stop(){
    roboclaw.ForwardM1(address, 0);
    //roboclaw.ForwardM1(address,speed);
    roboclaw.ForwardM2(address, 0);
}
//停止后保持不动
void stop_stuck(){
    roboclaw.ResetEncoders(address);
    //stop();
    roboclaw.SpeedAccelDeccelPositionM1M2(address, accel1, 1000, deccel1, 0, accel2, 1000, deccel2, 0, 1);
}
//停止后保持不动——修改后
void stop_stuck_fixed(){
    //for(int i=0;i<1500;++i){
        stop_stuck();
        //delay(1);
    //}
}
//原地左转，直到车头正对，在这之中可以被打断
void turnLeft(){
    //roboclaw.ForwardM1(address, speed);
    roboclaw.ForwardM1(address,speed);
    roboclaw.ForwardM2(address, speed);
    //roboclaw.BackwardM2(address,speed);
}
//原地右转，直到车头正对，在这之中可以被打断
void turnRight(){
    roboclaw.BackwardM1(address, speed);
    //roboclaw.ForwardM1(address,speed);
    //roboclaw.ForwardM2(address, speed);
    roboclaw.BackwardM2(address,speed);
}
//直行
void gofront(){
    roboclaw.BackwardM1(address, speed);
    roboclaw.ForwardM2(address, speed);
}
//向左转
void goleft(int level){
    roboclaw.BackwardM1(address, speed-level);
    roboclaw.ForwardM2(address, speed+level);
}
//向右转
void goright(int level){
    roboclaw.BackwardM1(address, speed+level);
    roboclaw.ForwardM2(address, speed-level);
}
/**
 * 检测不到物体时的程序，会进行400ms的延时，用来避免转到两个传感器中间就触发此程序-
 * 并会根据最后一次转向行进顺着方向进行原地旋转
 */
void gonothing(){
    // static int temp = 0;
    // if(temp==0){
    //     long time_now = millis();
    //     temp = 1;
    // }
    long time_now = millis();
    for(;;){
        if(millis()-time_now>400){
            //turnLeft();
            if(last_move_status==onright || last_move_status==onrightfront){
                turnRight();
            }else{
                turnLeft();
            }
            //roboclaw.ReadSpeedM1(address);
            //roboclaw.ReadSpeedM2(address);
            

        }
        if(detect()==onnothing){

        }else{
            return;
        }
    }
}

void gofront_fixed(){

}

void goleft_fixed(){

}

void goright_fixed(){
    
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

//探测器以下---------------------------------------------------------------------------------------------------
int detect_left(){

}

int detect_leftfront(){

}

int detect_leftfrontmore(){
    if(digitalRead(detector3)==LOW){
        return yes;
    }else{
        return no;
    }
}

int detect_front(){
    if(digitalRead(detector4)==LOW){
        return yes;
    }else{
        return no;
    }
}

int detect_right(){

}

int detect_rightfront(){

}

int detect_rightfrontmore(){
    if(digitalRead(detector5)==LOW){
        return yes;
    }else{
        return no;
    }
}

/**
 * 传感器检测函数
 */
int detect(){
    // if(digitalRead(detector5)==LOW){
    //     //infrared[5] = {no,no,yes,no,no};
    //     return onright;
    // }else if(digitalRead(detector1)==LOW){
    //     //infrared[5] = {no,yes,no,no,no};
    //     return onleft;
    // }else if(digitalRead(detector4)==LOW){
    //     //infrared[5] = {no,no,no,yes,no};
    //     return onrightfront;
    // }else if(digitalRead(detector2)==LOW){
    //     //infrared[5] = {yes,no,no,no,no};
    //     return onleftfront;
    // }else if(digitalRead(detector3)==LOW){
    //     //infrared[5] = {no,no,no,no,yes};
    //     return onfront;
    // }else{
    //     //infrared[5] = {no,no,no,no,no};
    //     return onnothing;
    // }
    if(detect_left()==yes){
        return onleft;
    }else if(detect_right()==yes){
        return onright;
    }else if(detect_leftfront()==yes){
        return onleftfront;
    }else if(detect_rightfront()==yes){
        return onrightfront;
    }else if(detect_leftfrontmore()==yes){
        return onleftfrontmore;
    }else if(detect_rightfrontmore()==yes){
        return onrightfrontmore;
    }else if(detect_front()==yes){
        return onfront;
    }else{
        return onnothing;
    }
}
//探测器以上---------------------------------------------------------------------------------------------------

//记录以下-----------------------------------------------------------------------------------------------------

//记录开始时间
void time_begin(int status){
    if(time_temp==timeno){
        time_start = millis();
        time_temp = timeyes;
        time_status = status;
    }
}

//存储日志函数
void record(){
    if(time_temp==timeyes){
        MyObject mylog;
        mylog.times = ++log_times;
        mylog.time = millis()-time_start;
        //mylog.time = 12233;
        mylog.statue = time_status;
        EEPROM.put(addr,mylog);
        addr += sizeof(MyObject);
        time_temp = timeno;
    }
    // if(addr>1000){

    // }else{
    //     MyObject jilu;
    //     jilu.time_record = millis();
    //     jilu.status = choice;
    //     EEPROM.put(addr,jilu);
    //     addr += sizeof(MyObject);
    // }
}
//记录以上-----------------------------------------------------------------------------------------------------

//行进程序
void move(int status){
    switch (status){
    case onleft:
        //状态1
        //record(1);
        //在正左方
        //left();
        goleft(goSpeedFast);
        break;
    case onleftfront:
        //状态2
        //record(2);
        //在左前方
        //left_front();
        goleft(goSpeedSlow);
        break;
    case onfront:
        //状态3
        //record(3);
        //在前方
        //forward();
        gofront();
        break;
    case onrightfront:
        //状态4
        //record(4);
        //在右前方
        //right_front();
        goright(goSpeedSlow);
        break;
    case onright:
        //状态5
        //record(5);
        //在正右方
        //right();
        goright(goSpeedFast);
        break;
    case onnothing:
        //状态6
        //record(6);
        //暂时没有检测到
        //如果没有检测到，可能是真的没有检测到，也有可能是在转弯过程中刚刚好转到了一个中间的位置-
        //所以不作为
        //turnLeft();
        //stop();
        gonothing();
        break;
    default:
        //状态7
        //record(7);
        //其他情况
        break;
    }
    //roboclaw.ForwardM1(address, speed);
    //roboclaw.ForwardM2(address, speed);
}

/**
 * 原地转向函数
 */
void status_set(){
    switch (detect()){
    case onleft:
        //状态1
        //record(1);
        //在正左方
        time_begin(onleft);
        turnLeft();
        break;
    case onleftfront:
        //状态2
        //record(2);
        //在左前方
        time_begin(onleftfront);
        turnLeft();
        break;
    case onfront:
        //状态3
        //record(3);
        //在前方
        record();
        //forward();
        //stop();
        //stop_stuck();
        stop_stuck_fixed();
        break;
    case onrightfront:
        //状态4
        //record(4);
        //在右前方
        time_begin(onrightfront);
        //right_front();
        turnRight();
        break;
    case onright:
        //状态5
        //record(5);
        //在正右方
        time_begin(onright);
        //right();
        turnRight();
        break;
    case onleftfrontmore:
        //状态7
        //record(6);
        //在左前方更靠近前方
        turnLeft();
        break;
    case onrightfrontmore:
        //状态8
        //record(6);
        //在右前方更靠近前方
        turnRight();
        break;
    case onnothing:
        //状态6
        //record(6);
        //暂时没有检测到
        //如果没有检测到，可能是真的没有检测到，也有可能是在转弯过程中刚刚好转到了一个中间的位置-
        //所以不作为
        break;
    default:
        //状态7
        //record(7);
        //其他情况
        break;
    }
}

/**
 * 行进转向函数
 */
void move_set(){
    switch (detect()){
    case onleft:
        //状态1
        //record(1);
        //在正左方
        last_move_status = onleft;
        move(onleft);
        break;
    case onleftfront:
        //状态2
        //record(2);
        //在左前方
        last_move_status = onleftfront;
        move(onleftfront);
        break;
    case onfront:
        //状态3
        //record(3);
        //在前方
        last_move_status = onfront;
        move(onfront);
        break;
    case onrightfront:
        //状态4
        //record(4);
        //在右前方
        last_move_status = onrightfront;
        move(onrightfront);
        break;
    case onright:
        //状态5
        //record(5);
        //在正右方
        last_move_status = onright;
        move(onright);
        break;
    case onnothing:
        //状态6
        //record(6);
        //暂时没有检测到
        //如果没有检测到，可能是真的没有检测到，也有可能是在转弯过程中刚刚好转到了一个中间的位置-
        //所以不作为
        move(onnothing);
        break;
    default:
        //状态7
        //record(7);
        //其他情况
        break;
    }
}


/**
 * 探测器打印日志函数
 */
void Println(){
    Serial.print(digitalRead(detector3));
    Serial.print(":");
    Serial.print(digitalRead(detector4));
    Serial.print(":");
    Serial.print(digitalRead(detector5));
    // Serial.print(":");
    // Serial.print(digitalRead(detector4));
    // Serial.print(":");
    // Serial.println(digitalRead(detector5));
}

//测试
void test_temp(){
    delay(3000);
    time_begin(onleft);
    turnLeft();
    delay(250);
    //stop();
    //stop_stuck();
    record();
    stop_stuck_fixed();
    for(;;){}
}

//原始函数：
void setup(){
    //定义模拟串口
    roboclaw.begin(38400);
    Serial.begin(9600);
    //设置传感器引脚
    pinMode(detector1,INPUT);
    pinMode(detector2,INPUT);
    pinMode(detector3,INPUT);
    pinMode(detector4,INPUT);
    pinMode(detector5,INPUT);
    //roboclaw.SetEncM1(address,0);
    //turn_round(900);
    //test_temp();
}

void loop(){
    //turn_round(900);
    //delay(4000);
    /**
     * 开始启动
     * 通过检测传感器的数据来决定位置
     */
    //detect();
    //status_set();
    //gofront();
    //goleft(goSpeedSlow);
    //goright(goSpeedSlow);
    //move();
    //move_set();
    //stop();
    //turnLeft();
    //turnRight();
    //test_temp();
    Println();
    //roboclaw.ResetEncoders(address);
    //stop();
    //stop_stuck();
    //roboclaw.SpeedAccelDeccelPositionM1(address, 50, 5, 50, 0, 1);
}