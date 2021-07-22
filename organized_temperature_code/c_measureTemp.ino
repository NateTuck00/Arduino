//measureTemp: simple quick return of the temp in F. Can add humidity with some changes in return or a global
float measureTemp(){

  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.println("Ping");//all good
    g_read_flag = 1;
    g_sensorfail = 0;
    break;
    
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    g_read_flag = 0;
    break;
    
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    g_read_flag = 0;
    break;
    
    default: 
    Serial.print("Unknown error,\t");
    g_read_flag = 0;
    break;
  }

  float temp = DHT.temperature;
  temp = ((1.8)*temp);     //Celsius to Fahrenheit
  temp = temp + 32;        
  return temp;// Note we can also pull a tempC or humidity
  
}//end measureTemp
