
//
//  (10k/(10k+39k))* Input Voltage 

void measureBatteryVoltage(){
  float sensorVal = analogRead(A1);
  float volt = (sensorVal/1023) * 12.6;

  if (volt < 2.5){      // if we're really below 12.6 volts
    g_voltage_warning++;
  }//endif

  else if (volt > 3.3){      // if we're really above 16 volts 
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
