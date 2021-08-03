

float measurePressure(){
  //4.5V = 3,000 PSI
  //.5V= 0 PSI;
  float sensorValue = analogRead(A2);   // /1023
  Serial.println(sensorValue);
  float pressure = (sensorValue / 1023) * 3000.0;

  return pressure;
}//end measurePressure



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float pressure= measurePressure();
  Serial.println(pressure);
}
