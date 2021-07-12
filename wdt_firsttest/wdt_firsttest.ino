#include <avr/wdt.h>

void setup() {
  // put your setup code here, to run once:
  //wdt_enable(WDTO_4S);
  Serial.begin(9600);
  wdt_reset();
  WDTCSR |= (1<< WDCE)|(1<<WDE); 
  WDTCSR = (1 << WDIE)|(1 << WDE)|(0 << WDP3)|(1 << WDP2)|(1 << WDP1)|(0 << WDP0);
    
}//end voidsetup()

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
  Serial.println("Anotha one.");
  wdt_reset();
}//end void loop()

ISR(WDT_vect) // Watchdog timer interrupt.
{
// Include your code here - be careful not to use functions they may cause the interrupt to hang and
// prevent a reset.
  Serial.println("We hit watchdogs here");
}//end ISR WDT
