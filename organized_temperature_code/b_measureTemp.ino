//measureTemp: simple quick return of the temp in F. Can add humidity with some changes in return or a global
float measureTemp(){

  int updateRet = rht.update();

  if(updateRet == 1){
    g_read_flag = 1;
    g_sensorfail = 0;
  }//endif 1
  
  if(updateRet == 0){
    g_read_flag = 0;
  }//endif no read
  
  return rht.tempF();// Note we can also pull a tempC or humidity
  
}//end measureTemp
