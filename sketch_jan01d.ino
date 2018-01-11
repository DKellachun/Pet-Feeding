#include "HX711.h"
#include <SoftwareSerial.h> //libaray of I2C
#include <SimpleDHT.h>
SoftwareSerial BT(10,11); //define serial BT  RX, TX
HX711 HX711_CH0(2, 3, 750); //SCK,DT,GapValue
//SCK引腳用於arduino和HX711模塊通訊的時序提供
//DT引腳用於從HX711讀取AD的數據
//GapValue用於校準輸出的重量值，如果數值偏大就加大該值，如果數據偏小就減小該值

int LED = 13;   //ARDUINO LED燈，亮起時代表初始化完成可以負重
long Weight = 0;    //定義一個變量用於存放承重的重量，單位為g



void setup()
{
  pinMode(LED, OUTPUT);       //設定LED是輸出引腳
  digitalWrite(LED, LOW);     //LED熄滅

  Serial.begin(9600);           //設定串口輸出波特率
  BT.begin(9600);
  HX711_CH0.begin();          //讀取傳感器重量
  delay(3000);                //延時3s用於傳感器穩定
  HX711_CH0.begin();          //重新讀取傳感器支架毛重用於後續計算

  digitalWrite(LED, HIGH);    //板載LED點亮，說明可以承重
}

void loop()
{

    Weight = HX711_CH0.Get_Weight();    //當前傳感器重量，該重量已經扣除支架重量
    BT.write(200);
    BT.write(Weight);
    Serial.print(Weight);     //串口輸出當前重量
    Serial.println(" g");     //單位為g
    delay(1000);  

}
