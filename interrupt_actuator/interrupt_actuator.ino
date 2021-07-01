
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
uint8_t g_last_button = 1; //I'll use this to check inputs with select
uint8_t g_button_before_last = 1;
uint8_t pressure;


uint8_t tests_needed = 0;
uint8_t newdisp_needed = 0;
uint8_t button_flag = 0;
uint8_t manual_control_needed = 0;


uint8_t button_code = 0;
uint8_t itr = 0;
uint8_t button_holder = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setBacklight(VIOLET);

  ///////////////////////////////////////////
  //Timer Section. Editing is very dangerous.
  ///////////////////////////////////////////
  TCCR1A = 0;                               // set entire TCCR1A register to 0
  TCCR1B = 0;                               // same for TCCR1B
  TCNT1  = 0;                               //initialize counter value to 0

  OCR1A = 20000;                             // = (16*10^6) / (hz*prescaler) - 1 (must be <65536)    6249= 25ms
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
    }//end up
  }//endif buttons

  if (!buttons) {
    button_code = 0;
    //Serial.println("No buttons");
  }//endif !buttons

  switch (itr) {
    case 1:
      if (button_flag == 1) {
        handle_button(button_code);  // functions reset their flags at the end

      }//endif
      break;

    case 2:
      if (newdisp_needed == 1) {
        Serial.println("If newdisp needed =1");
        displayLCD();
      }//endif
      break;

    case 3:
      if (tests_needed == 1) {
        runTest();
      }//endif
      break;

    case 4:
      if (manual_control_needed) {
        // don't reset this flag. new display and controls.
      }//endif
      break;

    default:;       //Nada

  }//endswitch


}//end void loop();

/*
  void read_button(){
  buttons = lcd.readButtons();

  if(buttons){
    //Serial.println("if buttons");

    if (buttons & BUTTON_UP){
      Serial.println("Up in loop");
      button_code=1;
    }//end up


    if (buttons & BUTTON_DOWN){
      //Serial.println("Down in loop");
      button_code=2;
    }//end up

    if (buttons & BUTTON_LEFT){
      //Serial.println("Left in loop");
      button_code=3;
    }//end up

    if (buttons & BUTTON_RIGHT){
      //Serial.println("Right in loop");
      button_code=4;
    }//end up

    if (buttons & BUTTON_SELECT){
      //Serial.println("Select in loop");
      button_code=5;
    }//end up

  }//endif buttons

  if(!buttons){
    button_code=0;
    //Serial.println("No buttons");
  }//endif !buttons

  }// end read_button()
*/

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
    tests_needed = 0;
    screen = 2;
    newdisp_needed = 1;
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

  newdisp_needed = 0;

}//end displayLCD(screen#)


void handle_button(uint8_t button_handler) {
  Serial.println("Handle button called");
  if (button_handler == 1) {
    if ((screen == 0) || (screen == 1)) {
      tests = tests + 5;
    }//endnestedif
    if ((screen == 3) || (screen == 4)) {
      tests = tests + 100;
    }//endnestedif
    newdisp_needed = 1;
  }//end UP

  if (button_handler == 2) {
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
    newdisp_needed = 1;
  }//end DOWN

  if (button_handler == 3) {
    if (screen > 0) {
      screen--;
    }//endnestedif
    newdisp_needed = 1;
  }//end LEFT

  if (button_handler == 4) {
    if (screen < 4) { // 01 , 2main menu, 34
      screen++;
    }//endnestedif

    if (screen == 5) {
      if (tests > 0) {
        tests_needed = 1;
      }//endnestedif
    }//endif unpause

    newdisp_needed = 1;
  }//end RIGHT

  if (button_handler == 5) {

    //This is a recently added checker used to try and pause while running.
    if (tests_needed == 1) {
      screen = 5; // This is a special pause screen.
      tests_needed = 0;
    }//endif select while running

    if ((screen == 0) || (screen == 4)) {
      tests_needed = 1;
      // may need to use own seperate display function for running

    }//endnestedif
    newdisp_needed = 1;
  }//end SELECT


  button_flag = 0;
}//end handle_button()


uint8_t cons_ups = 0;
uint8_t cons_downs = 0;
uint8_t cons_lefts = 0;
uint8_t cons_rights = 0;
uint8_t cons_selects = 0;

ISR(TIMER1_COMPA_vect) {
  //Serial.println("ISR ");
  //read_button();//Sets the button_code variable

  if (button_code == 1) {
    cons_ups++;
    //0 out the other ones
    cons_downs = 0;
    cons_lefts = 0;
    cons_rights = 0;
    cons_selects = 0;

    if (cons_ups > 4) {
      Serial.println("Held up long enough");
      cons_ups = 0;
      button_flag = 1;

    }//end consecutive ups case
  }//end UP code

  if (button_code == 2) {
    cons_downs++;
    //0 out the other ones
    cons_ups = 0;
    cons_lefts = 0;
    cons_rights = 0;
    cons_selects = 0;

    if (cons_downs > 4) {
      Serial.println("Held down long enough");
      cons_downs = 0;
      button_flag = 1;

    }//end consecutive downs case
  }//end DOWN code

  if (button_code == 3) {
    cons_lefts++;
    //0 out the other ones
    cons_ups = 0;
    cons_downs = 0;
    cons_rights = 0;
    cons_selects = 0;

    if (cons_lefts > 4) {
      Serial.println("Held left long enough");
      cons_lefts = 0;
      button_flag = 1;

    }//end consecutive lefts case
  }//end LEFT code

  if (button_code == 4) {
    cons_rights++;
    //0 out the other ones
    cons_ups = 0;
    cons_downs = 0;
    cons_lefts = 0;
    cons_selects = 0;

    if (cons_rights > 4) {
      Serial.println("Held right long enough");
      cons_rights = 0;
      button_flag = 1;

    }//end consecutive rights case
  }//end RIGHT code

  if (button_code == 5) {
    cons_selects++;
    //0 out the other ones
    cons_ups = 0;
    cons_downs = 0;
    cons_lefts = 0;
    cons_rights = 0;

    if (cons_selects > 4) {
      Serial.println("Held select long enough");
      cons_selects = 0;
      button_flag = 1;

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
