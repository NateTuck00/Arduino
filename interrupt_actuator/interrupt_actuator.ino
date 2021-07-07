
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

uint16_t tests = 1; // if on right screen up by 100 start on 100. left=1 go up by 5
uint8_t screen = 2; // Use left and right as iterator for screen if not running
//uint8_t pressure;//eventually if can't return it as function or flag high or low

uint8_t flags = 0; // flags |= B00000000
uint8_t flags_holder = 0;

uint8_t button_code = 0;
uint8_t itr = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }//endwhile


  lcd.begin(16, 2);
  lcd.setBacklight(VIOLET);

  if (!SD.begin(9)) {
    Serial.println("Initialization failed!");
    lcd.clear();
    lcd.print("Initialization failed");
    lcd.setBacklight(RED);
    while (1);
  }//endif
  Serial.println ("Initialization done.");

  myFile = SD.open ("test.txt", FILE_WRITE);//Open the file. Note that you can only open one file at a time. You must close this one before opening the next.


  if (myFile) { //if the file has opened correctly
    Serial.println("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");         // This writes into the actual file
    myFile.close();
    Serial.println("Done writing to file.");
  }//endif.

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



void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttons = lcd.readButtons();

  /*
     Loop needs to have the coding for what qualifies a disaster. We need to measure the pressure within runTest() itself.
     If pressure is OOB or dropping off, timeout for the travel of the actuator, switch turned off, or current is too high disaster=1;
     Can also check this within the ISR itself if slows down our loop too much.
  */


  //Serial.println("read_button called");
  if (buttons) {
    //Serial.println("if buttons");

    if (buttons & BUTTON_UP) {
      //Serial.println("Up in loop");
      button_code = 1;
    }//end up


    if (buttons & BUTTON_DOWN) {
      //Serial.println("Down in loop");
      button_code = 2;
    }//end up

    if (buttons & BUTTON_LEFT) {
      //Serial.println("Left in loop");
      button_code = 3;
    }//end up

    if (buttons & BUTTON_RIGHT) {
      //Serial.println("Right in loop");
      button_code = 4;
    }//end up

    if (buttons & BUTTON_SELECT) {
      //Serial.println("Select in loop");
      button_code = 5;

      flags_holder=0;
      flags_holder= (flags >> (1-1));
      if ((flags_holder & 1) == 1) {                                                                                         
      //if tests_needed=1;
        screen = 5;
        //tests_needed = 0;                                                                                               
        flags &= B11111110;
      }//end pause

    }//end up
  }//endif buttons

  if (!buttons) {
    button_code = 0;
    //Serial.println("No buttons");
  }//endif !buttons

  switch (itr) {
    case 1:
      flags_holder = 0;
      flags_holder = (flags >> (3-1));
      if ((flags_holder & 1) == 1) {                                                                                            
        //if button_flag==1
        handle_button(button_code);  // functions reset their flags at the end

      }//endif
      break;

    case 2:

      flags_holder = 0;
      flags_holder= (flags >> (2-1));
      if ((flags_holder & 1)== 1) {                                                                                                    
        //if newdisp_needed==1
        Serial.println("If newdisp needed =1");
        displayLCD();
      }//endif
      break;

    case 3:

      flags_holder = 0;
      flags_holder= (flags >> (1-1));
      if ((flags_holder & 1)== 1) {                                                                                                      
        //if tests_needed==1
        runTest();
      }//endif
      break;

    case 4:
      flags_holder = 0;
      flags_holder= (flags >> (4-1));
      if ((flags_holder & 1) == 1) {                                                                                                    
         //manual_control_needed
        // don't reset this flag. new display and controls.
      }//endif
      break;

    default:;       //Nada

  }//endswitch


}//end void loop();


void runTest() {
  // Display running menu. Select to pause. Right to run after select. Select again to stop. (menu)
  screen = 2;
  Serial.println("runTest called");
  char myStg[10];
  itoa(tests, myStg, 10);
  int len = strlen(myStg);

  lcd.setCursor(0, 0);

  if (tests > 0) {
    lcd.print("Running test ");
  }//endif

  for (int i = 0; i < len; i++) {
    lcd.print(myStg[i]);
  }//endfor

  delay(2000);
  lcd.clear();
  tests--;

  Serial.println(tests);

  if (tests < 1) {
    tests = 1;
    //tests_needed = 0;                                                                                                                                                                      
    flags &= B11111110;
    screen = 2;
    //newdisp_needed = 1;                                                                                                                                                                    
    flags |= B00000010;
  }//endif


}//endrunTest()


void displayLCD() {
  //if on left screen count is 1.
  //if on right count is 100;
  Serial.println("displayLCD called");
  lcd.clear();
  lcd.setCursor(0, 0);

  char myStg[10];
  itoa(tests, myStg, 10);
  int len = strlen(myStg);

  Serial.print("tests");
  Serial.println(tests);


  Serial.print("screen");
  Serial.println(screen);


  if (screen == 0) {
    //Left start screen
    lcd.print("Select:Run ");
    Serial.print("tests ");

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor

    Serial.println(tests);
  }//endif

  if (screen == 1) {
    //left count /disp
    lcd.print("L:+5 tests " );

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor

    Serial.print("tests ");
    Serial.println(tests);
  }//endif

  if (screen == 2) {
    //Main menu
    lcd.print("L:Some R:Many");

  }//endif

  if (screen == 3) {
    //right count / disp
    lcd.print("R:+100 tests ");

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor

    Serial.print("tests ");
    Serial.println(tests);
  }//endif

  if (screen == 4) {
    //right start screen
    lcd.print("Select:Run ");

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor

    Serial.print("tests ");
    Serial.println(tests);
  }//endif

  if (screen == 5) {
    lcd.print("L:edit R: ");

    for (int i = 0; i < len; i++) {
      lcd.print(myStg[i]);
    }//endfor
  }//endif pausescreen

  //newdisp_needed = 0;                                                                                                                                   
  flags &= B11111101;
}//end displayLCD(screen#)


void handle_button(uint8_t button_handler) {
  Serial.println("Handle button called");
  // Add control here for manual control of the actuator. Could be a set time or could be checked for at the start of the interrupt each time and a flag set to tell the ISR that the motor is on
  /*
    if(disaster==1){
      if(button_handler==1){
        //ignore the up case?
      }//endif UP

      if(button_handler==2){
         //ignore downs??
      }//endif DOWN

      if(button_handler==3){
        //retract motor and set motor on flag to be checked by ISR
      }//endif LEFT

      if(button_handler==4){
        //extend motor and set flag to be checked by ISR. Careful with this.

      }//endif RIGHT

      if(button_handler==5){
         //if select is pressed after an emergency, shut off?
      }//endif SELECT


    }//endif disaster
  */
  flags_holder = 0;
  flags_holder = (flags >>(5-1));
  if ((button_handler == 1) && ((flags_holder &1)== 0 )) {                                                                                                               

    if ((screen == 0) || (screen == 1)) {
      tests = tests + 5;
    }//endnestedif
    if ((screen == 3) || (screen == 4)) {
      tests = tests + 100;
    }//endnestedif

    //newdisp_needed = 1;                                                                                                                                     
    flags |= B00000010;
  }//end UP

  if ((button_handler == 2) && ((flags_holder & 1)== 0) ){                                                                                                           

    if ((screen == 0) || (screen == 1)) {
      if (tests > 5) {
        tests = tests - 5;
      }//enddoublynestedif
    }//endnestedif

    if ((screen == 3) || (screen == 4)) {
      if (tests > 100) {
        tests = tests - 100;
      }//enddoublynestedif
    }//endnestedif

    //newdisp_needed = 1;                                                                                                                                     
    flags |= B00000010; 
  }//end DOWN

  if ((button_handler == 3) && ((flags_holder & 1)== 0))   {                                                                                                         

    if (screen > 0) {
      screen--;
    }//endnestedif

    //newdisp_needed = 1;                                                                                                                                     
    flags |= B00000010;
  }//end LEFT

  if ((button_handler == 4) && ((flags_holder & 1)== 0)) {                                                                                                       

    if (screen < 4) { // 01 , 2main menu, 34
      screen++;
    }//endnestedif
    if (screen == 5) {
      if (tests > 0) {
        //tests_needed = 1;                                                                                                                                
        flags |= B00000001;
      }//endnestedif
    }//endif unpause

    //newdisp_needed = 1;                                                                                                                                     
    flags |= B00000010;
  }//end RIGHT

  if ((button_handler == 5) && ((flags_holder & 1)== 0)) {                                                                                                    
    /*
      //This is a recently added checker used to try and pause while running.
      if (tests_needed == 1) {
      screen = 5; // This is a special pause screen.
      tests_needed = 0;
      }//endif select while running
    */
    if ((screen == 0) || (screen == 4)) {
      //tests_needed = 1;                                                                                                                                     
      flags |= B00000001;
      // may need to use own seperate display function for running

    }//endnestedif
    //newdisp_needed = 1;                                                                                                                                       
    flags |= B00000010;
  }//end SELECT


  //button_flag = 0;                                                                                                                                           
  flags &= B11111011;
}//end handle_button()


uint8_t cons_ups = 0;
uint8_t cons_downs = 0;
uint8_t cons_lefts = 0;
uint8_t cons_rights = 0;
uint8_t cons_selects = 0;

ISR(TIMER1_COMPA_vect) {
  //Serial.println("ISR ");
  //read_button();//Sets the button_code variable

  /*
    if(manual_motor_on == 1){
      // can add an && above with specific iterator to adjust the length of manual control. Want to test with pressure sensor on 5v to see where to call disaster as well as to test length of pull (although only 2" variance)
      //turn off. Don't clear disaster code yet and just wait for more button presses to see. Can also add an iterator in the ISR to see how long the disaster button has been held
      // pin d1 and d2 connected to this.




    }//endif motor manually turned on

  */

  if (button_code == 1) {
    cons_ups++;
    //0 out the other ones
    cons_downs = 0;
    cons_lefts = 0;
    cons_rights = 0;
    cons_selects = 0;

    if (cons_ups > 8) {
      Serial.println("Held up long enough");
      cons_ups = 0;
      //button_flag = 1;                                                                                                                        ///3
      flags |= B00000100;

    }//end consecutive ups case
  }//end UP code

  if (button_code == 2) {
    cons_downs++;
    //0 out the other ones
    cons_ups = 0;
    cons_lefts = 0;
    cons_rights = 0;
    cons_selects = 0;

    if (cons_downs > 8) {
      Serial.println("Held down long enough");
      cons_downs = 0;
      //button_flag = 1;                                                                                                                          //3
      flags |= B00000100;

    }//end consecutive downs case
  }//end DOWN code

  if (button_code == 3) {
    cons_lefts++;
    //0 out the other ones
    cons_ups = 0;
    cons_downs = 0;
    cons_rights = 0;
    cons_selects = 0;

    if (cons_lefts > 8) {
      Serial.println("Held left long enough");
      cons_lefts = 0;
      //button_flag = 1;                                                                                                                              ///3
      flags |= B00000100;

    }//end consecutive lefts case
  }//end LEFT code

  if (button_code == 4) {
    cons_rights++;
    //0 out the other ones
    cons_ups = 0;
    cons_downs = 0;
    cons_lefts = 0;
    cons_selects = 0;

    if (cons_rights > 8) {
      Serial.println("Held right long enough");
      cons_rights = 0;
      //button_flag = 1;                                                                                                                              ///3
      flags |= B00000100;
      
    }//end consecutive rights case
  }//end RIGHT code

  if (button_code == 5) {
    cons_selects++;
    //0 out the other ones
    cons_ups = 0;
    cons_downs = 0;
    cons_lefts = 0;
    cons_rights = 0;

    if (cons_selects > 8) {
      Serial.println("Held select long enough");
      cons_selects = 0;
      //button_flag = 1;                                                                                                                              ///3
      flags |= B00000100; 
    }//end consecutive selects case
  }//end UP code

  if (button_code == 0) {
    //Serial.println("No press recognized in interrupt");
    //0 out everything
    cons_ups = 0;
    cons_downs = 0;
    cons_lefts = 0;
    cons_rights = 0;
    cons_selects = 0;
  }//end NO PRESS code



  itr++;
  if (itr == 5) {
    itr = 0;
  }//endif
}//end ISR
