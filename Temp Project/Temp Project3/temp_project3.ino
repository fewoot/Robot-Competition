/**
 * 第三阶段：完成
 * 平齐1200左右，误差在+-10,变化最小时170
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
#define TURNLEFT90 470
//左转——大
#define TURNLEFT_BIG 160
//左转——小
#define TURNLEFT_SMALL 140
//右转—90°
#define TURNRIGHT90 450
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

//微小角度转向位置（使用）
#define TURN_SLOW_POSITION 25

//微小前进位置（使用）
#define GO_SLOW_POSITION 25

//最小检测变化，用于两侧90°转向时判断是否有物体
#define MIN_DETECT_CHANGE 177

//对正时两个探测器数值差异范围
#define OffSET_THRESHOLD 10

/**
 * 定义检测到物体没有
 */
#define DETECT_YES 0
#define DETECT_NO 1

//记录无敌人时，左侧边界的距离
int last_detect_left = 0;

//记录无敌人时，右侧边界的距离
int last_detect_right = 0;

//记录两侧探测器的数值总和，没用
int last_detect_sum = 1200;

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
    for(;roboclaw.ReadEncM1(ADDRESS)>3 || roboclaw.ReadEncM2(ADDRESS)>3;){
        roboclaw.ResetEncoders(ADDRESS);
        //stop();
        roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 0, ACCEL2, 8000, DECCEL2, 0, 1);
    }
    
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
    roboclaw.ForwardM2(ADDRESS, speed);
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
    static int lastsum = 0;
    Serial.print("A0:");
    Serial.print(analogRead(A0));
    Serial.print("....A1:");
    Serial.print(analogRead(A1));
    Serial.print("....cha:");
    Serial.print(analogRead(A1)-analogRead(A0));
    Serial.print("....he:");
    Serial.print(analogRead(A1)+analogRead(A0));
    Serial.print("....change:");
    Serial.println(analogRead(A1)+analogRead(A0)-lastsum);
    
    lastsum = analogRead(A1)+analogRead(A0);
    
    //Serial.println()
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
    delay(1000);
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

//测试函数
void test(){
    //delay(5000);
    for(int i=0;i<10;++i){
        Serial.print("left:");
        Serial.print(analogRead(A2));
        Serial.print("....right:");
        Serial.print(analogRead(A3));
        Serial.print("....A2-A3:");
        Serial.println(analogRead(A2)-analogRead(A3));
        delay(1000);
    }
    turnLeftPosition(TURN_SLOW_POSITION);
    for(;;){
        Serial.print("left:");
        Serial.print(analogRead(A2));
        Serial.print("....right:");
        Serial.print(analogRead(A3));
        Serial.print("....A2-A3:");
        Serial.println(analogRead(A2)-analogRead(A3));
        delay(1000);
    }
    
}


//搜索敌人总函数
void searchForEnemy(){
    detectEnemy();//down
    alignment();//down
    //uploadDetect();
    //goFrontPosition();//down
}


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
    if(last_detect_left-analogRead(DETECTOR_LEFT_A0)>=MIN_DETECT_CHANGE){
        turnLeftPosition(TURNLEFT90);
        uploadDetect();
    }else if(last_detect_right-analogRead(DETECTOR_RIGHT_A1)>=MIN_DETECT_CHANGE){
        turnRightPosition(TURNRIGHT90);
        uploadDetect();
    }
    
}

/**
 * 对正函数
 * 会根据后面的两个传感器进行和边界对齐
 * 如果对齐（有一定的误差忽视），则会更新两侧的距离常数，同时前进一点
 */
void alignment(){
    if(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>OffSET_THRESHOLD){
        turnLeftPosition(TURN_SLOW_POSITION);
    }else if(analogRead(DETECTOR_BACK_A3)-analogRead(DETECTOR_BACK_A2)>OffSET_THRESHOLD){
        turnRightPosition(TURN_SLOW_POSITION);
    }else{
        //baseline();
        //last_detect_left = 
        uploadDetect();
        goFrontPosition();
    }
}

//距离更新函数
void uploadDetect(){
    delay(200);
    last_detect_left = analogRead(DETECTOR_LEFT_A0);
    last_detect_right = analogRead(DETECTOR_RIGHT_A1);
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
    // delay(3000);
    // turnRightPosition(350);
    // delay(9000);
    // turnRightPosition(360);
    // delay(9000);
    // turnRightPosition(370);
    //delay(3000);
    //turnLeftPosition(370);
    // delay(10000);
    // turnLeftPosition(500);
    //pinMode(3,INPUT);
    //roboclaw.SetEncM1(address,0);
    //turn_round(900);
    //test_temp();
    //stop();
    delay(1000);
    //首先更新一下场上的距离常数，在行动
    uploadDetect();
}

void loop(){
    //turnRightPosition(TURNLEFT90);
    // delay(3000);
    //Println();
    //Serial.println(analogRead(DETECTOR2));
    //faceToEnemy();
    // if(detectRight()==DETECT_YES){
    //     turnRightPosition(TURNRIGHT90);
    // }else if(detectLeft()==DETECT_YES){
    //     turnLeftPosition(TURNRIGHT90);
    // }else if(detectLeftFront()==DETECT_YES){
    //     turnLeftPosition(TURNLEFT_SMALL);
    // }else if(detectRightFront()==DETECT_YES){
    //     turnRightPosition(TURNRIGHT_SMALL);
    // }
    //test_temp();
    // //turn_round(900);
    // //delay(4000);
    // /**
    //  * 开始启动
    //  * 通过检测传感器的数据来决定位置
    //  */
    // //detect();
    // //status_set();
    // //gofront();
    // //goleft(goSpeedSlow);
    // //goright(goSpeedSlow);
    // //move();
    // //move_set();
    // //stop();
    // //turnLeft();
    // //turnRight();
    // //test_temp();
    // faceToEnemy();
    // Println();
    // //Serial.println(digitalRead(7));
    // //roboclaw.ResetEncoders(address);
    // //stop();
    // //stop_stuck();
    // //roboclaw.SpeedAccelDeccelPositionM1(address, 50, 5, 50, 0, 1);
    // //Serial.println(digitalRead(5));
    // // turnLeft(TURN_SPEED_FAST);
    // // delay(316);
    // // stop();
    // // delay(10000);

    // // turnLeft(TURN_SPEED_FAST);
    // // delay(317);
    // // stop();
    // // delay(10000);

    // // turnLeft(TURN_SPEED_FAST);
    // // delay(318);
    // // stop();
    // // delay(10000);

    // // turnLeft(TURN_SPEED_FAST);
    // // delay(319);
    // // stop();
    // // for(;;){}
    // //turnLeft(127);
    // //roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -3600, 1);
    // //M1PositionForward(3600);
    // //M1PositionBackward(3600);
    // //M2PositionForward(3600);
    // //turnLeftPosition(900);
    // //turnRightPosition(900);
    // // delay(5000);
    // // turnRightPosition(TURNRIGHT90);
    // // delay(5000);
    // // turnRightPosition(TURNRIGHT_BIG);
    // // delay(5000);
    // // turnRightPosition(TURNRIGHT_SMALL);
    
    // // delay(5000);
    // // turnLeftPosition(TURNLEFT_SMALL);
    // // delay(5000);
    // // turnLeftPosition(TURNLEFT_BIG);
    // // delay(5000);
    // // turnLeftPosition(TURNLEFT90);
    // // turnRightPosition(120);
    // // delay(3000);
    // // //turnLeftPosition(120);
    // // turnRightPosition(125);
    // // delay(3000);
    // // turnRightPosition(130);
    // //turnLeftPosition(130);
    //Println();
    // //test_temp();
    // //M2PositionForward(3600);
    // //turnRightPosition(3600);
    // //goright(20,10);
    // //faceToEnemy();
    // // switch (detect()){
    // // case ON_LEFT:
    // //     //状态1
    // //     //record(1);
    // //     //在正左方
    // //     //time_begin(onleft);
    // //     //turnLeft(TURN_SPEED_FAST);
    // //     turnLeftPosition(TURNLEFT90);
    // //     delay(5000);
    // //     //for(;;){}
    // //     break;
    // // }
    // //roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, 360, 1);
    //faceToEnemy();
    // turnLeftPosition(TURNLEFT90);
    // delay
    //Println();
    //roboclaw.ForwardM1(ADDRESS, 40);
    // roboclaw.BackwardM1(address,speed);
    // roboclaw.ForwardM2(address, speed);
    // roboclaw.BackwardM2(address,speed);
    // roboclaw.SpeedAccelDeccelPositionM1(address, accel, speed, deccel, position, flag);
    // roboclaw.SpeedAccelDeccelPositionM2(address, accel, speed, deccel, position, flag);
    
    // turnLeft(TURN_SLOW_SPEED);
    // delay(10000);
    // turnRight(TURN_SLOW_SPEED);
    // delay(10000);
    // gofront(GO_SLOW_SPEED);
    // delay(20000);
    //turnLeftPosition(25);
    //searchForEnemy();
    // roboclaw.ResetEncoders(ADDRESS);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 90, ACCEL2, 8000, DECCEL2, 90, 1);
    // for(;roboclaw.ReadEncM1(ADDRESS)<(GO_SLOW_POSITION+ERROR_POSITION);){}
    //goFrontPosition();
    //turnLeftPosition(TURNLEFT90+130);
    // turnRightPosition(TURNRIGHT90+130);
    // delay(5000);
    // turnRightPosition(TURNRIGHT90+130);
    // delay(5000);
    // turnRightPosition(TURNRIGHT90+130);
    // delay(5000);
    // turnRightPosition(TURNRIGHT90+130);
    // delay(5000);
    // turnLeftPosition(TURNLEFT90+130);
    // delay(5000);
    // turnLeftPosition(TURNLEFT90+130);
    // delay(5000);
    // turnLeftPosition(TURNLEFT90+130);
    // delay(5000);
    // detectEnemy();
    // //delay(1000);
    // uploadDetect();
    
    // if(millis()>20000){
    //     for(;;){}
    // }
    //test();
    //alignment();
    //delay(1000);
    searchForEnemy();
    // turnLeftPosition(TURNLEFT90);
    // delay(1000);
}
