  #include <SPI.h>
  #include <Wire.h> 
  #include <OLED_I2C.h>
  //#include <SparkFun_RHT03.h>
  #include <avr/wdt.h>            

  #include "Temp_PID.h"
  #include "a_dht.h"
  
    
  const int RHT03_DATA_PIN = 6; // RHT03 data pin
  //RHT03 rht; // This creates a RTH03 object, which we'll use to interact with the sensor
  #define DHT22_PIN 6
  dht DHT;
  OLED myOLED(SDA, SCL, 4);//added 
  
  #define resetPin 4
  
  tempPID tp;// a custom class built for our temp PID

  double g_output;
  double g_lastsp = 60;
  
  float g_f_latestTempF;
  float g_f_avg;
  float g_f_recentValues[10];

  volatile int8_t  g_loops = 0;//ISR iterators
  volatile int8_t g_itr = 0;
  volatile int16_t g_temp_itr = 0;
  
  extern uint8_t SmallFont [];
  extern uint8_t BigNumbers [];
  
  uint8_t g_read_flag = 0;
  uint8_t g_sensorfail = 0;
  uint8_t g_clr_cnt = 0;
  uint8_t g_blink_cnt = 0;
  uint8_t g_temp_timeout = 0;
  uint8_t g_voltage_warning = 0;
  uint8_t g_battery_shutoff = 0; 

  uint32_t g_below_goal = 0;
  uint32_t g_above_goal = 0;  //this can be used to count temp timeout. 2400 25ms loops= 1min
