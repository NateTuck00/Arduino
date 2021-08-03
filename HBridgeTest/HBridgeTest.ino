void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT);
  pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  delay(1000);
  digitalWrite(1,HIGH);
  delay(5000);
  digitalWrite(1,LOW);
  delay(1000);
  digitalWrite(2,HIGH);
  delay(5000);
  digitalWrite(2,LOW);
  delay(30000); 
 
}
