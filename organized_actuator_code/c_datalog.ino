
//This is the function call to write to the SD card during our tests to see the results. 
//

void datalog(){

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    //dataFile.println(dataString);
    dataFile.close();
    //Serial.println(dataString);
  }//endif
  
  // if the file isn't open, pop up an error:
  else {
    Serial.println(F("error opening datalog.txt"));
  }//end else
  
}//end void datalog()
