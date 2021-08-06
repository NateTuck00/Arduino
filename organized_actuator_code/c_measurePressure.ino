//
//
//
//

float measurePressure(){
  //4.5V = 3,000 PSI
  //.5V= 0 PSI;
  float sensorValue = analogRead(A2);   // /1023

  #ifdef debug
  Serial.println(sensorValue);
  #endif
  
  float pressure = (sensorValue / 1023) * 3000.0;

  return pressure;
}//end measurePressure
