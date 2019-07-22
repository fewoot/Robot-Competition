/**
 * 最后的车转向
 * 利用之前写好的函数进行转向
 * 要求：在最多0.4s内转向前方任意角度即400ms
 * 2019.7.18小结：电机设置完成，程序测试完成，还要覆写传感器程序(已完成),同时有新的问题，若用位置停止-
 * 则车身会产生摆动(已解决，用迅速刷新的新的位置坐标来减速，但还未在实车上实验)
 * 2019.7.21，已在小车上实验，但是目前距离定义的过进，但是DETECTOR1却意外的不错，还需要进一步研究，顺便：新传感器真垃圾！！
 */

/**
 * 记录：
 * 1-343
 * 2-350
 * 3-固定65mm
 * 4-固定90mm
 * 5-固定65mm
 * 6-333
 * 7-317
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

//定义日志是否已经开始
#define TIME_YES 1
#define TIME_NO 0

//定义电机驱动模块引脚
#define DRIVER_S1 11
#define DRIVER_S2 10

//定义探测距离
#define DETECT_DISTANCE 250

/**
 * 设定一些和传输命令有关的参数
 */
#define ADDRESS 0x80

//设置超时值
#define TIME_OUT 10000

//加速度设置，默认
#define ACCEL 655360
#define DECCEL 655360
#define ACCEL1 655360
#define ACCEL2 655360
#define DECCEL1 655360
#define DECCEL2 655360

//经测试，900左右END值是一圈
#define ONE_ROUND 900

//定义对方位置
#define ON_LEFT 1
#define ON_LEFT_FRONT 2
#define ON_FRONT 3
#define ON_RIGHT_FRONT 4
#define ON_RIGHT 5
#define ON_LEFT_FRONT_MORE 7
#define ON_RIGHT_FRONT_MORE 8
#define ON_NOTHING 6

//定义行进速度
#define GO_SPEED_FAST 25
#define GO_SPEED_SLOW 10

/**
 * 定义传感器
 */
#define DETECTOR1 A0
#define DETECTOR2 A1
#define DETECTOR3 6
#define DETECTOR4 7
#define DETECTOR5 9
#define DETECTOR6 A2
#define DETECTOR7 A3

/**
 * 定义检测到物体没有
 */
#define DETECT_YES 0
#define DETECT_NO 1

/**
 * 定义转向速度（0-127）
 */
#define TURN_SPEED_FAST 80
#define TURN_SPEED_MIDDLE 60
#define TURN_SPEED_SLOW 40


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
SoftwareSerial serial = SoftwareSerial(DRIVER_S2,DRIVER_S1);

//利用刚才新建的串口和通信超时值来新建一个对象
RoboClaw roboclaw = RoboClaw(&serial,TIME_OUT);

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
    roboclaw.ForwardM1(ADDRESS, 0);
    //roboclaw.ForwardM1(address,speed);
    roboclaw.ForwardM2(ADDRESS, 0);
}
//停止后保持不动
void stop_stuck(){
    roboclaw.ResetEncoders(ADDRESS);
    //stop();
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1000, DECCEL1, 0, ACCEL2, 1000, DECCEL2, 0, 1);
}
// //停止后保持不动——修改后
// void stop_stuck_fixed(){
//     //for(int i=0;i<1500;++i){
//         stop_stuck();
//         //delay(1);
//     //}
// }
//原地左转，直到车头正对，在这之中可以被打断
void turnLeft(int speed){
    //roboclaw.ForwardM1(address, speed);
    roboclaw.ForwardM1(ADDRESS,speed);
    roboclaw.ForwardM2(ADDRESS, speed);
    //roboclaw.BackwardM2(address,speed);
}
//原地右转，直到车头正对，在这之中可以被打断
void turnRight(int speed){
    roboclaw.BackwardM1(ADDRESS, speed);
    //roboclaw.ForwardM1(address,speed);
    //roboclaw.ForwardM2(address, speed);
    roboclaw.BackwardM2(ADDRESS,speed);
}
//直行
void gofront(int speed){
    roboclaw.BackwardM1(ADDRESS, speed);
    roboclaw.ForwardM2(ADDRESS, speed);
}
//向左转
void goleft(int speed,int level){
    roboclaw.BackwardM1(ADDRESS, speed-level);
    roboclaw.ForwardM2(ADDRESS, speed+level);
}
//向右转
void goright(int speed,int level){
    roboclaw.BackwardM1(ADDRESS, speed+level);
    roboclaw.ForwardM2(ADDRESS, speed-level);
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
            if(last_move_status==ON_RIGHT || last_move_status==ON_RIGHT_FRONT){
                //turnRight();
            }else{
                //turnLeft();
            }
            //roboclaw.ReadSpeedM1(address);
            //roboclaw.ReadSpeedM2(address);
            

        }
        if(detect()==ON_NOTHING){

        }else{
            return;
        }
    }
}
//动作组以上--------------------------------------------------------------------------------------------------


//状态组以下----------------------------------------------------------------------------------------------------
/**
 * 目前可以通过在运行程序中直接添加动作完成，不需要状态函数，先放着
 */
// void statusForward(){
//     //停止
//     stop();
// }
// void statusleft_front(){
//     //向左旋转
//     //turnLeft();
// }
// void statusright_front(){
//     //向右旋转
//     //turnRight();
// }
// void statusleft(){
//     //向左旋转
//     //turnLeft();
// }
// void statusright(){
//     //向右旋转
//     //turnRight();
// }
//状态组以上---------------------------------------------------------------------------------------------------


//探测器以下---------------------------------------------------------------------------------------------------
//检测左侧传感器
int detectLeft(){
    if(analogRead(DETECTOR1)<313){
        return DETECT_YES;
    }else{
       return DETECT_NO; 
    }
}
//检测左偏前传感器
int detectLeftFront(){
    if(analogRead(DETECTOR2)<310){
        return DETECT_YES;
    }else{
       return DETECT_NO; 
    }
}
//检测前偏左传感器
int detectLeftFrontMore(){
    if(digitalRead(DETECTOR3)==LOW){
        return DETECT_YES;
    }else{
        return DETECT_NO;
    }
}
//检测前方传感器
int detectFront(){
    if(digitalRead(DETECTOR4)==LOW){
        return DETECT_YES;
    }else{
        return DETECT_NO;
    }
}
//检测右方传感器
int detectRight(){
    if(analogRead(DETECTOR7)<317){
        return DETECT_YES;
    }else{
       return DETECT_NO; 
    }
}
//检测右偏前传感器
int detectRightFront(){
    if(analogRead(DETECTOR6)<333){
        return DETECT_YES;
    }else{
       return DETECT_NO; 
    }
}
//检测前偏右传感器
int detectRightFrontMore(){
    if(digitalRead(DETECTOR5)==LOW){
        return DETECT_YES;
    }else{
        return DETECT_NO;
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

    /**
     * 在这个模块中，先检测最侧边，依次往前，但是会有一些问题，待用
     */
    // if(detect_left()==yes){
    //     return onleft;
    // }else if(detect_right()==yes){
    //     return onright;
    // }else if(detect_leftfront()==yes){
    //     return onleftfront;
    // }else if(detect_rightfront()==yes){
    //     return onrightfront;
    // }else if(detect_leftfrontmore()==yes){
    //     return onleftfrontmore;
    // }else if(detect_rightfrontmore()==yes){
    //     return onrightfrontmore;
    // }else if(detect_front()==yes){
    //     return onfront;
    // }else{
    //     return onnothing;
    // }

    /**
     * 这个模块中，优先检测前方，在从侧边向前方递进
     */
    if(detectFront()==DETECT_YES){
        return ON_FRONT;
    }else if(detectLeft()==DETECT_YES){
        return ON_LEFT;
    }else if(detectRight()==DETECT_YES){
        return ON_RIGHT;
    }else if(detectLeftFront()==DETECT_YES){
        return ON_LEFT_FRONT;
    }else if(detectRightFront()==DETECT_YES){
        return ON_RIGHT_FRONT;
    }else if(detectLeftFrontMore()==DETECT_YES){
        return ON_LEFT_FRONT_MORE;
    }else if(detectRightFrontMore()==DETECT_YES){
        return ON_RIGHT_FRONT_MORE;
    }else{
        return ON_NOTHING;
    }
}
//探测器以上---------------------------------------------------------------------------------------------------


//记录以下-----------------------------------------------------------------------------------------------------

//记录开始时间
void time_begin(int status){
    if(time_temp==TIME_NO){
        time_start = millis();
        time_temp = TIME_YES;
        time_status = status;
    }
}

//存储日志函数
void record(){
    if(time_temp==TIME_YES){
        MyObject mylog;
        mylog.times = ++log_times;
        mylog.time = millis()-time_start;
        //mylog.time = 12233;
        mylog.statue = time_status;
        EEPROM.put(addr,mylog);
        addr += sizeof(MyObject);
        time_temp = TIME_NO;
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
    case ON_LEFT:
        //状态1
        //record(1);
        //在正左方
        //left();
        //goleft(goSpeedFast);
        break;
    case ON_LEFT_FRONT:
        //状态2
        //record(2);
        //在左前方
        //left_front();
        //goleft(goSpeedSlow);
        break;
    case ON_FRONT:
        //状态3
        //record(3);
        //在前方
        //forward();
        //gofront();
        break;
    case ON_RIGHT_FRONT:
        //状态4
        //record(4);
        //在右前方
        //right_front();
        //goright(goSpeedSlow);
        break;
    case ON_RIGHT:
        //状态5
        //record(5);
        //在正右方
        //right();
        //goright(goSpeedFast);
        break;
    case ON_NOTHING:
        //状态6
        //record(6);
        //暂时没有检测到
        //如果没有检测到，可能是真的没有检测到，也有可能是在转弯过程中刚刚好转到了一个中间的位置-
        //所以不作为
        //turnLeft();
        //stop();
        //gonothing();
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
void faceToEnemy(){
    switch (detect()){
    case ON_LEFT:
        //状态1
        //record(1);
        //在正左方
        //time_begin(onleft);
        turnLeft(TURN_SPEED_FAST);
        break;
    case ON_LEFT_FRONT:
        //状态2
        //record(2);
        //在左前方
        //time_begin(onleftfront);
        turnLeft(TURN_SPEED_MIDDLE);
        break;
    case ON_FRONT:
        //状态3
        //record(3);
        //在前方
        //record();
        //forward();
        delay(14);
        stop();
        //stop_stuck();
        //stop_stuck_fixed();
        break;
    case ON_RIGHT_FRONT:
        //状态4
        //record(4);
        //在右前方
        //time_begin(onrightfront);
        //right_front();
        turnRight(TURN_SPEED_MIDDLE);
        break;
    case ON_RIGHT:
        //状态5
        //record(5);
        //在正右方
        //time_begin(onright);
        //right();
        turnRight(TURN_SPEED_FAST);
        break;
    case ON_LEFT_FRONT_MORE:
        //状态7
        //record(6);
        //在左前方更靠近前方
        turnLeft(TURN_SPEED_SLOW);
        break;
    case ON_RIGHT_FRONT_MORE:
        //状态8
        //record(6);
        //在右前方更靠近前方
        turnRight(TURN_SPEED_SLOW);
        break;
    // case onnothing:
    //     //状态6
    //     //record(6);
    //     //暂时没有检测到
    //     //如果没有检测到，可能是真的没有检测到，也有可能是在转弯过程中刚刚好转到了一个中间的位置-
    //     //所以不作为
    //     break;
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
// void moveToEnemy(){
//     switch (detect()){
//     case ON_LEFT:
//         //状态1
//         //record(1);
//         //在正左方
//         last_move_status = onleft;
//         move(on);
//         break;
//     case onleftfront:
//         //状态2
//         //record(2);
//         //在左前方
//         last_move_status = onleftfront;
//         move(onleftfront);
//         break;
//     case onfront:
//         //状态3
//         //record(3);
//         //在前方
//         last_move_status = onfront;
//         move(onfront);
//         break;
//     case onrightfront:
//         //状态4
//         //record(4);
//         //在右前方
//         last_move_status = onrightfront;
//         move(onrightfront);
//         break;
//     case onright:
//         //状态5
//         //record(5);
//         //在正右方
//         last_move_status = onright;
//         move(onright);
//         break;
//     case onnothing:
//         //状态6
//         //record(6);
//         //暂时没有检测到
//         //如果没有检测到，可能是真的没有检测到，也有可能是在转弯过程中刚刚好转到了一个中间的位置-
//         //所以不作为
//         move(onnothing);
//         break;
//     default:
//         //状态7
//         //record(7);
//         //其他情况
//         break;
//     }
// }


/**
 * 探测器打印日志函数
 */
void Println(){
    
    Serial.println(detect());
    //Serial.println(analogRead(detector7));
    // Serial.print(digitalRead(detector3));
    // Serial.print(":");
    // Serial.print(digitalRead(detector4));
    // Serial.print(":");
    // Serial.println(digitalRead(detector5));
    // Serial.print(":");
    // Serial.print(digitalRead(detector4));
    // Serial.print(":");
    // Serial.println(digitalRead(detector5));
    //delay(400);
}

//测试
void test_temp(){
    //Serial.begin(9600);
    Serial.print("1:");
    Serial.print(analogRead(DETECTOR1));
    Serial.print(",2:");
    Serial.print(analogRead(DETECTOR2));
    Serial.print(",3:");
    Serial.print(digitalRead(DETECTOR3));
    Serial.print(",4:");
    Serial.print(digitalRead(DETECTOR4));
    Serial.print(",5:");
    Serial.print(digitalRead(DETECTOR5));
    Serial.print(",6:");
    Serial.print(analogRead(DETECTOR6));
    Serial.print(",7:");
    Serial.print(analogRead(DETECTOR7));
    Serial.println(":");
    //Serial.println(analogRead(A1));
    //Serial.
    delay(400);
    // delay(3000);
    // time_begin(onleft);
    // turnLeft();
    // delay(250);
    // //stop();
    // //stop_stuck();
    // record();
    // stop_stuck_fixed();
    // for(;;){}
}


//原始函数：
void setup(){
    //定义模拟串口
    roboclaw.begin(38400);
    Serial.begin(9600);
    //设置传感器引脚
    pinMode(DETECTOR1,INPUT);
    pinMode(DETECTOR2,INPUT);
    pinMode(DETECTOR3,INPUT);
    pinMode(DETECTOR4,INPUT);
    pinMode(DETECTOR5,INPUT);
    pinMode(DETECTOR6,INPUT);
    pinMode(DETECTOR7,INPUT);
    delay(3000);
    //pinMode(3,INPUT);
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
    faceToEnemy();
    Println();
    //Serial.println(digitalRead(7));
    //roboclaw.ResetEncoders(address);
    //stop();
    //stop_stuck();
    //roboclaw.SpeedAccelDeccelPositionM1(address, 50, 5, 50, 0, 1);
    //Serial.println(digitalRead(5));
}