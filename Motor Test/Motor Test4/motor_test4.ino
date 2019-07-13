#include <SoftwareSerial.h>
#include <RoboClaw.h>

#define address 0x80
//新建一个模拟串口
SoftwareSerial serial = SoftwareSerial(10,11);
//设置超时值
#define timeout 10000
//利用刚才新建的串口和通信超时值来新建一个对象
RoboClaw roboclaw = RoboClaw(&serial,timeout);

#define speed 8000


void setup(){
    roboclaw.begin(38400);
    //roboclaw.SetEncM1(address,0);
    //turn_round(900);
}

void loop(){
    turn_round(900);
    delay(4000);
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