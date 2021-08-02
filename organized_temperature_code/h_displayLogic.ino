
// This is the state machine's second stage where we check flag variables and errorcodes to control what is displayed
//

void displayLogic(){

  if (g_clr_cnt == 0){
      myOLED.clrScr();
    }//endif

    if(g_temp_timeout == 1){
      myOLED.setFont(SmallFont);
      myOLED.printNumF(g_f_latestTempF, 1, LEFT, 0);
      g_blink_cnt++;
      
      if(g_blink_cnt <= 10){                               
        //if it isn't blink time
        myOLED.print("EC:1", 45, 0);
        myOLED.printNumF(tp.dbl_setPoint, 1, 90, 0); 
      }//endnestedif
    }//endif

    else if (g_battery_shutoff == 1){
        myOLED.setFont(SmallFont);
        myOLED.printNumF(g_f_latestTempF, 1, LEFT, 0);
        g_blink_cnt++;

        if(g_blink_cnt != 10){
          myOLED.print("EC:2", 45, 0);
          myOLED.printNumF(tp.dbl_setPoint, 1, 90, 0);
        }//endnested if
    }//end else if
    
    else if( g_sensorfail != 1){
      myOLED.printNumF(g_f_latestTempF, 0, LEFT, 0);
      //myOLED.printNumF(g_output, 0, 40, 0);
      if ((abs(tp.dbl_setPoint - g_lastsp)) > .4){    //.4 here is a limit to change in set temp before we recognize it
         myOLED.printNumF(tp.dbl_setPoint, 0, 95, 0);
         g_lastsp = tp.dbl_setPoint; 
         g_clr_cnt ++;     
      }//endif dif >.3
    }//end else if no sensor fail

    
    
    if(g_sensorfail == 1){
      myOLED.setFont(SmallFont);
      myOLED.print("Reading ...", LEFT, 0);
      myOLED.printNumF(tp.dbl_setPoint, 1, 90, 0);
    }//endif fail

   
    if(g_blink_cnt > 10){
      g_blink_cnt = 0;
    }//endnested if
    
    
    if(g_clr_cnt >= 1){
      g_clr_cnt++;
      if(g_clr_cnt >= 80){
        g_clr_cnt = 0;
      }//endif 40
    }//endif

}//end void displayLogic()
