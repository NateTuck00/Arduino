  #include <SPI.h>
  #include <Wire.h> 
  #include <OLED_I2C.h>
  #include <SparkFun_RHT03.h>
  #include <avr/wdt.h>            // Including watchdog timer

  #include "Temp_PID.h"
  
    
  const int RHT03_DATA_PIN = 6; // RHT03 data pin
  RHT03 rht; // This creates a RTH03 object, which we'll use to interact with the sensor
  OLED myOLED(SDA, SCL);
  
  tempPID tp;

  
  double g_output;
  double g_lastsp = 60;
  
  float g_latestTempF;
  float g_avg;
  float recentValues[10];

  volatile int8_t  g_loops = 0;//ISR iterators
  volatile int8_t g_itr = 0;
  extern uint8_t SmallFont [];
  extern uint8_t BigNumbers [];
  uint8_t g_read_flag = 0;
  uint8_t g_sensorfail = 0;
  uint8_t g_clr_cnt = 0;
