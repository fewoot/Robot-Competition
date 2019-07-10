/**
 *      '-'
 *    \\------负极
 *    \\('+')
 *    \\------正极（没标识）
 *    \\
 *    \\------信息
 *      'S'
 */

/**
 * 注意：信号引脚应该接在digital口上，不是anolog口上！！
 * 已经集成在芯片上的那种不需要加电阻
 */

// Written by ladyada, public domain
// Amendde by fewoot

#include "DHT.h"//https://github.com/adafruit/DHT-sensor-library

#define DHTPIN 2     // 信号引脚位置

// 切换感应器型号
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// 接一个10K的电阻

//实例化对象
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    //Serial.println(F("DHTxx test!"));

    dht.begin();
}

void loop() {
    
    // 250毫秒读取一次
    // 传感器会和实际有2s延迟
    float humidity = dht.readHumidity();
    // 读取摄氏温度，默认
    float temperature = dht.readTemperature();
    // 读取华氏温度
    float fahrenheit = dht.readTemperature(true);

    // 检查是否错误，并重启
    if (isnan(humidity) || isnan(temperature) || isnan(fahrenheit)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    // 以华氏温度为单位计算热指数，默认
    float hif = dht.computeHeatIndex(fahrenheit, humidity);
    // 以摄氏温度计算热指数
    float hic = dht.computeHeatIndex(temperature, humidity, false);

}
