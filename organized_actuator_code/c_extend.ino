
void extend(){
  #ifdef debug
  Serial.println(F("extend called"));
  #endif
  //lcd.clear();
  //lcd.print("extending");
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  
}//extend()
