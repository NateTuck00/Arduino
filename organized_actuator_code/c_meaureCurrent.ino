//
//This should measure the current through my H bridge ground. It should set the disaster flag when we run into a current deemed unacceptable.
//
//
void measureCurrent(){
  #ifdef debug
  Serial.println(F("extend called"));
  #endif

  float sensorValue = analogRead(A3); //returns a value/ 1023 
  String concaterator = String(sensorValue,1);
  #ifdef debug
  Serial.print(F("DS"));
  Serial.println(dataString);
  #endif
  dataString += ",Current:";
  dataString.concat(concaterator);
  dataString += ",";
  #ifdef debug
  Serial.print(F("DS"));
  Serial.println(dataString);
  #endif
  // Now we have a sensor value. 80 correlates to ~13 amps. Need to decide on the overcurrent level.
  // Convert the reading through the .1Ω to ground and the 1kΩ into diode resistors  
  

  
}
