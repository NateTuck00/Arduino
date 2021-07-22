ISR(WDT_vect) // Watchdog timer interrupt.
{
  myOLED.clrScr();
// Include your code here - be careful not to use functions they may cause the interrupt to hang and prevent a reset

}//end ISR WDT
