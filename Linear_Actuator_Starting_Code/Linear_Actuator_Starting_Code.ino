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
  //define act_o_pin  //act open pin

 
  uint16_t tests=0;// if on right screen up by 100 start on 100. left=1 go up by 5
  uint8_t screen=2;// Use left and right as iterator for screen if not running 
  uint8_t g_last_button=1;//I'll use this to check inputs with select 
  uint8_t g_button_before_last=1;
  uint8_t pressure;
   
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

}//end void setup()



void runTest(){
// Display running menu. Select to pause. Right to run after select. Select again to stop. (menu)
  lcd.setCursor(0,0);
  lcd.print("Running test");
  delay(2000);
  lcd.clear();
  
}//endrunTest()


// Can also pass screen in
void displayLCD(){
//if on left screen count is 1. 
//if on right count is 100;
lcd.clear();
lcd.setCursor(0, 0);

  if(screen==0){
    //Left start screen
    lcd.print("LSel:Start " + tests);
    Serial.print("tests ");
    Serial.println(tests);
  }//endif

  if(screen==1){
    //left count /disp
    lcd.print("L:Start " + tests);
    Serial.print("tests ");
    Serial.println(tests);
  }//endif

  if(screen==2){
    //Main menu
    lcd.print("L:Some R:Many");
    
  }//endif

  if(screen==3){
    //right count / disp
     lcd.print("R:Start "+ tests);
     Serial.print("tests ");
     Serial.println(tests);
  }//endif

  if(screen==4){
    //right start screen
    lcd.print("RSel:Start " + tests);
    Serial.print("tests ");
    Serial.println(tests);
  }//endif

  
}//end displayLCD(screen#)


   
void loop() {
  // put your main code here, to run repeatedly:
  //lcd.setCursor(0, 1);
  
   uint8_t buttons = lcd.readButtons();
    
    
  if (buttons) {
    
    if (buttons & BUTTON_UP) {
      
      if((screen== 1)||(screen==0)){// This is left menu
        tests=tests+5;
      }//endif screen 
      if((screen== 3)||(screen==4)){// This is right menu
        tests=tests+100;
      }//endif screen 

      
      
      g_button_before_last= g_last_button;
      g_last_button=1;    
    }// END IF UP PRESSED

    
    if (buttons & BUTTON_DOWN) {
      
      if((screen== 1)||(screen==0)){
        if(tests > 5){
          tests=tests-5;
        }//endnestedif
      }//endif screen 
      
      if((screen== 3)||(screen==0)){
        if(tests > 100){
          tests=tests-100;
        }//endnestedif
      }//endif screen 

      
    
      g_button_before_last= g_last_button;
      g_last_button=2;  
    }// END IF DOWN PRESSED


    if (buttons & BUTTON_LEFT) {
      if(screen > 0){
        screen--;
      }//endif
        
      displayLCD();
      
      g_button_before_last= g_last_button;
      g_last_button=3;  
    }// END IF LEFT PRESSED

    
    if (buttons & BUTTON_RIGHT) {
      if(screen < 4){
      screen++;
      displayLCD();
      }//endif

      g_button_before_last= g_last_button;
      g_last_button=4;  
    }// END IF RIGHT PRESSED
    
    if (buttons & BUTTON_SELECT) {
      
      if((screen==4)||(screen==0)){
        runTest();
      }//endif
     
    }// END IF SELECT PRESSED
  }//end if buttons

  if (screen > 4){
    screen=4;
  }
  
  if (screen < 0){
    screen=0;
  }

  
}//end void loop()
