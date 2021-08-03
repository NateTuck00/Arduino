
//
//
uint8_t itr =0;

void setup() {
  // put your setup code here, to run once:
  DDRD = B00000110;
  
 
  digitalWrite(1,LOW);
  digitalWrite(2,LOW); 
  ///////////////////////////////////////////
  //Timer Section. Editing is very dangerous.
  ///////////////////////////////////////////
  TCCR1A = 0;                               // set entire TCCR1A register to 0
  TCCR1B = 0;                               // same for TCCR1B
  TCNT1  = 0;                               //initialize counter value to 0

  OCR1A = 6249;                             // = (16*10^6) / (hz*prescaler) - 1 (must be <65536)    6249= 25ms
  TCCR1B |= (1 << WGM12);                   // turn on CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10);      // Set CS11 and 10 for 64 prescaler
  TIMSK1 |= (1 << OCIE1A);                  // enable timer compare interrupt
  /////////////////////////////////////////

}// end setup


//This is the code we need to run while the dpin receiving is getting a float and then once grounded we stop immediately. 
// As soon as it is grounded and we stop, we log the pressure immediately away and retract. We'll want to check the pressure and to stop every time and have that in an infinite loop. 
// These can be subfuncs if tests > 0 and then we do the lcd display stuff and we log the pressure. we're going to want to also read buttons in the middle to see stop
// we can log in the down time once retracted or there and maybe the pause doesn't work mid actuation but... I'd like it to
void runTest(){
  noInterrupts();
  PORTD = B00000010; 
  delay(500);
  PORTD = B00000000; 
  interrupts();
  
}//end runTest

void runTestReverse(){
  noInterrupts();
  PORTD = B00000100; 
  delay(500);
  PORTD = B00000000; 
  interrupts();
  
}//end runTest

void loop() {
  // put your main code here, to run repeatedly:
  if(itr==2){
    runTest();
  }

  if(itr == 20){
    runTestReverse();
  }
  itr++;
}//end loop



ISR(TIMER1_COMPA_vect) {


  
}//endISR
