#include <OLED_I2C.h>

OLED myOLED(SDA, SCL);

extern uint8_t SmallFont[];


void setup() {
  // put your setup code here, to run once:
   if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...

    
   myOLED.setFont(SmallFont);
   pinMode(6,OUTPUT);
}//end void setup()


void loop() {

  digitalWrite(6,HIGH);

  myOLED.clrScr();
  myOLED.print("OLED_I2C text timeeee", LEFT, 0);
  myOLED.update();

  
  digitalWrite(6,LOW);
  
}//end voidloop()
