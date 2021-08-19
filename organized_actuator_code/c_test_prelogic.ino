

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

  
}//end test_prelogic()
