void measureSetTemp(){
   float sensorValue = analogRead(A3); //potetiometer input pin
   float volts = (sensorValue / 1023) * 5.0;  
   
   tp.g_setPoint = 55 + (35 * (volts / 5));//global setPoint
}//end measureSetTemp
