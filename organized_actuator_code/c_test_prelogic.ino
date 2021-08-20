
//This function needs to look at our amount of tests, set the extension and retraction flags if we can, and make sure that our 10 second wait has passed. 
//
//

void test_prelogic(){
  
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

  // so now we need to set the extension flag. We don't have to set retraction.
  //Once we're done datalogging and the ten second timer expires (which will be later) we can  
  // set the flag there for retraction, but if we aren't extending or retracting 
  if((extending == false)&&(retracting == false)&&(ten_sec_timer_on == false)&&(datalog_time == false)){
    // we know tests are needed, but none of the other stages are happening (and they'd all set their own flags in their own interrupt)
    if(digitalRead(8) != HIGH){
      extending = true;  
    }//endnested if
  }//endif
  
}//end test_prelogic()
