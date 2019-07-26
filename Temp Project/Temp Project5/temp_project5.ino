/**
 * 第三阶段：完成
 * 平齐1200左右，误差在+-10,变化最小时170
 * 2019.7.26新思路，一直以来经常有个问题，就是车在经过转向后可能会触发偏转90°的问题-
 * 今天有个新思路：如果两侧的值的和为1200+，则说明没有物体，如果两侧值的和为1000-，则-
 * 说明检测到物体，在目前的基础上可以增加判断条件，使得稳定性更高（已改）
 * 小结：已完成几乎所有台上内容
 */

/**
 * 记录：
 * 1-343   A
 * 2-350   A
 * 3-固定65mm
 * 4-固定90mm
 * 5-固定65mm
 * 6-333   A
 * 7-317   A
 */

/**
 * 转圈记录：
 * 依靠延时运行
 * 左转，127速度，316-317ms，大概90°，用时316ms以内
 * 依靠位置信息
 * 
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

//动作组以下-----------------------------------------------------------------------------------------------


/**
 * 判断侧边是否能检测到敌人
 * 会先判断侧边距离数据是否发生大的变化，若发生，则向那个方向转向
 * 之后会更新两侧的距离常数（不是一直的常数）
 */
void detectEnemy(){
    //if()
    //last_detect_sum = analogRead(DETECTOR_LEFT_A0)+analogRead(DETECTOR_RIGHT_A1);
    // Serial.print("A0 cha:");
    // Serial.print(last_detect_left-analogRead(DETECTOR_LEFT_A0));
    // Serial.print(".....A1 cha:");
    // Serial.println(last_detect_right-analogRead(DETECTOR_RIGHT_A1));
    if(last_detect_left-analogRead(DETECTOR_LEFT_A0)>=MIN_DETECT_CHANGE && analogRead(DETECTOR_LEFT_A0)+analogRead(DETECTOR_RIGHT_A1)<1100){
        turnLeftPosition(TURNLEFT90);
        uploadDetect();
        alignment_only_once = 0;
    }else if(last_detect_right-analogRead(DETECTOR_RIGHT_A1)>=MIN_DETECT_CHANGE && analogRead(DETECTOR_LEFT_A0)+analogRead(DETECTOR_RIGHT_A1)<1100){
        turnRightPosition(TURNRIGHT90);
        uploadDetect();
        alignment_only_once = 0;
    }
    
}

/**
 * 对正函数
 * 会根据后面的两个传感器进行和边界对齐
 * 如果对齐（有一定的误差忽视），则会更新两侧的距离常数，同时前进一点
 */
//对正函数1，通过只检测一次来限制刷新侧边值
void alignmentOnlyOnce(){
    if(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>OffSET_THRESHOLD){
        turnLeftPosition(TURN_SLOW_POSITION);
    }else if(analogRead(DETECTOR_BACK_A3)-analogRead(DETECTOR_BACK_A2)>OffSET_THRESHOLD){
        turnRightPosition(TURN_SLOW_POSITION);
    }else{
        //baseline();
        //last_detect_left = 
        if(alignment_only_once==0){
            uploadDetect();
            alignment_only_once = 1;
        }
        goFrontPosition();
    }
}

//对正函数2，先排除遇到四个直角的情况在对正
void alignmentMoreStringent(){
    if(analogRead(DETECTOR_BACK_A2)+analogRead(DETECTOR_BACK_A3)>=1700){
        turnLeftPosition(TURN_SLOW_POSITION);
    }
    if(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>OffSET_THRESHOLD){
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
}

//距离更新函数，会忽略传感器返回的无信号值
void uploadDetect(){
    //delay(100); temp_analogRead_A1-last_detect_right<ABNORMAL_INCREASE && temp_analogRead_A0-last_detect_left<ABNORMAL_INCREASE
    int temp_analogRead_A1 = analogRead(DETECTOR_RIGHT_A1);
    int temp_analogRead_A0 = analogRead(DETECTOR_LEFT_A0);
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

//后退至远处的边线附近
void BackToTheDefensivePosition(){
    // for(goBackOneStep();;){
    //     if(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>OffSET_THRESHOLD){
    //         turnLeftPosition(TURN_SLOW_POSITION);
    //     }else if(analogRead(DETECTOR_BACK_A3)-analogRead(DETECTOR_BACK_A2)-5>OffSET_THRESHOLD){
    //         turnRightPosition(TURN_SLOW_POSITION);
    //     }else{
    //         return;
    //     //     goBackTwoStep();
    //     //     return;
    //     // //delay(1000);
    //     // //stop();
    //     //     //delay(10000);
    //     }
    // }        //delay(1000);
    do{
        if(digitalRead(GRAYSCALE_SENSOR_PIN1)==DETECT_YES){
            roboclaw.ResetEncoders(ADDRESS);
            roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, TURN_SLOW_POSITION, 1);
            roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(TURN_SLOW_POSITION), 1);
            //stop();
        }else if(digitalRead(GRAYSCALE_SENSOR_PIN2)==DETECT_YES){
            roboclaw.ResetEncoders(ADDRESS);
            roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, TURN_SLOW_POSITION, 1);
            roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(TURN_SLOW_POSITION), 1);
            //stop();
        }else if(digitalRead(GRAYSCALE_SENSOR_PIN1)==DETECT_NO && digitalRead(GRAYSCALE_SENSOR_PIN2)==DETECT_NO){
            goBack();
            stop();
            return;
        }
        //if(digitalRead(GRAYSCALE_SENSOR_PIN2)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_PIN1)==DETECT_NO)
    }while(1);
    //stop();
    //delay(10000)
    //goBackOneStep();
}

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


/**
 * 侧前方检测敌方函数
 * 会向那个方向进行转向
 * 刷新上一次物体方向
 * 进入前方探测器警戒模式
 */
void detectEnemySide(){
    if(digitalRead(DETECTOR_LEFT_FRONT)==DETECT_YES){
        turnLeftPosition(TURN_LEFT_SIDE);
        last_detect_side = DETECT_LAST_LEFT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        times_of_turns++;
        //delay(100);
        //detectEnemyFrontAlert();
    }else if(digitalRead(DETECTOR_RIGHT_FRONT)==DETECT_YES){
        turnRightPosition(TURN_RIGHT_SIDE);
        last_detect_side = DETECT_LAST_RIGHT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        times_of_turns++;
        //delay(100);
        //detectEnemyFrontAlert();
    }
}
// long detect_time = 0;
// int detect_time_if_begun = COMPLEMENTARY_TIME_NO;
// void detectEnemyFrontAlert(){
//     while (digitalRead(DETECTOR_FRONT)==DETECT_YES){
//         stop();
//     }
//     if(digitalRead(DETECTOR_FRONT)==DETECT_NO && timing==ENABLE_TO_TIMING){
//         if(complementary_time_judge==COMPLEMENTARY_TIME_NO){
//             complementary_time = millis();
//             complementary_time_judge = COMPLEMENTARY_TIME_YES;
//         }
//         if(millis()-complementary_time>COMPLEMENTARY_TIME_DELAY){
//             complementary_time_judge = COMPLEMENTARY_TIME_NO;
//             detect_if_detected = DETECT_IF_DETECTED_NO;
//             timing = NOT_ENABLE_TO_TIMING;
//             //uploadDetect();
//             //return;
//             switch (last_detect_side){
//             case DETECT_LAST_FRONT:
//                 return;
//                 break;
//             case DETECT_LAST_LEFT:
//                 turnLeftPosition(TURN_LEFT_SIDE_COMPLEMENTARY);
//                 last_detect_side = DETECT_LAST_FRONT;
//                 uploadDetect();
//                 return;
//                 break;
//             case DETECT_LAST_RIGHT:
//                 turnRightPosition(TURN_RIGHT_SIDE_COMPLEMENTARY);
//                 last_detect_side = DETECT_LAST_FRONT;
//                 uploadDetect();
//                 return;
//                 break;
//             }
//         }
//     }
// }

//前探测器探测函数
void detectEnemyFront(){
    // if(digitalRead(DETECTOR_FRONT)==DETECT_YES){
    //     do{
    //         stop();
    //     } while (digitalRead(DETECTOR_FRONT)==DETECT_YES);
    //     //for(;;){
    // }
    while (digitalRead(DETECTOR_FRONT)==DETECT_YES){
        //stop();
        PrepareforAttack();
    }
    if(digitalRead(DETECTOR_FRONT)==DETECT_NO && timing==ENABLE_TO_TIMING){
        if(complementary_time_judge==COMPLEMENTARY_TIME_NO){
            complementary_time = millis();
            complementary_time_judge = COMPLEMENTARY_TIME_YES;
        }
        if(millis()-complementary_time>COMPLEMENTARY_TIME_DELAY){
            complementary_time_judge = COMPLEMENTARY_TIME_NO;
            detect_if_detected = DETECT_IF_DETECTED_NO;
            timing = NOT_ENABLE_TO_TIMING;
            //uploadDetect();
            //return;
            if(times_of_turns%2==0){
                last_detect_side = DETECT_LAST_FRONT;
                uploadDetect();
                times_of_turns = 0;
                return;
            }else{
                switch (last_detect_side){
                // case DETECT_LAST_FRONT:
                //     return;
                //     break;
                case DETECT_LAST_LEFT:
                    turnLeftPosition(TURN_LEFT_SIDE_COMPLEMENTARY);
                    last_detect_side = DETECT_LAST_FRONT;
                    uploadDetect();
                    times_of_turns = 0;
                    return;
                    //break;
                case DETECT_LAST_RIGHT:
                    turnRightPosition(TURN_RIGHT_SIDE_COMPLEMENTARY);
                    last_detect_side = DETECT_LAST_FRONT;
                    uploadDetect();
                    times_of_turns = 0;
                    return;
                    //break;
                }
                //times_of_turns = 0;
            }
        }
    }
        //}
}

// /**
//  * 前探测器警戒函数，一旦丢失目标，先开始计时，如果超过一定值就判定丢失目标
//  */
// void detectEnemyFrontAlert(){
//     delay(200);
//     if(digitalRead(DETECTOR_FRONT)==DETECT_YES){
//         stop();
//     }else{
//         //if(complementary_time_judge==COMPLEMENTARY_TIME_NO){
//         complementary_time = millis();
//         //}
//         for(;;){
//             if(millis()-complementary_time>COMPLEMENTARY_TIME_DELAY){
//                 complementary();
//                 return;
//             } 
//         }
        
//     }
// }

/**
 * 转角补偿函数（未用）
 */
void complementary(){
    if(last_detect_side==DETECT_LAST_LEFT){
        turnLeftPosition(TURN_LEFT_SIDE_COMPLEMENTARY);
    }else if(last_detect_side==DETECT_LAST_RIGHT){
        turnRightPosition(TURN_RIGHT_SIDE_COMPLEMENTARY);
    }
}

//准备攻击（未测，等待硬件完成）
void PrepareforAttack(){
    int16_t pwm1;
    int16_t pwm2;
    stop_stuck();
    roboclaw.ReadPWMs(ADDRESS,pwm1,pwm2);
    if(pwm1>1000 && pwm2>1000){
        //do{
        int storage_front_end_sensors[7][2];
        int storage_front_end_sensors_temp[7][2] = {
            {0,0},
            {0,0},
            {0,0},
            {0,0},
            {0,0},
            {0,0},
            {0,0}
        };
        do{
            for(int i=0;i<7;++i){
            storage_front_end_sensors[i][1] = digitalRead(GRAYSCALE_SENSOR_PIN1);
            storage_front_end_sensors[i][2] = digitalRead(GRAYSCALE_SENSOR_PIN2);
            }
            attack();
        }while(storage_front_end_sensors==storage_front_end_sensors_temp);
        BackToTheDefensivePosition();  
        //delay(4000);
        //stop();
        //}while(1);
        
    }
}

//攻击函数
void attack(){
    gofront(GO_SPEED_ATTACK);
}

//微小转向（未使用）
void turnSlowOrMove(int ready_to_turn){
    if(ready_to_turn==READY_TO_TURN_LEFT){
        turnLeft(TURN_SLOW_SPEED);
    }else if(ready_to_turn==READY_TO_TURN_RIGHT){
        turnRight(TURN_SLOW_SPEED);
    }else if(ready_to_turn==READY_TO_GO_FRONT){
        gofront(TURN_SLOW_SPEED);
    }
}

//停止
void stop(){
    roboclaw.ForwardM1(ADDRESS, 0);
    //roboclaw.ForwardM1(address,speed);
    roboclaw.ForwardM2(ADDRESS, 0);
}


//停止后保持不动
void stop_stuck(){
    //for(;roboclaw.ReadEncM1(ADDRESS)>3 || roboclaw.ReadEncM2(ADDRESS)>3;){
        roboclaw.ResetEncoders(ADDRESS);
        //stop();
        roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 0, ACCEL2, 8000, DECCEL2, 0, 1);
    //}
    
}
// //停止后保持不动——修改后
// void stop_stuck_fixed(){
//     //for(int i=0;i<1500;++i){
//         stop_stuck();
//         //delay(1);
//     //}
// }
//原地左转，直到车头正对，在这之中可以被打断,0-127
void turnLeft(int speed){
    //roboclaw.ForwardM1(address, speed);
    roboclaw.BackwardM1(ADDRESS,speed);
    roboclaw.ForwardM2(ADDRESS, speed);
    //roboclaw.BackwardM2(address,speed);
}
//原地右转，直到车头正对，在这之中可以被打断,0-127
void turnRight(int speed){
    roboclaw.ForwardM1(ADDRESS, speed);
    //roboclaw.ForwardM1(address,speed);
    //roboclaw.ForwardM2(address, speed);
    roboclaw.BackwardM2(ADDRESS,speed);
}
//直行,0-127
void gofront(int speed){
    roboclaw.ForwardM1(ADDRESS, speed);
    roboclaw.ForwardM2(ADDRESS, speed-1);
}
//向左转,0-127
void goleft(int speed,int level){
    roboclaw.ForwardM1(ADDRESS, speed-level);
    roboclaw.ForwardM2(ADDRESS, speed+level);
}
//向右转,0-127
void goright(int speed,int level){
    roboclaw.ForwardM1(ADDRESS, speed+level);
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
    // long time_now = millis();
    // for(;;){
    //     if(millis()-time_now>400){
    //         //turnLeft();
    //         if(last_move_status==ON_RIGHT || last_move_status==ON_RIGHT_FRONT){
    //             //turnRight();
    //         }else{
    //             //turnLeft();
    //         }
    //         //roboclaw.ReadSpeedM1(address);
    //         //roboclaw.ReadSpeedM2(address);
            

    //     }
    //     if(detect()==ON_NOTHING){

    //     }else{
    //         return;
    //     }
    // }
}

// void goFrontPosition(){

// }
//M1电机前进位置函数
void M1PositionForward(int position){
    //static int M1PositionTemp = 0;
    //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    roboclaw.SetEncM1(ADDRESS,0);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, position, 0);
    for(;;){
        if(roboclaw.ReadEncM1(ADDRESS)<(position+4)&&roboclaw.ReadEncM1(ADDRESS)>(position-4)){
            return;
        }
    }
}
//M1电机后退位置函数
void M1PositionBackward(int position){
    //roboclaw.SetEncM1(ADDRESS,0);
    
    roboclaw.SetEncM1(ADDRESS,0);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -position, 1);
    for(;;){
        if(roboclaw.ReadEncM1(ADDRESS)<(-position+4)&&roboclaw.ReadEncM1(ADDRESS)>(-position-4)){
            return;
        }
    }
}
//M2电机后退位置函数
void M2PositionBackward(int position){
    //static int M1PositionTemp = 0;
    //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    roboclaw.SetEncM2(ADDRESS,0);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -position, 0);
    for(;;){
        if(roboclaw.ReadEncM2(ADDRESS)<(-position+4)&&roboclaw.ReadEncM2(ADDRESS)>(-position-4)){
            return;
        }
    }
}
//M2电机前进位置函数
void M2PositionForward(int position){
    //roboclaw.SetEncM1(ADDRESS,0);
    
    roboclaw.SetEncM2(ADDRESS,0);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, position, 1);
    for(;;){
        if(roboclaw.ReadEncM2(ADDRESS)<(position+4)&&roboclaw.ReadEncM2(ADDRESS)>(position-4)){
            return;
        }
    }
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
// int detectLeft(){
//     // if(analogRead(DETECTOR1)<313){
//     //     return DETECT_YES;
//     // }else{
//     //    return DETECT_NO; 
//     // }

//     if(digitalRead(DETECTOR1)==LOW){
//         return DETECT_YES;
//     }else{
//         return DETECT_NO;
//     }
// }
//检测左偏前传感器
// int detectLeftFront(){
//     // if(digitalRead(DETECTOR2)==LOW){
//     //     return DETECT_YES;
//     // }else{
//     //     return DETECT_NO;
//     // }
    
//     if(analogRead(DETECTOR2)<310){
//         return DETECT_YES;
//     }else{
//        return DETECT_NO; 
//     }
// }
//检测前偏左传感器
// int detectLeftFrontMore(){
//     if(analogRead(DETECTOR3)<310){
//         return DETECT_YES;
//     }else{
//        return DETECT_NO; 
//     }
// }
//检测前方传感器
// int detectFront(){
//     if(digitalRead(DETECTOR3)==LOW){
//         return DETECT_YES;
//     }else{
//         return DETECT_NO;
//     }
// }
//检测右方传感器
// int detectRight(){
//     // if(analogRead(DETECTOR7)<317){
//     //     return DETECT_YES;
//     // }else{
//     //    return DETECT_NO; 
//     // }

//     if(digitalRead(DETECTOR5)==LOW){
//         return DETECT_YES;
//     }else{
//         return DETECT_NO;
//     }
// }
//检测右偏前传感器
// int detectRightFront(){
//     // if(digitalRead(DETECTOR4)==LOW){
//     //     return DETECT_YES;
//     // }else{
//     //     return DETECT_NO;
//     // }

//     if(analogRead(DETECTOR4)<333){
//         return DETECT_YES;
//     }else{
//        return DETECT_NO; 
//     }
// }
//检测前偏右传感器
// int detectRightFrontMore(){
//     if(analogRead(DETECTOR5)<333){
//         return DETECT_YES;
//     }else{
//        return DETECT_NO; 
//     }
    
// }

//检测后侧数据，返回应该向哪走（未使用）
int detectorBack(){
    if(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>TURN_ERROR_VALUE){
        return READY_TO_TURN_LEFT;
    }else if(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)<TURN_ERROR_VALUE){
        return READY_TO_TURN_RIGHT;
    }else{
        return READY_TO_GO_FRONT;
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

    // /**
    //  * 这个模块中，优先检测前方，在从侧边向前方递进
    //  */
    // if(detectFront()==DETECT_YES){
    //     return ON_FRONT;
    // // }else if(detectLeftFrontMore()==DETECT_YES){
    // //     return ON_LEFT_FRONT_MORE;
    // // }else if(detectRightFrontMore()==DETECT_YES){
    // //     return ON_RIGHT_FRONT_MORE;
    // }else if(detectLeftFront()==DETECT_YES){
    //     return ON_LEFT_FRONT;
    // }else if(detectRightFront()==DETECT_YES){
    //     return ON_RIGHT_FRONT;
    // }else if(detectLeft()==DETECT_YES){
    //     return ON_LEFT;
    // }else if(detectRight()==DETECT_YES){
    //     return ON_RIGHT;
    // }else{
    //     return ON_NOTHING;
    // }

//     if(detectFront()==DETECT_YES){
//         return ON_FRONT;
//     }else if(detectLeft()==DETECT_YES){
//         return ON_LEFT;
//     }else if(detectRight()==DETECT_YES){
//         return ON_RIGHT;
//     }else if(detectLeftFront()==DETECT_YES){
//         return ON_LEFT_FRONT;
//     }else if(detectRightFront()==DETECT_YES){
//         return ON_RIGHT_FRONT;
//     }else if(detectLeftFrontMore()==DETECT_YES){
//         return ON_LEFT_FRONT_MORE;
//     }else if(detectRightFrontMore()==DETECT_YES){
//         return ON_RIGHT_FRONT_MORE;
    
    
//     }else{
//         return ON_NOTHING;
//     }
}
//探测器以上---------------------------------------------------------------------------------------------------


//记录以下-----------------------------------------------------------------------------------------------------

//记录开始时间
// void time_begin(int status){
//     if(time_temp==TIME_NO){
//         time_start = millis();
//         time_temp = TIME_YES;
//         time_status = status;
//     }
// }

//存储日志函数
// void record(){
//     if(time_temp==TIME_YES){
//         MyObject mylog;
//         mylog.times = ++log_times;
//         mylog.time = millis()-time_start;
//         //mylog.time = 12233;
//         mylog.statue = time_status;
//         EEPROM.put(addr,mylog);
//         addr += sizeof(MyObject);
//         time_temp = TIME_NO;
//     }
//     // if(addr>1000){

//     // }else{
//     //     MyObject jilu;
//     //     jilu.time_record = millis();
//     //     jilu.status = choice;
//     //     EEPROM.put(addr,jilu);
//     //     addr += sizeof(MyObject);
//     // }
// }
//记录以上-----------------------------------------------------------------------------------------------------


//行进程序
// void move(int status){
//     switch (status){
//     case ON_LEFT:
//         //状态1
//         //record(1);
//         //在正左方
//         //left();
//         //goleft(goSpeedFast);
//         break;
//     case ON_LEFT_FRONT:
//         //状态2
//         //record(2);
//         //在左前方
//         //left_front();
//         //goleft(goSpeedSlow);
//         break;
//     case ON_FRONT:
//         //状态3
//         //record(3);
//         //在前方
//         //forward();
//         //gofront();
//         break;
//     case ON_RIGHT_FRONT:
//         //状态4
//         //record(4);
//         //在右前方
//         //right_front();
//         //goright(goSpeedSlow);
//         break;
//     case ON_RIGHT:
//         //状态5
//         //record(5);
//         //在正右方
//         //right();
//         //goright(goSpeedFast);
//         break;
//     case ON_NOTHING:
//         //状态6
//         //record(6);
//         //暂时没有检测到
//         //如果没有检测到，可能是真的没有检测到，也有可能是在转弯过程中刚刚好转到了一个中间的位置-
//         //所以不作为
//         //turnLeft();
//         //stop();
//         //gonothing();
//         break;
//     default:
//         //状态7
//         //record(7);
//         //其他情况
//         break;
//     }
//     //roboclaw.ForwardM1(address, speed);
//     //roboclaw.ForwardM2(address, speed);
// }

/**
 * 原地转向函数
 */
// void faceToEnemy(){

//     switch (detect()){
//     case ON_LEFT:
//         turnLeftPosition(TURNLEFT90);
//         break;
//     case ON_LEFT_FRONT:
//         turnLeftPosition(TURNLEFT_SMALL);
//         break;
//     case ON_RIGHT:
//         turnRightPosition(TURNRIGHT90);
//         break;
//     case ON_RIGHT_FRONT:
//         turnRightPosition(TURNRIGHT_SMALL);
//         break;
//     default:
//         stop();
//         break;
//     }
    // switch (detect()){
    // // case ON_LEFT:
    // //     //状态1
    // //     //record(1);
    // //     //在正左方
    // //     //time_begin(onleft);
    // //     //turnLeft(TURN_SPEED_FAST);
    // //     //time_begin(ON_LEFT);
    // //     turnLeftPosition(TURNLEFT90);
    // //     //record();
    // //     //delay(2000);
    // //     //for(;;){}
    // //     break;
    // case ON_LEFT:
    //     //状态2
    //     //record(2);
    //     //在左前方
    //     //time_begin(onleftfront);
    //     //turnLeft(TURN_SPEED_MIDDLE);
    //     turnLeftPosition(TURNLEFT90);
    //     //delay(2000);
    //     //for(;;){}
    //     break;
    // // case ON_FRONT:
    // //     //状态3
    // //     //record(3);
    // //     //在前方
    // //     //record();
    // //     //forward();
    // //     //delay(14);
    // //     stop();
    // //     //stop_stuck();
    // //     //stop_stuck_fixed();
    // //     break;
    // case ON_RIGHT:
    //     //状态4
    //     //record(4);
    //     //在右前方
    //     //time_begin(onrightfront);
    //     //right_front();
    //     turnRightPosition(TURNRIGHT90);
    //     //turnRight(TURN_SPEED_MIDDLE);
    //     //for(;;){}
    //     //delay(2000);
    //     break;
    // // case ON_RIGHT:
    // //     //状态5
    // //     //record(5);
    // //     //在正右方
    // //     //time_begin(onright);
    // //     //right();
    // //     turnRightPosition(TURNRIGHT90);
    // //     //turnRight(TURN_SPEED_FAST);
    // //     //for(;;){}
    // //     //delay(2000);
    // //     break;
    // case ON_LEFT_FRONT:
    //     //状态7
    //     //record(6);
    //     //在左前方更靠近前方
    //     //turnLeft(TURN_SPEED_SLOW);
    //     turnLeftPosition(TURNLEFT_SMALL);
    //     //delay(2000);
    //     //for(;;){}
    //     break;
    // case ON_RIGHT_FRONT:
    //     //状态8
    //     //record(6);
    //     //在右前方更靠近前方
    //     //turnRight(TURN_SPEED_SLOW);
        
    //     turnRightPosition(TURNRIGHT_SMALL);
    //     //delay(2000);
    //     //for(;;){}
    //     break;
    // // case onnothing:
    // //     //状态6
    // //     //record(6);
    // //     //暂时没有检测到
    // //     //如果没有检测到，可能是真的没有检测到，也有可能是在转弯过程中刚刚好转到了一个中间的位置-
    // //     //所以不作为
    // //     break;
    // default:
    //     stop();
    //     //状态7
    //     //record(7);
    //     //其他情况
    //     break;
    // }
//}

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

//初始基准线函数，13号灯双闪
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

/**
 * 探测器打印日志函数
 */
void Println(){
    // if(roboclaw.ReadEncM2(ADDRESS)>=1){
    //     Serial.println("YES");
    // }else{
    //     Serial.println("NO");
    // }
    //Serial.println(roboclaw.ReadEncM2(ADDRESS));
    // static int lastsum = 0;
    // Serial.print("A0:");
    // Serial.print(analogRead(A0));
    // Serial.print("....A1:");
    // Serial.print(analogRead(A1));
    // Serial.print("....cha:");
    // Serial.print(analogRead(A1)-analogRead(A0));
    // Serial.print("....he:");
    // Serial.print(analogRead(A1)+analogRead(A0));
    // Serial.print("....change:");
    // Serial.println(analogRead(A1)+analogRead(A0)-lastsum);
    // lastsum = analogRead(A1)+analogRead(A0);
    //Serial.rintln()
    // Serial.print(analogRead(DETECTOR1));
    // Serial.print(".....");
    // Serial.println(analogRead(DETECTOR7));
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
    //delay(1000);
}

//测试
void test_temp(){
    // //Serial.begin(9600);
    // Serial.print("1:");
    // Serial.print(digitalRead(DETECTOR1));
    // Serial.print(",2:");
    // Serial.print(analogRead(DETECTOR2));
    // //Serial.print(analogRead(DETECTOR2));
    // Serial.print(",3:");
    // Serial.print(digitalRead(DETECTOR3));
    // //Serial.print(digitalRead(DETECTOR3));
    // Serial.print(",4:");
    // Serial.print(analogRead(DETECTOR4));
    // Serial.print(",5:");
    // Serial.println(digitalRead(DETECTOR5));
    //Serial.print(digitalRead(DETECTOR5));
    // Serial.print(",6:");
    // Serial.print(digitalRead(DETECTOR6));
    // //Serial.print(analogRead(DETECTOR6));
    // Serial.print(",7:");
    // Serial.print(analogRead(DETECTOR7));
    // Serial.println(":");
    //Serial.println(analogRead(A1));
    //Serial.
    //delay(400);
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

//测试函数
void test(){
    //delay(5000);
    //for(int i=0;i<10;++i){
        // Serial.print("left:");
        // Serial.print(analogRead(DETECTOR_LEFT_A0));
        // Serial.print("....right:");
        // Serial.println(analogRead(DETECTOR_RIGHT_A1));
        // Serial.print("....A2-A3:");
        // Serial.println(analogRead(A2)-analogRead(A3));
        //delay(1000);
    //}
    // turnLeftPosition(TURN_SLOW_POSITION);
    // for(;;){
    //     Serial.print("left:");
    //     Serial.print(analogRead(A2));
    //     Serial.print("....right:");
    //     Serial.print(analogRead(A3));
    //     Serial.print("....A2-A3:");
    //     Serial.println(analogRead(A2)-analogRead(A3));
    //     delay(1000);
    // }
    
}


//搜索敌人总函数
void searchForEnemy(){
    if(detect_if_detected==DETECT_IF_DETECTED_NO){
        detectEnemy();//down
    // //alignmentOnlyOnce();//down
        alignmentMoreStringent();
    }
    detectEnemySide();
    detectEnemyFront();
    //uploadDetect();
    //goFrontPosition();//down
}



//原始函数：
void setup(){
    //定义模拟串口
    roboclaw.begin(38400);
    Serial.begin(9600);
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
    uploadDetect();
    // last_detect_left = 400;
    // last_detect_right = 400;
    
}

//两者平时大概在-500到+500左右，受到推力后大概在2000+


void loop(){
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
    searchForEnemy();
    // Serial.println(analogRead(DETECTOR_BACK_A2));
    // delay(1000);
}

