

#include <JC_Button.h> //https://github.com/JChristensen/JC_Button

/**
 * pin:探测引脚的位置
 * （选填）dbTime:反跳时间，默认为25ms
 * （选填）puEnable:是否启用内部的上拉电阻，默认为ture，反之为false
 * （选填）invert:是表示低逻辑级别，否表示高逻辑级别？？？默认为true，反之为false
 */
Button button(pin, dbTime, puEnable, invert);

/**
 * initialState:初始状态，默认为false（off）
 */
ToggleButton togbutton(pin, initialState, dbTime, puEnable, invert);



void setup(){
    //初始化
    button.begin();
}

void loop(){
    /**
     * 记录按钮的状态
     * 相当于在此处放了个标记，记录状态
     * 之后的方法会频繁借助于此函数
     * 此方法需要被频繁刷新，最好放在loop()的第一行
     * 返回ture/false
     */
    button.read();
    /**
     * 返回最近一次read()的结果
     * 此方法不会使按钮被read()
     */
    button.isPressed();
    button.isReleased();

    /**
     * 检查按钮的状态是否发生改变，即上两个read之间是否改变
     */
    button.wasPressed();
    button.wasReleased();

    /**
     * 检测按钮是否被按下了一定的时间，即是否长按
     * ms：设定的按下时间阈值，单位毫秒
     * 返回true/false
     */
    button.pressedFor(ms);
    button.releasedFor(ms);

    //返回上一次改变状态的时间，毫秒为单位，时间派生自arduino的millis()函数
    button.lastChange()

    //判断togbutton在上一个read()处是否改变了状态
    togbutton.changed();

    //返回togbutton在上一个read()处的状态
    togbutton.toggleState()
}



