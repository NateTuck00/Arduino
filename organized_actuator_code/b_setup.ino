void setup() {
  // put your setup code here, to run once:
    //pinMode(4, INPUT);
//#ifdef debug
  Serial.begin(9600);

  while (!Serial) {
    ;
  }//endwhile
//#endif

  lcd.begin(16, 2);
  lcd.setBacklight(VIOLET);


  if (!SD.begin(9)) {
#ifdef debug
    Serial.println(F("SD Initialization failed!"));
#endif

    lcd.clear();
    lcd.print("Initialization failed");
    lcd.setBacklight(RED);
    while (1);
  }//endif
#ifdef debug
  Serial.println (F("SD Initialization done."));
#endif

  myFile = SD.open ("test.txt", FILE_WRITE);//Open the file. Note that you can only open one file at a time. You must close this one before opening the next.


  if (myFile) { //if the file has opened correctly
#ifdef debug
    Serial.println(F("Writing to test.txt..."));
#endif

    myFile.println("test,current,pressure");         // This writes into the actual file
    myFile.close();
#ifdef debug
    Serial.println(F("Done writing to file."));
#endif
  }//endif


  else {
#ifdef debug
    Serial.println(F("Error opening test.txt"));
#endif
  }//endelse

  myFile = SD.open("test.txt");

  if (myFile) {
#ifdef debug
    Serial.println(F("test.txt:"));
#endif

    while (myFile.available()) {
      Serial.write(myFile.read());          // Read out the file
    }//endwhile more left in file to read

    myFile.close();
  }//end if file opens correctly
  else {
#ifdef debug
    Serial.println(F("Error opening test.txt"));
#endif

    lcd.setBacklight(RED);
  }//endelse file failed to open.



#ifdef debug
    Serial.println(F("Timers turning on."));
#endif
  ///////////////////////////////////////////
  //Timer Section. Editing is very dangerous.
  ///////////////////////////////////////////
  //WDTCSR |= (1 << WDCE)|(1 << WDE);
  //WDTCSR  = (1 << WDIE)|(1 << WDE)|(1 << WDP3)|(0 << WDP2)|(0 << WDP1)|(1 <<WDP0);   //1001 = 8 seconds 
  
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  
  OCR0A = 78;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS02) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  /////////////////////////////////////////

#ifdef debug
  Serial.println(F("Setup Complete"));
#endif


  lcd.print("Left+5 Right+100");
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
}//endvoid setup
