//measureTemp: simple quick return of the temp in F. Can add humidity with some changes in return or a global
float measureTemp(){

  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    #ifdef debug
    Serial.println(F("Ping"));//all good
    #endif
    
    g_read_flag = 1;
    g_sensorfail = 0;
    break;
    
    case DHTLIB_ERROR_CHECKSUM: 
    #ifdef debug
    Serial.print(F("Checksum error,\t")); 
    #endif
    
    g_read_flag = 0;
    break;
    
    case DHTLIB_ERROR_TIMEOUT: 
    #ifdef debug
    Serial.print(F("Time out error,\t")); 
    #endif
    
    g_read_flag = 0;
    break;
    
    default: 
    #ifdef debug
    Serial.print(F("Unknown error,\t"));
    #endif
    
    g_read_flag = 0;
    break;
  }

  float temp = DHT.temperature;
  temp = ((1.8)*temp);     //Celsius to Fahrenheit
  temp = temp + 32;        
  return temp;// Note we can also pull a tempC or humidity
  
}//end measureTemp
