void loop(){ 
  //0: measure temp, measure set temp, constrain, computePID, analogwrite
  //1: display temp. 
  //2: update display and check battery voltage                 
  wdt_reset();

  
  switch(g_itr){
    
    case 0://measure temp, measure set temp, constrain, computePID, analogwrite

    g_temp_itr++;
    if(g_temp_itr == 4000){
      g_f_latestTempF = measureTemp();
      g_temp_itr = 0;
    }//endif
    
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
    
    displayLogic();
    
  break;

    case 2: //update display. Check font in case of previous error codes swapping to small font
      myOLED.update(); 
      myOLED.setFont(BigNumbers);
      //measureBatteryVoltage();
  break;  
    
    default:;     //Nada
    
  }//endswitch
  
}//end void loop()
