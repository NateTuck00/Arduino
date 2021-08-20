uint8_t cons_ups = 0;
uint8_t cons_downs = 0;
uint8_t cons_lefts = 0;
uint8_t cons_rights = 0;
uint8_t cons_selects = 0;

//This 25 ms isr Handles button debouncing, should handle 3 second timeouts on extension, and should handle waiting 
//
//
void interrupt25() {

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

   if(extending == true){
    //measure pressure and overcurrent and add it to the dataString
    pressure = measurePressure(); 
    
   }//endif extending 

   if(retracting == true){
    pressure =  measurePressure(); 
   }//endif retracting
   

// 120*25ms = 3 seconds. Should never hit
if(three_sec_timer_on == true){
  three_sec_timer++;
  if(three_sec_timer >= 120){
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    
  }//endif
  
}//end 3sec timer


//400*25ms = 10 seconds. Should ALWAYS hit. 
if(ten_sec_timer_on == true){
  ten_sec_timer++;
  
  if(ten_sec_timer >= 400){
  
      if(digitalRead(7) == HIGH){
        // we still need to run the pre test logic...
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
    
      }//endif just finished retracting.

      if(digitalRead(8) == HIGH){
        
      }
      
      ten_sec_timer_on = false;
      ten_sec_timer = 0;
  }//endif
  
}//end 10 sec timer 


//Button debouncing code below//
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
  if (itr == 8) {
    itr = 0;
  }//endif
}//end ISR
