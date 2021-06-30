void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
   //int sensorValue = analogRead(A0);// check pins for analog in
   
   //float voltage = sensorValue * (5.0 / 1023.0);
   float voltage= 76.3;
   //voltage line assumed 5vin and 1023 possible output vals
   
   Serial.println(voltage);// serial print may not be what we end up using with the qwiic connect display, but it's a start
}
