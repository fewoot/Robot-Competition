#include <SevSeg.h> //https://github.com/DeanIsMe/SevSeg


/**
 *          A
 *      \\\\\\\\\\
 *     F\\      \\B
 *      \\  G   \\
 *      \\\\\\\\\\
 *     E\\      \\C
 *      \\      \\
 *      \\\\\\\\\\
 *          D       .DP
 */


/**
 *    共1   A    F  共2 共3  B   
 *     |    |   |   |   |   |
 *     \\\\\\\\\\\\\\\\\\\\\\\
 *     \\\\\\\\\\\\\\\\\\\\\\\
 *     \\\\.\\\\\.\\\\.\\\\\.\
 *     |    |   |   |   |   |
 *     E    D   DP  C   G  共4  
 */


SevSeg sevseg;

int LIGHTVALUE = 90;//光亮，0-100
String STRING = "Hello,World!";//显示的字符串
int NUMBER = 1000;//显示数字
int LOCATION = 1;//小数点位数
byte HARDWARE = COMMON_CATHODE;//接线模式:COMMON_CATHODE=共阴极/COMMON_ANODE=共阳极。
byte NUMDIGITS = 4;//数码管位数（几个数字）
//               共：1，2，3，4
byte DIGIEPINS[] = {2, 3, 4, 5};//公共引脚连接的引脚位置
//                    A, B, C, D, E,  F,  G,  DP
byte SEGMENTPINS[] = {6, 7, 8, 9, 10, 11, 12, 13};//数码管从A-DP依次连接的引脚位置

/**
 * 因为此库不可以有delay()等延时函数，所以在这自建一个延时函数
 * 原理：重复计算，拖延时间。。。
 * 注意，再更新显示时，需要将此函数拆分，
 * 如果只使用此函数可以加delay
 */
void write(int number){
    long delay_time = 2000;
    for(int i=0;;i++){
        if(i>=delay_time){
            sevseg.blank();
            return;
        }
        sevseg.setNumber(number);
        sevseg.refreshDisplay();
    }
}

void setup(){
    sevseg.begin(HARDWARE,NUMDIGITS,DIGIEPINS,SEGMENTPINS);//初始化
}

void loop(){
    /**
     * NUMBER是数字，LOCATION是小数点位置（从最右边向左移动位数）
     * 当LOCATION为-1或无时，无小数点
     * 当NUMBER是float类型时，LOCATION是小数点后位数
     * 超出范围显示----
     * 当有true时显示为16进制
     */    
    sevseg.setNumber(NUMBER);//无小数点
    sevseg.setNumber(NUMBER,LOCATION);//见下文
    sevseg.setNumber(NUMBER,LOCATION,true);//16进制

    /**
     *刷新，必须
     */
    sevseg.refreshDisplay();


    /**
     * 显示字符，尽可能像
     * 只有数字字符、‘ ’、‘-’、‘.’可以显示                        
     */
    sevseg.setChars(STRING);

    


    /**
     * 空白
     */
    sevseg.blank();

    /**
     * 光亮调整（-200到200）
     * 尽量再0-100之间
     */
    sevseg.setBrightness(LIGHTVALUE);

}
