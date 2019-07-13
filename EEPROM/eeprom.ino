//注意arduino UNO 板可以存储1kb的数据
#include <EEPROM.h>
//第一个地址，每个地址可以存储0-255字节的值
int addr = 0;

void setup(){
    //写入数据，val为byte数据
    EEPROM.write(addr, val);
    //读取数据，返回byte类型的值
    EEPROM.read(addr);
    //写入数据，data为任意类型的数据
    EEPROM.put(addr, data);
    //更新数据，只有当不同时才写入
    EEPROM.update(address, value);
    //读取数据，data为任意类型的实例化对象，会直接把这种类型的值赋值给它,并不会写入
    EEPROM.get(addr, data);
}

void loop(){
    
}

void Edelete(){
    for(int i=0;i<=1024;++i){
        EEPROM.write(i,0);
    }
}
