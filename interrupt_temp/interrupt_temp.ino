  #include <SPI.h>
  #include <Wire.h> 
  #include<OLED_I2C.h>
  #include <SparkFun_RHT03.h>
  #include <avr/wdt.h>            // Including watchdog timer
  
  const int RHT03_DATA_PIN = 6; // RHT03 data pin
  RHT03 rht; // This creates a RTH03 object, which we'll use to interact with the sensor
  OLED myOLED(SDA, SCL);
  
  const uint8_t kp = 20;
  const uint8_t ki = 1;
  
  double g_previousTime;
  double g_output, g_setPoint;
  double g_lastsp = 60;
  double g_cumulativeError;

  float g_latestTempF;
  float g_avg;
  float recentValues[10];

  volatile int8_t  g_loops = 0;//ISR iterators
  volatile int8_t g_itr = 0;
  extern uint8_t SmallFont [];
  extern uint8_t BigNumbers [];
  uint8_t g_read_flag = 0;
  uint8_t g_sensorfail = 0;
  uint8_t g_clr_cnt = 0;
  
//measureTemp: simple quick return of the temp in F. Can add humidity with some changes in return or a global
float measureTemp(){
  int updateRet = rht.update();

  if(updateRet == 1){
    g_read_flag = 1;
    g_sensorfail = 0;
  }//endif 1
  if(updateRet == 0){
    g_read_flag = 0;
  }//endif 0 
  
  return rht.tempF();
}//measureTemp


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


void measureSetTemp(){
   float sensorValue = analogRead(A3); //potetiometer input pin
   float volts = (sensorValue / 1023) * 5.0;  
   
   g_setPoint = 55 + (35 * (volts / 5));//global setPoint
}//end measureSetTemp


//computePID: uses several global variables to calculate errors in temp/setTemp, and time. Could have temp timeout inside or externally
double computePID(double inp) {
  double currentTime = millis();
  double elapsedTime = (double)(currentTime - g_previousTime);

  double error = inp - g_setPoint; // error here means how far off our input temp is from where the gauge is set
  g_cumulativeError += error * elapsedTime;//We clamp how much this can affect our output below to prevent windup 

  if(abs(g_cumulativeError*ki)>40){

    if(g_cumulativeError > (10/ki)){
      g_cumulativeError=(160/ki); 
    }//endif positive cumulative error

    if(g_cumulativeError < (-70/ki)){
      g_cumulativeError=(-70/ki);   
    }//endif negative cumulative error
    
  }//endif cumulating error either direction
  
  double out = kp * error + ki * g_cumulativeError;//output determined by I and P. 
  g_previousTime = currentTime;

  return out;
}// end computePID


void loop(){ 
  //0: measure temp, measure set temp, constrain, computePID, analogwrite
  //1: display temp. 
  //2: update display                 
  wdt_reset();
  float g_dif;
  float g_sum;
  
  switch(g_itr){
    case 0:
    g_latestTempF= measureTemp();
    measureSetTemp();        
          
    if((g_latestTempF==0.0)||(g_latestTempF==32.00)){
       g_sum=0;
       for(int i=0; i<10; i++){
          g_sum= g_sum + recentValues[i];   
       }//endfor
       g_avg= g_sum/10; 
       recentValues[g_loops]= g_avg;// Toss the 0.0s to read what the temp before read.
    }//endif 0.0
          
    else if((g_latestTempF > 99)||(g_latestTempF < 10)){
      g_dif= g_latestTempF - g_avg;
      if (abs(g_dif) >20){
        recentValues[g_loops]= g_avg;   
      }//if it randomly reads 99 on a bump and shorts
    }//end elseif 99+
    
    else{
      recentValues[g_loops]=g_latestTempF;                                 
    }//endelse

    g_loops++;
    if(g_loops==10){//g_loops reset to stay in the recent values array
      g_loops=0;
    }//endif

    g_output= computePID(recentValues[g_loops]); //note this was g_latestTempF but to incorporate the bounds checks with 32.00 and 0.0 we use the same value as we already checked
    
    //check output bounds
    if(g_output > 229){
      g_output=229;
    }//endif
    
    if(g_output < 26){
      g_output=26; 
    }//endif out of bounds
    
    analogWrite(10,g_output);//PWM control for car heater written here 
   
  break;


    case 1:
    if(g_clr_cnt == 0){
      myOLED.clrScr();
    }//endif
    
    if( g_sensorfail != 1){
      myOLED.printNumF(g_latestTempF, 1, LEFT, 0);
     
      if ((abs(g_setPoint - g_lastsp)) > .3){
         myOLED.printNumF(g_setPoint, 1, 70, 0);
         g_lastsp = g_setPoint; 
         g_clr_cnt = 1;     
      }//endif dif >.3
    }//endif no sensor fail
    
    if(g_sensorfail == 1){
      myOLED.setFont(SmallFont);
      myOLED.print("Reading ...", LEFT, 0);
      myOLED.printNumF(g_setPoint, 1, 90, 0);
    }//endif fail
    
    if(g_clr_cnt >= 1){
      g_clr_cnt++;
      if(g_clr_cnt >= 40){
        g_clr_cnt = 0;
      }//endif 40
    }//endif
    
  break;

    case 2: 
      myOLED.update(); 
      myOLED.setFont(BigNumbers);

 break;  
    
    default:;     //Nada
    
  }//endswitch
  
}//end void loop()



uint16_t cons_misreads = 0;
ISR(TIMER3_COMPA_vect){
  
  if(g_read_flag == 1){
    cons_misreads = 0;
  }//endif successful read
  
  if(g_read_flag == 0){
    cons_misreads++;
    if(cons_misreads > 3500){
       g_sensorfail = 1;
    }//endif cons misreads
   }//endif misread
   
  g_itr++;
  if(g_itr == 3){
    g_itr=0;
  }//endif
  
}//end ISR()


ISR(WDT_vect) // Watchdog timer interrupt.
{
  myOLED.clrScr();
// Include your code here - be careful not to use functions they may cause the interrupt to hang and prevent a reset

}//end ISR WDT
