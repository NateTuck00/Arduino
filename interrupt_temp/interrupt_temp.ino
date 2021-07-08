  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  #include <splash.h>             // may not be needed. 
  #include <SparkFun_RHT03.h>
  #include <avr/wdt.h>            // Including watchdog timer

  #define SCREEN_WIDTH 128 // OLED display width, in pixels
  #define SCREEN_HEIGHT 32 // OLED display height, in pixels

  #define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
  #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  const int RHT03_DATA_PIN = 6; // RHT03 data pin
  RHT03 rht; // This creates a RTH03 object, which we'll use to interact with the sensor

  const uint8_t kp = 10;
  const uint8_t ki = 1;
  
  double g_previousTime;
  double g_lastError;
  double g_output, g_setPoint;
  double g_cumulativeError;

  float g_latestTempF;
  float g_avg;
  float recentValues[10];// 
  float sum;
  float dif;

  volatile int8_t  g_loops =0;//ISR iterators
  volatile int8_t g_itr=0;

  
//measureTemp: simple quick return of the temp in F. Can add humidity with some changes in return or a global
float measureTemp(){
  int updateRet = rht.update();
  return rht.tempF();
}//end measureTemp


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Ports for dwrite
  //B: d8-13
  //C:Analog
  //D: 0-7
  //DDRx : data direction 1 being output
  //PIN: Read digital value of pin
  //DDRD = B00001000; // note 6 is defined after. We'll pick 4 to measure timing
  pinMode(6,OUTPUT);

  display.setTextColor(SSD1306_WHITE);  
  display.display();
  display.clearDisplay();
  
  rht.begin(RHT03_DATA_PIN);// We can check the connection here or in the while loop            
  pinMode(10, OUTPUT);//PWM control
  
  float tempHolder=0.0;
  for(int i=0; i<10; i++){
    tempHolder=measureTemp();
    
    while(tempHolder==0.0){//measure the temp again until it isn't dead on 0.0 ( we toss this errorcode when not getting a reading )
        tempHolder=measureTemp();
    }//end while
   
    recentValues[i]=tempHolder;
  }//endfor
  
  ///////////////////////////////////////////
  //Timer Section. Editing is very dangerous. 
  ///////////////////////////////////////////
  TCCR3A = 0;                               // set entire TCCR3A register to 0
  TCCR3B = 0;                               // same for TCCR3B
  TCNT3  = 0;                               //initialize counter value to 0
  
  OCR3A = 60000;                             // = (16*10^6) / (hz*prescaler) - 1 (must be <65536)    6249:25ms             2499:10ms
  TCCR3B |= (1 << WGM32);                   // turn on CTC mode
  TCCR3B |= (1 << CS31) | (1 << CS30);      // Set CS31 and 30 for 64 prescaler 
  TIMSK3 |= (1 << OCIE3A);                  // enable timer compare interrupt
  /////////////////////////////////////////

}//end void setup()


void measureSetTemp(){
   float sensorValue = analogRead(A3); //potetiometer input pin
   float volts = (sensorValue / 1023) * 5.0;  
     
   g_setPoint = 55 + (35 * (volts / 5));//global setPoint
}//end measureSetTemp


//computePID: uses several global variables to calculate errors in temp/setTemp, and time. Could have temp timeout inside or externally
double computePID(double inp) {
  double currentTime = millis();// This doesn't need to be a float, but it ensures our errors are floats for precision
  double elapsedTime = (double)(currentTime - g_previousTime);

  double error = g_setPoint - inp; // error here means how far off our temperature is from user input.
  g_cumulativeError += error * elapsedTime;//We want to clamp this to be roughly the max output value it can contribute to 229 (and we'll likely have error) 

  if(abs(g_cumulativeError*ki)>220){

    if(g_cumulativeError > (220/ki)){
      g_cumulativeError=(220/ki); 
    }//endif positive cumulative error

    if(g_cumulativeError < (-220/ki)){
      g_cumulativeError=(-220/ki);   
    }//endif negative cumulative error
    
  }//endif cumulating error either direction
  
  double out = kp * error + ki * g_cumulativeError;//output determined by I and P. 
  g_lastError = error;
  g_previousTime = currentTime;

  return out;
}// end computePID


//displayTemp: A function that preloads our display memory before executing the display command on the next clock cycle
void displayTemp(){
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Curr: " +String(g_latestTempF,1)+ " Set: " + String(g_setPoint));// Cut out display.display()for clock time
  //display.display(); 
}//end displayTemp()



void loop() {
  // put your main code here, to run repeatedly:
  //g_itr state machine. 
  //0: measure temp, measure set temp, constrain, computePID, analogwrite
  //1: display temp. PORTD = B00001000
  //                 PORTD = B00000000 

  switch(g_itr){
    case 0:
    digitalWrite(6,HIGH);
    g_latestTempF= measureTemp();
    measureSetTemp();        
          
    if(g_latestTempF==0.0){
       sum=0;
       for(int i=0; i<10; i++){
          sum= sum + recentValues[i];   
       }//endfor
       g_avg= sum/10; 
       recentValues[g_loops]= g_avg;// Toss the 0.0s to read what the temp before read.
    }//endif 0.0
          
    else if((g_latestTempF > 99)||(g_latestTempF < 10)){
      dif= g_latestTempF - g_avg;
      if (abs(dif) >20){
        recentValues[g_loops]= g_avg;   
      }//if it randomly reads 99 on a bump and shorts
    }//end elseif 99+
    else{
      recentValues[g_loops]=g_latestTempF;
    }//endelse

    g_loops++;
    if(g_loops==10){//g_loops reset to keep it in the array
      g_loops=0;
    }//endif

    g_output= computePID(g_latestTempF); 
    
    //check output bounds
    if(g_output > 229){
      g_output=229;
    }//endif
    
    if(g_output < 26){
      g_output=26; 
    }//endif out of bounds
    //displayTemp();
    
    analogWrite(10,g_output);//PWM control for car heater written here 
    digitalWrite(6,LOW);
   //displayTemp();

  break;


    case 1:
    //PORTD = B00001000;
    digitalWrite(6,HIGH);
    //displayTemp();
    //digitalWrite(6,LOW);
    //PORTD = B00000000;
    //display.display();
    Serial.println("Curr: " +String(g_latestTempF,1)+ " Set: " + String(g_setPoint));
    digitalWrite(6,LOW);
    break;

    default:;     //Nada
    
  }//endswitch

  
}//end void loop()


ISR(TIMER3_COMPA_vect){


  g_itr++;
  if(g_itr == 2){
    g_itr=0;
  }//endif
  
}//end ISR()
