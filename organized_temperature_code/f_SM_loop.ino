void loop(){ 
  //0: measure temp, measure set temp, constrain, computePID, analogwrite
  //1: display temp. 
  //2: update display                 
  wdt_reset();

  
  switch(g_itr){
    
    case 0://measure temp, measure set temp, constrain, computePID, analogwrite
    
    g_f_latestTempF = measureTemp();
    measureSetTemp();        
    checkTempBounds();

    g_loops++;
    if(g_loops==10){//g_loops reset to stay in the recent values array
      g_loops=0;
    }//endif
 
    tp.dbl_temp_inp = g_f_recentValues[g_loops];//remember tp is our tempPID object holding all our values needed for PID calculation
    g_output = tp.computePID(tp); 
    
    analogWrite(10,g_output);//PWM control for car heater written here 
   
  break;


    case 1://display temperature or errorcodes based on flags and timeout
    
    if(g_clr_cnt == 0){
      myOLED.clrScr();
    }//endif
    
    if( g_sensorfail != 1){
      myOLED.printNumF(g_f_latestTempF, 1, LEFT, 0);
     
      if ((abs(tp.dbl_setPoint - g_lastsp)) > .3){
         myOLED.printNumF(tp.dbl_setPoint, 1, 70, 0);
         g_lastsp = tp.dbl_setPoint; 
         g_clr_cnt = 1;     
      }//endif dif >.3
    }//endif no sensor fail
    
    if(g_sensorfail == 1){
      myOLED.setFont(SmallFont);
      myOLED.print("Reading ...", LEFT, 0);
      myOLED.printNumF(tp.dbl_setPoint, 1, 90, 0);
    }//endif fail
    
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

  break;  
    
    default:;     //Nada
    
  }//endswitch
  
}//end void loop()
