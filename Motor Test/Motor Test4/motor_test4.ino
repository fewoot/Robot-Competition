// #include <SoftwareSerial.h>
// #include <RoboClaw.h>

// #define address 0x80
// //新建一个模拟串口
// SoftwareSerial serial = SoftwareSerial(10,11);
// //设置超时值
// #define timeout 10000
// //利用刚才新建的串口和通信超时值来新建一个对象
// RoboClaw roboclaw = RoboClaw(&serial,timeout);

// #define speed 8000


// void setup(){
//     roboclaw.begin(38400);
//     //roboclaw.SetEncM1(address,0);
//     //turn_round(900);
// }

// void loop(){
//     turn_round(900);
//     delay(4000);
// }

// void turn_round(long value){
//     //这两个是设定编码器的值，val是一个32-bit的参数
//     roboclaw.SetEncM1(address,0);
//     //roboclaw.SetEncM2(address,0);
//     roboclaw.SpeedAccelDeccelPositionM1(address, 655360, speed, 655360, value, 1);
//     //roboclaw.peedAccelDeccelPositionM2(address, 655360, speed, 655360, value, 1);
//     //roboclaw.SpeedAccelDeccelPositionM1M2(address, 655360, speed, 655360, value, 655360, speed, 655360, value, 1);
//     //delay(3000);
// }

//注意arduino UNO 板可以存储1kb的数据
#include <EEPROM.h>
//第一个地址，每个地址可以存储0-255字节的值
int addr = 0;
//float f;
//char c[5]= {'h','e','l','l','o'};
//String s;

struct MyObject {
    long time_record;
    int status;
};

void Edelete(){
    for(int i=0;i<=1024;++i){
        EEPROM.write(i,0);
    }
}

void record(int choice){
    MyObject jilu;
    jilu.time_record = millis();
    jilu.status = choice;
    EEPROM.put(addr,jilu);
    addr += sizeof(MyObject);
}

void re_record(){
    MyObject luru;
    Serial.begin(9600);
    addr = 0;
    for(;;){
        EEPROM.get(addr,luru);
        Serial.print(luru.time_record);
        Serial.print(" : ");
        Serial.println(luru.status);
        addr += sizeof(MyObject);
    }
        
    
        
    
    

}


void setup(){
    //Edelete();
    //re_record();
    //Serial.begin(9600);
    // record(3);
    // delay(1000);
    // record(12);
    // delay(1000);
    // record(1);

    // long temp,temp1;
    // Serial.begin(9600);
    // delay(1000);
    // Serial.println(millis());
    // EEPROM.put(addr,millis());
    // EEPROM.get(addr,temp);
    // delay(2000);
    // addr += 4;
    // EEPROM.put(addr,millis());
    // EEPROM.get(addr,temp1);

    // delay(1000);
    // Serial.println(temp);
    // Serial.println(temp1);
    // Serial.begin(9600);
    // EEPROM.put(addr,c);
    // Serial.println(EEPROM.get(addr,s));
    // Serial.println(s);
    //Edelete();
}

void loop(){
    //static int i=1;
    //EEPROM.write(addr,i++);
    //Serial.println(EEPROM.read(addr++));
    // if(i>255){
    //     i = 1;
    // }
}