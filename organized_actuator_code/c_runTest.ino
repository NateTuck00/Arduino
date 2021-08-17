void runTest() {
  // Display running menu. Select to pause. Right to run after select. Select again to stop. (menu)
  screen = 2;
  String dataString = "Pressure Extension: ";
  int numMeasurements = 0;

  #ifdef debug
  Serial.println(F("runTest called"));
  #endif
  
  char myStg[10];
  itoa(tests, myStg, 10);
  int len = strlen(myStg);

  lcd.setCursor(0, 0);

  if (tests > 0) {
    lcd.print("Running test ");
  }//endif

  for (int i = 0; i < len; i++) {
    lcd.print(myStg[i]);
  }//endfor


  delay(3000);
  //wdt_reset();

  lcd.clear();
  lcd.print("Extending");

  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  int firstTime = millis();
  int lastTime = firstTime;
  int recentTime;

  
  while (digitalRead(8) != HIGH){  // Add in a 3 second timeout
    //delay(10);
    digitalRead(8);


    recentTime = millis();
/*
    if(((recentTime - lastTime) >= 100)&&(numMeasurements < 20 )){
      float sensorValue = analogRead(A2);
      #ifdef debug
      Serial.println(sensorValue);
      #endif
      float pressure = (sensorValue / 1023) * 3000.0;
      dataString += String(pressure);
      numMeasurements ++;
      lastTime = recentTime;
    }

    */
    digitalRead(8);

/*
    uint8_t buttons = lcd.readButtons();//This is the "Emergency" pause while you're extended. If you hit it here I probably want to have manual control option
    if (buttons) {
      if (buttons & BUTTON_SELECT) {
        button_code = 1;
        
        
      }//end nested Select only if
    }//endif
  */
    
  }//end extend
  digitalWrite(2,LOW);
  //wdt_reset();
  /*
  if (numMeasurements < 20){
    for(int i= numMeasurements; i < 20; i++){     // this can all likely be replaced with a float pressure = measurepressure call below. 
      float sensorValue = analogRead(A2);
      #ifdef debug
      Serial.println(sensorValue);
      #endif
      float pressure = (sensorValue / 1023) * 3000.0;
      dataString += String(pressure);
      
    }//endnested for
  }//endif
*/
/*
  noInterrupts();
  
  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    myFile.println(dataString);
    myFile.close();
    
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

  interrupts(); 
  //
  */
  
  dataString = "Pressure Retraction: ";
  
  lcd.clear();
  lcd.print("Waiting...");    

  delay(5000);
  //wdt_reset();// do a while buttoncheck here 
  delay(5000);
  
  lcd.clear();
  lcd.print("Retracting");
  digitalWrite(3,HIGH);


  firstTime = millis();
  lastTime = firstTime;
  while (digitalRead(7) != HIGH){
    
    digitalRead(7);
    recentTime = millis();

/*
    if(((recentTime - lastTime) >= 100)&&(numMeasurements < 20 )){
      float sensorValue2 = analogRead(A2);
      #ifdef debug
      Serial.println(sensorValue2);
      #endif
      float pressure2 = (sensorValue2 / 1023) * 3000.0;
      dataString += String(pressure2);
      numMeasurements ++;
      lastTime = recentTime;
    }//endif
  */
    
    digitalRead(7);
  }//endwhile
  digitalWrite(3,LOW);
  //wdt_reset();

/*
  if (numMeasurements < 20){
    for(int i= numMeasurements; i < 20; i++){     // this can all likely be replaced with a float pressure = measurepressure call below. 
      float sensorValue = analogRead(A2);
      
      #ifdef debug
      Serial.println(sensorValue);
      #endif
      
      float pressure = (sensorValue / 1023) * 3000.0;
      dataString += String(pressure);
    }//endnested for
  }//endif
  
  //datalog
  
  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    myFile.println(dataString);
    myFile.close();
    
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
  //
  dataString = "";
  */
  
  lcd.clear();
  lcd.print("Hold Sel 2 pause");     
  
  delay(5000);
  //wdt_reset();  //while buttoncheck 
  delay(5000);
  
  lcd.clear();
  
  tests--;

  #ifdef debug
  Serial.println(tests);
  #endif

  if (tests < 1) {
    tests = 1;
    //tests_needed = 0;                                                                                                                                                                      
    flags &= B11111110;
    screen = 2;
    //newdisp_needed = 1;                                                                                                                                                                    
    flags |= B00000010;
  }//endif

}//endrunTest()
