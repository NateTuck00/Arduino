#include <SPI.h>
#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET 4
//#define SCREEN_ADDRESS 0x3c

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);

  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(6,HIGH);
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Hello, World!"));
  display.display();

  digitalWrite(6,LOW);
}
