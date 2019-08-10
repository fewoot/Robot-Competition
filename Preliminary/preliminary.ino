/**
 * 预赛程序
 */

/**
 *记录：
 * 等待更新用122333标记
 * 2019年7月31日：当两个后侧传感器走到台子的边缘时，两个传感器的数值为360-370左右，而且因为结-
 * 构的原因，左边的传感器平均比右边的少一些，可以在读数后面加上2来平衡。(2好像有点大，可以试试1)-
 * 两个后侧传感器在台下正中时，读数为235-245，同样加上2，和边界紧挨的时候读数为178左右-
 * 两个后侧传感器在刀刃距离边缘3-5cm时读书为890左右-
 * 两个后侧传感器的红外折射盲区依然存在-
 * 在台子下两个后侧传感器可以正常工作
 * 
 * 2019年7月31日：经过测试，还是将两个后侧传感器分开了一定角度，这样才好增大两者的读数差异，减小-
 * 电压波动等的影响更新后数据：当两个后侧传感器走到台子的边缘时，两个传感器的数值为360左右，
 * 两个后侧传感器在台下正中时，读数为242左右，发现一个严重的问题，当两个传感器夹角过大时会频繁的检测到no singal-
 * 很危险
 * 
 * 2019年7月31日：经过改进，使得后侧两个传感器的夹角不会特别大，现在可以正常工作了。-
 * 更新记录：两个后侧传感器在边缘之上时数值为370左右，台下中点250左右，差值可以限定在3左右
 * 
 * 2019年7月31日：向右缓慢旋转90°编码器值约在390左右,台子走一半的编码器值为2800左右
 * 
 * 2019年7月31日：对于小板，可以通过实例化不同的电机对象来控制不同的电机，已经过实验，但是-
 * 如何用硬件串口来控制电机驱动板依然未知(已完成)，中传感器的数值已完成
 * 
 * 2019年8月1日：新建了后退上台和原地转身函数，未测试
 * 新建了上台电机的电机驱动对象，但是已经注释掉，需要解锁
 * 
 * 2019年8月4日：经过检测，出现了一个问题，电机的编码器出现问题，无法正常读取数值，很气，已经用延时来修复
 * 
 * 2019年8月7日：今天和两个小车进行了对撞，其中有一个推不过，总线也有烧焦的痕迹，明早继续实验
 */

/**
 * 目前用不到，暂存
 */

// void UseForMoreSubtleAdjustmentJudgmentWhenAdjustingInSitu(){
// // }
// /**
//  * 为了之后尽量沿直线走，先原地调整（利用慢速转向已经解决）
//  */
// void inOrderToGoAlongStraightFirstSteeralignment(){
//     // int last_detect_temp1[7];
//     // int last_detect_temp2[7];
//     // int last_detect_temp_averge1;
//     // int last_detect_temp_averge2;
//     // last_detect_temp1[0] = analogRead(DETECTOR_BACK_LEFT)+3;
//     // last_detect_temp2[0] = analogRead(DETECTOR_BACK_RIGHT);
//     // last_detect_temp1[1] = analogRead(DETECTOR_BACK_LEFT)+3;
//     // last_detect_temp2[1] = analogRead(DETECTOR_BACK_RIGHT);
//     // last_detect_temp1[2] = analogRead(DETECTOR_BACK_LEFT)+3;
//     // last_detect_temp2[2] = analogRead(DETECTOR_BACK_RIGHT);
//     // last_detect_temp1[3] = analogRead(DETECTOR_BACK_LEFT)+3;
//     // last_detect_temp2[3] = analogRead(DETECTOR_BACK_RIGHT);
//     // last_detect_temp1[4] = analogRead(DETECTOR_BACK_LEFT)+3;
//     // last_detect_temp2[4] = analogRead(DETECTOR_BACK_RIGHT);
//     // last_detect_temp1[5] = analogRead(DETECTOR_BACK_LEFT)+3;
//     // last_detect_temp2[5] = analogRead(DETECTOR_BACK_RIGHT);
//     // last_detect_temp1[6] = analogRead(DETECTOR_BACK_LEFT)+3;
//     // last_detect_temp2[6] = analogRead(DETECTOR_BACK_RIGHT);
//     // last_detect_temp_averge1 = (last_detect_temp1[1]+last_detect_temp1[2]+last_detect_temp1[0]+last_detect_temp1[3]+last_detect_temp1[4]+last_detect_temp1[5]+last_detect_temp1[6])/7;
//     // last_detect_temp_averge2 = (last_detect_temp2[1]+last_detect_temp2[2]+last_detect_temp2[0]+last_detect_temp2[3]+last_detect_temp2[4]+last_detect_temp2[5]+last_detect_temp2[6])/7;
    
//     // int last_detect_temp1[3];
//     // int last_detect_temp2[3];
//     // int last_detect_temp_averge1;
//     // int last_detect_temp_averge2;
//     // while (1){
//     //     last_detect_temp1[0] = analogRead(DETECTOR_BACK_LEFT)+1;
//     //     last_detect_temp2[0] = analogRead(DETECTOR_BACK_RIGHT);
//     //     last_detect_temp1[1] = analogRead(DETECTOR_BACK_LEFT)+1;
//     //     last_detect_temp2[1] = analogRead(DETECTOR_BACK_RIGHT);
//     //     last_detect_temp1[2] = analogRead(DETECTOR_BACK_LEFT)+1;
//     //     last_detect_temp2[2] = analogRead(DETECTOR_BACK_RIGHT);
//     //     last_detect_temp_averge1 = (last_detect_temp1[1]+last_detect_temp1[2]+last_detect_temp1[0])/3;
//     //     last_detect_temp_averge2 = (last_detect_temp2[1]+last_detect_temp2[2]+last_detect_temp2[0])/3;
//         // if(last_detect_temp1-last_detect_temp2>(OFFSET_THRESHOLD_ADJUST_SLOW-9)){
//         //     turnLeftPosition(TURN_SLOW_POSITION);
//         // }else if(last_detect_temp2-last_detect_temp1>(OFFSET_THRESHOLD_ADJUST_SLOW-9)){
//         //     turnRightPosition(TURN_SLOW_POSITION);
//         // }else{
//         //     //roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, 1800, ACCEL2, 2000, DECCEL2, 1800, 1);
//         //     //delay(1000);
//         //     return;
//         // }
//         // if(last_detect_temp_averge1-last_detect_temp_averge2>(OFFSET_THRESHOLD_ADJUST_SLOW-5)){
//         //     turnLeftPosition(TURN_SLOW_POSITION);
//         // }else if(last_detect_temp_averge2-last_detect_temp_averge1>(OFFSET_THRESHOLD_ADJUST_SLOW-5)){
//         //     turnRightPosition(TURN_SLOW_POSITION);
//         // }else{
//         //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, 1800, ACCEL2, 2000, DECCEL2, 1800, 1);
//         //     //delay(1000);
//         //     return;
//         // }
// }


// /**
//  * 检测不到物体时的程序，会进行400ms的延时，用来避免转到两个传感器中间就触发此程序-
//  * 并会根据最后一次转向行进顺着方向进行原地旋转（未用）
//  */
// void gonothing(){
//     // static int temp = 0;
//     // if(temp==0){
//     //     long time_now = millis();
//     //     temp = 1;
//     // }
//     // long time_now = millis();
//     // for(;;){
//     //     if(millis()-time_now>400){
//     //         //turnLeft();
//     //         if(last_move_status==ON_RIGHT || last_move_status==ON_RIGHT_FRONT){
//     //             //turnRight();
//     //         }else{
//     //             //turnLeft();
//     //         }
//     //         //roboclaw.ReadSpeedM1(address);
//     //         //roboclaw.ReadSpeedM2(address);
            

//     //     }
//     //     if(detect()==ON_NOTHING){

//     //     }else{
//     //         return;
//     //     }
//     // }
// }

/**
 * 已被编码器转向系统取代
 */
// //原地左转，直到车头正对，在这之中可以被打断,0-127
// void turnLeft(int speed){
//     //roboclaw.ForwardM1(address, speed);
//     roboclaw.BackwardM1(ADDRESS,speed);
//     roboclaw.ForwardM2(ADDRESS, speed);
//     //roboclaw.BackwardM2(address,speed);
// }

/**
 * 已被编码器转向系统取代
 */
// //原地右转，直到车头正对，在这之中可以被打断,0-127
// void turnRight(int speed){
//     roboclaw.ForwardM1(ADDRESS, speed);
//     //roboclaw.ForwardM1(address,speed);
//     //roboclaw.ForwardM2(address, speed);
//     roboclaw.BackwardM2(ADDRESS,speed);
// }


// //对齐时判断是否已经对齐过
// int alignment_only_once = 0;
// //记录两侧探测器的数值总和，没用
// int last_detect_sum = 1200;
// #define DETECTOR1 5
// #define DETECTOR2 A3
// #define DETECTOR3 6
// #define DETECTOR4 A2
// #define DETECTOR5 7
// #define DETECTOR6 7
// #define DETECTOR7 A3
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
// //定义探测距离
// #define DETECT_DISTANCE 250
// //定义日志是否已经开始
// #define TIME_YES 1
// #define TIME_NO 0
// //定义转向状态（目前未使用）
// #define READY_TO_TURN_RIGHT 1
// #define READY_TO_TURN_LEFT 0
// #define READY_TO_GO_FRONT 2
// //转向误差值（未使用）
// #define TURN_ERROR_VALUE 20
// //微小角度转向速度（未使用）
// #define TURN_SLOW_SPEED 9
// //微小前进速度（未使用）
// #define GO_SLOW_SPEED 8
// //定义后退速度
// #define GO_BAKC_SPEED 50
// //定义当两侧距离突然剧增时阈值
// #define MINI_CHANGE 150
// //定义异常增长值，本是为了防止传感器返回异常大的值后回落使得小车误以为监测到敌人，已经被取代
// #define ABNORMAL_INCREASE 300
// //右转——大
// #define TURNRIGHT_BIG 175//旧
// #define TURN_RIGHT_BIG 175
// //右转——小
// #define TURNRIGHT_SMALL 160//旧
// #define TURN_RIGHT_SMALL 160
// //左转——大
// #define TURNLEFT_BIG 160//旧
// // #define TURN_LEFT_BIG 160
// // //左转——小
// // #define TURNLEFT_SMALL 140//旧
// // #define TURN_LEFT_SMALL 140
// //#define TURNLEFT90 530//旧
// #define TURNRIGHT90 530//旧
// #define ONE_ROUND 900//旧
// #define DRIVER_S1 11//旧
// #define DRIVER_S2 10//旧
// #define DETECTOR_BACK_A2 A2//旧
// // #define OffSET_THRESHOLD 10//旧
// // #define TURN_RIGHT_SIDE //旧
// #define DETECTOR_LEFT_A0 A0//旧
// //#define GRAYSCALE_SENSOR_PIN2 //旧
// //#define MIN_DETECT_CHANGE 177//旧
// #define DETECTOR_RIGHT_A1 A1//旧
// // #define TURN_LEFT_SIDE //旧
// #define DETECTOR_BACK_A3 A3//旧


//#define GRAYSCALE_SENSOR_PIN1 //旧

/**
 * 所需的库
 */
#include <SoftwareSerial.h>
#include <RoboClaw.h>

//因为两个后侧传感器的硬件位置有偏差，所以可以在这里手动补偿一些值
#define LEFT_REAR_SENSOR_COMPENSATION_VALUE 3
#define RIGHT_REAR_SENSOR_COMPENSATION_VALUE 0

//左转90°

#define TURN_LEFT_POSITION_90 820
#define TURN_LEFT_POSITION_90_SLOWLY 465

//右转—90°

#define TURN_RIGHT_POSITION_90 800
#define TURN_RIGHT_POSITION_90_SLOWLY 455

//位置误差,用于在左右固定转向时在误差范围内取消轮胎锁定，使其不会回摆
#define ERROR_POSITION 10

//经测试，900左右END值是一圈

#define ONE_ROUND_POSITION 900

//定义电机驱动模块引脚
//电机和主板模拟引脚1

#define MOTOR_DRIVER_S1 11

//电机和主板模拟引脚2

#define MOTOR_DRIVER_S2 10

//设置电机板命令存储位置
#define ADDRESS 0x80

//设置电机和主板连接超时值
#define TIME_OUT 10000

//加速度设置，默认
#define ACCEL 655360
#define DECCEL 655360
#define ACCEL1 655360
#define ACCEL2 655360
#define DECCEL1 655360
#define DECCEL2 655360

//后侧左边传感器,已更改

#define DETECTOR_BACK_LEFT A7

//后侧右边传感器

#define DETECTOR_BACK_RIGHT A8

//左侧传感器

#define DETECTOR_LEFT A1

//右侧传感器

#define DETECTOR_RIGHT A0

//除4个距离传感器外其他传感器，等待更改
//左前方传感器
#define DETECTOR_LEFT_FRONT A6

//更靠近前方的左前方传感器
#define DETECTOR_LEFT_FRONT_MORE A5

//正前方传感器
#define DETECTOR_FRONT A4

//右前方传感器
#define DETECTOR_RIGHT_FRONT A2

//更靠近前方的右前方传感器
#define DETECTOR_RIGHT_FRONT_MORE A3

//边缘传感器1

#define GRAYSCALE_SENSOR_LEFT 36

//边缘传感器

#define GRAYSCALE_SENSOT_RIGHT 37

//进攻时的速度
#define GO_SPEED_ATTACK 20

//微小角度转向
#define TURN_SLOW_POSITION 25

//微小前进
#define GO_SLOW_POSITION 25

//最小检测变化，用于两侧90°转向时判断是否有物体,如果变化大于这个值，则判定有敌人

#define MIN_DETECT_TO_90_ENEMY_JUDGE 177

//对正时两个探测器数值差异范围，超过这个值则会调整

#define OFFSET_THRESHOLD_ADJUST_SLOW 8

//定义传输值no_signal值，当值大于等于它时，认为此值无效
#define NO_SIGNAL_VALUE 880

//传感器检测到物体
#define DETECT_YES 0

//传感器未检测到物体
#define DETECT_NO 1

//上一次检测到物体的方向，用于使小车再次转向补偿
#define DETECT_LAST_LEFT 1
#define DETECT_LAST_RIGHT 2
#define DETECT_LAST_FRONT 3

//左前转向位置，等待更新

#define TURN_LEFT_FRONT 570
#define TURN_LEFT_FRONT_MORE 250

//右前转向，等待更新

#define TURN_RIGHT_FRONT 560
#define TURN_RIGHT_FRONT_MORE 250

//左前补角转向,用于物体逃脱后补偿转向，等待更新
// #define TURN_LEFT_SIDE_COMPLEMENTARY //旧
// #define TURN_LEFT_FRONT_COMPLEMENTARY 
// #define TURN_LEFT_FRONT_MORE_COMPLEMENTARY 

//右前补角转向，用于物体逃脱后补偿转向，等待更新
// #define TURN_RIGHT_SIDE_COMPLEMENTARY //旧
// #define TURN_RIGHT_FRONT_COMPLEMENTARY 
// #define TURN_RIGHT_FRONT_MORE_COMPLEMENTARY 

//补偿计时是否已经开始，实际上是在侧面检测到敌人后丢失后开始计时，以便继续追踪
#define COMPLEMENTARY_TIME_YES 1
#define COMPLEMENTARY_TIME_NO 0

//补偿计时多久后判定丢失目标
#define COMPLEMENTARY_TIME_DELAY 1000

//判断前方是否已经检测到物体
#define DETECT_IF_DETECTED_YES 1
#define DETECT_IF_DETECTED_NO 0

//可以开始进入警戒状态，在检测前方时，会伴随检测这个值，目的是为了避免前方传感器无用检测，节省时间
#define ENABLE_TO_TIMING 1
#define NOT_ENABLE_TO_TIMING 0

//180°旋转,需要更新
#define TURN_LEFT_180 1200

//180°旋转，需要更新
#define TURN_RIGHT_180 1200

//在台下为了改变位置移动时要用的速度
#define ON_STAGE_SPEED 15

//上台时上台电机的速度
#define FOR_GOING_TO_STAGE_SPEED 40

//前方测敌传感器的70cm数值
#define FRONT_RING_SENSOR_TRIGGER_VALUE 150

//转动补偿
#define FRONT_TURN_COMPLEMENTARY 370

//可以向前窜一下
#define CAN_GO_FRONT_TO_ENEMY 0

//不可以向前窜一下
#define CAN_NOT_GO_FRONT_TO_ENEMY 1

//定义在台上
#define STILL_ON_STAGE 1

//定义在台下
#define CLOSE_TO_EDGE 0

//定义防止被铲起时后侧探测器会检测到的值
#define PREVENT_REAR_BACK_VALUE 122333

/**
 * 变量值
 */
//初始化是否可以进入警戒状态，即是否需要监视前方传感器
int timing = NOT_ENABLE_TO_TIMING;

//初始化上一次物体位置变量
int last_detect_side = DETECT_LAST_FRONT;

//初始化是否已经开始计时变量
int complementary_time_judge = COMPLEMENTARY_TIME_NO;

//初始化计时时间
long complementary_time = 0;

//初始化旋转次数，为了让小车不会过度补偿旋转
int times_of_turns = 0;

//记录无敌人时，左侧边界的距离
int last_detect_left = 0;

//记录无敌人时，右侧边界的距离
int last_detect_right = 0;

//初始化前方是否检测到物体的变量，是为了在检测到物体后禁用前进和对齐动作
int detect_if_detected = DETECT_IF_DETECTED_NO;

//更新时的暂存变量，在更新距离中和判断台上台下时用，初始化这个是为了防止两次检测的值不同
int temp_analogRead_A1 = 0;
int temp_analogRead_A0 = 0;

//初始化是否需要向前方窜一下
int enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;

/**
 * 实例化对象和一些准备设置
 */
//新建一个模拟串口,S1=P11,S2=P10，如果要用新的板子可能会不同
//SoftwareSerial serial = SoftwareSerial(MOTOR_DRIVER_S2,MOTOR_DRIVER_S1);//


//利用刚才新建的串口和通信超时值来新建一个对象
RoboClaw roboclaw = RoboClaw(&Serial1,TIME_OUT);
RoboClaw roboclaw_stage = RoboClaw(&Serial3,TIME_OUT);
// RboClaw roboclaw_stage = RoboClaw(&,TIME_OUT);


//动作组以下-----------------------------------------------------------------------------------------------
//动作组以下-----------------------------------------------------------------------------------------------
//动作组以下-----------------------------------------------------------------------------------------------
//动作组以下-----------------------------------------------------------------------------------------------
//动作组以下-----------------------------------------------------------------------------------------------

//攻击函数
void attack(){
    
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1700, DECCEL1, 999999, ACCEL2, 1700, DECCEL2, 999999, 1);
    //gofront(GO_SPEED_ATTACK);
}

//停止
void stop(){
    roboclaw.ForwardM1(ADDRESS, 0);
    //roboclaw.ForwardM1(address,speed);
    roboclaw.ForwardM2(ADDRESS, 0);
}

//停止后保持不动
//void stop_stuck(){//旧
void stopStuck(){
    //for(;roboclaw.ReadEncM1(ADDRESS)>3 || roboclaw.ReadEncM2(ADDRESS)>3;){
        roboclaw.ResetEncoders(ADDRESS);
        //stop();
        roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 0, ACCEL2, 8000, DECCEL2, 0, 1);
    //}
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

//M1电机前进位置函数
//不建议使用，因为编码器的负值无法比较大小
void M1PositionForward(int position){
    //static int M1PositionTemp = 0;
    //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    roboclaw.SetEncM1(ADDRESS,0);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, position, 0);
    for(;;){
        if(roboclaw.ReadEncM1(ADDRESS)<(position+ERROR_POSITION)&&roboclaw.ReadEncM1(ADDRESS)>(position-ERROR_POSITION)){
            return;
        }
    }
}

//M1电机后退位置函数
//不建议使用，因为编码器的负值无法比较大小
void M1PositionBackward(int position){
    //roboclaw.SetEncM1(ADDRESS,0);
    
    roboclaw.SetEncM1(ADDRESS,0);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -position, 1);
    for(;;){
        if(roboclaw.ReadEncM1(ADDRESS)<(-position+ERROR_POSITION)&&roboclaw.ReadEncM1(ADDRESS)>(-position-ERROR_POSITION)){
            return;
        }
    }
}

//M2电机后退位置函数
//不建议使用，因为编码器的负值无法比较大小
void M2PositionBackward(int position){
    //static int M1PositionTemp = 0;
    //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    roboclaw.SetEncM2(ADDRESS,0);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -position, 0);
    for(;;){
        if(roboclaw.ReadEncM2(ADDRESS)<(-position+ERROR_POSITION)&&roboclaw.ReadEncM2(ADDRESS)>(-position-ERROR_POSITION)){
            return;
        }
    }
}

//M2电机前进位置函数
//不建议使用，因为编码器的负值无法比较大小
void M2PositionForward(int position){
    //roboclaw.SetEncM1(ADDRESS,0);
    
    roboclaw.SetEncM2(ADDRESS,0);
    //}
    //roboclaw.ReadEncM1(ADDRESS)
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, position, 1);
    for(;;){
        if(roboclaw.ReadEncM2(ADDRESS)<(position+ERROR_POSITION)&&roboclaw.ReadEncM2(ADDRESS)>(position-ERROR_POSITION)){
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
    // delay(150);
    if(single>450){
        delay(single/3);
    }else{
        delay(150);
    }
    stop();
    // for(;;){
    //     if(roboclaw.ReadEncM1(ADDRESS)>=single-ERROR_POSITION){
    //         stop();
    //         //stop_stuck();
    //         return;
    //     }
    // }
}

//减速版向右转
void turnRightPositionSlowly(int single){
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
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1000, DECCEL1, single, ACCEL2, 1000, DECCEL2, -single, 1);
    // for(;;){
    //     if(roboclaw.ReadEncM1(ADDRESS)>=single-ERROR_POSITION){
    //         stop();
    //         //stop_stuck();
    //         return;
    //     }
    // }
    
}

//向左转位置函数
void turnLeftPosition(int single){
    //static int M1PositionTemp = 0;
    //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    //roboclaw.SetEncM2(ADDRESS,0);
    roboclaw.ResetEncoders(ADDRESS);
    // roboclaw.SetEncM1(ADDRESS,0);
    // roboclaw.SetEncM2(ADDRESS,0);
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
    // for(;;){
    //     if(roboclaw.ReadEncM2(ADDRESS)>=single-ERROR_POSITION){
    //         delay(100);
    //         stop();
    //         return;
    //     }
    // }
    // Serial.println(roboclaw.ReadEncM2(ADDRESS));
    // do{
    //     //Serial.println(roboclaw.ReadEncM2(ADDRESS));
    // }while(roboclaw.ReadEncM2(ADDRESS)!=0);
    // stop();
    if(single>450){
        delay(single/3);
    }else{
        delay(150);
    }
    stop();
    // return;
}

//减速版向左转位置函数
void turnLeftPositionSlowly(int single){
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
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1000, DECCEL1, -single, ACCEL2, 1000, DECCEL2, single, 1);
    // for(;;){
    //     if(roboclaw.ReadEncM2(ADDRESS)>=single-ERROR_POSITION){
    //         stop();
    //         return;
    //     }
    // }
}

//判断前方5个传感器是否监测到敌人，这个函数更精确
int determineIfThereIsAnObjectInFrontOfTheSide(int which_one){
    int temp = 0;
    // int detect_value[7];
    for(int i=0;i<7;++i){
        // detect_value[i] = analogRead(which_one);
        if(analogRead(which_one)<FRONT_RING_SENSOR_TRIGGER_VALUE){
            temp = 1;
        }
    }
    if(temp==1){
        return DETECT_NO;
    }else{
        return DETECT_YES;
    }

}



//微小前进位置函数
//void goFrontPosition(){
void MoveALittleForward(){
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, GO_SLOW_POSITION, ACCEL2, 8000, DECCEL2, GO_SLOW_POSITION, 1);
    // for(;roboclaw.ReadEncM1(ADDRESS)<GO_SLOW_POSITION-ERROR_POSITION;){}
    delay(150);
}

/**
 * 对齐边界墙后向前走一段距离
 */
void goForwardAfterAlignedTheWall(){
    // goFrontPosition();
    // goFrontPosition();
    // goFrontPosition();
    roboclaw.ForwardM1(ADDRESS, 17);
    roboclaw.ForwardM2(ADDRESS, 17);
    delay(600);
    stop();
    delay(100);
    //turnLeftPosition(TURNLEFT90);
}

//检测边缘传感器的函数
int grayScaleSensorDetect(){
    int temp = 0;
    int storage_front_end_sensors1[7];
    int storage_front_end_sensors2[7];
    // int storage_front_end_sensors1_temp[7] = {1,1,1,1,1,1,1};
    // int storage_front_end_sensors2_temp[7] = {1,1,1,1,1,1,1};
    for(int i=0;i<7;++i){
    storage_front_end_sensors1[i] = digitalRead(GRAYSCALE_SENSOT_RIGHT);
    storage_front_end_sensors2[i] = digitalRead(GRAYSCALE_SENSOR_LEFT);
        if(storage_front_end_sensors1[i]==1 || storage_front_end_sensors2[i]==1){
            //return STILL_ON_STAGE;
            temp++;
        }
    }
    if(temp==7){
        return CLOSE_TO_EDGE;
    }else{
        return STILL_ON_STAGE;
    }
    
    
}

/**
 * 转向辅助函数，用于防止刀刃插到台子上
 */
void preventsTheBladeFromGettingStuckUnderTable(){//
    // roboclaw.ForwardM1(ADDRESS, 30);
    // roboclaw.ForwardM2(ADDRESS, 10);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 400, ACCEL2, 8000, DECCEL2, -400, 1);
    delay(200);
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, 800, ACCEL2, 2000, DECCEL2, 0, 1);
    delay(300);
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 5000, DECCEL1, 0, ACCEL2, 5000, DECCEL2, 800, 1);
    delay(200);
    //stop();
}

/**
 * 后退函数，为了后退抵在边界墙上对齐用
 */
void BackToTouchTheWall(){
    roboclaw.BackwardM1(ADDRESS,20);
    roboclaw.BackwardM2(ADDRESS,20);
    delay(1500);
    stop();
}

/**
 * 台下动作，此时已经判断摔下台了
 */
void DecidedTheCarHadFallenOff(){
    //pinMode(13,OUTPUT);
    //digitalWrite(13,HIGH);//
    // goFrontPosition();
    // goFrontPosition();
    // goFrontPosition();
    // goFrontPosition();
    //转向，使车轮转向边界
    while(analogRead(DETECTOR_BACK_LEFT)-analogRead(DETECTOR_BACK_RIGHT)>20 || analogRead(DETECTOR_BACK_LEFT)+analogRead(DETECTOR_BACK_RIGHT)>550){
        turnLeftPosition(3*TURN_SLOW_POSITION);
        //防止刀刃卡住
        if(analogRead(DETECTOR_LEFT)<180){
            // turnLeftPosition(4*TURN_SLOW_POSITION);
            // goFrontPosition();
            preventsTheBladeFromGettingStuckUnderTable();
        }
    }
    // while(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>2 && analogRead(DETECTOR_BACK_A2)>analogRead(DETECTOR_BACK_A3)){
    //     turnLeftPosition(TURN_SLOW_POSITION);
    // }
    //goBack(GO_BAKC_SPEED)
    //后退，用边界来对正
    BackToTouchTheWall();
    
    //对正后前进一段
    goForwardAfterAlignedTheWall();
    //改变上台的位置
    changeThePositionGoingToStage();
    stepBackAndGetOnStage();
    //delay(1500);
    //stop();
    // while(1){
    //    baseline(); 
    // }
    //
    delay(10000);
}

/**
 * 上台函数
 */
void stepBackAndGetOnStage(){
    //接用此函数
    BackToTouchTheWall();
    delay(1000);
    //startTheOnStageMotor();//122333等待卡槽
}

/**
 * 启动上台电机，开始上台
 */
void startTheOnStageMotor(){
    // roboclaw_stage.BackwardM1(ADDRESS,FOR_GOING_TO_STAGE_SPEED);
    // roboclaw_stage.ForwardM2(ADDRESS,FOR_GOING_TO_STAGE_SPEED);
    // delay(1450);
    // roboclaw_stage.BackwardM1(ADDRESS,0);
    // roboclaw_stage.BackwardM2(ADDRESS,0);
    roboclaw_stage.BackwardM1(ADDRESS,FOR_GOING_TO_STAGE_SPEED);
    roboclaw_stage.ForwardM2(ADDRESS,FOR_GOING_TO_STAGE_SPEED);
    delay(1580);
    roboclaw_stage.BackwardM1(ADDRESS,0);
    delay(45);
    roboclaw_stage.BackwardM2(ADDRESS,0);
    if(analogRead(DETECTOR_LEFT)<600){
        turnRightPosition(TURN_RIGHT_180);
    }else{
        turnLeftPosition(TURN_LEFT_180);
    }
}

/**
 * 判断在台上还是在台下
 */
void judgeWhetherOnStageOrUnderTheStage(){
    if(temp_analogRead_A0+temp_analogRead_A1<580 || analogRead(DETECTOR_BACK_LEFT)<330){//
        delay(1000);
        if(temp_analogRead_A0+temp_analogRead_A1<580 || analogRead(DETECTOR_BACK_LEFT)<330){
            DecidedTheCarHadFallenOff();
        }
    }
}

/**
 * 为了改变上台位置，向前走
 */
void forChangeThePositionToMoveAlongWall(){
    //inOrderToGoAlongStraightFirstSteeralignment();
    //if(analogRead(DETECTOR_BACK_LEFT)>)
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, 2800, ACCEL2, 2000, DECCEL2, 2800, 1);

    // //int last_deistance_from_wall;
    // if(which_side==0){
    //     int time_go_along_with_wall = millis();
    //     do{
    //     //last_deistance_from_wall = analogRead(DETECTOR_LEFT_A0);
        
    //     //delay(200);
    //         if(analogRead(DETECTOR_LEFT)>238){
    //             roboclaw.ForwardM1(ADDRESS, speed);
    //             roboclaw.ForwardM2(ADDRESS, speed+13);
    //         }else if(analogRead(DETECTOR_LEFT)<200){
    //             roboclaw.ForwardM1(ADDRESS, speed+10);
    //             roboclaw.ForwardM2(ADDRESS, speed);
    //         }else{
    //             roboclaw.ForwardM1(ADDRESS, speed);
    //             roboclaw.ForwardM2(ADDRESS, speed);
    //         }
    //     //delay(200);
    //     }while(millis()-time_go_along_with_wall<2800);
    // }else{
    //         int time_go_along_with_wall = millis();
    //     do{
    //         //last_deistance_from_wall = analogRead(DETECTOR_LEFT_A0);
            
    //         //delay(200);
    //         if(analogRead(DETECTOR_RIGHT)>238){
    //             roboclaw.ForwardM1(ADDRESS, speed+13);
    //             roboclaw.ForwardM2(ADDRESS, speed);
    //         }else if(analogRead(DETECTOR_RIGHT)<200){
    //             roboclaw.ForwardM1(ADDRESS, speed);
    //             roboclaw.ForwardM2(ADDRESS, speed+13);
    //         }else{
    //             roboclaw.ForwardM1(ADDRESS, speed);
    //             roboclaw.ForwardM2(ADDRESS, speed);
    //         }
    //         //delay(200);
    //     }while(millis()-time_go_along_with_wall<2800);
    // }

    // roboclaw.ResetEncoders(ADDRESS);
    
}

/**
 * 对齐后改变上台位置
 */
void changeThePositionGoingToStage(){
    if(analogRead(DETECTOR_LEFT)<600){
        //turnRightPosition(TURN_RIGHT_POSITION_90);
        turnRightPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
        delay(800);
        forChangeThePositionToMoveAlongWall();
        delay(2500);
        //delay(2000);
        turnRightPosition(TURN_RIGHT_POSITION_90);
    }else{
        // turnLeftPosition(TURN_LEFT_POSITION_90);
        turnLeftPositionSlowly(TURN_LEFT_POSITION_90_SLOWLY);
        delay(800);
        forChangeThePositionToMoveAlongWall();
        delay(2500);
        //delay(2000);
        turnLeftPosition(TURN_LEFT_POSITION_90);
    }
}

//void detectEnemy(){//旧
/**
 * 判断侧边是否能检测到敌人
 * 会先判断侧边距离数据是否发生大的变化，若发生，则向那个方向转向
 * 之后会更新两侧的距离常数（不是一直的常数）
 */
void detectTheTwoSidesOfTheRightSideForEnemies(){
    //if()
    //last_detect_sum = analogRead(DETECTOR_LEFT_A0)+analogRead(DETECTOR_RIGHT_A1);
    // Serial.print("A0 cha:");
    // Serial.print(last_detect_left-analogRead(DETECTOR_LEFT_A0));
    // Serial.print(".....A1 cha:");
    // Serial.println(last_detect_right-analogRead(DETECTOR_RIGHT_A1));
    judgeWhetherOnStageOrUnderTheStage();
    if(last_detect_left-analogRead(DETECTOR_LEFT)>=MIN_DETECT_TO_90_ENEMY_JUDGE && analogRead(DETECTOR_LEFT)+analogRead(DETECTOR_RIGHT)<1100){
        turnLeftPosition(TURN_LEFT_POSITION_90);
        uploadDetect();
        //alignment_only_once = 0;
    }else if(last_detect_right-analogRead(DETECTOR_RIGHT)>=MIN_DETECT_TO_90_ENEMY_JUDGE && analogRead(DETECTOR_LEFT)+analogRead(DETECTOR_RIGHT)<1100){
        turnRightPosition(TURN_RIGHT_POSITION_90);
        uploadDetect();
        //alignment_only_once = 0;
    }
}

/**
 * 对齐函数，在每一次对齐后都会判断小车位置
 */
//void alignmentMoreStringent(){//旧
void alignWithWalls(){
    int last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
    int last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
    if(last_detect_back_left+last_detect_back_right>=1700){
        turnLeftPosition(2*TURN_SLOW_POSITION);
    }else if(last_detect_back_left-last_detect_back_right>OFFSET_THRESHOLD_ADJUST_SLOW){
        turnLeftPosition(TURN_SLOW_POSITION);
    }else if(last_detect_back_right-last_detect_back_left>OFFSET_THRESHOLD_ADJUST_SLOW){
        turnRightPosition(TURN_SLOW_POSITION);
    }else{
        uploadDetect();
        MoveALittleForward();
    }
    // judgeWhetherOnStageOrUnderTheStage();
}

/**
 * 另一种形式的对齐函数，原理和原对齐函数一致，但是需要经过7次取值，用平均值来计算
 */
void alignWithWallsUsingAverge(){
    int last_detect_alignment[7][2];
    for(int i=0;i<7;++i){
        last_detect_alignment[i][0] = analogRead(DETECTOR_BACK_LEFT);
    }
    for(int i=0;i<7;++i){
        last_detect_alignment[i][1] = analogRead(DETECTOR_BACK_RIGHT);
    }
    int last_detect_alignment_averge[2];
    last_detect_alignment_averge[0] = (last_detect_alignment[0][0]+last_detect_alignment[1][0]+last_detect_alignment[2][0]+last_detect_alignment[3][0]+last_detect_alignment[4][0]+last_detect_alignment[5][0]+last_detect_alignment[6][0])/7;
    last_detect_alignment_averge[1] = (last_detect_alignment[0][1]+last_detect_alignment[1][1]+last_detect_alignment[2][1]+last_detect_alignment[3][1]+last_detect_alignment[4][1]+last_detect_alignment[5][1]+last_detect_alignment[6][1])/7;
    if(last_detect_alignment_averge[0]+last_detect_alignment_averge[1]>=1700){
        turnLeftPosition(2*TURN_SLOW_POSITION);
    }else if(last_detect_alignment_averge[0]-last_detect_alignment_averge[1]>OFFSET_THRESHOLD_ADJUST_SLOW){
        turnLeftPosition(TURN_SLOW_POSITION);
    }else if(last_detect_alignment_averge[1]-last_detect_alignment_averge[0]>OFFSET_THRESHOLD_ADJUST_SLOW){
        turnRightPosition(TURN_SLOW_POSITION);
    }else{
        uploadDetect();
        MoveALittleForward();
    }
    judgeWhetherOnStageOrUnderTheStage();
}

//距离更新函数，会忽略传感器返回的无信号值
void uploadDetect(){
    //delay(100); temp_analogRead_A1-last_detect_right<ABNORMAL_INCREASE && temp_analogRead_A0-last_detect_left<ABNORMAL_INCREASE
    temp_analogRead_A1 = analogRead(DETECTOR_RIGHT);
    temp_analogRead_A0 = analogRead(DETECTOR_LEFT);
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


//后退函数，将敌人推下去后返回防守位置
//void goBack(){//旧
void AftertheEnemyDownAndReturnToTheSideOfTheField(){
    // if(analogRead(DETECTOR_LEFT)<){
    //     turnLeftPosition(4*TURN_SLOW_POSITION);
    // }else if(analogRead(DETECTOR_RIGHT)<){
    //     turnRightPosition(4*TURN_SLOW_POSITION);
    // }
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
        roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2500, DECCEL1, -5570, ACCEL2, 2500, DECCEL2, -5570, 1);
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
//void detectEnemySide(){//旧
void SideFrontToDetectIfThereAreEnemies(){
    determineIfItIsUnderTheStage();
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_YES){
        if(enemy_on_front_go_front_only_once==CAN_GO_FRONT_TO_ENEMY){
            enemy_on_front_go_front_only_once = CAN_NOT_GO_FRONT_TO_ENEMY;
            roboclaw.ResetEncoders(ADDRESS);
            roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 4*GO_SLOW_POSITION, ACCEL2, 8000, DECCEL2, 4*GO_SLOW_POSITION, 1);
            // for(;roboclaw.ReadEncM1(ADDRESS)<GO_SLOW_POSITION-ERROR_POSITION;){}
            delay(150);
        }
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        PrepareforAttack();
        //return;
    }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_YES){
        turnLeftPosition(TURN_LEFT_FRONT);
        delay(300);
        last_detect_side = DETECT_LAST_LEFT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        times_of_turns++;
        enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
        //delay(100);
        //detectEnemyFrontAlert();
    }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_YES){
        turnRightPosition(TURN_RIGHT_FRONT);
        delay(300);
        last_detect_side = DETECT_LAST_RIGHT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        times_of_turns++;
        enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
        //delay(100);
        //detectEnemyFrontAlert();
    }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT_MORE)==DETECT_YES){
        turnLeftPosition(TURN_LEFT_FRONT_MORE);
        last_detect_side = DETECT_LAST_LEFT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        times_of_turns++;
        enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
    }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT_MORE)==DETECT_YES){
        turnRightPosition(TURN_RIGHT_FRONT_MORE);
        last_detect_side = DETECT_LAST_RIGHT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        times_of_turns++;
        enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
    }
    // return;
}


//后退至远处的边线附近
//void BackToTheDefensivePosition(){//旧
void detectsWhetherTheEdgeIsReachedWhenPushingEnemy(){
    // for(goBackOneStep();;){
    //     if(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>OFFSET_THRESHOLD_ADJUST_SLOW){
    // //         turnLeftPosition(TURN_SLOW_POSITION);
    //     }else if(analogRead(DETECTOR_BACK_A3)-analogRead(DETECTOR_BACK_A2)-5>OFFSET_THRESHOLD_ADJUST_SLOW){
    // //         turnRightPosition(TURN_SLOW_POSITION);
    // //     }else{
    // //         return;
    // //     //     goBackTwoStep();
    // //     //     return;
    // //     // //delay(1000);
    // //     // //stop();
    // //     //     //delay(10000);
    // //     }
    // }        //delay(1000);
    do{
        if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_YES){
            roboclaw.ResetEncoders(ADDRESS);
            roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
            roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+11, 1);
            delay(150);
            //stop();
        }else if(digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_YES){
            roboclaw.ResetEncoders(ADDRESS);
            roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
            roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+11, 1);
            delay(150);
            //stop();
        }else if(digitalRead(GRAYSCALE_SENSOT_RIGHT)+digitalRead(GRAYSCALE_SENSOR_LEFT)==2){
            roboclaw.ResetEncoders(ADDRESS);
            roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION, 1);
            roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION, 1);
            delay(150);
        }
        if(digitalRead(GRAYSCALE_SENSOT_RIGHT)+digitalRead(GRAYSCALE_SENSOR_LEFT)==0){
            // alignWithWalls()

            // if(analogRead(DETECTOR_BACK_LEFT)-analogRead(DETECTOR_BACK_RIGHT)>OFFSET_THRESHOLD_ADJUST_SLOW){
            //     turnLeftPosition(TURN_SLOW_POSITION);
            // }else if(analogRead(DETECTOR_BACK_RIGHT)-analogRead(DETECTOR_BACK_LEFT)>OFFSET_THRESHOLD_ADJUST_SLOW){
            //     turnRightPosition(TURN_SLOW_POSITION);
            // }else{
            for(int i=0;i<7;){
                int last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
                int last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
                if(last_detect_back_left-last_detect_back_right>OFFSET_THRESHOLD_ADJUST_SLOW-4){
                    turnLeftPosition(TURN_SLOW_POSITION);
                }else if(last_detect_back_right-last_detect_back_left>OFFSET_THRESHOLD_ADJUST_SLOW-4){
                    turnRightPosition(TURN_SLOW_POSITION);
                }else{
                    ++i;
                }
            }
            AftertheEnemyDownAndReturnToTheSideOfTheField();
            //stop();
            return;
        }
        //if(digitalRead(GRAYSCALE_SENSOR_PIN2)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_PIN1)==DETECT_NO)
    }while(1);
    //stop();
    //delay(10000)
    //goBackOneStep();
}


//前探测器探测函数
void detectEnemyFront(){
    // if(digitalRead(DETECTOR_FRONT)==DETECT_YES){
    //     do{
    //         stop();
    //     } while (digitalRead(DETECTOR_FRONT)==DETECT_YES);
    //     //for(;;){
    // }
    // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_YES){
    //     //stop();
    //     // gofront(GO_SLOW_POSITION);
    //     if(enemy_on_front_go_front_only_once==CAN_GO_FRONT_TO_ENEMY){
    //         enemy_on_front_go_front_only_once = CAN_NOT_GO_FRONT_TO_ENEMY;
    //         roboclaw.ResetEncoders(ADDRESS);
    //         roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 4*GO_SLOW_POSITION, ACCEL2, 8000, DECCEL2, 4*GO_SLOW_POSITION, 1);
    //         // for(;roboclaw.ReadEncM1(ADDRESS)<GO_SLOW_POSITION-ERROR_POSITION;){}
    //         delay(150);
    //     }
    //     PrepareforAttack();
    //}else 
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_NO && timing==ENABLE_TO_TIMING){
        if(complementary_time_judge==COMPLEMENTARY_TIME_NO){
            complementary_time = millis();
            complementary_time_judge = COMPLEMENTARY_TIME_YES;
        }
        if(millis()-complementary_time>COMPLEMENTARY_TIME_DELAY){
            complementary_time_judge = COMPLEMENTARY_TIME_NO;
            detect_if_detected = DETECT_IF_DETECTED_NO;
            timing = NOT_ENABLE_TO_TIMING;
            enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
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
                    turnLeftPosition(FRONT_TURN_COMPLEMENTARY);
                    last_detect_side = DETECT_LAST_FRONT;
                    uploadDetect();
                    times_of_turns = 0;
                    return;
                    //break;
                case DETECT_LAST_RIGHT:
                    turnRightPosition(FRONT_TURN_COMPLEMENTARY);
                    last_detect_side = DETECT_LAST_FRONT;
                    uploadDetect();
                    times_of_turns = 0;
                    return;
                    //break;
                }
                //times_of_turns = 0;
            }
        }
    }    //}
}

//准备攻击()
void PrepareforAttack(){
    //两者平时大概在-500到+500左右，受到推力后大概在2000+
    // int16_t pwm1;
    // int16_t pwm2;
    // gofront(GO_SPEED_ATTACK-5);
    // MoveALittleForward();
    // roboclaw.ResetEncoders(ADDRESS);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 3*GO_SLOW_POSITION, ACCEL2, 8000, DECCEL2, 3*GO_SLOW_POSITION, 1);
    // // for(;roboclaw.ReadEncM1(ADDRESS)<GO_SLOW_POSITION-ERROR_POSITION;){}
    // delay(150);
    // stopStuck();
    // roboclaw.ReadPWMs(ADDRESS,pwm1,pwm2);
    if(analogRead(DETECTOR_FRONT)>=470){
        // //do{
        // int storage_front_end_sensors1[7];
        // int storage_front_end_sensors2[7];
        // // int storage_front_end_sensors_temp[7][2] = 
        // // {
        // //     {1,1},
        // //     {1,1},
        // //     {1,1},
        // //     {1,1},
        // //     {1,1},
        // //     {1,1},
        // //     {1,1}
        // // };
        // int storage_front_end_sensors1_temp[7] = {1,1,1,1,1,1,1};
        // int storage_front_end_sensors2_temp[7] = {1,1,1,1,1,1,1};
        // if(grayScaleSensorDetect()==STILL_ON_STAGE){


        // do{
        roboclaw.ResetEncoders(ADDRESS);
        while(1){//122333
            if(analogRead(DETECTOR_LEFT_FRONT_MORE)-analogRead(DETECTOR_RIGHT_FRONT_MORE)>180){
                // goleft(GO_SPEED_ATTACK,7);
                roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1700, DECCEL1, 999999, ACCEL2, 2000, DECCEL2, 999999, 1);
            }else if(analogRead(DETECTOR_RIGHT_FRONT_MORE)-analogRead(DETECTOR_LEFT_FRONT_MORE)>180){
                roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, 999999, ACCEL2, 1700, DECCEL2, 999999, 1);
                // goright(GO_SPEED_ATTACK,7);
            }else{
                attack();
            }
            //122333
            
            if(grayScaleSensorDetect()==CLOSE_TO_EDGE){
                if(analogRead(DETECTOR_BACK_LEFT)<PREVENT_REAR_BACK_VALUE || analogRead(DETECTOR_BACK_RIGHT)<PREVENT_REAR_BACK_VALUE){
                    preventRearBackMove();
                    continue;
                }
                break;
            }
        }
        // }while(grayScaleSensorDetect()==STILL_ON_STAGE);


        // }
        // do{//
        //     attack();
        //     for(int i=0;i<7;++i){
        //     storage_front_end_sensors1[i] = digitalRead(GRAYSCALE_SENSOT_RIGHT);
        //     storage_front_end_sensors2[i] = digitalRead(GRAYSCALE_SENSOR_LEFT);
        //     }
        // }while(storage_front_end_sensors1!=storage_front_end_sensors1_temp && storage_front_end_sensors2!=storage_front_end_sensors2_temp);//
        enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
        stopStuck();
        detectsWhetherTheEdgeIsReachedWhenPushingEnemy();  
        //delay(4000);
        //stop();
        //}while(1);
        
    }
}

//被铲起后后退保护程序
void preventRearBackMove(){
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, -900, ACCEL2, 8000, DECCEL2, -900, 1);
    delay(300);
}
//动作组以上--------------------------------------------------------------------------------------------------
//动作组以上--------------------------------------------------------------------------------------------------
//动作组以上--------------------------------------------------------------------------------------------------
//动作组以上--------------------------------------------------------------------------------------------------
void test(){
    int last_detect_temp1[7];
    int last_detect_temp2[7];
    int last_detect_temp_averge1;
    int last_detect_temp_averge2;
    last_detect_temp1[0] = analogRead(DETECTOR_BACK_LEFT)+3;
    last_detect_temp2[0] = analogRead(DETECTOR_BACK_RIGHT);
    last_detect_temp1[1] = analogRead(DETECTOR_BACK_LEFT)+3;
    last_detect_temp2[1] = analogRead(DETECTOR_BACK_RIGHT);
    last_detect_temp1[2] = analogRead(DETECTOR_BACK_LEFT)+3;
    last_detect_temp2[2] = analogRead(DETECTOR_BACK_RIGHT);
    last_detect_temp1[3] = analogRead(DETECTOR_BACK_LEFT)+3;
    last_detect_temp2[3] = analogRead(DETECTOR_BACK_RIGHT);
    last_detect_temp1[4] = analogRead(DETECTOR_BACK_LEFT)+3;
    last_detect_temp2[4] = analogRead(DETECTOR_BACK_RIGHT);
    last_detect_temp1[5] = analogRead(DETECTOR_BACK_LEFT)+3;
    last_detect_temp2[5] = analogRead(DETECTOR_BACK_RIGHT);
    last_detect_temp1[6] = analogRead(DETECTOR_BACK_LEFT)+3;
    last_detect_temp2[6] = analogRead(DETECTOR_BACK_RIGHT);
    last_detect_temp_averge1 = (last_detect_temp1[1]+last_detect_temp1[2]+last_detect_temp1[0]+last_detect_temp1[3]+last_detect_temp1[4]+last_detect_temp1[5]+last_detect_temp1[6])/7;
    last_detect_temp_averge2 = (last_detect_temp2[1]+last_detect_temp2[2]+last_detect_temp2[0]+last_detect_temp2[3]+last_detect_temp2[4]+last_detect_temp2[5]+last_detect_temp2[6])/7;
    Serial.print(last_detect_temp_averge1);
    Serial.print("    ");
    Serial.print(last_detect_temp_averge2);
    Serial.print("    ");
    Serial.println(last_detect_temp_averge1-last_detect_temp_averge2);
    delay(1000);
    // Serial.print(analogRead(DETECTOR_BACK_LEFT));
    // Serial.print("    ");
    // Serial.print(analogRead(DETECTOR_BACK_RIGHT));
    // Serial.print("    ");
    // Serial.println(analogRead(DETECTOR_BACK_LEFT)-analogRead(DETECTOR_BACK_RIGHT));
    // delay(1000);
}


void test2(){
    // Serial.print(analogRead(DETECTOR_BACK_LEFT));
    // Serial.print("      ");
    // Serial.println(analogRead(DETECTOR_BACK_RIGHT));
    // Serial.print("      ");
    // // Serial.println(analogRead(DETECTOR_LEFT)+analogRead(DETECTOR_RIGHT));
    Serial.print(analogRead(DETECTOR_LEFT_FRONT));
    Serial.print("      ");
    Serial.print(analogRead(DETECTOR_LEFT_FRONT_MORE));
    Serial.print("      ");
    Serial.print(analogRead(DETECTOR_FRONT));
    Serial.print("      ");
    Serial.print(analogRead(DETECTOR_RIGHT_FRONT_MORE));
    Serial.print("      ");
    Serial.println(analogRead(DETECTOR_RIGHT_FRONT));
    // Serial.print("      ");
    delay(1000);
    
}

//搜索敌人总函数
void searchForEnemy(){
    if(detect_if_detected==DETECT_IF_DETECTED_NO){
        detectTheTwoSidesOfTheRightSideForEnemies();//down
    // //alignmentOnlyOnce();//down
        alignWithWalls();
    }
    SideFrontToDetectIfThereAreEnemies();
    detectEnemyFront();
    //uploadDetect();
    //goFrontPosition();//down
}

void determineIfItIsUnderTheStage(){
    int temp_times = 0;
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_YES){
        temp_times++;
    }
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_YES){
        temp_times++;
    }
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT_MORE)==DETECT_YES){
        temp_times++;
    }
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_YES){
        temp_times++;
    }
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT_MORE)==DETECT_YES){
        temp_times++;
    }
    if(temp_times>=3){
        DecidedTheCarHadFallenOff();
    }
    // Serial.println(temp_times);
    // delay(1000);
}

//原始函数：
void setup(){
    //定义模拟串口
    roboclaw.begin(38400);
    roboclaw_stage.begin(19200);
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
    // stopStuck();
    
}


void loop(){
    // changeThePositionGoingToStage();
    // determineIfItIsUnderTheStage();
    // turnLeftPosition(TURN_LEFT_POSITION_90);
    // delay(20000);
    // attack();
    // delay(2000);
    // stop();
    // delay(200000);
    searchForEnemy();
    // detectTheTwoSidesOfTheRightSideForEnemies();//down
    // // //alignmentOnlyOnce();//down
    // alignWithWalls();
    // SideFrontToDetectIfThereAreEnemies();
    // detectEnemyFront();
    // alignWithWalls();
    // detectsWhetherTheEdgeIsReachedWhenPushingEnemy();
    // delay(20000);
    // Serial.println(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT));
    // SideFrontToDetectIfThereAreEnemies();
    // if(millis()>50000){
    //     do{
    //         stop();
    //     }while(1);
    // }
    // turnLeftPosition(TURN_LEFT_POSITION_90);
    // delay(20000);
    // turnLeftPositionSlowly(TURN_LEFT_POSITION_90_SLOWLY);
    // changeThePositionGoingToStage();
    // delay(20000);
    // detectEnemyFront();
    // if(detect_if_detected==DETECT_IF_DETECTED_NO){
    //     detectTheTwoSidesOfTheRightSideForEnemies();//down
    // // //alignmentOnlyOnce();//down
    //     alignWithWalls();
    // }
    // Serial.println(grayScaleSensorDetect());
    // Serial.print("left:");
    //     Serial.print(analogRead(DETECTOR_LEFT_FRONT_MORE));
    //     Serial.print("....right:");
    //     Serial.println(analogRead(DETECTOR_RIGHT_FRONT_MORE));
    //     // Serial.print("....A2-A3:");
    //     // Serial.println(analogRead(DETECTOR_LEFT)+analogRead(DETECTOR_RIGHT));
    //     delay(1000);
    // alignWithWalls();
    // turnLeftPosition(TURN_SLOW_POSITION);
    // searchForEnemy();
    // SideFrontToDetectIfThereAreEnemies();
    // turnLeftPosition(TURN_LEFT_FRONT_MORE);
    // delay(1000);
    // turnRightPosition(TURN_RIGHT_FRONT_MORE);
    // delay(10000);
    // delay(1000);
    // detectEnemyFront();
    // test2();
    // PrepareforAttack();
    //  int storage_front_end_sensors1[7];
    //     int storage_front_end_sensors2[7];
    //     // int storage_front_end_sensors_temp[7][2] = 
    //     // {
    //     //     {1,1},
    //     //     {1,1},
    //     //     {1,1},
    //     //     {1,1},
    //     //     {1,1},
    //     //     {1,1},
    //     //     {1,1}
    //     // };
    //     int storage_front_end_sensors1_temp[7] = {1,1,1,1,1,1,1};
    //     int storage_front_end_sensors2_temp[7] = {1,1,1,1,1,1,1};
    //     do{//
    //         //attack();
    //         for(int i=0;i<7;++i){
    //         storage_front_end_sensors1[i] = digitalRead(GRAYSCALE_SENSOT_RIGHT);
    //         storage_front_end_sensors2[i] = digitalRead(GRAYSCALE_SENSOR_LEFT);
    //         }
    //         for(int i=0;i<7;++i){
    //             Serial.print(storage_front_end_sensors1[i]);
    //             Serial.print("    ");
    //             Serial.print(storage_front_end_sensors2[i]);
    //             Serial.print("......");
    //             Serial.print(storage_front_end_sensors1_temp[i]);
    //             Serial.print("    ");
    //             Serial.println(storage_front_end_sensors2_temp[i]);
    //         }
    //         delay(4000);
    //     }while(storage_front_end_sensors1!=storage_front_end_sensors1_temp && storage_front_end_sensors2!=storage_front_end_sensors2_temp);//
    //     Serial.println("ohhhhhhhh");
    //     delay(1000);
    // Serial.println(grayScaleSensorDetect());
    // delay(2000);
    // test2();
    // SideFrontToDetectIfThereAreEnemies();
    // detectEnemyFront();
    // test2();
    // SideFrontToDetectIfThereAreEnemies();
    // Serial.println(analogRead(DETECTOR_RIGHT_FRONT));
    // delay(1000);
    // Serial.println(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT_MORE));
    // delay(1000);
    // turnLeftPosition(TURN_LEFT_FRONT+100);
    // delay(4000);
    // turnLeftPosition(TURN_LEFT_FRONT+150);
    // delay(4000);
    // turnLeftPosition(TURN_LEFT_FRONT+200);
    // delay(10000);
    // turnRightPosition(TURN_RIGHT_FRONT+100);
    // delay(4000);
    // turnRightPosition(TURN_RIGHT_FRONT+150);
    // delay(4000);
    // turnRightPosition(TURN_RIGHT_FRONT+200);
    // delay(20000);
    
}
