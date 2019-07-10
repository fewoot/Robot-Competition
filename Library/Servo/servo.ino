
/*
用Servo.h库来加载电机程序
在Servoname.write中的数字为对应角度，且范围为0-180
基于Project003中得到可变化的电压值（0-1023），可以将两者连接形成-
实时控制的电机，但要转换单位
 */

#include <Servo.h>  //https://www.arduino.cc/en/Reference/Servo
/**
 * 红线接+
 * 黑/棕接地
 * 黄/橙/白接引脚
 */
Servo servo;

int PIN = 11;//引脚位置
int MIN = 544;//servo.attach中默认值，可选
int MAX = 2400;//servo.attach中默认值，可选
int ANGLE = 90;//旋转角度
int MS = 1500;//servo.writeMicroseconds中默认值

void setup(){
    //PIN是连接的引脚
    servo.attach(PIN);
    //MIN、MAX可选，分别指最小角度0°和最大角度180°，以微妙为单位，默认分别为544、2400
    servo.attach(PIN,MIN,MAX);

    //test
    Serial.begin(9600);
}

void loop(){
    //ANGLE是旋转的角度，角度是相对于绝对参考系而言，不是再旋转的角度
    //当是自旋转马达时，ANGLE是旋转速度，90是静止，0、180对应不同方向的最大旋转速度
    servo.write(ANGLE);

    //MS是微妙，在平常马达上代表角度，1500在中间，1000、2000是两个方向的最大值
    //在自旋马达上与servo.write()意义一样
    servo.writeMicroseconds(MS);

    //返回当前设置的马达的转动角度，在0-180之间
    servo.read();

    //返回判断，ture则servo有对应的引脚，false则无
    servo.attached();
    
    //取消一个引脚的连接
    servo.detach();
}
