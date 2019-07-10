
/**
 * 模拟串口库，具体使用方法和Serial一模一样
 */
#include <SoftwareSerial.h>
/**
 * 模拟串口，定义一个模拟串口
 * 串口可以进行通信，但同一时间只可以有一个串口工作
 */
SoftwareSerial mySerial (rxPin, txPin);

void setup(){
    mySerial.begin(9600);
}

void loop(){
    mySerial.write();
    mySerial.println();
    mySerial.print();
}