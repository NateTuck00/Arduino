
void extend(){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  
  noInterrupts();
  while (digitalRead(8) != LOW){
    digitalRead(8);
    digitalWrite(2,LOW);
  }//endwhile
  digitalWrite(3,LOW);
  interrupts();

}//extend()
