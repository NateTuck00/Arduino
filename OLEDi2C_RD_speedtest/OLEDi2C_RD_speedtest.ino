#include <OLED_I2C.h>

#include <Wire.h>// out to save mem

OLED myOLED(SDA, SCL);

extern uint8_t SmallFont[];

String test= "this work?";
float flt=72.56;

void setup() {
  // put your setup code here, to run once:
   if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...

   Wire.setClock(400000); 
   myOLED.setFont(SmallFont);
   pinMode(6,OUTPUT);
}//end void setup()


void loop() {

  digitalWrite(6,HIGH);

  myOLED.clrScr();
 // test.concat(flt);
 // test.concat(" Set:");
  
  myOLED.print(test, LEFT, 0);
  
 
  myOLED.update();

  
  digitalWrite(6,LOW);
  
}//end voidloop()
