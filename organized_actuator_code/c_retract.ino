

void retract(){
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  
  noInterrupts();
  while (digitalRead(7) != LOW){
    digitalRead(7);
    digitalWrite(3,LOW);
  }//endwhile
  digitalWrite(2,LOW);
  interrupts();
  
}//retract()
