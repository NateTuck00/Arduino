// datalog()
//This is the function call to write to the SD card during our tests to see the results. 
// We'll want to be logging 10 or so pressure values per cycle as a CSV value and file. 
//
void datalog(String dataString){

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

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
    Serial.println(F("error opening datalog.txt"));
    #endif
  }//end else
  
}//end void datalog()
