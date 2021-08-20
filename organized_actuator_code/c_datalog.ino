// datalog()
//This is the function call to write to the SD card during our tests to see the results. 
// We'll want to be logging 10 or so pressure values per cycle as a CSV value and file. 
//
void datalog(String data){
  #ifdef debug
  Serial.println(F("datalog called. "));
  Serial.print("DS:");
  Serial.println(dataString);
  #endif
  lcd.clear();
  lcd.print("logging"); 
  File dataFile = SD.open("test.txt", FILE_WRITE);

  

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    
    #ifdef debug
    Serial.println(dataString);
    #endif
  }//endif
  
  // if the file isn't open, pop up an error:
  else {
    #ifdef debug
    Serial.println(F("error opening test.txt"));
    #endif
  }//end else
  dataString = "";
  datalog_time = false;
  
}//end void datalog()
