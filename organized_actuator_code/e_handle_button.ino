void handle_button(uint8_t button_handler) {
  #ifdef debug
  Serial.println(F("Handle button called"));
  #endif
  // Add control here for manual control of the actuator. Could be a set time or could be checked for at the start of the interrupt each time and a flag set to tell the ISR that the motor is on
  /*
    if(disaster==1){
      if(button_handler==1){
        //ignore the up case?
      }//endif UP

      if(button_handler==2){
         //ignore downs??
      }//endif DOWN

      if(button_handler==3){
        //retract motor and set motor on flag to be checked by ISR
      }//endif LEFT

      if(button_handler==4){
        //extend motor and set flag to be checked by ISR. Careful with this.

      }//endif RIGHT

      if(button_handler==5){
         //if select is pressed after an emergency, shut off?
      }//endif SELECT


    }//endif disaster
  */
  flags_holder = 0;
  flags_holder = (flags >> (5 - 1));
  if ((button_handler == 1) && ((flags_holder & 1) == 0 )) {

    if ((screen == 0) || (screen == 1)) {
      tests = tests + 5;
    }//endnestedif
    if ((screen == 3) || (screen == 4)) {
      tests = tests + 100;
    }//endnestedif

    //newdisp_needed = 1;
    flags |= B00000010;
  }//end UP

  if ((button_handler == 2) && ((flags_holder & 1) == 0) ) {

    if ((screen == 0) || (screen == 1)) {
      if (tests > 5) {
        tests = tests - 5;
      }//enddoublynestedif
    }//endnestedif

    if ((screen == 3) || (screen == 4)) {
      if (tests > 100) {
        tests = tests - 100;
      }//enddoublynestedif
    }//endnestedif

    //newdisp_needed = 1;
    flags |= B00000010;
  }//end DOWN

  if ((button_handler == 3) && ((flags_holder & 1) == 0))   {

    if (screen > 0) {
      screen--;
    }//endnestedif

    //newdisp_needed = 1;
    flags |= B00000010;
  }//end LEFT

  if ((button_handler == 4) && ((flags_holder & 1) == 0)) {

    if (screen < 4) { // 01 , 2main menu, 34
      screen++;
    }//endnestedif
    if (screen == 5) {
      if (tests > 0) {
        //tests_needed = 1;
        flags |= B00000001;
      }//endnestedif
    }//endif unpause

    //newdisp_needed = 1;
    flags |= B00000010;
  }//end RIGHT

  if ((button_handler == 5) && ((flags_holder & 1) == 0)) {
    /*
      //This is a recently added checker used to try and pause while running.
      if (tests_needed == 1) {
      screen = 5; // This is a special pause screen.
      tests_needed = 0;
      }//endif select while running
    */
    if ((screen == 0) || (screen == 4)) {
      //tests_needed = 1;
      flags |= B00000001;
      // may need to use own seperate display function for running

    }//endnestedif
    //newdisp_needed = 1;
    flags |= B00000010;
  }//end SELECT


  //button_flag = 0;
  flags &= B11111011;
}//end handle_button()
