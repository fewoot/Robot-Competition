#include <FiniteStateMachine.h> //https://playground.arduino.cc/Code/FiniteStateMachine/



//自定义方法
void function_1(){}
void function_2(){}
void function_3(){}
void function_4(){}

/**
 * enterFunction 是在此状态被启用时执行的方法
 * updateFunction 是状态刷新时正好处在对应的此状态下会执行的方法
 * exitFunction 是取消此状态是执行的方法
 */

//用状态类来声明状态，注意，（错误）这里其实是将函数对应的指针作为参数，但在调用时可加可不加‘&’，编译器会自己判断
//不知道为什么，可能是库函数的源码编写设定问题，在这里不用加&，而在protothread库中要加，-
//在这里能不能加上待定
//State ethernetDebugState = State( enterFunction , updateFunction , exitFunction );
State state_one = State(function_1);
State state_two = State(function_2);
State state_three = State(function_3);
State state_four = State(function_4);




//声明状态对象，state_XXX是初始状态
FSM stateMachine = FSM(state_one);


void setup(){
    
}

void loop(){
    //刷新状态机
    stateMachine.update();

    //准备改变状态，改变会在之后遇到的第一次刷新时启用
    stateMachine.transitionTo(State);

    //立即转换状态
    stateMachine.immediateTransitionTo(State);

    //返回当前状态
    stateMachine.getCurrentState();

    //返回当前状态，和上一条殊途同归
    stateMachine.State();

    //判断当前状态机是否是括号中的State状态
    stateMachine.isInState(State);
}
