
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

#include <SPI.h>
#include <SD.h >  // These two are for the SD card

File myFile;

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();// This should connect to analog 4&5 and prevent you from reading from those.

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

volatile int toggle = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin(16, 2);
  
  lcd.setBacklight(VIOLET);
  
  pinMode(5, OUTPUT); // This is one of our 4 free pins and will be used to watch the ISR timer 
  pinMode(6, OUTPUT);

  /*
  ///////////////////////////////////////////////////////
  TCCR2A = 0;                               // set entire TCCR1A register to 0
  TCCR2B = 0;                               // same for TCCR1B
  TCNT2  = 0;                               //initialize counter value to 0

  OCR2A = 255;                             // = (16*10^6) / (hz*prescaler) - 1 (must be < 256)    78 is just over 5ms (77.125)
  TCCR2A |= (1 << WGM21);                   // turn on CTC mode
  TCCR2B |= (1 << CS22) | (1 << CS20);                    //  prescale
  TIMSK2 |= (1 << OCIE2A);                  // enable timer compare interrupt
///////////////////////////////////////////////////////////
*/
/*
  TCCR1A = 0;                               // set entire TCCR1A register to 0
  TCCR1B = 0;                               // same for TCCR1B
  TCNT1  = 0;                               //initialize counter value to 0

  OCR1A = 78;                             // = (16*10^6) / (hz*prescaler) - 1 (must be <65536)    6249= 25ms
  TCCR1B |= (1 << WGM12);                   // turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);      // Set CS11 and 10 for 64 prescaler
  TIMSK1 |= (1 << OCIE1A);                  // enable timer compare interrupt
*/


  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  
  OCR0A = 78;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS02) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(5,HIGH);
  //lcd.clear();
  lcd.print("Testing time!");
  digitalWrite(5,LOW);
}

ISR(TIMER0_COMPA_vect){
  digitalWrite(6,HIGH);
/*
   if(toggle == 0){
    toggle = 1;
    digitalWrite(5, HIGH);
   }

   else{
    toggle = 0;
    digitalWrite(5, LOW);                                                                                                                                                                                                                                                                                                                                                                       
   }
*/

  digitalWrite(6,LOW);
}//end ISR
