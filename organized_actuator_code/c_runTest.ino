void runTest() {
  // Display running menu. Select to pause. Right to run after select. Select again to stop. (menu)

  
  
  screen = 2;
  Serial.println("runTest called");
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

                      // Add in the control here for the relays
  //noInterrupts();
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(1,HIGH);
  delay(5000);
  digitalWrite(1,LOW);
  delay(1000);
  digitalWrite(2,HIGH);
  delay(5000);
  digitalWrite(2,LOW);
  
  //duty cycle
  delay(24000); 
    
  lcd.clear();
  tests--;

  Serial.println(tests);

  if (tests < 1) {
    tests = 1;
    //tests_needed = 0;                                                                                                                                                                      
    flags &= B11111110;
    screen = 2;
    //newdisp_needed = 1;                                                                                                                                                                    
    flags |= B00000010;
  }//endif

  //interrupts();
}//endrunTest()
