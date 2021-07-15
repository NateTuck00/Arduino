/*
  This cpp contains a PID implementation for temperature using P and I
  The output is scaled 0-255 with the ends capped for pwm safety bounds. 
  The cumulative error bounds can be adjusted to change the curve and windup of the PID
*/

#include "Arduino.h"
#include "Temp_PID.h"

double tempPID::computePID(tempPID tp) {
  double currentTime = millis();
  double elapsedTime = (double)(currentTime - tp.g_previousTime);

  double error = temp_inp - g_setPoint; // error here means how far off our temp_input temp is from where the gauge is set
  g_cumulativeError += error * elapsedTime;//We clamp how much this can affect our output below to prevent windup 

  if(abs(g_cumulativeError*ki)>40){

    if(g_cumulativeError > (10/ki)){
      g_cumulativeError=(160/ki); 
    }//endif positive cumulative error

    if(g_cumulativeError < (-70/ki)){
      g_cumulativeError=(-70/ki);   
    }//endif negative cumulative error
    
  }//endif cumulating error either direction
  
  double out = kp * error + ki * g_cumulativeError;//output determined by I and P. 
  g_previousTime = currentTime;

  //check output bounds
    if(out > 229){
      out=229;
    }//endif
    
    if(out < 26){
      out=26; 
    }//endif out of bounds

  return out;
}// end 
