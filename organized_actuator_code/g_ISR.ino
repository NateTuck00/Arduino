uint8_t cons_ups = 0;
uint8_t cons_downs = 0;
uint8_t cons_lefts = 0;
uint8_t cons_rights = 0;
uint8_t cons_selects = 0;

ISR(TIMER1_COMPA_vect) {
  //Serial.println("ISR ");
  //read_button();//Sets the button_code variable

  /*
    if(manual_motor_on == 1){
      // can add an && above with specific iterator to adjust the length of manual control. Want to test with pressure sensor on 5v to see where to call disaster as well as to test length of pull (although only 2" variance)
      //turn off. Don't clear disaster code yet and just wait for more button presses to see. Can also add an iterator in the ISR to see how long the disaster button has been held
      // pin d1 and d2 connected to this.




    }//endif motor manually turned on

  */

  /*
   * if(tests_neeeded == 1)
   * flags_holder = 0;
     flags_holder= (flags >> (1-1));
     if ((flags_holder & 1)== 1) {
   *   runTest
   * }
   * 
   */


  if (button_code == 1) {
    cons_ups++;
    //0 out the other ones
    cons_downs = 0;
    cons_lefts = 0;
    cons_rights = 0;
    cons_selects = 0;

    if (cons_ups > 8) {
      #ifdef debug
      Serial.println(F("Held up long enough"));
      #endif
      cons_ups = 0;
      //button_flag = 1;                                                                                                                        ///3
      flags |= B00000100;

    }//end consecutive ups case
  }//end UP code

  if (button_code == 2) {
    cons_downs++;
    //0 out the other ones
    cons_ups = 0;
    cons_lefts = 0;
    cons_rights = 0;
    cons_selects = 0;

    if (cons_downs > 8) {
      #ifdef debug
      Serial.println(F("Held down long enough"));
      #endif
      cons_downs = 0;
      //button_flag = 1;                                                                                                                          //3
      flags |= B00000100;

    }//end consecutive downs case
  }//end DOWN code

  if (button_code == 3) {
    cons_lefts++;
    //0 out the other ones
    cons_ups = 0;
    cons_downs = 0;
    cons_rights = 0;
    cons_selects = 0;

    if (cons_lefts > 8) {
      #ifdef debug
      Serial.println(F("Held left long enough"));
      #endif
      cons_lefts = 0;
      //button_flag = 1;                                                                                                                              ///3
      flags |= B00000100;

    }//end consecutive lefts case
  }//end LEFT code

  if (button_code == 4) {
    cons_rights++;
    //0 out the other ones
    cons_ups = 0;
    cons_downs = 0;
    cons_lefts = 0;
    cons_selects = 0;

    if (cons_rights > 8) {
      #ifdef debug
      Serial.println(F("Held right long enough"));
      #endif
      cons_rights = 0;
      //button_flag = 1;                                                                                                                              ///3
      flags |= B00000100;
      
    }//end consecutive rights case
  }//end RIGHT code

  if (button_code == 5) {
    cons_selects++;
    //0 out the other ones
    cons_ups = 0;
    cons_downs = 0;
    cons_lefts = 0;
    cons_rights = 0;

    if (cons_selects > 8) {
      #ifdef debug
      Serial.println(F("Held select long enough"));
      #endif
      cons_selects = 0;
      //button_flag = 1;                                                                                                                              ///3
      flags |= B00000100; 
    }//end consecutive selects case
  }//end UP code

  if (button_code == 0) {
    //Serial.println("No press recognized in interrupt");
    //0 out everything
    cons_ups = 0;
    cons_downs = 0;
    cons_lefts = 0;
    cons_rights = 0;
    cons_selects = 0;
  }//end NO PRESS code



  itr++;
  if (itr == 5) {
    itr = 0;
  }//endif
}//end ISR
