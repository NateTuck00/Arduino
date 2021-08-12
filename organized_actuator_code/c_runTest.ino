void runTest() {
  // Display running menu. Select to pause. Right to run after select. Select again to stop. (menu)
  screen = 2;
  
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

  // Add in the control here for the relays. The entirety of what we write to the SD card could just be a struct 
  /*
   *   void runTest(){
          noInterrupts();
          PORTD = B00000010; 
          
          delay(500); // You can measure pressure in here as often as you'd like.... and it'll really be a while like i type up below

           //While (DigitalPingroundSignalSwitch != LOW){
              measure pressure;
              digitalRead(that pin);
              
              // may need to wdt_reset(); 
            }//endwhile
           // once you hit past it you record the time difference on extension... or can wait till after retract

          
          PORTD = B00000000; 
          interrupts(); 
        }//end runTest
   */
   
  delay(2000);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  lcd.clear();
  lcd.print("Extending");

  delay(10000);
  digitalWrite(2,LOW);
  
  lcd.clear();
  lcd.print("Retracting");
  digitalWrite(3,HIGH);
  delay(10000);
  digitalWrite(3,LOW);
  
  lcd.clear();
  lcd.print("Waiting...");      //dataloggging? or we can split wait in half and double log
  delay(2000);
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
