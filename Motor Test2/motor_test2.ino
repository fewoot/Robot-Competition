/**
 * 让我们做一个小算术吧：
 * pwm输出0-255
 * 对应0-5v（应该）
 * 所以51pwm = 1v
 * 所以0-2v对应0-102pwm；
 */


#define value1 255
#define motor1 5
#define motor2 6
#define value2 50

//#define move 11
//#define steer 10
//#define turnSpeed 0

void setup(){
    pinMode(motor1,OUTPUT);
    Serial.begin(9600);
}

void loop(){
    //analogWrite(motor1,value1);
    // Serial.println(analogRead(motor1));
    //analogWrite(right,value_right);
    for(int i=0;i<255;++i){
       analogWrite(motor1,i); 
       //analogWrite(right,i);
       Serial.println(i);
       delay(300);
       //delay(2000);
    }

    
    //analogWrite(5,value);
}
/**
 * analogWrite中，电机没有按照预期的反转再正转，应该是电机驱动的模式设置有问题，还要再看看用户手册（成功了）
 * 成功条件：mode3 option4，170停止
 * 今天最大的收获是搞懂了电机的转动，至少转起来了
 * 对于传感器和结构还是没有开始
 * 是时候计划一下了
 */
