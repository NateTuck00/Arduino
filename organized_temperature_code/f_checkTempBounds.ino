
//Note that this function uses a couple globals with the recent temps,array, and average.
//The code is mainly separated to improve the State Machine's legibility

void checkTempBounds(){
    static float dif;
    static float sum;
    
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
  
}//end checkTempBounds()
