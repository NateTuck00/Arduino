void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttons = lcd.readButtons();

  /*
     Loop needs to have the coding for what qualifies a disaster. We need to measure the pressure within runTest() itself.
     If pressure is OOB or dropping off, timeout for the travel of the actuator, switch turned off, or current is too high disaster=1;
     Can also check this within the ISR itself if slows down our loop too much.
  */


  //Serial.println("read_button called");
  if (buttons) {
    //Serial.println("if buttons");

    if (buttons & BUTTON_UP) {
      //Serial.println("Up in loop");
      button_code = 1;
    }//end up


    if (buttons & BUTTON_DOWN) {
      //Serial.println("Down in loop");
      button_code = 2;
    }//end up

    if (buttons & BUTTON_LEFT) {
      //Serial.println("Left in loop");
      button_code = 3;
    }//end up

    if (buttons & BUTTON_RIGHT) {
      //Serial.println("Right in loop");
      button_code = 4;
    }//end up

    if (buttons & BUTTON_SELECT) {
      //Serial.println("Select in loop");
      button_code = 5;


      flags_holder = 0;
      flags_holder = (flags >> (1-1));
      if ((flags_holder & 1) == 1) {                                                                                         
      //if tests_needed=1;
        screen = 5;
        //tests_needed = 0;                                                                                               
        flags &= B11111110;     // this one was commented out but should it be? 
      }//end pause
                                                                                      //Auto pause on select

    }//end up
  }//endif buttons

  if (!buttons) {
    button_code = 0;
    //Serial.println("No buttons");
  }//endif !buttons

  switch (itr) {
    case 1:
      flags_holder = 0;
      flags_holder = (flags >> (3-1));
      if ((flags_holder & 1) == 1) {                                                                                            
        //if button_flag==1
        handle_button(button_code);  // functions reset their flags at the end

      }//endif
      break;

    case 2:

      flags_holder = 0;
      flags_holder= (flags >> (2-1));
      if ((flags_holder & 1)== 1) {                                                                                                    
        //if newdisp_needed==1
        #ifdef debug
        Serial.println(F("If newdisp needed =1"));
        #endif
        displayLCD();
      }//endif
      break;

    case 3:

      flags_holder = 0;
      flags_holder= (flags >> (1-1));
      if ((flags_holder & 1)== 1) {                                                                                                      
        //if tests_needed==1
        //noInterrupts();
        runTest();
        //interrupts();
        
      }//endif
      break;

    case 4:
      flags_holder = 0;
      flags_holder= (flags >> (4-1));
      if ((flags_holder & 1) == 1) {                                                                                                    
         //manual_control_needed
        // don't reset this flag. new display and controls.
      }//endif
      break;

    default:;       //Nada

  }//endswitch


}//end void loop();
