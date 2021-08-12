

void extend(){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  delay(2000);
  noInterrupts();
  while (digitalRead(6) != HIGH){
    digitalRead(6);
    digitalWrite(2,LOW);
  }
  interrupts();

}
