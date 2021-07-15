void setup() {
  
  if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
    
  pinMode(6,OUTPUT);

  myOLED.setFont(SmallFont);
  myOLED.print("Reading...", LEFT, 0);
  myOLED.update();
  
  rht.begin(RHT03_DATA_PIN);            
  pinMode(10, OUTPUT);//PWM control
  
  float tempHolder=0.0;
  for(int i=0; i<10; i++){
    tempHolder=measureTemp();
    
    while((tempHolder==0.0)||(tempHolder==32.00)){//measure the temp again until it isn't dead on 0.0 ( we toss this errorcode when not getting a reading )
        tempHolder=measureTemp();
    }//end while
   
    recentValues[i]=tempHolder;
  }//endfor

  wdt_reset();
  WDTCSR |= (1 << WDCE)|(1 << WDE);
  WDTCSR  = (1 << WDIE)|(1 << WDE)|(1 << WDP3)|(0 << WDP2)|(0 << WDP1)|(1 <<WDP0);
  ///////////////////////////////////////////
  //Timer Section. Editing is very dangerous. 
  ///////////////////////////////////////////
  TCCR3A = 0;                               // set entire TCCR3A register to 0
  TCCR3B = 0;                               // same for TCCR3B
  TCNT3  = 0;                               //initialize counter value to 0
  
  OCR3A = 6249;                             // = (16*10^6) / (hz*prescaler) - 1 (must be <65536)    6249:25ms             2499:10ms
  TCCR3B |= (1 << WGM32);                   // turn on CTC mode
  TCCR3B |= (1 << CS31) | (1 << CS30);      // Set CS31 and 30 for 64 prescaler 
  TIMSK3 |= (1 << OCIE3A);                  // enable timer compare interrupt
  /////////////////////////////////////////

  myOLED.setFont(BigNumbers);
  myOLED.clrScr();
}//end void setup()
