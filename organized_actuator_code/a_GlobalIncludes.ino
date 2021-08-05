#include <SPI.h>
#include <SD.h >  // These two are for the SD card

//#include <SdFat.h>
//SdFat SD;



File myFile;

//#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();// This should connect to analog 4&5 and prevent you from reading from those.

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

uint16_t tests = 1; // if on right screen up by 100 start on 100. left=1 go up by 5
uint8_t screen = 2; // Use left and right as iterator for screen if not running
//uint8_t pressure;//eventually if can't return it as function or flag high or low

uint8_t flags = 0; // flags |= B00000000              // 6 in use. 7 can be switch flag
uint8_t flags_holder = 0;

uint8_t button_code = 0;
uint8_t itr = 0;
