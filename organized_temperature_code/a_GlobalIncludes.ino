  #include <SPI.h>
  #include <Wire.h> 
  #include <OLED_I2C.h>
  #include <avr/wdt.h>            
  #include "Temp_PID.h"
  #include "a_dht.h"
    

  //#define debug 1   // Uncommment the define to run in debugging mode and have a serial output 
  
  #define DHT22_PIN 6
  dht DHT;
  OLED myOLED(SDA, SCL, 4);//added  the 4 as a redundant reset pin
  #define resetPin 4       //redundancy 
  
  tempPID tp;// a custom class built for our temp PID

  double g_output;//0-255 AnalogWrite PWM
  double g_lastsp = 60;//Last SetPoint
  
  float g_f_latestTempF;
  float g_f_avg;//temp average
  float g_f_recentValues[10];//recent temp values

  volatile int8_t  g_loops = 0;//ISR iterators
  volatile int8_t g_itr = 0;
  volatile int16_t g_temp_itr = 0;
  
  extern uint8_t SmallFont [];//a character class for the display
  extern uint8_t BigNumbers [];//nums for display
  
  uint8_t g_read_flag = 0;
  uint8_t g_sensorfail = 0;
  uint8_t g_clr_cnt = 0;//clear display
  uint8_t g_blink_cnt = 0;//blink display
  uint8_t g_temp_timeout = 0;
  uint8_t g_voltage_warning = 0;
  uint8_t g_battery_shutoff = 0; 

  uint32_t g_below_goal = 0;
  uint32_t g_above_goal = 0;  //this can be used to count temp timeout. 2400 25ms loops= 1min
