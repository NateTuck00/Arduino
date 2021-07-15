void loop(){ 
  //0: measure temp, measure set temp, constrain, computePID, analogwrite
  //1: display temp. 
  //2: update display                 
  wdt_reset();
  float dif;
  float sum;
  
  switch(g_itr){
    
    case 0://measure temp, measure set temp, constrain, computePID, analogwrite
    
    g_f_latestTempF = measureTemp();
    measureSetTemp();        
          
    if((g_f_latestTempF==0.0)||(g_f_latestTempF==32.00)){ //if errorcode temp
       sum=0;
       for(int i=0; i<10; i++){
          sum= sum + g_f_recentValues[i];   
       }//endfor
       g_f_avg= sum/10; 
       g_f_recentValues[g_loops]= g_f_avg;// Toss the 0.0s to read what the temp before read.
    }//endif 0.0
          
    else if((g_f_latestTempF > 99)||(g_f_latestTempF < 10)){  // if temperature value is concerning
      dif= g_f_latestTempF - g_f_avg;
      if (abs(dif) >20){
        g_f_recentValues[g_loops]= g_f_avg;   
      }//if it randomly reads 99 on a bump and shorts
    }//end elseif 99+
    
    else{ // if the temperature value has no issues
      g_f_recentValues[g_loops]=g_f_latestTempF;                                 
    }//endelse

    g_loops++;
    if(g_loops==10){//g_loops reset to stay in the recent values array
      g_loops=0;
    }//endif
 
    tp.dbl_temp_inp = g_f_recentValues[g_loops];
    g_output = tp.computePID(tp); //note this was g_latestTempF but to incorporate the bounds checks with 32.00 and 0.0 we use the same value as we already checked
    
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
