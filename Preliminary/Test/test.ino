

// //所需要的库
// #include <SoftwareSerial.h>
// #include <RoboClaw.h>

// //地址
// #define address 0x80
// #define accel 655360
// #define deccel 655360
// #define accel1 655360
// #define accel2 655360
// #define deccel1 655360
// #define deccel2 655360

// //经测试，900左右END值是一圈
// #define oneround 900
// //新建一个模拟串口
// SoftwareSerial serial1 = SoftwareSerial(10,11);//s2，s1
// // SoftwareSerial serial2 = SoftwareSerial(6,5);

// //设置超时值
// #define timeout 10000

// //利用刚才新建的串口和通信超时值来新建一个对象
// RoboClaw roboclaw = RoboClaw(&serial1,timeout);
// //RoboClaw roboclaw2 = RoboClaw(&serial2,timeout);
void setup(){
    // Serial.begin(9600);
    // roboclaw.begin(19200);
    //roboclaw2.begin(19200);
    //Serial.begin(9600);
}

void loop(){
    // Serial.println(analogRead(A0));
    // roboclaw.ForwardM1(address,0);
    // roboclaw.ForwardM2(address,0);
    // // Serial.println("hello,world");
    // // delay(1000);
    // // baseline();
    // roboclaw2.ForwardM1(address,20);
}

// void baseline(){
//     pinMode(13,OUTPUT);
//     digitalWrite(13,HIGH);
//     delay(1000);
//     digitalWrite(13,LOW);
//     delay(100);
//     digitalWrite(13,HIGH);
//     delay(100);
//     digitalWrite(13,LOW);
//     delay(100);
// }
//初始基准线函数，13号灯双闪
// void baseline(){
//     pinMode(13,OUTPUT);
//     digitalWrite(13,HIGH);
//     delay(1000);
//     digitalWrite(13,LOW);
//     delay(100);
//     digitalWrite(13,HIGH);
//     delay(100);
//     digitalWrite(13,LOW);
//     delay(100);
// }