
#include <LiquidCrystal.h>  //https://www.arduino.cc/en/Reference/LiquidCrystal

/**
 * rs：LCD上RS引脚连接到主板的位置
 * rw：LCD上RW引脚连接到主板的位置（接地时可省略）
 * enable：LCD上E引脚连接到主板的位置
 * d*：LCD上d*引脚连接到主板的位置
 * 当使用4-bit时，d0、1、2、3不用
 * VSS：接地
 * VDD：电源，接5V
 * A：LED背光灯正极（记得接电阻）
 * K:LED背光灯负极，接GND
 * V0:控制显示对比度
 */

/**
 * 一个方格16×5
 * 2行  16列
 * 
 * 
 */
const int rs = 12;
const int rw = 11;//待定，通常是接地
const int enable = 11;
const int d7 = 2;
const int d6 = 3;
const int d5 = 4;
const int d4 = 5;
const int d3 = 6;
const int d2 = 7;
const int d1 = 8;
const int d0 = 9;

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);
LiquidCrystal lcd(rs, rw, enable, d4, d5, d6, d7);
LiquidCrystal lcd(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7);
LiquidCrystal lcd(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
int cols = 0;
int rows = 0;
int col = 0;
int row = 0;
String data = "Hello, World.";

void setup(){
    //cols：行数，rows：列数
    lcd.begin(cols, rows);

    //清屏，光标放左上角
    lcd.clear();

    //设置光标位置，变量定义同上
    lcd.setCursor(col, row);

    //将光标归位到左上角
    lcd.home();

    //显示字符，data：显示的数据
    //返回显示的字节数
    lcd.write(data);

    //打印数据，data同上
    //BASE：可选，如果打印数字，此变量为数字的进制-
    //BASE可选值：BIN-2，DEC-10，OCT-8，HEX-16
    //返回字节数
    lcd.print(data);
    lcd.print(data, BASE);

    //了解更多：https://www.arduino.cc/en/Reference/LiquidCrystal
    ...
}

void loop(){
    
}
