void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    ;
  }//endwhile

  lcd.begin(16, 2);
  lcd.setBacklight(VIOLET);

  if (!SD.begin(9)) {
    Serial.println("SD Initialization failed!");
    lcd.clear();
    lcd.print("Initialization failed");
    lcd.setBacklight(RED);
    while (1);
  }//endif
  Serial.println ("SD Initialization done.");

  myFile = SD.open ("test.txt", FILE_WRITE);//Open the file. Note that you can only open one file at a time. You must close this one before opening the next.


  if (myFile) { //if the file has opened correctly
    Serial.println("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");         // This writes into the actual file
    myFile.close();
    Serial.println("Done writing to file.");
  }//endif

  
  else {
    Serial.println("Error opening test.txt");
  }//endelse

  myFile = SD.open("test.txt");

  if (myFile) {
    Serial.println("test.txt:");

    while (myFile.available()) {
      Serial.write(myFile.read());          // Read out the file
    }//endwhile more left in file to read

    myFile.close();
  }//end if file opens correctly
  else {
    Serial.println("Error opening test.txt");
    lcd.setBacklight(RED);
  }//endelse file failed to open.


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

  Serial.println("Setup Complete");
  lcd.print("Left+5 Right+100");
}//endvoid setup
