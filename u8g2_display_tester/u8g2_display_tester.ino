#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  u8g2.setFont(u8g2_font_crox4hb_tr);
  pinMode(6,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(6,HIGH);
  u8g2.clearBuffer();
  
  u8g2.drawStr(0,16, "Hello World!");
  u8g2.sendBuffer();

  digitalWrite(6,LOW);
  //delay(1000);
  
}
