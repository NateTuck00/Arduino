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

  uint16_t tests=0;// if on right screen up by 100 start on 100. left=1 go up by 5
  uint8_t screen=2;// Use left and right as iterator for screen if not running 
  uint8_t g_last_button=1;//I'll use this to check inputs with select 
  uint8_t g_button_before_last=1;
  uint8_t pressure;
  
void setup() {
  // put your setup code here, to run once:
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
}///end void setup()

void runTest(){
// Display running menu. Select to pause. Right to run after select. Select again to stop. (menu)
  lcd.setCursor(0,0);
  lcd.print("Running test");
  delay(2000);
  lcd.clear();
  
}//endrunTest()

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

void handle_button(uint8_t button_code, uint8_t screen, uint16_t tests){
  
  if(button_code==0){
    return;
  }//endif0

  if(button_code==1){
    Serial.println("Up");
  }//end UP

  if(button_code==2){
    Serial.println("Down");
  }//end DOWN

  if(button_code==3){
    Serial.println("Left");
  }//end LEFT

  if(button_code==4){
    Serial.println("Right");
  }//end RIGHT

  if(button_code==5){
    Serial.println("Select");
  }//end SELECT
  
}//end void handle_button()



uint8_t first_time;
uint8_t secnd_time;
uint8_t button_code;
uint8_t bpressed;
void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttons = lcd.readButtons();
  
  if(buttons){
    Serial.println("if buttons");
    
  
      Serial.println("While buttons");
      if(buttons & BUTTON_UP){
      Serial.println("UP HELD");
      button_code=1;
      
      }//endif UP

      if(buttons & BUTTON_DOWN){
      button_code=2;
      
      }//endif DOWN

      if(buttons & BUTTON_LEFT){
      button_code=3;
      
      }//endif LEFT

      if(buttons & BUTTON_RIGHT){
      button_code=4;
      
      }//endif RIGHT

      if(buttons & BUTTON_SELECT){
      button_code=5;
      
      }//endif SELECT


  
  handle_button(button_code,screen,tests);
  
    

    
  }//endifbuttons

}//END VOID LOOP
