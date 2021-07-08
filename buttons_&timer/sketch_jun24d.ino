void setup() {
  // put your setup code here, to run once:
  TCCR1A = 0;                               // set entire TCCR1A register to 0
  TCCR1B = 0;                               // same for TCCR1B
  TCNT1  = 0;                               //initialize counter value to 0
  
  OCR1A = 6249;                             // = (16*10^6) / (hz*prescaler) - 1 (must be <65536)    6249. 9999=25ms
  TCCR1B |= (1 << WGM12);                   // turn on CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10);      // Set CS11 and 10 for 64 prescaler 
  TIMSK1 |= (1 << OCIE1A);                  // enable timer compare interrupt
}

void loop() {
  // put your main code here, to run repeatedly:

}

void read_button(){
  uint8_t buttons = lcd.readButtons();
  
  Serial.println("read_button called");
  if(buttons){
    Serial.println("if buttons");

    if (buttons & BUTTON_UP){
      Serial.println("Up in loop");
      button_code=1;
    }//end up
    
    
    if (buttons & BUTTON_DOWN){
      //Serial.println("Down in loop");
      button_code=2;
    }//end up

    if (buttons & BUTTON_LEFT){
      //Serial.println("Left in loop");
      button_code=3;
    }//end up

    if (buttons & BUTTON_RIGHT){
      //Serial.println("Right in loop");
      button_code=4;
    }//end up

    if (buttons & BUTTON_SELECT){
      //Serial.println("Select in loop");
      button_code=5;
    }//end up
    
  }//endif buttons

  if(!buttons){
    button_code=0;
    //Serial.println("No buttons");
  }//endif !buttons

}// end read_button()


uint8_t itr=0;
ISR(TIMER1_COMPA_vect){
  if(itr==0){
    digitalWrite(10,HIGH);
  }

  if(itr==1){
    digitalWrite (10,LOW);
  }
  
  itr++;
  if(itr==2){
    itr=0;
  }
}//endisr
