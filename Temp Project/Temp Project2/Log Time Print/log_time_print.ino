#include <SoftwareSerial.h>
#include <RoboClaw.h>
#include <EEPROM.h>
//定义日志格式
struct MyObject {
    //执行次数
    int times;
    //记录状态
    /**
     * 状态规定：左-1，左前-2，右前-4，右-5
     */
    int statue;
    //记录时间，应该是一次完整转向所用的时间
    int time;
};

//定义日志地址
int addr = 0;

MyObject mylog;

void setup(){
    Serial.begin(9600);
    //MyObject mylog;
}



void loop(){
    
    EEPROM.get(addr,mylog);
    switch (mylog.statue){
    case 1:
        Serial.print("次数：");
        Serial.print(mylog.times);
        Serial.print("， 方向：左， 时间：");
        Serial.print(mylog.time);
        //左    
        break;
    case 2:
        Serial.print("次数：");
        Serial.print(mylog.times);
        Serial.print("， 方向：左前， 时间：");
        Serial.print(mylog.time);
        //左前   
        break;
    case 4:
        Serial.print("次数：");
        Serial.print(mylog.times);
        Serial.print("， 方向：右前， 时间：");
        Serial.print(mylog.time);
        //右前    
        break;
    case 5:
        Serial.print("次数：");
        Serial.print(mylog.times);
        Serial.print("， 方向：右， 时间：");
        Serial.print(mylog.time);
        //右    
        break;
    default:
        break;
    }
    addr += sizeof(MyObject);
    if(addr>1024){
        for(;;){}
    }
}
