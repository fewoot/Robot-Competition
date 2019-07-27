/**
 * 第6阶段，此阶段处理台下问题
 * 首先处理怎么知道自己在台下，可以通过检测四个传感器的读数来检测
 * 思路1.可以通过原函数不断调整位置，从而得知自己在台下
 */

/**
 * 记录：后侧两个最小是345左右，侧面也是345左右，当掉落以后，侧面最大是270-285左右，最近是198左右，后面贴墙左是189，右是179
 */
/**
 * 所需的库
 */
#include <SoftwareSerial.h>
#include <RoboClaw.h>
#include <EEPROM.h>

//左转90°
#define TURNLEFT90 530
//左转——大
#define TURNLEFT_BIG 160
//左转——小
#define TURNLEFT_SMALL 140
//右转—90°
#define TURNRIGHT90 530
//右转——大
#define TURNRIGHT_BIG 175
//右转——小
#define TURNRIGHT_SMALL 160

//位置误差
#define ERROR_POSITION 7

//经测试，900左右END值是一圈
#define ONE_ROUND 900

// //定义日志是否已经开始
// #define TIME_YES 1
// #define TIME_NO 0

//定义电机驱动模块引脚
#define DRIVER_S1 11
#define DRIVER_S2 10

//定义异常增长值
#define ABNORMAL_INCREASE 300

// //定义探测距离
// #define DETECT_DISTANCE 250

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


// //定义对方位置
// #define ON_LEFT 1
// #define ON_LEFT_FRONT 2
// #define ON_FRONT 3
// #define ON_RIGHT_FRONT 4
// #define ON_RIGHT 5
// #define ON_LEFT_FRONT_MORE 7
// #define ON_RIGHT_FRONT_MORE 8
// #define ON_NOTHING 6

//定义行进速度
// #define GO_SPEED_FAST 25
// #define GO_SPEED_SLOW 10

/**
 * 定义传感器
 */
#define DETECTOR_BACK_A2 A2
#define DETECTOR_BACK_A3 A3
#define DETECTOR_LEFT_A0 A0
#define DETECTOR_RIGHT_A1 A1
#define DETECTOR_LEFT_FRONT 7
#define DETECTOR_FRONT 6
#define DETECTOR_RIGHT_FRONT 5
#define GRAYSCALE_SENSOR_PIN2 8
#define GRAYSCALE_SENSOR_PIN1 9
// #define DETECTOR1 5
// #define DETECTOR2 A3
// #define DETECTOR3 6
// #define DETECTOR4 A2
// #define DETECTOR5 7
// #define DETECTOR6 7
// #define DETECTOR7 A3

//定义转向状态（目前未使用）
#define READY_TO_TURN_RIGHT 1
#define READY_TO_TURN_LEFT 0
#define READY_TO_GO_FRONT 2

//转向误差值（未使用）
#define TURN_ERROR_VALUE 20

//微小角度转向速度（未使用）
#define TURN_SLOW_SPEED 9

//微小前进速度（未使用）
#define GO_SLOW_SPEED 8

#define GO_SPEED_ATTACK 15

//微小角度转向位置（使用）
#define TURN_SLOW_POSITION 25

//微小前进位置（使用）
#define GO_SLOW_POSITION 25

//最小检测变化，用于两侧90°转向时判断是否有物体
#define MIN_DETECT_CHANGE 177

//对正时两个探测器数值差异范围
#define OffSET_THRESHOLD 10

//定义传输值no_signal值
#define NO_SIGNAL_VALUE 870

/**
 * 定义检测到物体没有
 */
#define DETECT_YES 0
#define DETECT_NO 1

//定义上一次检测到物体的方向
#define DETECT_LAST_LEFT 1
#define DETECT_LAST_RIGHT 2
#define DETECT_LAST_FRONT 3

//定义左前转向位置
#define TURN_LEFT_SIDE 210
//定义右前转向位置
#define TURN_RIGHT_SIDE 200

//定义左前补角转向位置
#define TURN_LEFT_SIDE_COMPLEMENTARY 210
//定义右前补角转向位置
#define TURN_RIGHT_SIDE_COMPLEMENTARY 220

//定义计时是否已经开始
#define COMPLEMENTARY_TIME_YES 1
#define COMPLEMENTARY_TIME_NO 0
//定义计时多久后判定丢失目标
#define COMPLEMENTARY_TIME_DELAY 400

//判断前方是否已经检测到物体
#define DETECT_IF_DETECTED_YES 1
#define DETECT_IF_DETECTED_NO 0

//定义后退速度
#define GO_BAKC_SPEED 50

//定义当两侧距离突然剧增时阈值
#define MINI_CHANGE 150

//定义可以开始进入警戒状态
#define ENABLE_TO_TIMING 1

//定义不能进入警戒状态
#define NOT_ENABLE_TO_TIMING 0

//初始化是否可以进入警戒状态
int timing = NOT_ENABLE_TO_TIMING;

//定义上一次物体位置变量
int last_detect_side = DETECT_LAST_FRONT;
//定义是否已经开始计时变量
int complementary_time_judge = COMPLEMENTARY_TIME_NO;
//定义计时变量
long complementary_time = 0;

//定义旋转次数
int times_of_turns = 0;

//记录无敌人时，左侧边界的距离
int last_detect_left = 0;

//记录无敌人时，右侧边界的距离
int last_detect_right = 0;

//记录两侧探测器的数值总和，没用
int last_detect_sum = 1200;

//对齐时判断是否已经对齐过
int alignment_only_once = 0;

//定义前方是否检测到物体的变量
int detect_if_detected = DETECT_IF_DETECTED_NO;

int temp_analogRead_A1 = 0;
int temp_analogRead_A0 = 0;


/**
 * 定义转向速度（0-127）
 */
// #define TURN_SPEED_FAST 127
// #define TURN_SPEED_MIDDLE 100
// #define TURN_SPEED_SLOW 100


//用于储存探测器收集到的数据
//int infrared[5] = {no,no,no,no,no};

// //定义日志地址
// int addr = 0;

// //定义上一次的转向移动状态
// int last_move_status = 0;

// //定义日志记录次数
// int log_times = 0;

// //定义时间起始处
// long time_start = 0;

// //定义是否已经开始计时，1为已经开始，0为未开始
// int time_temp = 0;

// //定义日志状态
// int time_status = 0;

//新建一个模拟串口,S1=P11,S2=P10
SoftwareSerial serial = SoftwareSerial(DRIVER_S2,DRIVER_S1);

//利用刚才新建的串口和通信超时值来新建一个对象
RoboClaw roboclaw = RoboClaw(&serial,TIME_OUT);

//定义日志格式
// struct MyObject {
//     //执行次数
//     int times;
//     //记录状态
//     /**
//      * 状态规定：左-1，左前-2，右前-4，右-5
//      */
//     int statue;
//     //记录时间，应该是一次完整转向所用的时间
//     long time;
// };


//后退函数，后退距离为台子的垂直距离小一点
void goBack(){
    roboclaw.ResetEncoders(ADDRESS);
    // roboclaw.BackwardM1(ADDRESS,speed);
    // roboclaw.BackwardM2(ADDRESS,speed-1);
    //for(;;){
        // if(analogRead(DETECTOR_BACK_A2)>900 && analogRead(DETECTOR_BACK_A3)>900){
        //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -2795, ACCEL2, 2000, DECCEL2, -2795, 1);
        //     delay(50);
        //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3500, DECCEL1, -2795, ACCEL2, 3500, DECCEL2, -2795, 1);
        // }else if(analogRead(DETECTOR_BACK_A2)>800 && analogRead(DETECTOR_BACK_A3)>800){
        //     //roboclaw.ResetEncoders(ADDRESS);
        //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -2795, ACCEL2, 2000, DECCEL2, -2795, 1);
        //     delay(50);
        //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3500, DECCEL1, -2795, ACCEL2, 3500, DECCEL2, -2795, 1);
        // }else if(analogRead(DETECTOR_BACK_A2)<700 && analogRead(DETECTOR_BACK_A3)<700){
        //     stop();
        //     return;
        // }else if(analogRead(DETECTOR_BACK_A2)<800 && analogRead(DETECTOR_BACK_A3)<800){
        //     //roboclaw.ResetEncoders(ADDRESS);
        //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -2795, ACCEL2, 2000, DECCEL2, -2795, 1);
        // }
        // if(analogRead(DETECTOR_BACK_A2)<400 || analogRead(DETECTOR_BACK_A3)<400){
        //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 200, DECCEL1, -8000, ACCEL2, 200, DECCEL2, -8000, 1);
        //     delay(50);
        //     stop();
        //     //delay(1000);
        //     return;
        // }
        roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2500, DECCEL1, -5590, ACCEL2, 2500, DECCEL2, -5570, 1);
        delay(3000);
        // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3000, DECCEL1, -5590, ACCEL2, 3000, DECCEL2, -5570, 1);
        // delay(1000);
        // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -5590, ACCEL2, 2000, DECCEL2, -5570, 1);
        // delay(5000);
    //}
    // roboclaw.ResetEncoders(ADDRESS);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -5590, ACCEL2, 2000, DECCEL2, -5570, 1);
    // delay(300);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3500, DECCEL1, -5590, ACCEL2, 3500, DECCEL2, -5570, 1);
    // delay(800);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -5590, ACCEL2, 2000, DECCEL2, -5570, 1);
    // while (roboclaw.ReadEncM1(ADDRESS)<(position+4)&&roboclaw.ReadEncM1(ADDRESS)>(position-4)){
    //     /* code */
    // }
}


void alignmentMoreStringent(){
    if(analogRead(DETECTOR_BACK_A2)+analogRead(DETECTOR_BACK_A3)>=1700){
        turnLeftPosition(2*TURN_SLOW_POSITION);
    }else if(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>OffSET_THRESHOLD){
        turnLeftPosition(TURN_SLOW_POSITION);
    }else if(analogRead(DETECTOR_BACK_A3)-analogRead(DETECTOR_BACK_A2)-5>OffSET_THRESHOLD){
        turnRightPosition(TURN_SLOW_POSITION);
    }else{
        
        // int temp_analogRead_A1 = analogRead(DETECTOR_RIGHT_A1);
        // int temp_analogRead_A0 = analogRead(DETECTOR_LEFT_A0);
        // if(last_detect_right-temp_analogRead_A1<=MINI_CHANGE && last_detect_left-temp_analogRead_A0<=MINI_CHANGE && temp_analogRead_A1-last_detect_right<ABNORMAL_INCREASE && temp_analogRead_A0-last_detect_left<ABNORMAL_INCREASE){
        //     //uploadDetect();
        //     last_detect_left = temp_analogRead_A0;
        //     last_detect_right = temp_analogRead_A1;
        // }
        uploadDetect();
        goFrontPosition();
    }
    judgeWhetherOnStageOrUnderTheStage();
}


//向右转位置函数
void turnRightPosition(int single){
    //M1PositionBackward(single);
    //M2PositionForward(single);
    roboclaw.ResetEncoders(ADDRESS);
    //roboclaw.SetEncM1(ADDRESS,0);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, single, 1);
    // // for(;;){
    // //     if(roboclaw.ReadEncM1(ADDRESS)<(position+4)&&roboclaw.ReadEncM1(ADDRESS)>(position-4)){
    // //         return;
    // //     }
    // // }

    // //roboclaw.SetEncM2(ADDRESS,0);
    // //}
    // //roboclaw.ReadEncM1(ADDRESS)
    // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, single, 1);
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, single, ACCEL2, 8000, DECCEL2, -single, 1);
    for(;;){
        if(roboclaw.ReadEncM1(ADDRESS)>=single-ERROR_POSITION){
            stop();
            //stop_stuck();
            return;
        }
    }
}
void stop(){
    roboclaw.ForwardM1(ADDRESS, 0);
    //roboclaw.ForwardM1(address,speed);
    roboclaw.ForwardM2(ADDRESS, 0);
}


//向左转位置函数
void turnLeftPosition(int single){
    //static int M1PositionTemp = 0;
    //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    //roboclaw.SetEncM2(ADDRESS,0);
    roboclaw.ResetEncoders(ADDRESS);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -single, 0);
    // // for(;;){
    // //     if(roboclaw.ReadEncM2(ADDRESS)<(-position+4)&&roboclaw.ReadEncM2(ADDRESS)>(-position-4)){
    // //         return;
    // //     }
    // // }

    // //static int M1PositionTemp = 0;
    // //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    // //roboclaw.SetEncM1(ADDRESS,0);
    // //}
    // //roboclaw.ReadEncM1(ADDRESS)
    // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -single, 0);
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, -single, ACCEL2, 8000, DECCEL2, single, 1);
    for(;;){
        if(roboclaw.ReadEncM2(ADDRESS)>=single-ERROR_POSITION){
            stop();
            return;
        }
    }
}

//微小前进位置函数
void goFrontPosition(){
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, GO_SLOW_POSITION, ACCEL2, 8000, DECCEL2, GO_SLOW_POSITION, 1);
    for(;roboclaw.ReadEncM1(ADDRESS)<GO_SLOW_POSITION-ERROR_POSITION;){}
    delay(200);
}

void uploadDetect(){
    //delay(100); temp_analogRead_A1-last_detect_right<ABNORMAL_INCREASE && temp_analogRead_A0-last_detect_left<ABNORMAL_INCREASE
    temp_analogRead_A1 = analogRead(DETECTOR_RIGHT_A1);
    temp_analogRead_A0 = analogRead(DETECTOR_LEFT_A0);
    if(temp_analogRead_A1<NO_SIGNAL_VALUE){
        //uploadDetect();
        last_detect_right = temp_analogRead_A1;
    }
    if(temp_analogRead_A0<NO_SIGNAL_VALUE){
        last_detect_left = temp_analogRead_A0;
    }
    
    // last_detect_left = analogRead(DETECTOR_LEFT_A0);
    // last_detect_right = analogRead(DETECTOR_RIGHT_A1);
}

void judgmentUnderTheStage(){
    //pinMode(13,OUTPUT);
    digitalWrite(13,HIGH);
    goFrontPosition();
    goFrontPosition();
    goFrontPosition();
    goFrontPosition();
    while(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>40 || analogRead(DETECTOR_BACK_A2)+analogRead(DETECTOR_BACK_A3)>550){
        turnLeftPosition(2*TURN_SLOW_POSITION);
    }
    //goBack(GO_BAKC_SPEED)
    //backOnTheStage();
    baseline();
    delay(10000);
}

void baseline(){
    pinMode(13,OUTPUT);
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(100);
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
}

void judgeWhetherOnStageOrUnderTheStage(){
    if(temp_analogRead_A0+temp_analogRead_A1<580){
        judgmentUnderTheStage();
    }else{
        //pinMode(13,OUTPUT);
        digitalWrite(13,LOW);
    }
}

void backOnTheStage(){
    roboclaw.BackwardM1(ADDRESS,10);
    roboclaw.BackwardM2(ADDRESS,10);
}



//原始函数：
void setup(){
    //定义模拟串口
    roboclaw.begin(38400);
    Serial.begin(9600);
    pinMode(13,HIGH);
    //设置传感器引脚
    // pinMode(DETECTOR1,INPUT);
    // pinMode(DETECTOR2,INPUT);
    // pinMode(DETECTOR3,INPUT);
    // pinMode(DETECTOR4,INPUT);
    // pinMode(DETECTOR5,INPUT);
    // pinMode(DETECTOR6,INPUT);
    // pinMode(DETECTOR7,INPUT);
    // delay(300
    //stop();
    delay(2000);
    //首先更新一下场上的距离常数，再行动
    //uploadDetect();
    // last_detect_left = 400;
    // last_detect_right = 400;
    
}

//两者平时大概在-500到+500左右，受到推力后大概在2000+


void loop(){
    //alignmentMoreStringent();
    //uploadDetect();
    //judgeWhetherOnStageOrUnderTheStage();
    //uploadDetect();
    Serial.print("left:");
    Serial.print(analogRead(DETECTOR_LEFT_A0));
    Serial.print("     right:");
    Serial.print(analogRead(DETECTOR_RIGHT_A1));
    Serial.print("     back_left");
    Serial.print(analogRead(DETECTOR_BACK_A2));
    Serial.print("     back_right:");
    Serial.println(analogRead(DETECTOR_BACK_A3));
    delay(1000);
    //test();
    //PrepareforAttack();
    // Serial.println(digitalRead(GRAYSCALE_SENSOR_PIN));
    // delay(1000);
    // Serial.print("pwm1:");
    // Serial.print(pwm1);
    // Serial.print("    pwm2:");
    // Serial.println(pwm2);
    // delay(1000);
    // //     //time_begin(onleft);
    // //     //turn
    //test();
    //alignment();
    //delay(1000);
    
    //test();
    // turnRightPosition(TURN_RIGHT_SIDE);
    // delay(1000);
    // turnRightPosition(TURN_RIGHT_SIDE_COMPLEMENTARY);
    // delay(5000);
    // turnLeftPosition(TURN_LEFT_SIDE);
    // delay(1000);
    // turnLeftPosition(TURN_LEFT_SIDE_COMPLEMENTARY);
    // delay(5000);
    // turnRightPosition(TURNRIGHT90+90);
    // delay(1000);
    // BackToTheDefensivePosition();
    // //goBack();
    // // delay(1000);
    // // stop();
    // baseline();
    // delay(10000);
    //searchForEnemy();
    // Serial.println(analogRead(DETECTOR_BACK_A2));
    // delay(1000);
}

