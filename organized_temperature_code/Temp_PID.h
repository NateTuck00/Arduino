//computePID: uses several global variables to calculate errors in temp/setTemp, and time. Could have temp timeout inside or externally
//Consts: P&I
//Inputs: "inp" temp, g_previousTime, g_cumulativeError, g_setPoint
//Outputs: double out
#ifndef Temp_PID
#define Temp_PID

#include "Arduino.h"


const uint8_t kp = 20;
const uint8_t ki = 1;

class tempPID 
{
  public:
  double temp_inp; 
  double g_previousTime;
  double g_cumulativeError;
  double g_setPoint;

  double computePID(tempPID tp);
  
  private:
  
};


#endif
