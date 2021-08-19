


ISR(TIMER0_COMPA_vect){
//if retraction flag is high, keep checking that pin and shut off the digital write if it hits. Otherwise, for every 5 calls of this function we call the secondary ISR function
//if(retracting == 1){
//retracting_timer++;         // this being the three second timeout for both extension and retraction.  
//  if(digitalRead(7) == HIGH){
//    digitalWrite(3,LOW);
//    retracting = 0; 
//    retracting_timer=0;
//    dutycycle_timer++;      // this timer has to be 10 seconds.
//    datalog_needed = 1;     // this can mark us to datalog 
//  }
//}

//for every 5 calls here we call the other isr that handles timing in 25ms 
small_isr_counter++;
if(small_isr_counter == 5){
  small_isr_counter = 0;  
  interrupt25();
}//endif
  
}//end ISR 
