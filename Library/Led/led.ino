

#include <LED.h>    //https://playground.arduino.cc/Code/LED/

/**
 * 注意：led是小电阻原件，必须加电阻！！！！！
 */

int PIN = 11;//引脚位置
int TIME = 1000;//持续时间
int TIMES = 1;//次数
int VALUE = 255;//亮度


//设定led为对象，PIN为相连引脚
LED led = LED(PIN);


void setup(){
    
}

void loop(){
    //判断led是否亮起，是返回true，否则false
    led.getState();

    //点亮led
    led.on();

    //关闭led
    led.off();

    //led状态反向
    led.toggle();

    //led闪烁
    //TIME是持续时间（毫秒），TIMES是在持续时间里闪烁的次数
    led.blink(TIME,TIMES);

    //设置亮度，VALUE是亮度值（0-255）
    led.setValue(VALUE);

    //逐渐变亮，TIME是持续时间（毫秒）
    led.fadeIn(TIME);

    //逐渐变暗，TIME是持续时间（毫秒）
    led.fadeOut(TIME);
}