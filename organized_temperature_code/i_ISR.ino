uint16_t cons_misreads = 0;
ISR(TIMER3_COMPA_vect){
  
  if(tp.dbl_setPoint > tp.dbl_temp_inp){
    //if we can't reach our setpoint
    g_below_goal++;
    g_above_goal = 0;
  }//endif below goal

  if(tp.dbl_setPoint < tp.dbl_temp_inp){
    //if we are above our setpoint
    g_below_goal = 0;
    g_above_goal++;
  }//endif above goal

  if((g_below_goal < 400)&&(g_above_goal < 400)){
    g_temp_timeout = 0;
  }//endif
  
  if((g_below_goal >= 9600)||(g_above_goal >= 9600)){
    g_temp_timeout = 1;
  }//endif
  
  if(g_read_flag == 1){
    cons_misreads = 0;
  }//endif successful read
  
  if(g_read_flag == 0){
    cons_misreads++;
    if(cons_misreads > 10){
       g_sensorfail = 1;
    }//endif cons misreads
   }//endif misread
   
  g_itr++;
  if(g_itr == 3){
    g_itr=0;
  }//endif
  
}//end ISR()
