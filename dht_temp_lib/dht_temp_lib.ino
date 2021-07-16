

#include "dht.h"

dht DHT;

#define DHT11_PIN 4
#define DHT21_PIN 5
#define DHT22_PIN 6


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);

  delay(2000);


}//end void loop()
