void measureSetTemp(){
   float sensorValue = analogRead(A2); //potetiometer input pin
   float volts = (sensorValue / 1023) * 5.0;  
   
   tp.dbl_setPoint = 90 - (35 * (volts / 5));
}//end measureSetTemp
