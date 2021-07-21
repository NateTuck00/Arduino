void loop(){ 
  //0: measure temp, measure set temp, constrain, computePID, analogwrite
  //1: display temp. 
  //2: update display                 
  wdt_reset();

  
  switch(g_itr){
    
    case 0://measure temp, measure set temp, constrain, computePID, analogwrite

    g_temp_itr++;
    if(g_temp_itr == 4000){
      g_f_latestTempF = measureTemp();
      g_temp_itr = 0;
    }
    
    measureSetTemp();        
    checkTempBounds();

    g_loops++;
    if(g_loops==10){//g_loops reset to stay in the recent values array
      g_loops=0;
    }//endif
 
    tp.dbl_temp_inp = g_f_recentValues[g_loops];//remember tp is our tempPID object holding all our values needed for PID calculation
    g_output = tp.computePID(tp); 

    if (g_battery_shutoff == 0){
      analogWrite(10,g_output);//PWM control for car heater written here 
    }//endif
    else{
      analogWrite(10,0);  
    }//endelse
    
  break;


    case 1://display temperature or errorcodes based on flags and timeout
    
    if (g_clr_cnt == 0){
      myOLED.clrScr();
    }//endif

    if(g_temp_timeout == 1){
      myOLED.setFont(SmallFont);
      myOLED.printNumF(g_f_latestTempF, 1, LEFT, 0);
      g_blink_cnt++;
      
      if(g_blink_cnt != 10){                               //if it isn't blink time
        myOLED.print("EC:1", 45, 0);
        myOLED.printNumF(tp.dbl_setPoint, 1, 90, 0); 
      }//endnestedif
    }//endif
    
    else if( g_sensorfail != 1){
      myOLED.printNumF(g_f_latestTempF, 0, LEFT, 0);
      myOLED.printNumF(g_output, 0, 40, 0);
      if ((abs(tp.dbl_setPoint - g_lastsp)) > .4){
         myOLED.printNumF(tp.dbl_setPoint, 0, 95, 0);
         g_lastsp = tp.dbl_setPoint; 
         g_clr_cnt = 1;     
      }//endif dif >.3
    }//end else if no sensor fail

    else if (g_battery_shutoff == 1){
        myOLED.setFont(SmallFont);
        myOLED.printNumF(g_f_latestTempF, 1, LEFT, 0);
        g_blink_cnt++;

        if(g_blink_cnt != 10){
          myOLED.print("EC:2", 45, 0);
          myOLED.printNumF(tp.dbl_setPoint, 1, 90, 0);
        }//endnested if
    }//end else if
    
    if(g_sensorfail == 1){
      myOLED.setFont(SmallFont);
      myOLED.print("Reading ...", LEFT, 0);
      myOLED.printNumF(tp.dbl_setPoint, 1, 90, 0);
    }//endif fail

   
    if(g_blink_cnt >= 10){
      g_blink_cnt = 0;
    }//endnested if
    
    
    if(g_clr_cnt >= 1){
      g_clr_cnt++;
      if(g_clr_cnt >= 40){
        g_clr_cnt = 0;
      }//endif 40
    }//endif
    
  break;

    case 2: //update display. Check font in case of previous error codes swapping to small font
      myOLED.update(); 
      myOLED.setFont(BigNumbers);
      //measureBatteryVoltage();
  break;  
    
    default:;     //Nada
    
  }//endswitch
  
}//end void loop()
