uint16_t cons_misreads = 0;
ISR(TIMER3_COMPA_vect){
  
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
