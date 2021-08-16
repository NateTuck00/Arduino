
//
//  (10k/(10k+39k))* Input Voltage = Voltage offboard

void measureBatteryVoltage(){
  static float sensorVal = analogRead(A1);
  static float volt_onboard = (sensorVal/1023) * 5; //This is a digital to analog conversion to find the volts /5 on the pin.

  #define UnderVolt 2.48 
  #define OverVolt 3.3

  #ifdef debug
  Serial.print(F("Sensor val: "));
  Serial.println(sensorVal);
  Serial.println(volt_onboard);
  #endif

  if (volt_onboard < UnderVolt){           // 2.48 volts on pin =< 12 volts off pin before voltage divider  (Volt * (10K/49k))< 12 
    g_voltage_warning++;
  }//endif

  else if (volt_onboard > OverVolt){      // if we're really above 16 volts offboard 
    g_voltage_warning++;
  }//endif

  else{
    g_voltage_warning = 0;  
    g_battery_shutoff = 0;
  }//if voltage is in range


  if (g_voltage_warning >= 10){
    g_battery_shutoff = 1;
  }//endif


  
}//end measureBatteryVoltage()
