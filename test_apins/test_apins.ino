void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
   float sensorValue = analogRead(A2); //potetiometer input pin
   float volts = (sensorValue / 1023) * 5.0;  
   float setPoint = 90- (35 * (volts/5));
   Serial.println(setPoint);
}
