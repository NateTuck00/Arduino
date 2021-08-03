//
//
//
//

float measurePressure(){
  //4.5V = 3,000 PSI
  //.5V= 0 PSI;
  float sensorValue = analogRead(A2);   // /1023
  Serial.println(sensorValue);
  float pressure = (sensorValue / 1023) * 3000.0;

  return pressure;
}//end measurePressure
