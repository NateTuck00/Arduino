//
// We want to measure the pressure as we go in and see where it hits. 
// It on average for me tops out at about 670 PSI. 
//

float measurePressure(){
  //4.5V = 1600 PSI
  //.5V= 0 PSI;
  #define MAXPRESSURE 1600.0
  #define RANGE 818
  #define OFFSET 102
  float sensorValue = analogRead(A2);   // /1023

  #ifdef debug
  Serial.println(sensorValue);
  #endif
  
  float pressure = ((sensorValue -OFFSET)/RANGE) * MAXPRESSURE; // Our PSI sensor has a .5V offset on both ends of the voltage range, and we adjust the 1023 analog scale accordingly 
  if (pressure > MAXPRESSURE){
    pressure = MAXPRESSURE;
  }//endif

  if (pressure < 0){
    pressure = 0; 
  }//endif
  
  return pressure;
}//end measurePressure
