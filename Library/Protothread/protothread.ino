#include <pt.h>//

//声明新线程，可以声明多个线程
static struct pt PtName;

/**
 * 创建新线程，*PtName是新线程的指针
 * 这还是一个函数，在loop中被调用
 * 注意：在线程中不要用局部变量，会被不断刷新，出现bug，可以用静止变量-static，或全局变量
 * 在线程中的程序不要用delay()等停滞函数，因为线程要不断刷新
 * 此线程可以有多个
 */
static int protothreadName(struct pt *pt){

    //开始进程
    PT_BEGIN(pt);

    /**
     * 因为进程碰到“PT_END(pt);”就停止了，所以要用无限循环框住
     * 但不是必须的，也可以不要，但那样线程只能运行一次
     */
    while(1) {
        //coding

        /**
         * pt是需要暂停的线程，condition是继续线程的条件
         */
        PT_WAIT_UNTIL(pt,condition);
    }
    
    //关闭进程
    PT_END(pt);
}

void setup() {
  //初始化线程
  //(错误)其实&不是必须的，编译器会自动加上，这只是提醒你这里参数是指针
  //好像&是必须的，还是加上吧。。。
  PT_INIT(&pt1);
}

void loop() {
  //启动进程
  protothreadName(&pt1);
}



