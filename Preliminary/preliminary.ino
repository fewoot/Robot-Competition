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
 * 
 * 2019年8月23日：今天回来了，车已经做好80%了，但是有一点超重，明天可以再改进一下，传感器，电机已经检查完毕-
 * 可以读取编码值。还没有进行推力实验，今天早点回去吧
 * 
 * 2019年8月30日：车子已经全部完成了，所有动作都成功，但是还是有传感器的跳值问题，急需解决，经过实际测试，-
 * 因为有些探测条件是共用的，所以有重叠，继续改进
 * 
 * 2019年9月1日：明天就要开学了，还有20多天报名就截止了，时间很紧，今天把台下的动作都做得差不多了，-
 * 以后就是修改一些小bug，今天就到这吧，回家！
 * 
 * 2019年9月8日：现在大体上都已经完成，但是现在推敌人时会出现突然的突刺，然后掉下去，原因不明，明天再看吧
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

// /**
//  * 另一种形式的对齐函数，原理和原对齐函数一致，但是需要经过7次取值，用平均值来计算
//  */
// void alignWithWallsUsingAverge(){
//     int last_detect_alignment[7][2];
//     for(int i=0;i<7;++i){
//         last_detect_alignment[i][0] = analogRead(DETECTOR_BACK_LEFT);
//     }
//     for(int i=0;i<7;++i){
//         last_detect_alignment[i][1] = analogRead(DETECTOR_BACK_RIGHT);
//     }
//     int last_detect_alignment_averge[2];
//     last_detect_alignment_averge[0] = (last_detect_alignment[0][0]+last_detect_alignment[1][0]+last_detect_alignment[2][0]+last_detect_alignment[3][0]+last_detect_alignment[4][0]+last_detect_alignment[5][0]+last_detect_alignment[6][0])/7;
//     last_detect_alignment_averge[1] = (last_detect_alignment[0][1]+last_detect_alignment[1][1]+last_detect_alignment[2][1]+last_detect_alignment[3][1]+last_detect_alignment[4][1]+last_detect_alignment[5][1]+last_detect_alignment[6][1])/7;
//     if(last_detect_alignment_averge[0]+last_detect_alignment_averge[1]>=1700){
//         turnLeftPosition(2*TURN_SLOW_POSITION);
//     }else if(last_detect_alignment_averge[0]-last_detect_alignment_averge[1]>OFFSET_THRESHOLD_ADJUST_SLOW){
//         turnLeftPosition(TURN_SLOW_POSITION);
//     }else if(last_detect_alignment_averge[1]-last_detect_alignment_averge[0]>OFFSET_THRESHOLD_ADJUST_SLOW){
//         turnRightPosition(TURN_SLOW_POSITION);
//     }else{
//         uploadDetect();
//         moveALittleForward();
//     }
//     judgeWhetherOnStageOrUnderTheStage();
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
//左前补角转向,用于物体逃脱后补偿转向，等待更新
// #define TURN_LEFT_SIDE_COMPLEMENTARY //旧
// #define TURN_LEFT_FRONT_COMPLEMENTARY 
// #define TURN_LEFT_FRONT_MORE_COMPLEMENTARY 
//右前补角转向，用于物体逃脱后补偿转向，等待更新
// #define TURN_RIGHT_SIDE_COMPLEMENTARY //旧
// #define TURN_RIGHT_FRONT_COMPLEMENTARY 
// #define TURN_RIGHT_FRONT_MORE_COMPLEMENTARY 
//#define GRAYSCALE_SENSOR_PIN1 //旧


// void dynamicBack(){
//     int speed_back_to_field = 15;
//     for(;;){
            
//         long last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
//         long last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
//         // for(int i=0;i<9;++i){
//         //     last_detect_back_left += analogRead(DETECTOR_BACK_LEFT);
//         //     last_detect_back_right += analogRead(DETECTOR_BACK_RIGHT);
//         // }
//         // last_detect_back_left = last_detect_back_left/10;
//         // last_detect_back_right = last_detect_back_right/10;
//         if(last_detect_back_left>800 && last_detect_back_right>800){
//             // roboclaw.ForwardM1(ADDRESS, speed);
//             roboclaw.BackwardM1(ADDRESS,30);
//             // roboclaw.ForwardM2(ADDRESS, speed);
//             roboclaw.BackwardM2(ADDRESS,35);
//             continue;
//         }else if(last_detect_back_left>470 && last_detect_back_right>470){
//             speed_back_to_field = 25;
//         }else if(last_detect_back_left<470 || last_detect_back_right<470){
//             // roboclaw.ForwardM1(ADDRESS, speed);
//             // roboclaw.BackwardM1(ADDRESS,15);
//             // roboclaw.ForwardM2(ADDRESS, speed);
//             // roboclaw.BackwardM2(ADDRESS,15);
//             speed_back_to_field = 15;
//         }

//         if(last_detect_back_left<417 && last_detect_back_right<417){
//             // // roboclaw.ForwardM1(ADDRESS, speed);
//             // roboclaw.BackwardM1(ADDRESS,15);
//             // // roboclaw.ForwardM2(ADDRESS, speed);
//             // roboclaw.BackwardM2(ADDRESS,15);
//             stop();
//             uploadDetect();
//             // delay(30000);
//             return;
//         }
        
//         if(last_detect_back_left-last_detect_back_right>20){
//             // roboclaw.ForwardM1(ADDRESS, speed);
//             roboclaw.BackwardM1(ADDRESS,speed_back_to_field+10);
//             // roboclaw.ForwardM2(ADDRESS, speed);
//             roboclaw.BackwardM2(ADDRESS,speed_back_to_field);
//         }else if(last_detect_back_right-last_detect_back_left>20){
//             // roboclaw.ForwardM1(ADDRESS, speed);
//             roboclaw.BackwardM1(ADDRESS,speed_back_to_field);
//             // roboclaw.ForwardM2(ADDRESS, speed);
//             roboclaw.BackwardM2(ADDRESS,speed_back_to_field+10);
//         }else{
//             roboclaw.BackwardM1(ADDRESS,speed_back_to_field);
//             // roboclaw.ForwardM2(ADDRESS, speed);
//             roboclaw.BackwardM2(ADDRESS,speed_back_to_field);
//         }
    
//         // if(analogRead(DETECTOR_BACK_LEFT)>900 && analogRead(DETECTOR_BACK_A3)>900){
//         //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -2795, ACCEL2, 2000, DECCEL2, -2795, 1);
//         //     delay(50);
//         //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3500, DECCEL1, -2795, ACCEL2, 3500, DECCEL2, -2795, 1);
//         // }else if(analogRead(DETECTOR_BACK_A2)>800 && analogRead(DETECTOR_BACK_A3)>800){
//         //     //roboclaw.ResetEncoders(ADDRESS);
//         //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -2795, ACCEL2, 2000, DECCEL2, -2795, 1);
//         //     delay(50);
//         //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3500, DECCEL1, -2795, ACCEL2, 3500, DECCEL2, -2795, 1);
//         // }else if(analogRead(DETECTOR_BACK_A2)<700 && analogRead(DETECTOR_BACK_A3)<700){
//         //     stop();
//         //     return;
//         // }else if(analogRead(DETECTOR_BACK_A2)<800 && analogRead(DETECTOR_BACK_A3)<800){
//         //     //roboclaw.ResetEncoders(ADDRESS);
//         //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -2795, ACCEL2, 2000, DECCEL2, -2795, 1);
//         // }
//         // if(analogRead(DETECTOR_BACK_A2)<400 || analogRead(DETECTOR_BACK_A3)<400){
//         //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 200, DECCEL1, -8000, ACCEL2, 200, DECCEL2, -8000, 1);
//         //     delay(50);
//         //     stop();
//         //     //delay(1000);
//         //     return;
//         // }
//         // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2500, DECCEL, -5570, 1);
//         // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2500, DECCEL, -5570, 1);
//         // // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2500, DECCEL1, -5570, ACCEL2, 2500, DECCEL2, -5570, 1);
//         // delay(3000);
//         // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3000, DECCEL1, -5590, ACCEL2, 3000, DECCEL2, -5570, 1);
//         // delay(1000);
//         // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -5590, ACCEL2, 2000, DECCEL2, -5570, 1);
//         // delay(5000);

//     }
// }

/**
 * 所需的库
 */
#include <math.h>
#include <SoftwareSerial.h>
#include <RoboClaw.h>

//后侧左边传感器,已更改
#define DETECTOR_BACK_LEFT A7

//后侧右边传感器
#define DETECTOR_BACK_RIGHT A8

//左侧传感器
#define DETECTOR_LEFT A0

//右侧传感器
#define DETECTOR_RIGHT A1

//左前方传感器
#define DETECTOR_LEFT_FRONT A5

//更靠近前方的左前方传感器
#define DETECTOR_LEFT_FRONT_MORE A3

//正前方传感器
#define DETECTOR_FRONT A2

//右前方传感器
#define DETECTOR_RIGHT_FRONT A6

//更靠近前方的右前方传感器
#define DETECTOR_RIGHT_FRONT_MORE A4

//边缘传感器1
#define GRAYSCALE_SENSOR_LEFT 37

//边缘传感器
#define GRAYSCALE_SENSOT_RIGHT 36

//电机和主板模拟引脚1
#define MOTOR_DRIVER_S1 11

//电机和主板模拟引脚2
#define MOTOR_DRIVER_S2 10

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//180°旋转
#define TURN_LEFT_180 1200

//180°旋转
#define TURN_RIGHT_180 1200

//左转90°
#define TURN_LEFT_POSITION_90 820
#define TURN_LEFT_POSITION_90_NEW 667//550
#define TURN_LEFT_POSITION_90_SLOWLY 415

//右转—90°
#define TURN_RIGHT_POSITION_90 820
#define TURN_RIGHT_POSITION_90_NEW 667//567
#define TURN_RIGHT_POSITION_90_SLOWLY 440

//左前转向位置，等待更新
#define TURN_LEFT_FRONT 570
#define TURN_LEFT_FRONT_MORE 250

//右前转向，等待更新
#define TURN_RIGHT_FRONT 560
#define TURN_RIGHT_FRONT_MORE 240
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//定义防止被铲起时后侧探测器会检测到的值
#define PREVENT_REAR_BACK_VALUE 300

//因为两个后侧传感器的硬件位置有偏差，所以可以在这里手动补偿一些值
#define LEFT_REAR_SENSOR_COMPENSATION_VALUE 3
#define RIGHT_REAR_SENSOR_COMPENSATION_VALUE 0

//位置误差,用于在左右固定转向时在误差范围内取消轮胎锁定，使其不会回摆
#define ERROR_POSITION 10

//经测试，900左右END值是一圈
#define ONE_ROUND_POSITION 900

//设置电机板命令存储位置
#define ADDRESS 0x80

//上台电机板命令存储位置
#define ADDRESS_STAGE 0x81

//设置电机和主板连接超时值
#define TIME_OUT 10000

//加速度设置，默认
#define ACCEL 655360
#define DECCEL 655360
#define ACCEL1 655360
#define ACCEL2 655360
#define DECCEL1 655360
#define DECCEL2 655360

//进攻时的速度
#define GO_SPEED_ATTACK 20

//微小角度转向
#define TURN_SLOW_POSITION 30

//微小前进
#define GO_SLOW_POSITION 30

//最小检测变化，用于两侧90°转向时判断是否有物体,如果变化大于这个值，则判定有敌人
#define MIN_DETECT_TO_90_ENEMY_JUDGE 177

//对正时两个探测器数值差异范围，超过这个值则会调整
#define OFFSET_THRESHOLD_ADJUST_SLOW 7

//定义传输值no_signal值，当值大于等于它时，认为此值无效
#define NO_SIGNAL_VALUE 900

//传感器检测到物体
#define DETECT_YES 0

//传感器未检测到物体
#define DETECT_NO 1

//上一次检测到物体的方向，用于使小车再次转向补偿
#define DETECT_LAST_LEFT 1
#define DETECT_LAST_RIGHT 2
#define DETECT_LAST_FRONT 3

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

//在台下为了改变位置移动时要用的速度
#define ON_STAGE_SPEED 15

//上台时上台电机的速度
#define FOR_GOING_TO_STAGE_SPEED 40

//前方测敌传感器的70cm数值
#define FRONT_RING_SENSOR_TRIGGER_VALUE 190

//转动补偿
#define FRONT_TURN_COMPLEMENTARY 370

//可以向前窜一下
#define CAN_GO_FRONT_TO_ENEMY 0

//不可以向前窜一下
#define CAN_NOT_GO_FRONT_TO_ENEMY 1

//定义没在边缘
#define STILL_ON_STAGE 1

//定义在边缘
#define CLOSE_TO_EDGE 0

//上台电机速度
#define STAGE_SPEED 450

//上台电机转一圈位置
#define STAGE_MOTOR_ONE_ROUND 558

//上台时的延时
#define STAGE_DELAY 1500

//进入台下动作的最大时间限制，为了让车子从误入台下中出来
#define TIME_UNDER_STAGE_TO_RETURN 4000

//前方传感器重复记录次数，滤波
#define TIMES_FRONT_DETECTOR_FLITER 37

//进攻时的速度
#define ATTACK_SPEED 1977

//边缘传感器的重复检测次数
#define GRAY_SENSOR_TIMES_OF_REDETECT 17

//对齐于边界
#define ALIGN_TO_THE_BORDER 1

//对齐于擂台
#define ALIGN_TO_THE_PLATFORM 0

//目标丢失后对齐两个后端传感器的值之差
#define LOST_ENEMY_TO_TURN_THE_COMPENSATES_BETWEEN_TWO_BACK_DETECTOR 15

//来定义将敌人推到边缘后以什么样的速度前进，防止车子冲下去，但现在通过另一种方式解决-
//两者都用此变量，暂时保存
#define MODE_PUSHING_ENEMY 1

//来定义将敌人推到边缘后以什么样的速度前进，防止车子冲下去，但现在通过另一种方式解决-
//两者都未用此变量，暂时保存
#define MODE_LOST_ENEMY 0

//新的90°转向系统，会在第一次对齐时记录两侧测的数据，并在之后不断检测两侧数据之和-
//根据和来判断是否有敌人，此定义代表可以记录数据
#define CAN_REMEMBER_DISTANCE 0

//定义不可以记录数据
#define CAN_NOT_REMEMBER_DISTANCE 1

#define TIMES_DETECT_REAL_SIDE_MAX 600


/**
 * 变量值
 */
//初始化是否可以进入警戒状态，即是否需要监视前方传感器,避免进入丢失函数，占用资源
int timing = NOT_ENABLE_TO_TIMING;

//初始化上一次物体位置变量，为了之后补偿转向
int last_detect_side = DETECT_LAST_FRONT;

//初始化是否已经开始计时变量
int complementary_time_judge = COMPLEMENTARY_TIME_NO;

//初始化计时时间
long complementary_time = 0;

//初始化旋转次数，为了让小车不会过度补偿旋转
long value_of_turns = 0;

//记录无敌人时，左侧边界的距离
int last_detect_left = 0;

//记录无敌人时，右侧边界的距离
int last_detect_right = 0;

//初始化前方是否检测到物体的变量，是为了在检测到物体后禁用前进和对齐动作
int detect_if_detected = DETECT_IF_DETECTED_NO;

//更新时的暂存变量，在更新距离中和判断台上台下时用，初始化这个是为了防止两次检测的值不同-
//并且为了排除异常值而不影响原来的值
int temp_analogRead_right_upload = 0;
int temp_analogRead_left_upload = 0;

//初始化是否需要向前方窜一下
int enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;

//判断是否将敌人识别成边界，防止对撞中误判断为边界，让这个延时1s
int judge_if_think_enemy_is_edge = 0;

//记录首次三个传感器都检测到时的时间
long time_if_think_enemy_is_edge = 0;

//当车离边界太远时会进行找寻转向，单方向固定，此变量便可以随情况而转动
int too_far_turn_direction = 0;

//让车可以随情况而转向，此变量可以锁定判断，让方向只进行一次判断
int too_far_turn_if_had_judeged = 0;

//在台下对齐时判断对齐的是哪一侧，默认对齐边界
int which_had_align = ALIGN_TO_THE_BORDER;

//初始化是否可以记录原始两侧的数据
int detect_enemy_two_side_can_or_not_remember_the_distance = CAN_REMEMBER_DISTANCE;

//原始左侧数据
long stationary_distance_left = 0;

//原始右侧数据
long stationary_distance_right = 0;

long times_detect_real_side = 0;

int temp_detect_two_side_left = 0;
int temp_detect_two_side_right = 0;

/**
 * 实例化对象和一些准备设置
 */
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
    // roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, ATTACK_SPEED, DECCEL, 6999999, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, ATTACK_SPEED, DECCEL, 6999999, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1700, DECCEL1, 999999, ACCEL2, 1700, DECCEL2, 999999, 1);
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
        roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, 0, 1);
        roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, 0, 1);
        // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 0, ACCEL2, 8000, DECCEL2, 0, 1);
    //}
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

//向右转90°特别版，中等速度
void turnRightPosition90(){
    //M1PositionBackward(single);
    //M2PositionForward(single);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, TURN_RIGHT_POSITION_90_NEW, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, -TURN_RIGHT_POSITION_90_NEW, 1);
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
    // roboclaw.ForwardM1(ADDRESS, 127);
    // // roboclaw.BackwardM1(ADDRESS,127);
    // // roboclaw.ForwardM2(ADDRESS, 127);
    // roboclaw.BackwardM2(ADDRESS,127);
    // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, single, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, single, ACCEL2, 8000, DECCEL2, -single, 1);
    // delay(150);
    // if(single>450){
    //     delay(single/3);
    // }else{
    //     delay(150);
    // }
    // stop();
    // while (1){
    //     /* code */
    //     if(roboclaw.ReadEncM1(ADDRESS)>=single-ERROR_POSITION){
    //         stop();
    //         //stop_stuck();
    //         return;
    //     }
    // }
    while(roboclaw.ReadEncM1(ADDRESS)<(TURN_RIGHT_POSITION_90_NEW-ERROR_POSITION)){
        //NULL
    }
    stop();
    
    // for(;;){
        
    // }
}

//向右转90°，专门针对台下
void turnRightPosition90ForUnderStage(){
    //M1PositionBackward(single);
    //M2PositionForward(single);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, TURN_RIGHT_POSITION_90_NEW-120, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, (-TURN_RIGHT_POSITION_90_NEW)+120, 1);
    
    while(roboclaw.ReadEncM1(ADDRESS)<(TURN_RIGHT_POSITION_90_NEW-120-ERROR_POSITION)){

    }
    stop();
    
    // for(;;){
        
    // }
}

//向右转位置函数
void turnRightPosition(int single){
    //M1PositionBackward(single);
    //M2PositionForward(single);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, single, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -single, 1);
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
    // roboclaw.ForwardM1(ADDRESS, 127);
    // // roboclaw.BackwardM1(ADDRESS,127);
    // // roboclaw.ForwardM2(ADDRESS, 127);
    // roboclaw.BackwardM2(ADDRESS,127);
    // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, single, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, single, ACCEL2, 8000, DECCEL2, -single, 1);
    // delay(150);
    // if(single>450){
    //     delay(single/3);
    // }else{
    //     delay(150);
    // }
    // stop();
    // while (1){
    //     /* code */
    //     if(roboclaw.ReadEncM1(ADDRESS)>=single-ERROR_POSITION){
    //         stop();
    //         //stop_stuck();
    //         return;
    //     }
    // }
    long temp_turn = millis();
    // while(roboclaw.ReadEncM2(ADDRESS)<(single-ERROR_POSITION)){
        
    while(roboclaw.ReadEncM1(ADDRESS)<(single-ERROR_POSITION)){
        if(millis()-temp_turn>4000){
                    break;
                }
    }
    stop();
    
    // for(;;){
        
    // }
}

//减速版向右转，专门针对台下转移位置使用，速度很慢，但准确
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
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 1000, DECCEL, single, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 1000, DECCEL, -single, 1);
    while(roboclaw.ReadEncM1(ADDRESS)<single-ERROR_POSITION){

    }
    stop();
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1000, DECCEL1, single, ACCEL2, 1000, DECCEL2, -single, 1);
    // for(;;){
    //     if(roboclaw.ReadEncM1(ADDRESS)>=single-ERROR_POSITION){
    //         stop();
    //         //stop_stuck();
    //         return;
    //     }
    // }
    
}

//向左90°特别版，中等速度
void turnLeftPositon90(){
    //static int M1PositionTemp = 0;
    //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    //roboclaw.SetEncM2(ADDRESS,0);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, -TURN_LEFT_POSITION_90_NEW, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, TURN_LEFT_POSITION_90_NEW, 1);
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
    // roboclaw.ForwardM1(ADDRESS, 127);
    // roboclaw.BackwardM1(ADDRESS,127);
    // roboclaw.ForwardM2(ADDRESS, 127);
    // roboclaw.BackwardM2(ADDRESS,127);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, -single, ACCEL2, 8000, DECCEL2, single, 1);
    // while (1){
    //     /* code */
    //     // Serial.println(roboclaw.ReadEncM2(ADDRESS));
    //     if(roboclaw.ReadEncM2(ADDRESS)>=single-ERROR_POSITION){
    //     // delay(100);
    //     stop();
    //     return;
    //     }
    // }
    while(roboclaw.ReadEncM2(ADDRESS)<(TURN_LEFT_POSITION_90_NEW-ERROR_POSITION)){

    }
    stop();
    
    // for(;;){
        
    // }
    // Serial.println(roboclaw.ReadEncM2(ADDRESS));
    // do{
    //     //Serial.println(roboclaw.ReadEncM2(ADDRESS));
    // }while(roboclaw.ReadEncM2(ADDRESS)!=0);
    // stop();
    // if(single>450){
    //     delay(single/3);
    // }else{
    //     delay(150);
    // }
    // stop();
    // return;
}

//向左转90°特别针对台下
void turnLeftPositon90ForUnderStage(){
    //static int M1PositionTemp = 0;
    //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    //roboclaw.SetEncM2(ADDRESS,0);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, (-TURN_LEFT_POSITION_90_NEW)+120, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, TURN_LEFT_POSITION_90_NEW-120, 1);
    while(roboclaw.ReadEncM2(ADDRESS)<(TURN_LEFT_POSITION_90_NEW-120-ERROR_POSITION)){

    }
    stop();
    
    
}

//向左转位置函数
void turnLeftPosition(int single){
    //static int M1PositionTemp = 0;
    //if(roboclaw.ReadEncM1(ADDRESS)==-position){
    //roboclaw.SetEncM2(ADDRESS,0);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -single, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, single, 1);
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
    // roboclaw.ForwardM1(ADDRESS, 127);
    // roboclaw.BackwardM1(ADDRESS,127);
    // roboclaw.ForwardM2(ADDRESS, 127);
    // roboclaw.BackwardM2(ADDRESS,127);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, -single, ACCEL2, 8000, DECCEL2, single, 1);
    // while (1){
    //     /* code */
    //     // Serial.println(roboclaw.ReadEncM2(ADDRESS));
    //     if(roboclaw.ReadEncM2(ADDRESS)>=single-ERROR_POSITION){
    //     // delay(100);
    //     stop();
    //     return;
    //     }
    // }
    long temp_turn = millis();
    while(roboclaw.ReadEncM2(ADDRESS)<(single-ERROR_POSITION)){
        if(millis()-temp_turn>4000){
            break;
        }
    }
    stop();
    
    // for(;;){
        
    // }
    // Serial.println(roboclaw.ReadEncM2(ADDRESS));
    // do{
    //     //Serial.println(roboclaw.ReadEncM2(ADDRESS));
    // }while(roboclaw.ReadEncM2(ADDRESS)!=0);
    // stop();
    // if(single>450){
    //     delay(single/3);
    // }else{
    //     delay(150);
    // }
    // stop();
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
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 1000, DECCEL, -single, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 1000, DECCEL, single, 1);


    while(roboclaw.ReadEncM2(ADDRESS)<single-ERROR_POSITION){

    }

    // delay(1000);

    stop();
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1000, DECCEL1, -single, ACCEL2, 1000, DECCEL2, single, 1);
    // for(;;){
    //     if(roboclaw.ReadEncM2(ADDRESS)>=single-ERROR_POSITION){
    //         stop();
    //         return;
    //     }
    // }
}

//判断前方5个传感器是否监测到敌人，这个函数更精确-
//在这个函数中，一旦有一次没监测到敌人，都视为异常值，不算数
int determineIfThereIsAnObjectInFrontOfTheSide(int which_one){
    int temp = 0;
    // int detect_value[7];
    for(int i=0;i<TIMES_FRONT_DETECTOR_FLITER;++i){
        // detect_value[i] = analogRead(which_one);
        if(analogRead(which_one)<FRONT_RING_SENSOR_TRIGGER_VALUE){
            temp = 1;
        }
        // temp += analogRead(which_one);
    }
    // Serial.print("temp_last:");
    // Serial.println(temp);
    // temp = temp/TIMES_FRONT_DETECTOR_FLITER;
    // Serial.print("      ");
    // Serial.print(temp);
    if(temp==0){
        return DETECT_YES;
    }else{
        return DETECT_NO;
    }

}



//微小前进位置函数，经过测试，实际完成前进动作需要300ms左右，但目前情况不错，所以不做更改
//void goFrontPosition(){
void moveALittleForward(){
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, GO_SLOW_POSITION, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, GO_SLOW_POSITION, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, GO_SLOW_POSITION, ACCEL2, 8000, DECCEL2, GO_SLOW_POSITION, 1);
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
    int storage_front_end_sensors1;
    int storage_front_end_sensors2;
    // int storage_front_end_sensors1_temp[7] = {1,1,1,1,1,1,1};
    // int storage_front_end_sensors2_temp[7] = {1,1,1,1,1,1,1};
    for(int i=0;i<GRAY_SENSOR_TIMES_OF_REDETECT;++i){
    storage_front_end_sensors1 = digitalRead(GRAYSCALE_SENSOT_RIGHT);
    storage_front_end_sensors2 = digitalRead(GRAYSCALE_SENSOR_LEFT);
        if(storage_front_end_sensors1==DETECT_NO || storage_front_end_sensors2==DETECT_NO){
            //return STILL_ON_STAGE;
            temp++;
        }
    }
    if(temp==GRAY_SENSOR_TIMES_OF_REDETECT){
        return CLOSE_TO_EDGE;
    }else{
        return STILL_ON_STAGE;
    }
}

/**
 * 右转向辅助函数，用于防止刀刃插到台子上
 */
void preventsTheBladeFromGettingStuckUnderTableRight(){//
    // roboclaw.ForwardM1(ADDRESS, 30);
    // roboclaw.ForwardM2(ADDRESS, 10);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -400, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, 400, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 400, ACCEL2, 8000, DECCEL2, -400, 1);
    delay(200);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2000, DECCEL, 0, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2000, DECCEL, 800, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, 800, ACCEL2, 2000, DECCEL2, 0, 1);
    delay(300);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 5000, DECCEL, 800, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 5000, DECCEL, 0, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 5000, DECCEL1, 0, ACCEL2, 5000, DECCEL2, 800, 1);
    delay(200);
    //stop();
}

/**
 * 左转向辅助函数，用于防止刀刃插到台子上
 */
void preventsTheBladeFromGettingStuckUnderTableLeft(){//
    // roboclaw.ForwardM1(ADDRESS, 30);
    // roboclaw.ForwardM2(ADDRESS, 10);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, 400, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -400, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 400, ACCEL2, 8000, DECCEL2, -400, 1);
    delay(200);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2000, DECCEL, 800, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2000, DECCEL, 0, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, 800, ACCEL2, 2000, DECCEL2, 0, 1);
    delay(300);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 5000, DECCEL, 0, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 5000, DECCEL, 800, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 5000, DECCEL1, 0, ACCEL2, 5000, DECCEL2, 800, 1);
    delay(200);
    //stop();
}

/**
 * 后退函数，为了后退抵在边界墙上对齐用
 */
void backToTouchTheWall(){
    // roboclaw.BackwardM1(ADDRESS,20);
    // roboclaw.BackwardM2(ADDRESS,20);
    // delay(1500);
    // stop();
    roboclaw.BackwardM1(ADDRESS,20);
    roboclaw.BackwardM2(ADDRESS,20);
    long last_detect_back_left = 0;
    long last_detect_back_right = 0;
    long temp_time = millis();
    which_had_align = ALIGN_TO_THE_BORDER;
    // delay(200);
    do{
        /* code */
        last_detect_back_left = 0;
        last_detect_back_right = 0;
        // last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
        // last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
        // long last_temp_left = analogRead(DETECTOR_LEFT);
        // long last_temp_right = analogRead(DETECTOR_RIGHT);
        for(int i=0;i<10;++i){
            last_detect_back_left += analogRead(DETECTOR_BACK_LEFT);
            last_detect_back_right += analogRead(DETECTOR_BACK_RIGHT);
            // last_temp_left += analogRead(DETECTOR_LEFT);
            // last_temp_right += analogRead(DETECTOR_RIGHT);
        }
        last_detect_back_left = last_detect_back_left/10;
        last_detect_back_right = last_detect_back_right/10;
        // last_temp_left = last_temp_left/10;
        // last_temp_right = last_temp_right/10;
        // Serial.println(last_detect_back_left+last_detect_back_right);
        if(millis()-temp_time>1500){
            which_had_align = ALIGN_TO_THE_PLATFORM;
            break;
        }
    } while (last_detect_back_left+last_detect_back_right>385);
    
    // stop();
    if(which_had_align==ALIGN_TO_THE_BORDER){
        roboclaw.BackwardM1(ADDRESS,10);
        roboclaw.BackwardM2(ADDRESS,10);
        delay(200);
    }
    stop();
}

//检查点：2019年9月1日（已更新）
/**
 * 台下动作，此时已经判断摔下台了
 */
void decidedTheCarHadFallenOff(){
    //pinMode(13,OUTPUT);
    //digitalWrite(13,HIGH);//
    // goFrontPosition();
    // goFrontPosition();
    // goFrontPosition();
    // goFrontPosition();
    //转向，使车轮转向边界
    
    long time_of_under_stage_to_return = millis();
    int times_prevent = 0;
    if(analogRead(DETECTOR_BACK_LEFT)>analogRead(DETECTOR_BACK_RIGHT)){
        roboclaw.BackwardM1(ADDRESS,15);
        roboclaw.ForwardM2(ADDRESS, 15);
    }else{
        roboclaw.BackwardM2(ADDRESS,15);
        roboclaw.ForwardM1(ADDRESS, 15);
    }
    
    // 
    // while(abs(analogRead(DETECTOR_BACK_LEFT)-analogRead(DETECTOR_BACK_RIGHT))>20){
    
    while(abs(analogRead(DETECTOR_BACK_LEFT)-analogRead(DETECTOR_BACK_RIGHT))>20 || analogRead(DETECTOR_BACK_LEFT)+analogRead(DETECTOR_BACK_RIGHT)>700){
        // turnLeftPosition(3*TURN_SLOW_POSITION);
        //防止刀刃卡住
        if(times_prevent==0){
            if(analogRead(DETECTOR_LEFT)<210 || analogRead(DETECTOR_LEFT_FRONT)>580){
            // turnLeftPosition(4*TURN_SLOW_POSITION);
            // goFrontPosition();
                preventsTheBladeFromGettingStuckUnderTableLeft();
                times_prevent = 1;
                roboclaw.BackwardM1(ADDRESS,15);
                roboclaw.ForwardM2(ADDRESS, 15);
            }

            if(analogRead(DETECTOR_RIGHT)<210 || analogRead(DETECTOR_RIGHT_FRONT)>580){
                preventsTheBladeFromGettingStuckUnderTableRight();
                times_prevent = 1;
                roboclaw.BackwardM2(ADDRESS,15);
                roboclaw.ForwardM1(ADDRESS, 15);
            }
        }
        

        if(millis()-time_of_under_stage_to_return>TIME_UNDER_STAGE_TO_RETURN){
            return;
        }
    }

    // long time_of_under_stage_to_return = millis();
    // // int times_prevents
    // while(analogRead(DETECTOR_BACK_LEFT)-analogRead(DETECTOR_BACK_RIGHT)>20 || analogRead(DETECTOR_BACK_LEFT)+analogRead(DETECTOR_BACK_RIGHT)>550){
    //     turnLeftPosition(3*TURN_SLOW_POSITION);
    //     //防止刀刃卡住
    //     if(analogRead(DETECTOR_LEFT)<180){
    //         // turnLeftPosition(4*TURN_SLOW_POSITION);
    //         // goFrontPosition();
    //         // preventsTheBladeFromGettingStuckUnderTable();
    //     }
    //     if(millis()-time_of_under_stage_to_return>TIME_UNDER_STAGE_TO_RETURN){
    //         return;
    //     }
    // }
    // while(analogRead(DETECTOR_BACK_A2)-analogRead(DETECTOR_BACK_A3)>2 && analogRead(DETECTOR_BACK_A2)>analogRead(DETECTOR_BACK_A3)){
    //     turnLeftPosition(TURN_SLOW_POSITION);
    // }
    //goBack(GO_BAKC_SPEED)
    //后退，用边界来对正
    backToTouchTheWall();
    
    //对正后前进一段
    goForwardAfterAlignedTheWall();
    //改变上台的位置
    changeThePositionGoingToStage();
    // if(analogRead(DETECTOR_BACK_LEFT)>400){
    //     turnLeftPositionSlowly(TURN_LEFT_180);
    // }
    stepBackAndGetOnStage();
    //delay(1500);
    //stop();
    // while(1){
    //    baseline(); 
    // }
    //
    // delay(10000);
}

/**
 * 上台函数
 */
void stepBackAndGetOnStage(){
    //接用此函数
    // backToTouchTheWall();
    if(analogRead(DETECTOR_BACK_LEFT)<330){
        roboclaw.BackwardM1(ADDRESS,17);
        roboclaw.BackwardM2(ADDRESS,17);
        delay(450);
        stop();
        roboclaw.ResetEncoders(ADDRESS);
        roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, TURN_RIGHT_180-200, 1);
        roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, -TURN_RIGHT_180+200, 1);
        delay(800);
    }
    roboclaw.BackwardM1(ADDRESS,25);
    roboclaw.BackwardM2(ADDRESS,25);
    delay(300);
    roboclaw.BackwardM1(ADDRESS,17);
    roboclaw.BackwardM2(ADDRESS,17);
    delay(300);
    // stop();
    startTheOnStageMotor();
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
    // roboclaw_stage.BackwardM1(ADDRESS,FOR_GOING_TO_STAGE_SPEED);
    // roboclaw_stage.ForwardM2(ADDRESS,FOR_GOING_TO_STAGE_SPEED);
    // delay(1580);
    // roboclaw_stage.BackwardM1(ADDRESS,0);
    // delay(45);
    // roboclaw_stage.BackwardM2(ADDRESS,0);
    roboclaw_stage.ResetEncoders(ADDRESS_STAGE);
    //，空地测试可以转一圈，实地测试的时候可能不是一圈，还需要进一步测试（已测试）
    // roboclaw_stage.SpeedAccelDeccelPositionM1M2(ADDRESS_STAGE, ACCEL1, STAGE_SPEED, DECCEL1, -STAGE_MOTOR_ONE_ROUND, ACCEL2, STAGE_SPEED, DECCEL2, STAGE_MOTOR_ONE_ROUND, 1);
    roboclaw_stage.SpeedAccelDeccelPositionM1(ADDRESS_STAGE, ACCEL, STAGE_SPEED, DECCEL, -STAGE_MOTOR_ONE_ROUND, 1);
    roboclaw_stage.SpeedAccelDeccelPositionM2(ADDRESS_STAGE, ACCEL, STAGE_SPEED, DECCEL, STAGE_MOTOR_ONE_ROUND, 1);
    delay(STAGE_DELAY);
    roboclaw_stage.ForwardM1(ADDRESS_STAGE, 0);
    // roboclaw.BackwardM1(ADDRESS,speed);
    roboclaw_stage.ForwardM2(ADDRESS_STAGE, 0);
    if(analogRead(DETECTOR_LEFT)<600){
        roboclaw.ResetEncoders(ADDRESS);
        roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, TURN_RIGHT_180, 1);
        roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, -TURN_RIGHT_180, 1);
        delay(800);
        // turnRightPosition(TURN_RIGHT_180);
    }else{
        roboclaw.ResetEncoders(ADDRESS);
        roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, -TURN_LEFT_180, 1);
        roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, TURN_LEFT_180, 1);
        delay(800);
        // turnLeftPosition(TURN_LEFT_180);
    }
}

/**
 * 判断在台上还是在台下
 */
//检查点：2019年9月2日11点26分（已更新）
void judgeWhetherOnStageOrUnderTheStage(){
    //，对于后侧传感器的值，出现过在台子边缘检测异常的情况，还需进一步测试（已测试）
    if(analogRead(DETECTOR_LEFT)+analogRead(DETECTOR_RIGHT)<570 || analogRead(DETECTOR_BACK_LEFT)<320){
    // if(analogRead(DETECTOR_BACK_LEFT)<330){//

    // if(temp_analogRead_left_upload+temp_analogRead_right_upload<580){//

        stop();
        delay(100);
        if(analogRead(DETECTOR_LEFT)+analogRead(DETECTOR_RIGHT)<570 || analogRead(DETECTOR_BACK_LEFT)<320){
        // if(analogRead(DETECTOR_BACK_LEFT)<330){
            stop();
            delay(100);
        // if(temp_analogRead_left_upload+temp_analogRead_right_upload<580 ){
            if(analogRead(DETECTOR_LEFT)+analogRead(DETECTOR_RIGHT)<570 || analogRead(DETECTOR_BACK_LEFT)<320){
                decidedTheCarHadFallenOff();
            }
            
        }
    }
}

/**
 * 为了改变上台位置，向前走
 */
void forChangeThePositionToMoveAlongWall(int distance){
    //inOrderToGoAlongStraightFirstSteeralignment();
    //if(analogRead(DETECTOR_BACK_LEFT)>)
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3500, DECCEL, distance, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3500, DECCEL, distance, 1);
    while(roboclaw.ReadEncM2(ADDRESS)<(distance-ERROR_POSITION) || roboclaw.ReadEncM1(ADDRESS)<(distance-ERROR_POSITION)){

    }
    stop();
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, 2800, ACCEL2, 2000, DECCEL2, 2800, 1);

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
    if(analogRead(DETECTOR_LEFT)<284){
        // switch (analogRead(DETECTOR_RIGHT)){
        // case :
        //     /* code */
        //     break;
        
        // default:
        //     break;
        // }
        // if(analogRead(DETECTOR_RIGHT))
        //turnRightPosition(TURN_RIGHT_POSITION_90);
        turnRightPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
        // delay(800);
        forChangeThePositionToMoveAlongWall(6260);
        // delay(2000);
        //delay(2000);
        // turnRightPosition90();
        // turnRightPosition(TURN_RIGHT_POSITION_90-70);
        if(which_had_align==ALIGN_TO_THE_BORDER){
            turnRightPosition90ForUnderStage();
        }else{
            turnLeftPositon90ForUnderStage();
        }
    }else if(analogRead(DETECTOR_LEFT)<425){
        turnRightPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
        // delay(800);
        forChangeThePositionToMoveAlongWall(4494);
        // delay(2000);
        //delay(2000);
        // turnRightPosition90();
        // turnRightPosition(TURN_RIGHT_POSITION_90-70);
        // turnRightPosition90ForUnderStage();
        if(which_had_align==ALIGN_TO_THE_BORDER){
            turnRightPosition90ForUnderStage();
        }else{
            turnLeftPositon90ForUnderStage();
        }

    }else if(analogRead(DETECTOR_LEFT)<620){
        turnRightPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
        // delay(800);
        forChangeThePositionToMoveAlongWall(2783);
        // delay(2000);
        //delay(2000);
        // turnRightPosition90();
        // turnRightPosition(TURN_RIGHT_POSITION_90-70);
        // turnRightPosition90ForUnderStage();
        if(which_had_align==ALIGN_TO_THE_BORDER){
            turnRightPosition90ForUnderStage();
        }else{
            turnLeftPositon90ForUnderStage();
        }

    }else{
        if(analogRead(DETECTOR_RIGHT)<284){
            turnLeftPositionSlowly(TURN_LEFT_POSITION_90_SLOWLY);
            // delay(800);
            forChangeThePositionToMoveAlongWall(6260);
            // delay(2000);
            //delay(2000);
            // turnLeftPositon90();
            // turnRightPosition(TURN_RIGHT_POSITION_90);
            // turnLeftPosition(TURN_LEFT_POSITION_90-70);
            // turnRightPosition90ForUnderStage();
            // if()
            // turnLeftPositon90ForUnderStage();
            if(which_had_align==ALIGN_TO_THE_BORDER){
                turnLeftPositon90ForUnderStage();
            }else{
                turnRightPosition90ForUnderStage();
            }

        }else if(analogRead(DETECTOR_RIGHT)<425){
            turnLeftPositionSlowly(TURN_LEFT_POSITION_90_SLOWLY);
            // delay(800);
            forChangeThePositionToMoveAlongWall(4494);
            // delay(2000);
            //delay(2000);
            // turnLeftPositon90();
            // turnRightPosition(TURN_RIGHT_POSITION_90);
            // turnLeftPosition(TURN_LEFT_POSITION_90-70);
            // turnLeftPositon90ForUnderStage();
            if(which_had_align==ALIGN_TO_THE_BORDER){
                turnLeftPositon90ForUnderStage();
            }else{
                turnRightPosition90ForUnderStage();
            }

        }else{
            // turnRightPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
            // delay(800);
            // forChangeThePositionToMoveAlongWall(2783);
            // delay(2000);
            // //delay(2000);
            // turnRightPosition90();
            // turnLeftPosition(TURN_LEFT_POSITION_90);
            turnLeftPositionSlowly(TURN_LEFT_POSITION_90_SLOWLY);
            // delay(800);
            forChangeThePositionToMoveAlongWall(2700);
            // turnLeftPositon90ForUnderStage();
            if(which_had_align==ALIGN_TO_THE_BORDER){
                turnLeftPositon90ForUnderStage();
            }else{
                turnRightPosition90ForUnderStage();
            }

            // delay(2000);
            //delay(2000);
            // turnLeftPositon90();
            // turnRightPosition(TURN_RIGHT_POSITION_90);
            // turnLeftPosition(TURN_LEFT_POSITION_90-70);
            // turnLeftPosition(TURN_LEFT_POSITION_90);
        }
    }

    // if(analogRead(DETECTOR_RIGHT)<284){
    //         turnLeftPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
    //         // delay(800);
    //         forChangeThePositionToMoveAlongWall(6260);
    //         // delay(2000);
    //         //delay(2000);
    //         turnLeftPositon90();
    //         // turnRightPosition(TURN_RIGHT_POSITION_90);
    //     }else if(analogRead(DETECTOR_RIGHT)<425){
    //         turnLeftPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
    //         // delay(800);
    //         forChangeThePositionToMoveAlongWall(4494);
    //         // delay(2000);
    //         //delay(2000);
    //         turnLeftPositon90();
    //     }else if(analogRead(DETECTOR_RIGHT)<583){
    //         // turnRightPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
    //         // delay(800);
    //         // forChangeThePositionToMoveAlongWall(2783);
    //         // delay(2000);
    //         // //delay(2000);
    //         // turnRightPosition90();
    //         // turnLeftPosition(TURN_LEFT_POSITION_90);
    //         turnLeftPositionSlowly(TURN_LEFT_POSITION_90_SLOWLY);
    //         // delay(800);
    //         forChangeThePositionToMoveAlongWall(2700);
    //         // delay(2000);
    //         //delay(2000);
    //         turnLeftPositon90();
    //         // turnLeftPosition(TURN_LEFT_POSITION_90);
        
    // }else{
    //     if(analogRead(DETECTOR_LEFT)<284){
    //     // switch (analogRead(DETECTOR_RIGHT)){
    //     // case :
    //     //     /* code */
    //     //     break;
        
    //     // default:
    //     //     break;
    //     // }
    //     // if(analogRead(DETECTOR_RIGHT))
    //     //turnRightPosition(TURN_RIGHT_POSITION_90);
    //     turnRightPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
    //     // delay(800);
    //     forChangeThePositionToMoveAlongWall(6260);
    //     // delay(2000);
    //     //delay(2000);
    //     turnRightPosition90();
    //     // turnRightPosition(TURN_RIGHT_POSITION_90);
    //     }else if(analogRead(DETECTOR_LEFT)<425){    
    //     turnRightPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
    //     // delay(800);
    //     forChangeThePositionToMoveAlongWall(4494);
    //     // delay(2000);
    //     //delay(2000);
    //     turnRightPosition90();
    //     }else{
    //     turnRightPositionSlowly(TURN_RIGHT_POSITION_90_SLOWLY);
    //     // delay(800);
    //     forChangeThePositionToMoveAlongWall(2783);
    //     // delay(2000);
    //     //delay(2000);
    //     turnRightPosition90();
    //     }
        
    // }
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
    // int temp_detect_two_side_left = 0;
    // int temp_detect_two_side_right = 0;
    // for(int i=0;i<3;++i){
    //     temp_detect_two_side_left += analogRead(DETECTOR_LEFT);
    //     temp_detect_two_side_right += analogRead(DETECTOR_RIGHT);
    // }
    // temp_detect_two_side_left = temp_detect_two_side_left/3;
    // temp_detect_two_side_right = temp_detect_two_side_right/3;
    temp_detect_two_side_left = analogRead(DETECTOR_LEFT);
    temp_detect_two_side_right = analogRead(DETECTOR_RIGHT);
    judgeWhetherOnStageOrUnderTheStage();//台下判断
    if(last_detect_left-temp_detect_two_side_left>=MIN_DETECT_TO_90_ENEMY_JUDGE && temp_detect_two_side_left+temp_detect_two_side_right<1100){//122333
        // turnLeftPosition(TURN_LEFT_POSITION_90);
        turnLeftPositon90();
        // delay(100);//122333
        // Serial.println("left");
        detect_enemy_two_side_can_or_not_remember_the_distance = CAN_REMEMBER_DISTANCE;
        uploadDetect();
        times_detect_real_side = TIMES_DETECT_REAL_SIDE_MAX;

        // uploadDetect();
        //alignment_only_once = 0;
    }else if(last_detect_right-temp_detect_two_side_right>=MIN_DETECT_TO_90_ENEMY_JUDGE && temp_detect_two_side_left+temp_detect_two_side_right<1100){//122333
        turnRightPosition90();
        // delay(100);//122333
        detect_enemy_two_side_can_or_not_remember_the_distance = CAN_REMEMBER_DISTANCE;
        uploadDetect();
        times_detect_real_side = TIMES_DETECT_REAL_SIDE_MAX;

    }else if((temp_detect_two_side_left+temp_detect_two_side_right)<1200){
        // i = 500;
        //新的转向系统，在没敌人时，两侧之和是1200+，有敌人时在1010-，通过这个来判断是否有敌人
        times_detect_real_side = TIMES_DETECT_REAL_SIDE_MAX;

        if(abs(stationary_distance_left-temp_detect_two_side_left)>abs(stationary_distance_right-temp_detect_two_side_right)){
            turnLeftPositon90();
            detect_enemy_two_side_can_or_not_remember_the_distance = CAN_REMEMBER_DISTANCE;
            // uploadDetect();
            uploadDetectForce();
            
            return;
        }else{
            turnRightPosition90();
            detect_enemy_two_side_can_or_not_remember_the_distance = CAN_REMEMBER_DISTANCE;
            // uploadDetect();
            uploadDetectForce();
            return;

        }
        // }else if(abs(stationary_distance_left-temp_detect_two_side_left)<abs(stationary_distance_right-temp_detect_two_side_right)){
        //     turnRightPosition90();
        //     detect_enemy_two_side_can_or_not_remember_the_distance = CAN_REMEMBER_DISTANCE;
        //     // uploadDetect();

        // }
        
    }
//     else 
    
// //      
//         // turnRightPosition(TURN_RIGHT_POSITION_90);
//         // uploadDetect();
//         // Serial.println("right");
//         //al
//     }
    // if(last_detect_left-analogRead(DETECTOR_LEFT)>=MIN_DETECT_TO_90_ENEMY_JUDGE && analogRead(DETECTOR_LEFT)+analogRead(DETECTOR_RIGHT)<1100){
    //     // turnLeftPosition(TURN_LEFT_POSITION_90);
    //     turnLeftPositon90();
    //     // Serial.println("left");
    //     uploadDetect();
    //     //alignment_only_once = 0;
    // }else if(last_detect_right-analogRead(DETECTOR_RIGHT)>=MIN_DETECT_TO_90_ENEMY_JUDGE && analogRead(DETECTOR_LEFT)+analogRead(DETECTOR_RIGHT)<1100){
    //     turnRightPosition90();
    //     // turnRightPosition(TURN_RIGHT_POSITION_90);
    //     uploadDetect();
    //     // Serial.println("right");
    //     //alignment_only_once = 0;
    // }
}

/**
 * 对齐函数，在每一次对齐后都会判断小车位置
 */
//void alignmentMoreStringent(){//旧
void alignWithWalls(){
    long last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
    long last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
    for(int i=0;i<9;++i){
        last_detect_back_left += analogRead(DETECTOR_BACK_LEFT);
        last_detect_back_right += analogRead(DETECTOR_BACK_RIGHT);
    }
    last_detect_back_left = last_detect_back_left/10;
    last_detect_back_right = last_detect_back_right/10;
    // Serial.print("left:");//122333
    // Serial.print(last_detect_back_left);//122333
    // Serial.print("   right:");//122333
    // Serial.print(last_detect_back_right);//122333
    // if()
    if(last_detect_back_left+last_detect_back_right>=1817){
        if(analogRead(DETECTOR_BACK_LEFT)+analogRead(DETECTOR_BACK_RIGHT)>=1817){
            // delay(200);
            
            if(analogRead(DETECTOR_BACK_LEFT)+analogRead(DETECTOR_BACK_RIGHT)>=1817){
                if(too_far_turn_if_had_judeged==0){
                    too_far_turn_if_had_judeged = 1;
                    /**
                     * 这里是为了防止车到边缘后向错误的方向进行距离过大-
                     * 转向错误的方向浪费时间，并且只会判断一次转向的方向
                     */
                    if(analogRead(DETECTOR_LEFT)>analogRead(DETECTOR_RIGHT)){
                        too_far_turn_direction = 0;
                    }else{
                        too_far_turn_direction = 1;
                    }
                }

                if(too_far_turn_direction==0){
                    turnLeftPosition(2*TURN_SLOW_POSITION);
                }else{
                    turnRightPosition(2*TURN_SLOW_POSITION);
                }
            }
        }
    }else if(last_detect_back_left-last_detect_back_right>OFFSET_THRESHOLD_ADJUST_SLOW){
        // Serial.print("    turn left");//122333
        turnLeftPosition(TURN_SLOW_POSITION);
    }else if(last_detect_back_right-last_detect_back_left>OFFSET_THRESHOLD_ADJUST_SLOW){
        // Serial.print("    turn right");//122333
        turnRightPosition(TURN_SLOW_POSITION);
    }else{
        // Serial.print("    over");//122333
        too_far_turn_if_had_judeged = 0;
        moveALittleForward();
        
        uploadDetectAndDetectEnemy();
        // uploadDetect();
    }
    // Serial.println(" ");//122333
    // if(grayScaleSensorDetect()==CLOSE_TO_EDGE){
    //     // turnLeftPositionSlowly
    //     roboclaw.ResetEncoders(ADDRESS);
    //     roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, TURN_RIGHT_180, 1);
    //     roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, -TURN_RIGHT_180, 1);
    //     while(roboclaw.ReadEncM1(ADDRESS)<TURN_RIGHT_180-ERROR_POSITION){

    //     }
    //     stop();
    // }
    // judgeWhetherOnStageOrUnderTheStage();

}

//距离更新函数，会忽略传感器返回的无信号值
void uploadDetect(){
    // delay(100);//122333
    //delay(100); temp_analogRead_right_upload-last_detect_right<ABNORMAL_INCREASE && temp_analogRead_left_upload-last_detect_left<ABNORMAL_INCREASE
    temp_analogRead_right_upload = 0;
    temp_analogRead_left_upload = 0;
    for(int i=0;i<5;++i){
        temp_analogRead_right_upload += analogRead(DETECTOR_RIGHT);
        temp_analogRead_left_upload += analogRead(DETECTOR_LEFT);
    }
    temp_analogRead_right_upload = temp_analogRead_right_upload/5;
    temp_analogRead_left_upload = temp_analogRead_left_upload/5;
    
    // if(temp_analogRead_left_upload+temp_analogRead_right_upload>1170){//122333
    if(temp_analogRead_right_upload<NO_SIGNAL_VALUE){
    //uploadDetect();
        last_detect_right = temp_analogRead_right_upload;
    // Serial.print(last_detect_right);
    }
    // }else{
    //     last_detect_right = 0;//122333
    // }
    if(temp_analogRead_left_upload<NO_SIGNAL_VALUE){
        last_detect_left = temp_analogRead_left_upload;
        // Serial.println(last_detect_left);
    }
    // }else{
    //     last_detect_left = 0;//122333
    // }
    // }
    
    // last_detect_left = analogRead(DETECTOR_LEFT_A0);
    // last_detect_right = analogRead(DETECTOR_RIGHT_A1);
}

void uploadDetectAndDetectEnemy(){
    // for(int i=0;i<500;++i){
    //     temp_analogRead_right_upload = analogRead(DETECTOR_RIGHT);
    //     temp_analogRead_left_upload = analogRead(DETECTOR_LEFT);
    if(detect_enemy_two_side_can_or_not_remember_the_distance==CAN_REMEMBER_DISTANCE){
            temp_analogRead_right_upload = 0;
            temp_analogRead_left_upload = 0;
            for(int i=0;i<5;++i){
                temp_analogRead_right_upload += analogRead(DETECTOR_RIGHT);
                temp_analogRead_left_upload += analogRead(DETECTOR_LEFT);
            }
            // temp_analogRead_right_upload = temp_analogRead_right_upload/5;
            // temp_analogRead_left_upload = temp_analogRead_left_upload/5;
        
            // temp_analogRead_right_upload = 0;
            // temp_analogRead_left_upload = 0;
            // for(int i=0;i<5;++i){
            //     temp_analogRead_right_upload += analogRead(DETECTOR_RIGHT);
            //     temp_analogRead_left_upload += analogRead(DETECTOR_LEFT);
            // }
            // temp_analogRead_right_upload = temp_analogRead_right_upload/5;
            // temp_analogRead_left_upload = temp_analogRead_left_upload/5;
            stationary_distance_left = temp_analogRead_left_upload/5;
            stationary_distance_right = temp_analogRead_right_upload/5;
            detect_enemy_two_side_can_or_not_remember_the_distance = CAN_NOT_REMEMBER_DISTANCE;
        }else{
            uploadDetect();
        }
        
        // if(last_detect_right-temp_analogRead_right_upload>MIN_DETECT_TO_90_ENEMY_JUDGE && temp_analogRead_right_upload+temp_analogRead_left_upload<1100){
        //     turnRightPosition90();
        //     // delay(100);
        //     // delay(100);//122333

        //     uploadDetect();
        // }else{
            // if(temp_analogRead_right_upload<NO_SIGNAL_VALUE){
            //     //uploadDetect();
            //     last_detect_right = temp_analogRead_right_upload;
                // Serial.print(last_detect_right);
            // }
            // }else{
            //     last_detect_right = 0;
            // }
        // }

        // if(last_detect_left-temp_analogRead_left_upload>MIN_DETECT_TO_90_ENEMY_JUDGE && temp_analogRead_right_upload+temp_analogRead_left_upload<1100){
        //     turnLeftPositon90();
        //     // delay(100);
        //     // delay(100);//122333

        //     uploadDetect();
        // }else{
            // if(temp_analogRead_left_upload<NO_SIGNAL_VALUE){
            //     last_detect_left = temp_analogRead_left_upload;
                // Serial.println(last_detect_left);

            // }
            // }else{
            //     last_detect_left = 0;
            // }
        // }
    // }
}

void uploadDetectForce(){
    temp_analogRead_right_upload = 0;
    temp_analogRead_left_upload = 0;
    for(int i=0;i<5;++i){
        temp_analogRead_right_upload += analogRead(DETECTOR_RIGHT);
        temp_analogRead_left_upload += analogRead(DETECTOR_LEFT);
    }
    // temp_analogRead_right_upload = temp_analogRead_right_upload/5;
    // temp_analogRead_left_upload = temp_analogRead_left_upload/5;

    // temp_analogRead_right_upload = 0;
    // temp_analogRead_left_upload = 0;
    // for(int i=0;i<5;++i){
    //     temp_analogRead_right_upload += analogRead(DETECTOR_RIGHT);
    //     temp_analogRead_left_upload += analogRead(DETECTOR_LEFT);
    // }
    // temp_analogRead_right_upload = temp_analogRead_right_upload/5;
    // temp_analogRead_left_upload = temp_analogRead_left_upload/5;
    stationary_distance_left = temp_analogRead_left_upload/5;
    stationary_distance_right = temp_analogRead_right_upload/5;
}

// long time_//检查点：2019年9月6日11点36分（已更新）
//void goBack(){//旧
//后退函数，将敌人推下去后返回防守位置//检查点：2019年9月5日17点56分（已更新）
void aftertheEnemyDownAndReturnToTheSideOfTheField(){
    roboclaw.ResetEncoders(ADDRESS);
    // roboclaw.ForwardM1(ADDRESS, speed);
    // roboclaw.BackwardM1(ADDRESS,speed);
    // roboclaw.ForwardM2(ADDRESS, speed);
    // roboclaw.BackwardM2(ADDRESS,speed);
    // long time_temp = millis();
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 1000, DECCEL, -1000, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 1000, DECCEL, -1000, 0);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 4000, DECCEL, -4570, 0);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 4000, DECCEL, -4570, 0);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 1000, DECCEL, -5570, 0);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 1000, DECCEL, -5570, 0);
    // while(roboclaw.ReadEncM1(ADDRESS)<5570-ERROR_POSITION && roboclaw.ReadEncM2(ADDRESS)<5570-ERROR_POSITION){

    // }
    // Serial.print(millis()-time_temp);
    delay(3000);
    // stop();
    // delay(1000000);
    // while()
    // do{
    //     /* code */
    //     int speed_back_to_field = 0;
    //     long last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
    //     long last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
    //     for(int i=0;i<9;++i){
    //         last_detect_back_left += analogRead(DETECTOR_BACK_LEFT);
    //         last_detect_back_right += analogRead(DETECTOR_BACK_RIGHT);
    //     }
    //     last_detect_back_left = last_detect_back_left/10;
    //     last_detect_back_right = last_detect_back_right/10;
    //     if(last_detect_back_left>700 || last_detect_back_right>700){
    //         // roboclaw.ForwardM1(ADDRESS, speed);
    //         roboclaw.BackwardM1(ADDRESS,30);
    //         // roboclaw.ForwardM2(ADDRESS, speed);
    //         roboclaw.BackwardM2(ADDRESS,30);
    //         continue;
    //     }else if(last_detect_back_left>470 && last_detect_back_right>470){
    //         speed_back_to_field = 50;
    //     }else if(last_detect_back_left<417 || last_detect_back_right<417){
    //         // // roboclaw.ForwardM1(ADDRESS, speed);
    //         // roboclaw.BackwardM1(ADDRESS,15);
    //         // // roboclaw.ForwardM2(ADDRESS, speed);
    //         // roboclaw.BackwardM2(ADDRESS,15);
    //         stop();
    //         uploadDetect();
    //         delay(30000);
    //         return;
    //     }else if(last_detect_back_left<470 || last_detect_back_right<470){
    //         // roboclaw.ForwardM1(ADDRESS, speed);
    //         // roboclaw.BackwardM1(ADDRESS,15);
    //         // roboclaw.ForwardM2(ADDRESS, speed);
    //         // roboclaw.BackwardM2(ADDRESS,15);
    //         speed_back_to_field = 15;
    //     }
    //     if(last_detect_back_left-last_detect_back_right>10){
    //         // roboclaw.ForwardM1(ADDRESS, speed);
    //         roboclaw.BackwardM1(ADDRESS,speed_back_to_field+10);
    //         // roboclaw.ForwardM2(ADDRESS, speed);
    //         roboclaw.BackwardM2(ADDRESS,speed_back_to_field);
    //     }else if(last_detect_back_right-last_detect_back_left>10){
    //         // roboclaw.ForwardM1(ADDRESS, speed);
    //         roboclaw.BackwardM1(ADDRESS,speed_back_to_field);
    //         // roboclaw.ForwardM2(ADDRESS, speed);
    //         roboclaw.BackwardM2(ADDRESS,speed_back_to_field+10);
    //     }else{
    //         roboclaw.BackwardM1(ADDRESS,speed_back_to_field);
    //         // roboclaw.ForwardM2(ADDRESS, speed);
    //         roboclaw.BackwardM2(ADDRESS,speed_back_to_field);
    //     }
        
        

    //     // }else if
        
    // } while (1);
    
    
    // if()

    // /
    // /
    // roboclaw.ForwardM1(ADDRESS, speed);
    // roboclaw.BackwardM1(ADDRESS,speed);
    // roboclaw.ForwardM2(ADDRESS, speed);
    // roboclaw.BackwardM2(ADDRESS,speed);
    // if(analogRead(DETECTOR_LEFT)<){
    //     turnLeftPosition(4*TURN_SLOW_POSITION);
    // }else if(analogRead(DETECTOR_RIGHT)<){
    //     turnRightPosition(4*TURN_SLOW_POSITION);
    // }
    // roboclaw.ResetEncoders(ADDRESS);
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
        // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2500, DECCEL, -5570, 1);
        // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2500, DECCEL, -5570, 1);
        // // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2500, DECCEL1, -5570, ACCEL2, 2500, DECCEL2, -5570, 1);
        // delay(3000);
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

//检查点：2019年9月2日20点52分（已更新）
//判断是否在台下，是另一种判断，防止误将边界当成敌人
//2019年9月2日想法：当前面传感器检测到的时候，测定两侧和后面的值，应该会有所不同（已废弃）
/**
 * 更新：想到另一种判断方法，前方传感器1分，两侧前端2分，两侧后端4分，这样可以区分是哪几个-
 * 传感器检测到，然后根据不同的情况进行区别设计
 */
void determineIfItIsUnderTheStage(){
    // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_YES && determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_YES){
    //     judge_if_think_enemy_is_edge = 0;
    //     decidedTheCarHadFallenOff();
    //     return;
    // }
    int temp_times = 0;
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_YES){
        temp_times++;
    }
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_YES){
        temp_times += 4;
    }
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT_MORE)==DETECT_YES){
        temp_times += 2;
    }
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_YES){
        temp_times += 4;
    }
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT_MORE)==DETECT_YES){
        temp_times += 2;
    }

    ////////////////////////////
    if(temp_times>=8){
        judge_if_think_enemy_is_edge = 0;
        decidedTheCarHadFallenOff();
        return;
        // digitalWrite(13,HIGH);
    }else if(temp_times==7){
    //     long temp_detect_front_to_judge_if_under_stage = 0;
    // long temp_detect_LFM_to_judge_if_under_stage = 0;
    // long temp_detect_RFM_to_judge_if_under_stage = 0;
    // long temp_detect_LF_to_judge_if_under_stage = 0;
    // long temp_detect_RF_to_judge_if_under_stage = 0;
    //     for(int i=0;i<20;++i){
    //         temp_detect_front_to_judge_if_under_stage += analogRead(DETECTOR_FRONT);
    //         temp_detect_LFM_to_judge_if_under_stage += analogRead(DETECTOR_LEFT_FRONT_MORE);
    //         temp_detect_RFM_to_judge_if_under_stage += analogRead(DETECTOR_RIGHT_FRONT_MORE);
    //         temp_detect_LF_to_judge_if_under_stage += analogRead(DETECTOR_LEFT_FRONT);
    //         temp_detect_RF_to_judge_if_under_stage += analogRead(DETECTOR_RIGHT_FRONT);
    //     }
    //     temp_detect_front_to_judge_if_under_stage = temp_detect_front_to_judge_if_under_stage/20;
    //     temp_detect_LFM_to_judge_if_under_stage = temp_detect_LFM_to_judge_if_under_stage/20;
    //     temp_detect_RFM_to_judge_if_under_stage = temp_detect_RFM_to_judge_if_under_stage/20;
    //     temp_detect_LF_to_judge_if_under_stage = temp_detect_LF_to_judge_if_under_stage/20;
        //     temp_detect_RF_to_judge_if_under_stage = temp_detect_RF_to_judge_if_under_stage/20;
        judge_if_think_enemy_is_edge = 0;
        if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_YES){
            turnLeftPosition(TURN_LEFT_FRONT_MORE);
        }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_YES){
            turnRightPosition(TURN_RIGHT_FRONT_MORE);
        }
        // digitalWrite(13,LOW);

    }else if(temp_times==5){
        long temp_detect_front_to_judge_if_under_stage = 0;
    // long temp_detect_LFM_to_judge_if_under_stage = 0;
    // long temp_detect_RFM_to_judge_if_under_stage = 0;
    // long temp_detect_LF_to_judge_if_under_stage = 0;
    // long temp_detect_RF_to_judge_if_under_stage = 0;
        for(int i=0;i<20;++i){
            temp_detect_front_to_judge_if_under_stage += analogRead(DETECTOR_FRONT);
            // temp_detect_LFM_to_judge_if_under_stage += analogRead(DETECTOR_LEFT_FRONT_MORE);
            // temp_detect_RFM_to_judge_if_under_stage += analogRead(DETECTOR_RIGHT_FRONT_MORE);
            // temp_detect_LF_to_judge_if_under_stage += analogRead(DETECTOR_LEFT_FRONT);
            // temp_detect_RF_to_judge_if_under_stage += analogRead(DETECTOR_RIGHT_FRONT);
        }
        temp_detect_front_to_judge_if_under_stage = temp_detect_front_to_judge_if_under_stage/20;
        if(temp_detect_front_to_judge_if_under_stage>=317){
            judge_if_think_enemy_is_edge = 0;
            decidedTheCarHadFallenOff();
            return;
        // digitalWrite(13,HIGH);

        }else{
            // digitalWrite(13,LOW);
            if(judge_if_think_enemy_is_edge==0){
                time_if_think_enemy_is_edge = millis();
                judge_if_think_enemy_is_edge = 1;
            }
            if(millis()-time_if_think_enemy_is_edge>2000 && judge_if_think_enemy_is_edge==1){
                judge_if_think_enemy_is_edge = 0;
                decidedTheCarHadFallenOff();
                return;
            }
        }
        // temp_detect_LFM_to_judge_if_under_stage = temp_detect_LFM_to_judge_if_under_stage/20;
        // temp_detect_RFM_to_judge_if_under_stage = temp_detect_RFM_to_judge_if_under_stage/20;
        // temp_detect_LF_to_judge_if_under_stage = temp_detect_LF_to_judge_if_under_stage/20;
        // temp_detect_RF_to_judge_if_under_stage = temp_detect_RF_to_judge_if_under_stage/20;
        

        // if(millis()-time_if_think_enemy_is_edge>1000){
            
        // }
    // }
    }else{
        // digitalWrite(13,LOW);
        judge_if_think_enemy_is_edge = 0;
    }
        

    // Serial.println(temp_times);
    // delay(1000);
}

//void detectEnemySide(){//旧
/**
 * 侧前方检测敌方函数
 * 会向那个方向进行转向
 * 刷新上一次物体方向
 * 进入前方探测器警戒模式
 */
void sideFrontToDetectIfThereAreEnemies(){
    determineIfItIsUnderTheStage();//台下判断
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_YES){
        if(enemy_on_front_go_front_only_once==CAN_GO_FRONT_TO_ENEMY){
            enemy_on_front_go_front_only_once = CAN_NOT_GO_FRONT_TO_ENEMY;
            roboclaw.ForwardM1(ADDRESS, 31);
            // roboclaw.BackwardM1(ADDRESS,speed);
            roboclaw.ForwardM2(ADDRESS, 31);
            // roboclaw.BackwardM2(ADDRESS,speed);
            // roboclaw.ResetEncoders(ADDRESS);
            // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2000, DECCEL, 7*GO_SLOW_POSITION, 1);
            // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2000, DECCEL, 7*GO_SLOW_POSITION, 1);
            // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, , ACCEL2, 8000, DECCEL2, , 1);
            // for(;roboclaw.ReadEncM1(ADDRESS)<GO_SLOW_POSITION-ERROR_POSITION;){}
            //因为这个函数是攻击前的动作，不宜用编码器的值，以放敌人在这个途中-
            //就相撞而无法达到指定位置，延时已经过测试
            delay(170);

            // stopStuck();
            stop();
            // roboclaw.ResetEncoders(ADDRESS);
            roboclaw.SetEncM1(ADDRESS,9000);
            roboclaw.SetEncM2(ADDRESS,9000);
            // delay(100000);
        }

        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        if(grayScaleSensorDetect()==CLOSE_TO_EDGE){
            delay(500);
            if(grayScaleSensorDetect()==CLOSE_TO_EDGE){
                // turnLeftPositionSlowly
                roboclaw.ResetEncoders(ADDRESS);
                roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, TURN_RIGHT_180, 1);
                roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, -TURN_RIGHT_180, 1);
                while(roboclaw.ReadEncM1(ADDRESS)<TURN_RIGHT_180-ERROR_POSITION){
                }
                stop();
                return;
            }
        }
        prepareforAttack();
        //return;
    }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_YES){
        turnLeftPosition(TURN_LEFT_FRONT);
        // delay(300);
        last_detect_side = DETECT_LAST_LEFT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        // value_of_turns += 570;
        enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
        //delay(100);
        //lostEnemyAlert();
    }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_YES){
        turnRightPosition(TURN_RIGHT_FRONT);
        // delay(300);
        last_detect_side = DETECT_LAST_RIGHT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        // value_of_turns -= 570;
        enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
        //delay(100);
        //lostEnemyAlert();
    }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT_MORE)==DETECT_YES){
        turnLeftPosition(TURN_LEFT_FRONT_MORE);
        last_detect_side = DETECT_LAST_LEFT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        // value_of_turns += 250;
        enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
    }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT_MORE)==DETECT_YES){
        turnRightPosition(TURN_RIGHT_FRONT_MORE);
        last_detect_side = DETECT_LAST_RIGHT;
        complementary_time_judge = COMPLEMENTARY_TIME_NO;
        detect_if_detected = DETECT_IF_DETECTED_YES;
        timing = ENABLE_TO_TIMING;
        // value_of_turns -= 240;
        enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
    }
    // return;
}

//void BackToTheDefensivePosition(){//旧
//后退至远处的边线附近
void detectsWhetherTheEdgeIsReachedWhenPushingEnemy(int mode){
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

    //一次对齐//////////////////////////////////////////////////////////////////
    long temp_time_gray_sensor = millis();
    
    do{
        if(millis()-temp_time_gray_sensor>10000){
            return;
        }
        if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_NO && digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_NO){
            // roboclaw.ResetEncoders(ADDRESS);
            // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
            // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
            // delay(150);
            // roboclaw.ForwardM1(ADDRESS, 10);
            roboclaw.BackwardM1(ADDRESS,20);
            // roboclaw.ForwardM2(ADDRESS, speed)
            roboclaw.BackwardM2(ADDRESS,20);
            //stop();
        }else if(digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_YES && digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_NO){
            // roboclaw.ResetEncoders(ADDRESS);
            // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
            // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
            // delay(150);
            roboclaw.ForwardM1(ADDRESS, 10);
            // roboclaw.BackwardM1(ADDRESS,10)
            // roboclaw.ForwardM2(ADDRESS, speed)
            roboclaw.BackwardM2(ADDRESS,20);
            //stop();
        }else if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_NO){
            // roboclaw.ResetEncoders(ADDRESS);
            // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
            // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
            // delay(150);
            // roboclaw.ForwardM1(ADDRESS, 10);
            roboclaw.BackwardM1(ADDRESS,20);
            roboclaw.ForwardM2(ADDRESS, 10);
            // roboclaw.BackwardM2(ADDRESS,0);
        }else if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_YES){
            //二次对齐////////////////////////////////////////////////////////////////////////
            do{
                if(millis()-temp_time_gray_sensor>10000){
                    return;
                }
                if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_YES){
                    // roboclaw.ResetEncoders(ADDRESS);
                    // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                    // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
                    // delay(150);
                    if(mode==MODE_PUSHING_ENEMY){
                        roboclaw.ForwardM1(ADDRESS, 20);
                        // roboclaw.BackwardM1(ADDRESS,20);
                        roboclaw.ForwardM2(ADDRESS, 20); 
                    }else{
                        roboclaw.ForwardM1(ADDRESS, 10);
                        // roboclaw.BackwardM1(ADDRESS,20);
                        roboclaw.ForwardM2(ADDRESS, 10); 
                    }
                    
                    // roboclaw.BackwardM2(ADDRESS,20);
                    //stop();
                }else if(digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_YES && digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_NO){
                    // roboclaw.ResetEncoders(ADDRESS);
                    // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                    // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
                    // delay(150);
                    roboclaw.ForwardM1(ADDRESS, 20);
                    // roboclaw.BackwardM1(ADDRESS,10)
                    // roboclaw.ForwardM2(ADDRESS, speed)
                    roboclaw.BackwardM2(ADDRESS,0);
                    //stop();
                }else if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_NO){
                    // roboclaw.ResetEncoders(ADDRESS);
                    // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                    // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                    // delay(150);
                    // roboclaw.ForwardM1(ADDRESS, 10);
                    roboclaw.BackwardM1(ADDRESS,0);
                    roboclaw.ForwardM2(ADDRESS, 20);
                    // roboclaw.BackwardM2(ADDRESS,0);
                }else if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_NO && digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_NO){
                    //三次对齐////////////////////////////////////////////////////////////////////////
                    do{
                        if(millis()-temp_time_gray_sensor>10000){
                            return;
                        }
                        if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_NO && digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_NO){
                            // roboclaw.ResetEncoders(ADDRESS);
                            // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                            // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
                            // delay(150);
                            // roboclaw.ForwardM1(ADDRESS, 10);
                            roboclaw.BackwardM1(ADDRESS,20);
                            // roboclaw.ForwardM2(ADDRESS, speed)
                            roboclaw.BackwardM2(ADDRESS,20);
                            //stop();
                        }else if(digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_YES && digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_NO){
                            // roboclaw.ResetEncoders(ADDRESS);
                            // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                            // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
                            // delay(150);
                            roboclaw.ForwardM1(ADDRESS, 0);
                            // roboclaw.BackwardM1(ADDRESS,10)
                            // roboclaw.ForwardM2(ADDRESS, speed)
                            roboclaw.BackwardM2(ADDRESS,20);
                            //stop();
                        }else if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_NO){
                            // roboclaw.ResetEncoders(ADDRESS);
                            // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                            // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                            // delay(150);
                            // roboclaw.ForwardM1(ADDRESS, 10);
                            roboclaw.BackwardM1(ADDRESS,20);
                            roboclaw.ForwardM2(ADDRESS, 0);
                            // roboclaw.BackwardM2(ADDRESS,0);
                        }else if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_YES){
                            
                            // digitalWrite(13,HIGH);
                            // stop();
                            // delay(100000);
                            // digitalWrite(13,HIGH);
                            // stop();
                            // delay(100000);
                            aftertheEnemyDownAndReturnToTheSideOfTheField();
                            // delay(100);//122333

                            // uploadDetect();
                            // //stop();
                            return;
                            
                        }
                                // }else{
                                //     digitalWrite(13,LOW);
                                // }
                                


                                // if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_YES){
                                //     roboclaw.ResetEncoders(ADDRESS);
                                //     roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                                //     roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
                                //     delay(150);
                                //     //stop();
                                // }else if(digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_YES){
                                //     roboclaw.ResetEncoders(ADDRESS);
                                //     roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                                //     roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
                                //     delay(150);
                                //     //stop();
                                // }else if(digitalRead(GRAYSCALE_SENSOT_RIGHT)+digitalRead(GRAYSCALE_SENSOR_LEFT)==2){
                                //     roboclaw.ResetEncoders(ADDRESS);
                                //     roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                                //     roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                                //     delay(150);
                                // }
                                // if(digitalRead(GRAYSCALE_SENSOT_RIGHT)+digitalRead(GRAYSCALE_SENSOR_LEFT)==0){
                                //     // alignWithWalls()

                                //     // if(analogRead(DETECTOR_BACK_LEFT)-analogRead(DETECTOR_BACK_RIGHT)>OFFSET_THRESHOLD_ADJUST_SLOW){
                                //     //     turnLeftPosition(TURN_SLOW_POSITION);
                                //     // }else if(analogRead(DETECTOR_BACK_RIGHT)-analogRead(DETECTOR_BACK_LEFT)>OFFSET_THRESHOLD_ADJUST_SLOW){
                                //     //     turnRightPosition(TURN_SLOW_POSITION);
                                //     // }else{




                                //     for(int i=0;i<7;){
                                //         int last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
                                //         int last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
                                //         if(last_detect_back_left-last_detect_back_right>OFFSET_THRESHOLD_ADJUST_SLOW){
                                //             turnLeftPosition(TURN_SLOW_POSITION);
                                //         }else if(last_detect_back_right-last_detect_back_left>OFFSET_THRESHOLD_ADJUST_SLOW){
                                //             turnRightPosition(TURN_SLOW_POSITION);
                                //         }else{
                                //             ++i;
                                //         }
                                //     }
                                //     aftertheEnemyDownAndReturnToTheSideOfTheField();
                                //     uploadDetect();
                                //     //stop();
                                //     return;
                                // }
                                //if(digitalRead(GRAYSCALE_SENSOR_PIN2)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_PIN1)==DETECT_NO)
                    }while(1);
                }
            }while(1);
            
        }
                // }else{
                //     digitalWrite(13,LOW);
                // }
                


                // if(digitalRead(GRAYSCALE_SENSOT_RIGHT)==DETECT_YES){
                //     roboclaw.ResetEncoders(ADDRESS);
                //     roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                //     roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
                //     delay(150);
                //     //stop();
                // }else if(digitalRead(GRAYSCALE_SENSOR_LEFT)==DETECT_YES){
                //     roboclaw.ResetEncoders(ADDRESS);
                //     roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                //     roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -TURN_SLOW_POSITION+15, 1);
                //     delay(150);
                //     //stop();
                // }else if(digitalRead(GRAYSCALE_SENSOT_RIGHT)+digitalRead(GRAYSCALE_SENSOR_LEFT)==2){
                //     roboclaw.ResetEncoders(ADDRESS);
                //     roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                //     roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -(2*TURN_SLOW_POSITION), 1);
                //     delay(150);
                // }
                // if(digitalRead(GRAYSCALE_SENSOT_RIGHT)+digitalRead(GRAYSCALE_SENSOR_LEFT)==0){
                //     // alignWithWalls()

                //     // if(analogRead(DETECTOR_BACK_LEFT)-analogRead(DETECTOR_BACK_RIGHT)>OFFSET_THRESHOLD_ADJUST_SLOW){
                //     //     turnLeftPosition(TURN_SLOW_POSITION);
                //     // }else if(analogRead(DETECTOR_BACK_RIGHT)-analogRead(DETECTOR_BACK_LEFT)>OFFSET_THRESHOLD_ADJUST_SLOW){
                //     //     turnRightPosition(TURN_SLOW_POSITION);
                //     // }else{




                //     for(int i=0;i<7;){
                //         int last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
                //         int last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
                //         if(last_detect_back_left-last_detect_back_right>OFFSET_THRESHOLD_ADJUST_SLOW){
                //             turnLeftPosition(TURN_SLOW_POSITION);
                //         }else if(last_detect_back_right-last_detect_back_left>OFFSET_THRESHOLD_ADJUST_SLOW){
                //             turnRightPosition(TURN_SLOW_POSITION);
                //         }else{
                //             ++i;
                //         }
                //     }
                //     aftertheEnemyDownAndReturnToTheSideOfTheField();
                //     uploadDetect();
                //     //stop();
                //     return;
                // }
                //if(digitalRead(GRAYSCALE_SENSOR_PIN2)==DETECT_YES && digitalRead(GRAYSCALE_SENSOR_PIN1)==DETECT_NO)
    }while(1);
    //stop();
    //delay(10000)
    //goBackOneStep();
}

//前探测器探测函数
void lostEnemy(){
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
    //     prepareforAttack();
    //}else 
    if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_NO && timing==ENABLE_TO_TIMING){
        if(complementary_time_judge==COMPLEMENTARY_TIME_NO){
            complementary_time = millis();
            complementary_time_judge = COMPLEMENTARY_TIME_YES;
        }

        if(millis()-complementary_time>COMPLEMENTARY_TIME_DELAY && complementary_time_judge==COMPLEMENTARY_TIME_YES){
            complementary_time_judge = COMPLEMENTARY_TIME_NO;
            detect_if_detected = DETECT_IF_DETECTED_NO;
            timing = NOT_ENABLE_TO_TIMING;
            enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
            long last_detect_back_left = 0;
            long last_detect_back_right = 0;
            detect_enemy_two_side_can_or_not_remember_the_distance = CAN_REMEMBER_DISTANCE;
            //uploadDetect();
            //return;
            // if(value_of_turns%2==0){
            //     last_detect_side = DETECT_LAST_FRONT;
            //     uploadDetect();
            //     value_of_turns = 0;
            //     return;
            // }else{
                switch (last_detect_side){
                // case DETECT_LAST_FRONT:
                //     return;
                //     break;
                case DETECT_LAST_LEFT:
                    // roboclaw.ForwardM1(ADDRESS, 10);
                    // long last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
                    // long last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
                    do{
                        /* code */
                        last_detect_back_left = 0;
                        last_detect_back_right = 0;
                        for(int i=0;i<10;++i){
                            last_detect_back_left += analogRead(DETECTOR_BACK_LEFT);
                            last_detect_back_right += analogRead(DETECTOR_BACK_RIGHT);
                        }
                        last_detect_back_left = last_detect_back_left/10;
                        last_detect_back_right = last_detect_back_right/10;
                        roboclaw.BackwardM1(ADDRESS,23);
                        roboclaw.ForwardM2(ADDRESS, 23);
                    } while (last_detect_back_left-last_detect_back_right>LOST_ENEMY_TO_TURN_THE_COMPENSATES_BETWEEN_TWO_BACK_DETECTOR || last_detect_back_left+last_detect_back_right>1800);
                    
                    
                    // while (){
                    //     /* code */
                        
                    // }
                    stop();
                    
                    // roboclaw.BackwardM2(ADDRESS,10);
                    // turnLeftPosition(abs(value_of_turns%TURN_LEFT_POSITION_90));
                    
                    last_detect_side = DETECT_LAST_FRONT;
                    // uploadDetect();
                    // value_of_turns = 0;
                    return;
                    //break;
                case DETECT_LAST_RIGHT:
                    do{
                        /* code */
                        last_detect_back_left = 0;
                        last_detect_back_right = 0;
                        for(int i=0;i<10;++i){
                            last_detect_back_left += analogRead(DETECTOR_BACK_LEFT);
                            last_detect_back_right += analogRead(DETECTOR_BACK_RIGHT);
                        }
                        last_detect_back_left = last_detect_back_left/10;
                        last_detect_back_right = last_detect_back_right/10;
                        roboclaw.ForwardM1(ADDRESS, 23);
                        // roboclaw.BackwardM1(address,speed);
                        // roboclaw.ForwardM2(address, speed);
                        roboclaw.BackwardM2(ADDRESS,23);
                    } while (last_detect_back_right-last_detect_back_left>LOST_ENEMY_TO_TURN_THE_COMPENSATES_BETWEEN_TWO_BACK_DETECTOR || last_detect_back_left+last_detect_back_right>1800);
                
                    // last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
                    // last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
                    

                    // while (){
                    //     /* code */
                        
                    // }
                    stop();
                    // turnRightPosition(TURN_RIGHT_POSITION_90-abs(value_of_turns%TURN_RIGHT_POSITION_90));
                    last_detect_side = DETECT_LAST_FRONT;
                    // uploadDetect();
                    // value_of_turns = 0;
                    return;
                    //break;
                }
                //value_of_turns = 0;
            // }
        }
    }    //}
}

//准备攻击()
void prepareforAttack(){
    //两者平时大概在-500到+500左右，受到推力后大概在2000+
    // int16_t pwm1;
    // int16_t pwm2;
    // // gofront(GO_SPEED_ATTACK-5);
    // // moveALittleForward();
    // // roboclaw.ResetEncoders(ADDRESS);
    // // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, 3*GO_SLOW_POSITION, ACCEL2, 8000, DECCEL2, 3*GO_SLOW_POSITION, 1);
    // // for(;roboclaw.ReadEncM1(ADDRESS)<GO_SLOW_POSITION-ERROR_POSITION;){}
    // // delay(150);
    // stopStuck();
    // roboclaw.ReadPWMs(ADDRESS,pwm1,pwm2);

    //结合探测器函数中设置的值
    if(roboclaw.ReadEncM1(ADDRESS)<(9000-50) || roboclaw.ReadEncM2(ADDRESS)<(9000-50)){
    // if(analogRead(DETECTOR_FRONT)>=470){//
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
        //当车子前方被抬起来了以后，会以一个比较慢的速度前进2s，这个变量就是负责锁定这个功能，0为否，1为是
        int temp_move_slow_to_prevent_crash_to_the_stage = 0;//122333
        long temp_time_move_slow_delay = 0;
        while(1){
            if(temp_move_slow_to_prevent_crash_to_the_stage==1){
                roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, ATTACK_SPEED-900, DECCEL, 699999, 1);
                roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, ATTACK_SPEED-900, DECCEL, 699999, 1);
                if(millis()-temp_time_move_slow_delay>2000){
                    // break;
                    temp_move_slow_to_prevent_crash_to_the_stage = 0;
                }
            }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_YES){
                roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, ATTACK_SPEED, DECCEL, 699999, 1);
                roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, ATTACK_SPEED+1300, DECCEL, 699999, 1);

            }else if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_YES){
                roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, ATTACK_SPEED+1300, DECCEL, 699999, 1);
                roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, ATTACK_SPEED, DECCEL, 699999, 1);

            }else if(analogRead(DETECTOR_LEFT_FRONT_MORE)-analogRead(DETECTOR_RIGHT_FRONT_MORE)>150){
                // goleft(GO_SPEED_ATTACK,7);
                roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, ATTACK_SPEED, DECCEL, 699999, 1);
                roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, ATTACK_SPEED+900, DECCEL, 699999, 1);

                // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1700, DECCEL1, 999999, ACCEL2, 2500, DECCEL2, 999999, 1);
            }else if(analogRead(DETECTOR_RIGHT_FRONT_MORE)-analogRead(DETECTOR_LEFT_FRONT_MORE)>150){
                roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, ATTACK_SPEED+900, DECCEL, 699999, 1);
                roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, ATTACK_SPEED, DECCEL, 699999, 1);

                // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2500, DECCEL1, 999999, ACCEL2, 1700, DECCEL2, 999999, 1);
                // goright(GO_SPEED_ATTACK,7);
            // }else
            }else{
                attack();
            }

            if(grayScaleSensorDetect()==CLOSE_TO_EDGE){

                stop();
                temp_move_slow_to_prevent_crash_to_the_stage = 1;
                // stopStuck();//122333
                delay(500);//122333
                if(analogRead(DETECTOR_BACK_LEFT)<PREVENT_REAR_BACK_VALUE || analogRead(DETECTOR_BACK_RIGHT)<PREVENT_REAR_BACK_VALUE){
                    preventRearBackMove();
                    continue;
                }
                
                if(grayScaleSensorDetect()==CLOSE_TO_EDGE){
                    break;
                }

                if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_NO && determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT_MORE)==DETECT_NO && determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT_MORE)==DETECT_NO && determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_NO && determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_NO){
                    
                    // enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
                    // judge_if_think_enemy_is_edge = 0;
                    // // stopStuck();
                    // detectsWhetherTheEdgeIsReachedWhenPushingEnemy(); 
                    // uploadDetect(); 

                    // return;
                    // break;
                    roboclaw.ForwardM1(ADDRESS, 15);
                    // roboclaw.BackwardM1(ADDRESS,speed);
                    roboclaw.ForwardM2(ADDRESS, 15);
                    long temp_time_attack = millis();
                    while(grayScaleSensorDetect()==DETECT_YES){
                        if(millis()-temp_time_attack>4000){
                            return;
                        }
                    }
                    stop();
                    // roboclaw.BackwardM2(ADDRESS,speed);
                    enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
                    judge_if_think_enemy_is_edge = 0;
                    // stopStuck();
                    detectsWhetherTheEdgeIsReachedWhenPushingEnemy(MODE_PUSHING_ENEMY); 
                    // uploadDetect(); 
                    return;
                }
            }
            

            // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_NO && determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT_MORE)==DETECT_NO && determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT_MORE)==DETECT_NO && determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_NO && determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_NO){
            //     // for(;;){
            //     //     int speed_back_to_field = 0;
            //     //     long last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
            //     //     long last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
            //     //     for(int i=0;i<9;++i){
            //     //         last_detect_back_left += analogRead(DETECTOR_BACK_LEFT);
            //     //         last_detect_back_right += analogRead(DETECTOR_BACK_RIGHT);
            //     //     }
            //     //     last_detect_back_left = last_detect_back_left/10;
            //     //     last_detect_back_right = last_detect_back_right/10;
            //     //     if(last_detect_back_left>700 || last_detect_back_right>700){
            //     //         // roboclaw.ForwardM1(ADDRESS, speed);
            //     //         roboclaw.BackwardM1(ADDRESS,30);
            //     //         // roboclaw.ForwardM2(ADDRESS, speed);
            //     //         roboclaw.BackwardM2(ADDRESS,30);
            //     //         continue;
            //     //     }else if(last_detect_back_left>470 && last_detect_back_right>470){
            //     //         speed_back_to_field = 50;
            //     //     }else if(last_detect_back_left<417 || last_detect_back_right<417){
            //     //         // // roboclaw.ForwardM1(ADDRESS, speed);
            //     //         // roboclaw.BackwardM1(ADDRESS,15);
            //     //         // // roboclaw.ForwardM2(ADDRESS, speed);
            //     //         // roboclaw.BackwardM2(ADDRESS,15);
            //     //         stop();
            //     //         uploadDetect();
            //     //         // delay(30000);
            //     //         return;
            //     //     }else if(last_detect_back_left<470 || last_detect_back_right<470){
            //     //         // roboclaw.ForwardM1(ADDRESS, speed);
            //     //         // roboclaw.BackwardM1(ADDRESS,15);
            //     //         // roboclaw.ForwardM2(ADDRESS, speed);
            //     //         // roboclaw.BackwardM2(ADDRESS,15);
            //     //         speed_back_to_field = 15;
            //     //     }

            //     //     if(last_detect_back_left-last_detect_back_right>10){
            //     //         // roboclaw.ForwardM1(ADDRESS, speed);
            //     //         roboclaw.BackwardM1(ADDRESS,speed_back_to_field+10);
            //     //         // roboclaw.ForwardM2(ADDRESS, speed);
            //     //         roboclaw.BackwardM2(ADDRESS,speed_back_to_field);
            //     //     }else if(last_detect_back_right-last_detect_back_left>10){
            //     //         // roboclaw.ForwardM1(ADDRESS, speed);
            //     //         roboclaw.BackwardM1(ADDRESS,speed_back_to_field);
            //     //         // roboclaw.ForwardM2(ADDRESS, speed);
            //     //         roboclaw.BackwardM2(ADDRESS,speed_back_to_field+10);
            //     //     }else{
            //     //         roboclaw.BackwardM1(ADDRESS,speed_back_to_field);
            //     //         // roboclaw.ForwardM2(ADDRESS, speed);
            //     //         roboclaw.BackwardM2(ADDRESS,speed_back_to_field);
            //     //     }
                
        
            //     //     // if(analogRead(DETECTOR_BACK_LEFT)>900 && analogRead(DETECTOR_BACK_A3)>900){
            //     //     //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -2795, ACCEL2, 2000, DECCEL2, -2795, 1);
            //     //     //     delay(50);
            //     //     //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3500, DECCEL1, -2795, ACCEL2, 3500, DECCEL2, -2795, 1);
            //     //     // }else if(analogRead(DETECTOR_BACK_A2)>800 && analogRead(DETECTOR_BACK_A3)>800){
            //     //     //     //roboclaw.ResetEncoders(ADDRESS);
            //     //     //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -2795, ACCEL2, 2000, DECCEL2, -2795, 1);
            //     //     //     delay(50);
            //     //     //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3500, DECCEL1, -2795, ACCEL2, 3500, DECCEL2, -2795, 1);
            //     //     // }else if(analogRead(DETECTOR_BACK_A2)<700 && analogRead(DETECTOR_BACK_A3)<700){
            //     //     //     stop();
            //     //     //     return;
            //     //     // }else if(analogRead(DETECTOR_BACK_A2)<800 && analogRead(DETECTOR_BACK_A3)<800){
            //     //     //     //roboclaw.ResetEncoders(ADDRESS);
            //     //     //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -2795, ACCEL2, 2000, DECCEL2, -2795, 1);
            //     //     // }
            //     //     // if(analogRead(DETECTOR_BACK_A2)<400 || analogRead(DETECTOR_BACK_A3)<400){
            //     //     //     roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 200, DECCEL1, -8000, ACCEL2, 200, DECCEL2, -8000, 1);
            //     //     //     delay(50);
            //     //     //     stop();
            //     //     //     //delay(1000);
            //     //     //     return;
            //     //     // }
            //     //     // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2500, DECCEL, -5570, 1);
            //     //     // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2500, DECCEL, -5570, 1);
            //     //     // // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2500, DECCEL1, -5570, ACCEL2, 2500, DECCEL2, -5570, 1);
            //     //     // delay(3000);
            //     //     // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 3000, DECCEL1, -5590, ACCEL2, 3000, DECCEL2, -5570, 1);
            //     //     // delay(1000);
            //     //     // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2000, DECCEL1, -5590, ACCEL2, 2000, DECCEL2, -5570, 1);
            //     //     // delay(5000);

            //     // }
            //     // dynamicBack();
            //     return;
            // }
        }
        // while(1){
        //     if(grayScaleSensorDetect()==CLOSE_TO_EDGE){
        //         if(analogRead(DETECTOR_BACK_LEFT)<PREVENT_REAR_BACK_VALUE || analogRead(DETECTOR_BACK_RIGHT)<PREVENT_REAR_BACK_VALUE){
        //             preventRearBackMove();
        //             continue;
        //         }
        //         break;
        //     }
        //     if(analogRead(DETECTOR_LEFT_FRONT_MORE)-analogRead(DETECTOR_RIGHT_FRONT_MORE)>150){
        //         // goleft(GO_SPEED_ATTACK,7);
        //         roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 1700, DECCEL, 999999, 1);
        //         roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2500, DECCEL, 999999, 1);
        //         // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 1700, DECCEL1, 999999, ACCEL2, 2500, DECCEL2, 999999, 1);
        //     }else if(analogRead(DETECTOR_RIGHT_FRONT_MORE)-analogRead(DETECTOR_LEFT_FRONT_MORE)>150){
        //         roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2500, DECCEL, 999999, 1);
        //         roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 1700, DECCEL, 999999, 1);
        //         // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 2500, DECCEL1, 999999, ACCEL2, 1700, DECCEL2, 999999, 1);
        //         // goright(GO_SPEED_ATTACK,7);
        //     }else{
        //         attack();
        //     }
            
            
        // }
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
        judge_if_think_enemy_is_edge = 0;
        // stopStuck();
        detectsWhetherTheEdgeIsReachedWhenPushingEnemy(MODE_PUSHING_ENEMY); 
        // uploadDetect(); 
        //delay(4000);
        //stop();
        //}while(1);
    }
}

//被铲起后后退保护程序
void preventRearBackMove(){
    // roboclaw.ResetEncoders(ADDRESS);
    // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, -200, 1);
    // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, -200, 1);
    // // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, -900, ACCEL2, 8000, DECCEL2, -900, 1);
    // delay(300);
    roboclaw.ResetEncoders(ADDRESS);
    roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2500, DECCEL, -1200, 1);
    roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2500, DECCEL, -1200, 1);
    // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, -900, ACCEL2, 8000, DECCEL2, -900, 1);
    delay(617);
    stop();
}


void letUsGo(){
    // backToTouchTheWall();
    // roboclaw.BackwardM1(ADDRESS,20);
    // roboclaw.BackwardM2(ADDRESS,20);
    // delay(1500);
    // stop();
    while(analogRead(DETECTOR_LEFT)>200){
        
    }
    
    // roboclaw.ForwardM1(address, speed);
    // roboclaw.BackwardM1(ADDRESS,10);
    stepBackAndGetOnStage();
    
    // delay(100000);
}

void letUsGo2(){
    //这个是为了可以将车斜着摆放而设计的，可以直接从中间上台
    while(analogRead(DETECTOR_RIGHT)>200){

    }
    roboclaw.BackwardM1(ADDRESS,25);
    roboclaw.BackwardM2(ADDRESS,25);
    delay(300);
    roboclaw.BackwardM1(ADDRESS,17);
    roboclaw.BackwardM2(ADDRESS,17);
    delay(600);
    roboclaw_stage.ResetEncoders(ADDRESS_STAGE);
    //，空地测试可以转一圈，实地测试的时候可能不是一圈，还需要进一步测试（已测试）
    roboclaw_stage.SpeedAccelDeccelPositionM1M2(ADDRESS_STAGE, ACCEL1, STAGE_SPEED, DECCEL1, -STAGE_MOTOR_ONE_ROUND, ACCEL2, STAGE_SPEED, DECCEL2, STAGE_MOTOR_ONE_ROUND, 1);
    delay(STAGE_DELAY);
    // roboclaw.BackwardM1(ADDRESS,30);
    // roboclaw.BackwardM2(ADDRESS,30);
    // delay(400);
    stop();
    if(analogRead(DETECTOR_LEFT)<600){
        roboclaw.ResetEncoders(ADDRESS);
        roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, TURN_RIGHT_180, 1);
        roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, -TURN_RIGHT_180, 1);
        delay(800);
        // turnRightPosition(TURN_RIGHT_180);
    }else{
        roboclaw.ResetEncoders(ADDRESS);
        roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 3000, DECCEL, -TURN_LEFT_180, 1);
        roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 3000, DECCEL, TURN_LEFT_180, 1);
        delay(800);
        // turnLeftPosition(TURN_LEFT_180);
    }
}

//动作组以上--------------------------------------------------------------------------------------------------
//动作组以上--------------------------------------------------------------------------------------------------
//动作组以上--------------------------------------------------------------------------------------------------
//动作组以上--------------------------------------------------------------------------------------------------

void smallDetectTest(){
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
        Serial.print("understage|");
    }
    long temp_detect_front_to_judge_if_under_stage = 0;
    long temp_detect_LFM_to_judge_if_under_stage = 0;
    long temp_detect_RFM_to_judge_if_under_stage = 0;
    long temp_detect_LF_to_judge_if_under_stage = 0;
    long temp_detect_RF_to_judge_if_under_stage = 0;
        for(int i=0;i<20;++i){
            temp_detect_front_to_judge_if_under_stage += analogRead(DETECTOR_FRONT);
            temp_detect_LFM_to_judge_if_under_stage += analogRead(DETECTOR_LEFT_FRONT_MORE);
            temp_detect_RFM_to_judge_if_under_stage += analogRead(DETECTOR_RIGHT_FRONT_MORE);
            temp_detect_LF_to_judge_if_under_stage += analogRead(DETECTOR_LEFT_FRONT);
            temp_detect_RF_to_judge_if_under_stage += analogRead(DETECTOR_RIGHT_FRONT);
        }
        temp_detect_front_to_judge_if_under_stage = temp_detect_front_to_judge_if_under_stage/20;
        temp_detect_LFM_to_judge_if_under_stage = temp_detect_LFM_to_judge_if_under_stage/20;
        temp_detect_RFM_to_judge_if_under_stage = temp_detect_RFM_to_judge_if_under_stage/20;
        temp_detect_LF_to_judge_if_under_stage = temp_detect_LF_to_judge_if_under_stage/20;
        temp_detect_RF_to_judge_if_under_stage = temp_detect_RF_to_judge_if_under_stage/20;
        Serial.print("|front:");
        Serial.print(temp_detect_front_to_judge_if_under_stage);
        Serial.print("|LFM:");
        Serial.print(temp_detect_LFM_to_judge_if_under_stage);
        Serial.print("|RFM:");
        Serial.print(temp_detect_RFM_to_judge_if_under_stage);
        Serial.print("|LF:");
        Serial.print(temp_detect_LF_to_judge_if_under_stage);
        Serial.print("|RF:");
        Serial.print(temp_detect_RF_to_judge_if_under_stage);
        Serial.print("|temps:");
        Serial.print(temp_times);
        Serial.println(" ");
        delay(1000);
        // Serial.print("|right:");
        
    
    // pinMode(13,OUTPUT);
    // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_FRONT)==DETECT_YES){
    //     // digitalWrite(13,HIGH);
    //     Serial.print("  front:yes  ");
    // }
    // // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT)==DETECT_YES){
    // //     // digitalWrite(13,LOW);
    // //     Serial.print("    left:yes    ");
    // // }
    // // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT)==DETECT_YES){
    // //     /* code */
    // //     Serial.print("    right:yes     ");

    // // }
    // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT)==DETECT_YES){
    //     Serial.print(" left front:yes   ");

    // }
    // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT)==DETECT_YES){
    //     Serial.print(" right front:yes  ");

    // }
    // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_LEFT_FRONT_MORE)==DETECT_YES){
    //     Serial.print("  LFM:yes ");

    // }
    // if(determineIfThereIsAnObjectInFrontOfTheSide(DETECTOR_RIGHT_FRONT_MORE)==DETECT_YES){
    //     Serial.print("  RFM:yes  ");

    // }
    // Serial.println(" ");
}

void bigDetectorTest(){
    // Serial.print
    long last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
    long last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
    long last_temp_left = analogRead(DETECTOR_LEFT);
    long last_temp_right = analogRead(DETECTOR_RIGHT);
    for(int i=0;i<9;++i){
        last_detect_back_left += analogRead(DETECTOR_BACK_LEFT);
        last_detect_back_right += analogRead(DETECTOR_BACK_RIGHT);
        last_temp_left += analogRead(DETECTOR_LEFT);
        last_temp_right += analogRead(DETECTOR_RIGHT);
    }
    last_detect_back_left = last_detect_back_left/10;
    last_detect_back_right = last_detect_back_right/10;
    last_temp_left = last_temp_left/10;
    last_temp_right = last_temp_right/10;

    // Serial.print("left:");
    // Serial.print(last_temp_left);

    // Serial.print("     ");

    // Serial.print("right:");
    // Serial.print(last_temp_right);

    // Serial.print("     ");

    // Serial.print("left+right:");
    // Serial.print(last_temp_left+last_temp_right);

    // Serial.print("     ");

    Serial.print("back left:");
    Serial.print(last_detect_back_left);

    Serial.print("    ");

    Serial.print("back right:");
    Serial.print(last_detect_back_right);


    Serial.print("    ");
    Serial.print(last_detect_back_right+last_detect_back_left);
    // Serial.print(last_temp_left);
    Serial.println("     ");
    // Serial.println(roboclaw.ReadEncM1(ADDRESS));
    // 
    // Serial.println(last_detect_back_right);
    // Serial.println(last_detect_back_leftlast_detect_back_right);

    // Serial.print("ba
    
    delay(800);
}
//测试程序
void test(){
    turnLeftPositon90();
    delay(4000);
    turnRightPosition90();
    delay(1000000);
    // long temp = millis();
    // // for(times_detect_real_side=0;times_detect_real_side<TIMES_DETECT_REAL_SIDE_MAX;times_detect_real_side++){
    //        detectTheTwoSidesOfTheRightSideForEnemies();
    //     // }
    //     Serial.print(millis()-temp);
    //     delay(1000000);
    // roboclaw.ForwardM1(ADDRESS, 31);
    //         // roboclaw.BackwardM1(ADDRESS,speed);
    //         roboclaw.ForwardM2(ADDRESS, 31);
    //         // roboclaw.BackwardM2(ADDRESS,speed);
    //         // roboclaw.ResetEncoders(ADDRESS);
    //         // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2000, DECCEL, 7*GO_SLOW_POSITION, 1);
    //         // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2000, DECCEL, 7*GO_SLOW_POSITION, 1);
    //         // roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, ACCEL1, 8000, DECCEL1, , ACCEL2, 8000, DECCEL2, , 1);
    //         // for(;roboclaw.ReadEncM1(ADDRESS)<GO_SLOW_POSITION-ERROR_POSITION;){}
    //         //因为这个函数是攻击前的动作，不宜用编码器的值，以放敌人在这个途中-
    //         //就相撞而无法达到指定位置，延时已经过测试
    //         delay(250);

    //         // stopStuck();
    //         stop();
    //         delay(1000000);
    // // // if(temp_move_slow_to_prevent_crash_to_the_stage==1){
    // //             roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, ATTACK_SPEED-900, DECCEL, 699999, 1);
    // //             roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, ATTACK_SPEED-900, DECCEL, 699999, 1);
    // //             if(millis()>2000){
    // //                 // break;
    // //                 // temp_move_slow_to_prevent_crash_to_the_stage = 0;
    // //             }
    // // // attack();
    // // // while(1){
      
    // // // // delay(1000);
    // // // if(grayScaleSensorDetect()==CLOSE_TO_EDGE){
    // // //     break;
    // // // }  
    // // // }
    // // // // stop();
    // // // stopStuck();
    // // // delay(1000000);
    // // // // roboclaw.ForwardM1(ADDRESS, 15);
    // // //                 // roboclaw.BackwardM1(ADDRESS,speed);
    // // //                 roboclaw.ForwardM2(ADDRESS, 15);
    // // //                 long temp_time_attack = millis();
    // // //                 while(grayScaleSensorDetect()==DETECT_YES){
    // // //                     if(millis()-temp_time_attack>20000){
    // // //                         return;
    // // //                     }
    // // //                 }
    // // //                 stop();
    // // //                 // roboclaw.BackwardM2(ADDRESS,speed);
    // // //                 enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
    // // //                 judge_if_think_enemy_is_edge = 0;
    // // //                 // stopStuck();
    // // //                 detectsWhetherTheEdgeIsReachedWhenPushingEnemy(MODE_PUSHING_ENEMY); 
    // // //                 uploadDetect(); 
    // // //                 // return;
    // // //                 delay(1000000);
    // // // stepBackAndGetOnStage();
    // // // turnLeftPositon90();
    // // // digitalWrite(13,HIGH);
    // // // delay(1000000);
    // // // // dynamicBack();
    // // // // enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
    // // //                 // judge_if_think_enemy_is_edge = 0;
    // // //                 // // stopStuck();
    // // //                 // detectsWhetherTheEdgeIsReachedWhenPushingEnemy(); 
    // // //                 // uploadDetect(); 

    // // //                 // return;
    // // //                 // break;
    // // //                 roboclaw.ForwardM1(ADDRESS, 15);
    // // //                 // roboclaw.BackwardM1(ADDRESS,speed);
    // // //                 roboclaw.ForwardM2(ADDRESS, 15);
    // // //                 while(grayScaleSensorDetect()==STILL_ON_STAGE){

    // // //                 }
    // // //                 // delay(1000);
    // // //                 // roboclaw.BackwardM2(ADDRESS,speed);
    // // //                 enemy_on_front_go_front_only_once = CAN_GO_FRONT_TO_ENEMY;
    // // //                 judge_if_think_enemy_is_edge = 0;
    // // //                 // stopStuck();
    // // //                 detectsWhetherTheEdgeIsReachedWhenPushingEnemy(MODE_PUSHING_ENEMY); 
    // // //                 uploadDetect(); 
    // // //                 // return;
    // // // // detectsWhetherTheEdgeIsReachedWhenPushingEnemy(MODE_LOST_ENEMY);
    // // // delay(100000);
    // // // // aftertheEnemyDownAndReturnToTheSideOfTheField();
    // // // // roboclaw.ForwardM1(ADDRESS, 10);
    // // // // // roboclaw.BackwardM1(ADDRESS,10)
    // // // // // roboclaw.ForwardM2(ADDRESS, speed)
    // // // // roboclaw.BackwardM2(ADDRESS,20);
    // // // // delay(5000);
    // // // // stop();
    // // // // delay(1000000);
    // // // // attack();
    // // // determineIfItIsUnderTheStage();
    // // long temp = millis();
    // // grayScaleSensorDetect();
    // // Serial.print(millis()-temp);
    // // delay(100000);
    // // // roboclaw.ResetEncoders(ADDRESS);
    // // // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 2500, DECCEL, 1200, 1);
    // // // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 2500, DECCEL, 1200, 1);
    // // // while (roboclaw.ReadEncM1(ADDRESS)<1200-ERROR_POSITION && roboclaw.ReadEncM2(ADDRESS)<1200-ERROR_POSITION){
    // // //     /* code */
    // // // }
    // // // Serial.print(millis()-temp);
    // // // // delay(150);
    // // // stop();
    // // // delay(100000);
    // // // stepBackAndGetOnStage();
    // // // roboclaw_stage.ResetEncoders(ADDRESS_STAGE);
    // // // roboclaw_stage.SpeedAccelDeccelPositionM1M2(ADDRESS_STAGE, ACCEL1, STAGE_SPEED, DECCEL1, -STAGE_MOTOR_ONE_ROUND, ACCEL2, STAGE_SPEED, DECCEL2, STAGE_MOTOR_ONE_ROUND, 1);
    // // // stepBackAndGetOnStage();
    // // // roboclaw.BackwardM1(ADDRESS,20);
    // // // roboclaw.BackwardM2(ADDRESS,20);
    // // // long last_detect_back_left = 0;
    // // // long last_detect_back_right = 0;
    // // // long temp_time = millis();
    // // // which_had_align = ALIGN_TO_THE_BORDER;
    // // // // delay(200);
    // // // do{
    // // //     /* code */
    // // //     last_detect_back_left = 0;
    // // //     last_detect_back_right = 0;
    // // //     // last_detect_back_left = analogRead(DETECTOR_BACK_LEFT);
    // // //     // last_detect_back_right = analogRead(DETECTOR_BACK_RIGHT);
    // // //     // long last_temp_left = analogRead(DETECTOR_LEFT);
    // // //     // long last_temp_right = analogRead(DETECTOR_RIGHT);
    // // //     for(int i=0;i<10;++i){
    // // //         last_detect_back_left += analogRead(DETECTOR_BACK_LEFT);
    // // //         last_detect_back_right += analogRead(DETECTOR_BACK_RIGHT);
    // // //         // last_temp_left += analogRead(DETECTOR_LEFT);
    // // //         // last_temp_right += analogRead(DETECTOR_RIGHT);
    // // //     }
    // // //     last_detect_back_left = last_detect_back_left/10;
    // // //     last_detect_back_right = last_detect_back_right/10;
    // //     // last_temp_left = last_temp_left/10;
    // //     // last_temp_right = last_temp_right/10;
    // //     // Serial.println(last_detect_back_left+last_detect_back_right);
    // //     if(millis()-temp_time>1500){
    // //         which_had_align = ALIGN_TO_THE_PLATFORM;
    // //         break;
    // //     }
    // // } while (last_detect_back_left+last_detect_back_right>380);
    
    // // // stop();
    // // if(which_had_align==ALIGN_TO_THE_BORDER){
    // //     roboclaw.BackwardM1(ADDRESS,10);
    // //     roboclaw.BackwardM2(ADDRESS,10);
    // //     delay(200);
    // // }
    // // stop();
    // // long temp = millis();
    // // roboclaw.ResetEncoders(ADDRESS);
    // roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, ACCEL, 8000, DECCEL, GO_SLOW_POSITION, 1);
    // roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, ACCEL, 8000, DECCEL, GO_SLOW_POSITION, 1);
    // while(roboclaw.ReadEncM1(ADDRESS)<30){}
    // Serial.println(millis()-temp);
    // changeThePositionGoingToStage();
    // forChangeThePositionToMoveAlongWall(6300);
}

//测试程序
void test2(){
    #define DETECT_TIME_FRONT_SPECIAL_FOR_READY_TO_GO_TO_STAGE 20
    long detector_front_temp = 0;
    long detecor_left_front_more_temp = 0;
    long detecor_right_front_more_temp = 0;
    for(int i=0;i<DETECT_TIME_FRONT_SPECIAL_FOR_READY_TO_GO_TO_STAGE;++i){
        detector_front_temp += analogRead(DETECTOR_FRONT);
        detecor_left_front_more_temp += analogRead(DETECTOR_LEFT_FRONT_MORE);
        detecor_right_front_more_temp += analogRead(DETECTOR_RIGHT_FRONT_MORE);
    }
    detector_front_temp = detector_front_temp/DETECT_TIME_FRONT_SPECIAL_FOR_READY_TO_GO_TO_STAGE;
    detecor_left_front_more_temp = detecor_left_front_more_temp/DETECT_TIME_FRONT_SPECIAL_FOR_READY_TO_GO_TO_STAGE;
    detecor_right_front_more_temp = detecor_right_front_more_temp/DETECT_TIME_FRONT_SPECIAL_FOR_READY_TO_GO_TO_STAGE;
    Serial.print(detector_front_temp);
    Serial.print("     ");
    Serial.print(detecor_left_front_more_temp);
    Serial.print("     ");
    Serial.println(detecor_right_front_more_temp);
    delay(800);
    // turnLeftPositionSlowly(TURN_LEFT_POSITION_90_SLOWLY);
    // turnLeftPositionSlowly(TURN_LEFT_POSITION_90_SLOWLY);
    // forChangeThePositionToMoveAlongWall(6260);
    // turnLeftPositon90();
}

//搜索敌人总函数
void searchForEnemy(){
    if(detect_if_detected==DETECT_IF_DETECTED_NO){
        alignWithWalls();
        // for(times_detect_real_side=0;times_detect_real_side<TIMES_DETECT_REAL_SIDE_MAX;times_detect_real_side++){
           detectTheTwoSidesOfTheRightSideForEnemies();
        // }
    }
    sideFrontToDetectIfThereAreEnemies();
    lostEnemy();
}


//原始函数：
void setup(){
    //定义模拟串口
    roboclaw.begin(38400);
    roboclaw_stage.begin(19200);
    Serial.begin(9600);
    // pinMode(13,OUTPUT);//122333
    // digitalWrite(13,LOW);//122333
    //stop();
    delay(2000);
    //首先更新一下场上的距离常数，再行动
    // letUsGo();//122333
    // roboclaw.ResetEncoders(ADDRESS);
    // uploadDetect();
}

//主函数
void loop(){
    // bigDetectorTest();
    // test();
    // smallDetectTest();
    // test2();
    searchForEnemy();
    // delay(100000);
}
