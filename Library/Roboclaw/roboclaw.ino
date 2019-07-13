//所需要的库
#include <SoftwareSerial.h>
#include <RoboClaw.h>

//新建一个模拟串口
SoftwareSerial serial = SoftwareSerial(10,11);

//设置超时值
#define timeout 10000

//利用刚才新建的串口和通信超时值来新建一个对象
RoboClaw roboclaw = RoboClaw(&serial,timeout);

//初始化模拟串口，参数是波特率
roboclaw.begin(38400);


//控制电机移动，address是指令存储的地址，speed值在0-127中
ForwardM1(address, speed);
BackwardM1(address,speed);
ForwardM2(address, speed);
BackwardM2(address,speed);
ForwardBackwardM1(address,speed);
ForwardBackwardM2(address,speed);

//混合模式下设置电机转动，其中只有这里speed会从中间划分一道分水岭，即向前还是向后
ForwardMixed(address,speed);
BackwardMixed(address,speed);
TurnRightMixed(address,speed);
TurnLeftMixed(address,speed);
ForwardBackwardMixed(address,speed);
LeftRightMixed(address,speed);

//读取编码器的值，返回一个32-bit的值，最好用long存储
ReadEncM1(address);
ReadEncM2(address);
ReadSpeedM1(address);
ReadSpeedM2(address);
ResetEncoders(address);

//这两个是设定编码器的值，val是一个32-bit的参数
SetEncM1(address,val);
SetEncM2(address,val);

//使电机旋转固定的距离（角度），flag值为0/1，0表示暂存命令，1表示立即执行
SpeedDistanceM1(address, speed, distance, flag);
SpeedDistanceM2(address, speed, distance, flag);
SpeedDistanceM1M2(address, speed1, distance1, speed2, distance2, flag);
//accel是加速度
SpeedAccelDistanceM1(address, accel, speed, distance, flag);
SpeedAccelDistanceM2(address, accel, speed, distance, flag);
SpeedAccelDistanceM1M2(address, accel, speed1, distance1, speed2, distance2, flag);

//使电机旋转到特定位置，accel是加速度，deccel是减速度，position是位置，是在编码器计数中的位置，
//flag为0暂存命令，1立即执行
SpeedAccelDeccelPositionM1(address, accel, speed, deccel, position, flag);
peedAccelDeccelPositionM2(address, accel, speed, deccel, position, flag);
SpeedAccelDeccelPositionM1M2(address, accel1, speed1, deccel1, position1, accel2, speed2, deccel2, position2, flag);