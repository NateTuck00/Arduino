


ISR(TIMER0_COMPA_vect){
//if retraction flag is high, keep checking that pin and shut off the digital write if it hits. Otherwise, for every 5 calls of this function we call the secondary ISR function

if(retracting == true){
  three_sec_timer_on = true;       // this being the three second timeout for both extension and retraction.
    
   if(digitalRead(7) == HIGH){
      digitalWrite(3,LOW);
      retracting = false; 
      three_sec_timer_on = false; 
      three_sec_timer = 0;
      ten_sec_timer_on = true;      // this timer has to be 10 seconds.
      datalog_time = true;     // this can mark us to datalog 
  }//end nested if
}//endif


if(extending == true){
  three_sec_timer_on = true;       // this could be an overwrite of this variable and unneeded. 
  #ifdef debug
  Serial.print(F("3 sec timer (/120): "));
  Serial.println(three_sec_timer);
  #endif
    
   if(digitalRead(8) == HIGH){
      digitalWrite(2,LOW);
      extending = false; 
      three_sec_timer_on = false;
      three_sec_timer = 0;
      ten_sec_timer_on = true;      // this timer has to be 10 seconds.
      datalog_time = true;     // this can mark us to datalog 
  }//end nested if
}//endif


//for every 5 calls here we call the other isr that handles timing in 25ms 
small_isr_counter++;
if(small_isr_counter == 5){
  small_isr_counter = 0;  
  interrupt25();
}//endif
  
}//end ISR 
