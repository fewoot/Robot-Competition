

//所需要的库
// #include <SoftwareSerial.h>
#include <RoboClaw.h>

//地址
#define address 0x81
#define accel 655360
#define deccel 655360
#define accel1 655360
#define accel2 655360
#define deccel1 655360
#define deccel2 655360

//经测试，900左右END值是一圈
#define oneround 900
//新建一个模拟串口
// SoftwareSerial serial1 = SoftwareSerial(10,11);//s2，s1
// SoftwareSerial serial3 = SoftwareSerial(6,5);

//设置超时值
#define timeout 10000

//利用刚才新建的串口和通信超时值来新建一个对象
RoboClaw roboclaw = RoboClaw(&Serial1,timeout);
RoboClaw roboclaw2 = RoboClaw(&Serial3,timeout);
// RoboClaw roboclaw2 = RoboClaw(&serial3,timeout);
void setup(){
    Serial.begin(9600);
    roboclaw.begin(38400);
    roboclaw2.begin(19200);
    //Serial.begin(9600);
}

void loop(){

    // roboclaw2.ForwardM1(address, 30);
    // roboclaw2.SpeedAccelDeccelPositionM1M2(address, accel, 800, deccel, 900, accel, 800, deccel, 900, 1);
    // Serial.print(roboclaw2.ReadEncM1(address));
    // Serial.println(roboclaw2.ReadEncM2(address));
    // delay(1000);
    // // delay(1000);
    // roboclaw.ReadEncM1(address);
    // roboclaw.ReadEncM2(address);
    // delay(60000);
    // Serial.println(analogRead(A0));
    // roboclaw.ForwardM1(address,0);
    // roboclaw.ForwardM2(address,0);
    // // Serial.println("hello,world");
    // // delay(1000);
    // baseline();
    // roboclaw2.ForwardM1(address,20);
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
