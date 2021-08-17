//
//
//
//

float measurePressure(){
  //4.5V = 3,000 PSI
  //.5V= 0 PSI;
  #define MAXPRESSURE 1600.0
  float sensorValue = analogRead(A2);   // /1023

  #ifdef debug
  Serial.println(sensorValue);
  #endif
  
  float pressure = (sensorValue / 1023) * MAXPRESSURE;

  return pressure;
}//end measurePressure
