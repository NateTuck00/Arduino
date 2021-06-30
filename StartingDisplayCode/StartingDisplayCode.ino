#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <splash.h>             // may not be needed. 

#include <SparkFun_RHT03.h>
//#include <PID_v1.h>      can do this if I find my manual code isn't working

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int RHT03_DATA_PIN = 6; // RHT03 data pin
RHT03 rht; // This creates a RTH03 object, which we'll use to interact with the sensor
int sensorValue = 0;



void setup(){
  Serial.begin(9600);
  rht.begin(RHT03_DATA_PIN);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }//endif

  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 second
  display.clearDisplay();

  pinMode(10,OUTPUT);       // Declaring PWM pin 10 as an output
  
}//end setup



void loop() {
  analogWrite(10, 78);  //Here is where we declare the Hz value on pwm. 488 is the maximum value. analogWrite is x/255 with 255 being our 488 Hz in this scenario.  78 should be about 149.2HZ

  //sensorValue = analogRead(A3);
  
  display.clearDisplay();
  //temp control
///////////////////////////////////////////////////////////////////////////////////////////////////////
  int updateRet = rht.update();
  
  // If successful, the update() function will return 1.
  // If update fails, it will return a value <0
  if (updateRet == 1)
  {
    // The humidity(), tempC(), and tempF() functions can be called -- after 
    // a successful update() -- to get the last humidity and temperature
    // value 
    float latestHumidity = rht.humidity();
    float latestTempC = rht.tempC();
    float latestTempF = rht.tempF();
    
    // Now print the values:
    Serial.println("Humidity: " + String(latestHumidity, 1) + " %");
    Serial.println("Temp (F): " + String(latestTempF, 1) + " deg F");
    Serial.println("Temp (C): " + String(latestTempC, 1) + " deg C");
  }
  else
  {
    // If the update failed, try delaying for RHT_READ_INTERVAL_MS ms before
    // trying again.
    delay(RHT_READ_INTERVAL_MS);
  }
  
  delay(1000);

  //temp control
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.display();
  delay (2000);
}//end loop
