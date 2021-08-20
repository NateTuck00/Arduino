

void retract(){
  #ifdef debug
  Serial.println(F("retract called"));
  #endif
  //lcd.clear();
  //lcd.print("retracting");
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  
}//retract()
