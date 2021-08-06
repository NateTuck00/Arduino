void displayLCD() {
  //if on left screen count is 1.
  //if on right count is 100;
  #ifdef debug
  Serial.println("displayLCD called");
  #endif
  
  lcd.clear();
  lcd.setCursor(0, 0);

  char myStg[10];
  itoa(tests, myStg, 10);
  int len = strlen(myStg);

  #ifdef debug
  Serial.print(F("tests"));
  Serial.println(tests);
  Serial.print(F("screen"));
  Serial.println(screen);
  #endif

  if (screen == 0) {
    //Left start screen
    lcd.print(F("Select:Run "));
    #ifdef debug
    Serial.print(F("tests "));
    #endif

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor
    #ifdef debug
    Serial.println(tests);
    #endif
  }//endif

  if (screen == 1) {
    //left count /disp
    lcd.print(F("L:+5 tests "));

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor
    #ifdef debug
    Serial.print(F("tests "));
    Serial.println(tests);
    #endif
  }//endif

  if (screen == 2) {
    //Main menu
    lcd.print("L:Some R:Many");

  }//endif

  if (screen == 3) {
    //right count / disp
    lcd.print("R:+100 tests ");

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor
    #ifdef debug
    Serial.print(F("tests "));
    Serial.println(tests);
    #endif
  }//endif

  if (screen == 4) {
    //right start screen
    lcd.print("Select:Run ");

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor
    
    #ifdef debug
    Serial.print(F("tests "));
    Serial.println(tests);
    #endif
  }//endif

  if (screen == 5) {
    lcd.print("L:edit R: ");

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor
  }//endif pausescreen

  //newdisp_needed = 0;                                                                                                                                   
  flags &= B11111101;
}//end displayLCD(screen#)
