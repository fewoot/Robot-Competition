/**
 * 对于加速和减速的理解：
 * 1.加速减速是有默认值的，为655360
 * 2.原值、百分比、时间值之间有比例关系
 * 3. 百分比 = ( 原值 / 32768 ) x 100
 * 4. 原值 = ( 百分比 / 100 ) x 32768
 * 5. 时间 = ( 原值 / 32768 ) x 1
 * 6. 原值 = 32768 / 时间
 * 7.时间单位是s
 */

//所需要的库
#include <SoftwareSerial.h>
#include <RoboClaw.h>

//地址
#define ADDRESS 0x80
#define accel 655360
#define deccel 655360
#define accel1 655360
#define accel2 655360
#define deccel1 655360
#define deccel2 655360

//经测试，900左右END值是一圈
#define oneround 900
//新建一个模拟串口
SoftwareSerial serial = SoftwareSerial(10,11)//S2,S1

//设置超时值
#define timeout 10000

//利用刚才新建的串口和通信超时值来新建一个对象
RoboClaw roboclaw = RoboClaw(&serial,timeout)

//初始化模拟串口，参数是波特率
roboclaw.begin(38400)


//控制电机移动，ADDRESS是指令存储的地址，speed值是0-127
roboclaw.ForwardM1(ADDRESS, speed)
roboclaw.BackwardM1(ADDRESS,speed)
roboclaw.ForwardM2(ADDRESS, speed)
roboclaw.BackwardM2(ADDRESS,speed)
roboclaw.ForwardBackwardM1(ADDRESS,speed)
roboclaw.ForwardBackwardM2(ADDRESS,speed)

//混合模式下设置电机转动，其中只有这里speed会从中间划分一道分水岭，即向前还是向后
roboclaw.ForwardMixed(ADDRESS,speed)
roboclaw.BackwardMixed(ADDRESS,speed)
roboclaw.TurnRightMixed(ADDRESS,speed)
roboclaw.TurnLeftMixed(ADDRESS,speed)
roboclaw.ForwardBackwardMixed(ADDRESS,speed)
roboclaw.LeftRightMixed(ADDRESS,speed)

//读取编码器的值，返回一个32-bit的值，最好用long存储
//注意：电机驱动的负值不是负值，-1 = 4294967259，依次递减
roboclaw.ReadEncM1(ADDRESS)
roboclaw.ReadEncM2(ADDRESS)
roboclaw.ReadSpeedM1(ADDRESS)
roboclaw.ReadSpeedM2(ADDRESS)
roboclaw.ResetEncoders(ADDRESS)

//这两个是设定编码器的值，val是一个32-bit的参数
roboclaw.SetEncM1(ADDRESS,val)
roboclaw.SetEncM2(ADDRESS,val)

//使电机旋转固定的距离（角度），flag值为0/1，0表示暂存命令，1表示立即执行
roboclaw.SpeedDistanceM1(ADDRESS, speed, distance, flag)
roboclaw.SpeedDistanceM2(ADDRESS, speed, distance, flag)
roboclaw.SpeedDistanceM1M2(ADDRESS, speed1, distance1, speed2, distance2, flag)
//accel是加速度
roboclaw.SpeedAccelDistanceM1(ADDRESS, accel, speed, distance, flag)
roboclaw.SpeedAccelDistanceM2(ADDRESS, accel, speed, distance, flag)
roboclaw.SpeedAccelDistanceM1M2(ADDRESS, accel, speed1, distance1, speed2, distance2, flag)

//使电机旋转到特定位置，accel是加速度，deccel是减速度，position是位置，是在编码器计数中的位置，
//在这个给、函数中，speed是编码器函数，0-8000，不同于上面的
//flag为0暂存命令，1立即执行
roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, accel, speed, deccel, position, flag)
roboclaw.SpeedAccelDeccelPositionM2(ADDRESS, accel, speed, deccel, position, flag)
roboclaw.SpeedAccelDeccelPositionM1M2(ADDRESS, accel1, speed1, deccel1, position1, accel2, speed2, deccel2, position2, flag)
roboclaw.ReadPWMs( ADDRESS, &pwm1, &pwm2)



/**
 * 这个函数可以读取两个电机的位置信息和速度信息
 */
void displayspeed(void){
    uint8_t status1,status2,status3,status4
    bool valid1,valid2,valid3,valid4
    
    int32_t enc1= roboclaw.ReadEncM1(ADDRESS, &status1, &valid1)
    int32_t enc2 = roboclaw.ReadEncM2(ADDRESS, &status2, &valid2)
    int32_t speed1 = roboclaw.ReadSpeedM1(ADDRESS, &status3, &valid3)
    int32_t speed2 = roboclaw.ReadSpeedM2(ADDRESS, &status4, &valid4)
    Serial.print("Encoder1:")
    if(valid1){
        Serial.print(enc1,HEX)
        Serial.print(" ")
        Serial.print(status1,HEX)
        Serial.print(" ")
    }else{
        Serial.print("invalid ")
    }

    Serial.print("Encoder2:")
    if(valid2){
        Serial.print(enc2,HEX)
        Serial.print(" ")
        Serial.print(status2,HEX)
        Serial.print(" ")
    }else{
        Serial.print("invalid ")
    }

    Serial.print("Speed1:")
    if(valid3){
        Serial.print(speed1,HEX)
        Serial.print(" ")
    }else{
        Serial.print("invalid ")
    }

    Serial.print("Speed2:")
    if(valid4){
        Serial.print(speed2,HEX)
        Serial.print(" ")
    }else{
        Serial.print("invalid ")
    }

    Serial.println()
}