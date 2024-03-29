#include <SPI.h>
#include <SD.h >  // These two are for the SD card
//#include <avr/wdt.h> //watchdog timer

File myFile;

//#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();// This should connect to analog 4&5 and prevent you from reading from those.

#define debug 1 //uncomment this line to print serial, comment for some slight memory and runtime savings

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

#define NOP __asm__ __volatile__ ("nop\n\t")

volatile uint16_t tests = 1; // if on right screen up by 100 start on 100. left=1 go up by 5
uint8_t screen = 2; // Use left and right as iterator for screen if not running
float pressure;//eventually if can't return it as function or flag high or low

uint8_t flags = 0; // flags |= B00000000              // 6 in use. 7 can be switch flag
uint8_t flags_holder = 0;

uint8_t button_code = 0;
uint8_t itr = 0;

volatile uint8_t small_isr_counter = 0; 
volatile int three_sec_timer = 0; 
volatile int ten_sec_timer = 0; 
volatile bool three_sec_timer_on = false; 
volatile bool ten_sec_timer_on = false; 
volatile bool extending = false;
volatile bool retracting = false; 
volatile bool datalog_time = false; 
String dataString = ""; 
