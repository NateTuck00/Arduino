void displayLCD() {
  //if on left screen count is 1.
  //if on right count is 100;
  Serial.println("displayLCD called");
  lcd.clear();
  lcd.setCursor(0, 0);

  char myStg[10];
  itoa(tests, myStg, 10);
  int len = strlen(myStg);

  Serial.print("tests");
  Serial.println(tests);


  Serial.print("screen");
  Serial.println(screen);


  if (screen == 0) {
    //Left start screen
    lcd.print("Select:Run ");
    Serial.print("tests ");

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor

    Serial.println(tests);
  }//endif

  if (screen == 1) {
    //left count /disp
    lcd.print("L:+5 tests " );

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor

    Serial.print("tests ");
    Serial.println(tests);
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

    Serial.print("tests ");
    Serial.println(tests);
  }//endif

  if (screen == 4) {
    //right start screen
    lcd.print("Select:Run ");

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor

    Serial.print("tests ");
    Serial.println(tests);
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
