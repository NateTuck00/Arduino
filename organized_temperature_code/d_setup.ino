void setup() {
  #ifdef debug
  Serial.begin(115200);
  #endif
  
  //display reset
  delay(1000);
  pinMode( resetPin, OUTPUT ); // Setup reset pin direction (used by both SPI and I2C)
  digitalWrite( resetPin, HIGH );
  delay( 1 ); // VDD (3.3V) goes high at start, lets just chill for a ms
  digitalWrite( resetPin, LOW ); // bring reset low
  delay( 10 ); // wait 10ms
  digitalWrite( resetPin, HIGH ); // bring out of reset


  myOLED.begin(SSD1306_128X32);
  myOLED.setFont(SmallFont);
  myOLED.print("Reading...", LEFT, 0);
  myOLED.update();
             
  pinMode(10, OUTPUT);//PWM control
  
  float tempHolder=0.0;
  for(int i=0; i<10; i++){
    tempHolder=measureTemp();
    while((tempHolder==0.0)||(tempHolder==32.00)){//measure the temp again until it isn't dead on 0.0 ( we toss this errorcode when not getting a reading )
        tempHolder=measureTemp();
        delay(2000);
        
    }//end while
    g_f_recentValues[i]=tempHolder;
  }//endfor


  wdt_reset();
  WDTCSR |= (1 << WDCE)|(1 << WDE);
  WDTCSR  = (1 << WDIE)|(1 << WDE)|(1 << WDP3)|(0 << WDP2)|(0 << WDP1)|(1 <<WDP0);
 
  TCCR3A = 0;                               // set entire TCCR3A register to 0
  TCCR3B = 0;                               // same for TCCR3B
  TCNT3  = 0;                               //initialize counter value to 0
  
  OCR3A = 6249;                             // = (16*10^6) / (hz*prescaler) - 1 (must be <65536)    6249:25ms             2499:10ms
  TCCR3B |= (1 << WGM32);                   // turn on CTC mode
  TCCR3B |= (1 << CS31) | (1 << CS30);      // Set CS31 and 30 for 64 prescaler 
  TIMSK3 |= (1 << OCIE3A);                  // enable timer compare interrupt
  

  myOLED.setFont(BigNumbers);
  myOLED.clrScr();
}//end void setup()
