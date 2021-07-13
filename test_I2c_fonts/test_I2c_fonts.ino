#include <SPI.h>
#include <Wire.h>
#include <OLED_I2C.h>
OLED myOLED(SDA, SCL);

extern uint8_t SmallFont [];
extern uint8_t BigNumbers [];

float c_temp = 73.24;
float s_temp = 74.88;
void setup() {
  // put your setup code here, to run once:
  if(!myOLED.begin(SSD1306_128X32))
    while(1);  

    //myOLED.setFont(SmallFont);
    myOLED.setFont(BigNumbers);
}//end void setup()

String toprint ="";
 
void loop() {
  // put your main code here, to run repeatedly:
  myOLED.clrScr();
  
  myOLED.printNumF(c_temp,1, LEFT, 0);
  myOLED.printNumF(s_temp,1, 70, 0);
  myOLED.update();

}//end void loop()
