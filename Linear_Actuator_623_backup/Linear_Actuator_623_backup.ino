/*
  This is the first version of the code I'll be using for the linear actuator clutch tester project

  Goals: 
  Log data into an SD card
  Use the buttons on the LCD display as well as the display 
  Export CSV files to said SD card
  Control thee two seperate motors for the linear actuator, and potentially detect the travel distance of the actuator 

*/
  #include <SPI.h>
  #include <SD.h >  // These two are for the SD card 

  File myFile;

  #include <Wire.h>
  #include <Adafruit_RGBLCDShield.h>
  #include <utility/Adafruit_MCP23017.h>

  Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();// This should connect to analog 4&5 and prevent you from reading from those.
  
  #define RED 0x1
  #define YELLOW 0x3
  #define GREEN 0x2
  #define TEAL 0x6
  #define BLUE 0x4
  #define VIOLET 0x5
  #define WHITE 0x7

  //define act_c_pin  //Whichever wire we connect the closing motor signal to (although likely a relay will be needed)
  //define act_o_pin  

  void runTest(){

    
  }//endrunTest()

  
void setup() {
  // Activate serial and SD card, potentially find actuator or open entirely
  Serial.begin(9600);
  while(!Serial){
      ;
  }//endwhile
  lcd.begin(16, 2);
  lcd.setBacklight(WHITE);
  
  Serial.print("Initializing SD Card...");
  lcd.print("Initializing SD ");// This is the most you'll want to print to the LCD at a time

  if (!SD.begin(9)) {
    Serial.println("Initialization failed!"); 
    lcd.clear();
    lcd.print("Initialization failed");
    lcd.setBacklight(RED);
    while (1);
  }//endif
  Serial.println ("Initialization done.");
  
  myFile = SD.open ("test.txt", FILE_WRITE);//Open the file. Note that you can only open one file at a time. You must close this one before opening the next. 


  if(myFile){//if the file has opened correctly
    Serial.println("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");         // This writes into the actual file
    myFile.close();
    Serial.println("Done writing to file.");
  }//endif. 
  
  else{ 
    Serial.println("Error opening test.txt");
  }//endelse

  myFile = SD.open("test.txt");
  
  if(myFile){
      Serial.println("test.txt:");

      while (myFile.available()){
        Serial.write(myFile.read());          // Read out the file
      }//endwhile more left in file to read
      
      myFile.close();
  }//end if file opens correctly
  else{
    Serial.println("Error opening test.txt");
    lcd.setBacklight(RED); 
  }//endelse file failed to open.

  lcd.clear();
  lcd.print("Setup complete ");
  delay(2000);
  lcd.clear();

  lcd.print("Double press select to confirm ");
  delay(1000);
  
  for (int positionCounter = 0; positionCounter < 15; positionCounter++) {
   lcd.scrollDisplayLeft();
   delay(400);  //Scrolling speed
 }

   for (int positionCounter = 0; positionCounter < 15; positionCounter++) {
   lcd.scrollDisplayRight();
   delay(400);
 }  
  
  lcd.clear();
}//end void setup()





void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
 
   uint8_t buttons = lcd.readButtons();
   uint8_t last_button;//I'll use this to check inputs with select 
   uint8_t button_before_last; 
   
  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print("Up Menu ");
      lcd.setBacklight(RED);
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("Down Menu ");
      lcd.setBacklight(YELLOW);
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print("Left Menu ");
      lcd.setBacklight(GREEN);
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("Right Menu ");
      lcd.setBacklight(TEAL);
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SELECT ");
      lcd.setBacklight(VIOLET);
    }
  }//end if buttons
  
}//end void loop()
