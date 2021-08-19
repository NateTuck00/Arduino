
#include <SPI.h>
#include <SD.h >  
//#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>


#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
File myFile; 

#define MAXPRESSURE 1600.0
float sensorValue = 0;
float pressure = 0;
float vals [100];
int i = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    ;
  }//endwhile
  Serial.println(F("test")); 

  lcd.begin(16, 2);
  lcd.setBacklight(VIOLET);

  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);

  if (!SD.begin(9)) {
    Serial.println(F("SD Initialization failed!"));
    lcd.clear();
    lcd.print("Initialization failed");
    while (1);
  }//endif


  myFile = SD.open ("test.txt", FILE_WRITE);
  if (myFile){
    myFile.println("Test passes "); 
    myFile.close(); 
  }//endif
  delay(2000); 

  digitalWrite(2, HIGH); 
  while (digitalRead(8) != HIGH){
    digitalRead(8);
    delay(20);
    sensorValue = analogRead(A2);
    pressure= ((sensorValue - 102)/818) * MAXPRESSURE; 
    //pressure = (sensorValue/1023) * MAXPRESSURE; 
    if(i<109){
      vals[i] = pressure;
    }//endif 
    i++;
    Serial.println(sensorValue); 
  }//endwhile
  digitalWrite(2,LOW);


  digitalWrite(3,HIGH); 
  while(digitalRead(7) != HIGH){
    digitalRead(7);  
  }//endwhile
  digitalWrite(3,LOW);

  
  myFile = SD.open ("test.txt", FILE_WRITE);
  if (myFile){

    for(int j=0; j<99; j++){
      myFile.print("Pressure: "); 
      myFile.println(vals[j]);
    }//endfor
    myFile.close(); 
  }//endif
  else{
    lcd.clear();
    lcd.print("init failed"); 
    delay(2000); 
  }
}//end setup()

void loop() {
  // put your main code here, to run repeatedly:

  for (int j=0; j< 99; j++){
    lcd.print(j);
    lcd.print("pres ");
    lcd.println(vals[j]);
    delay(100);
    lcd.clear(); 
  }//endfor

}//endloop
