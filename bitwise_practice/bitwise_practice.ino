void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

 uint8_t flags=0;
 flags |= B00000100;
 uint8_t flags_holder=0;
 flags_holder = (flags >> (3-1));
  if( (flags_holder & 1)==1){

    Serial.println("True. 3 is recognized");
  }
  else{
    Serial.println("you messed up. reread");
  }


}

void loop() {
  // put your main code here, to run repeatedly:

}
