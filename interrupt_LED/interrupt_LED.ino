
boolean toggle1 = 0;

void setup() {
  // put your setup code here, to run once:
  cli();//Stops interrupts

  TCCR3A = 0;// set entire TCCR1A register to 0
  TCCR3B = 0;// same for TCCR1B
  TCNT3  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR3A = 6249;// = (16*10^6) / (hz*prescaler) - 1 (must be <65536)
  // turn on CTC mode
  TCCR3B |= (1 << WGM32);
  // Set CS11 and 10 for 64 prescaler
  TCCR3B |= (1 << CS31) | (1 << CS30);  
  // enable timer compare interrupt
  TIMSK3 |= (1 << OCIE3A);


sei(); 
}


ISR(TIMER3_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  if (toggle1){
    digitalWrite(8,HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(8,LOW);
    toggle1 = 1;
  }
}



void loop() {
  // put your main code here, to run repeatedly:

}
