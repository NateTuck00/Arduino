//This is a mock up for my arduino gardening device

//For right now, this device will measure light coming into the device, measure moisture, and use either a solenoid or a pump to water the plant

//potential expansions: additional plants in a line with a dc motor controlling some wheel drive, light control instead of a timed outlet on LED lights

//Inputs: Soil moisture, light exposure, 
//Outputs: LCD screen updates, water when needed, potentially lighting changes when needed based on time of year and or light within a shady day, LED of plant health if multiple,
// and finally SD card readings 

//Input and output frequency? 1 minute for testing. 1 hour? for implementation or could be while outlet is on


/*
LCD screen states
watering...
moisture : %d %
Average light: (not sure on the unit yet)

*/

/*
Current parts:
esp015 for wifi if I want to add mobile monitoring or potentially pull weather data in for the date instead of outlet
st7735 lcd since I have it spare
wayintop thermistor and photoresistor for now since again, I have it spare
*/



/*
Current plan:
Make and test code firstly for photoresistor and then thermistor using 1k and 10k resistors respectively
Then we will figure out the st7735 on arduino instead of a tm4c like I'm used to (adafruit's library is here: https://github.com/adafruit/Adafruit-ST7735-Library)

*/
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>
#include <Fonts/FreeSerif9pt7b.h>

//#define debug 1

#define cs   4 //CS
#define sclk 5 //SCK
#define mosi 6 //SDA
#define dc   7 //A0
#define rst  8 //RESET

#define VIN 5 // V power voltage
#define R 1000 //ohm resistance value

#define COLOR1 ST7735_WHITE
#define COLOR2 ST7735_BLACK

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

int Light;
float Temp;
int Health;
void setup() {
  // put your setup code here, to run once:
  #ifdef debug
  Serial.begin(9600);
  #endif

  tft.setFont(&FreeSerif9pt7b);
  tft.initR(INITR_BLACKTAB);  
  tft.setRotation(2);

  tft.fillScreen(ST7735_BLACK); 
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(0);
  tft.drawRect(0, 0, 128, 160, COLOR1);
  tft.drawLine(0, 50, 128, 50, COLOR1);
  tft.drawLine(0, 100, 128, 100, COLOR1);
}//end setup


void loop() {

  

  Light=measure_light();
  Temp=measure_temp();

  tft.fillRect(1, 25, 80, 17, COLOR2);//x,y,width,height
  tft.fillRect(1, 80, 80, 17, COLOR2);
  tft.fillRect(1, 130, 100, 20, COLOR2);

  temperature_to_lcd(Temp, 20);
  light_to_lcd(Light, 65);

  if((Temp > 68)&&(Light > 1200)){
    Health=3;
  }
  else if((Temp <= 68)&&(Light <= 1200)){
    Health=1;
  }
  else{
    Health=2;
  }
  health_to_lcd(Health, 115);

  delay(5000);
 

}//end void loop


int measure_light(){
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  #ifdef debug
  Serial.print(F("Light Voltage: ")); 
  Serial.println(voltage);
  #endif

  //float Vout = float(sensorValue) * (VIN / float(1023));// Conversion analog to voltage
  float RLDR = (R * (VIN - voltage))/voltage; // Conversion voltage to resistance
  int phys=500/(RLDR/1000); // Conversion resitance to lumen
  return phys;
  
  //return voltage;

}//end measure_light


float measure_temp(){

  int ThermistorPin = 1;
  int Vo;
  float R1 = 10000;
  float logR2, R2, T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  //Now we print the given temp values
  #ifdef debug
  Serial.print(F("Temperature: ")); 
  Serial.print(T);
  Serial.println(F(" F\n")); 
  #endif

  return T;
}//end measure_temp



void temperature_to_lcd(float temperature, unsigned char text_position){
    int text_color;
    tft.setCursor(4, text_position);
    tft.setTextColor(COLOR1, COLOR2);
    tft.setTextSize(1);
    tft.print("Temperature:");
    tft.setTextSize(0);
    if (temperature > 68){
        text_color = ST7735_GREEN;
    }//endif
    else{
        text_color = ST7735_RED;
    }//end else

    tft.setCursor(1, text_position + 20);
    fix_number_position(temperature);
    tft.setTextColor(text_color, COLOR2);
    tft.print(temperature, 1);
    tft.setCursor(108, text_position + 20);
    tft.print("F");

}//end temp_to_lcd

void light_to_lcd(float light, unsigned char text_position){
    int text_color;
    tft.setTextColor(COLOR1, COLOR2);
    tft.setCursor(4, text_position);
    tft.setTextSize(0);
    tft.println("Light:");
    tft.setTextSize(1);
    tft.setCursor(1, text_position + 30);
    fix_number_position(light);

    if (light > 1200){
        text_color = ST7735_GREEN;
    }//endif
    else{
        text_color = ST7735_RED;
    }//end else
    tft.setTextColor(text_color, COLOR2);
    tft.print(light, 1);
    tft.setCursor(108, text_position + 30);
    tft.print("L");
}

void health_to_lcd(int health, unsigned char text_position){
    tft.setTextColor(COLOR1, COLOR2);
    tft.setCursor(4, text_position);
    tft.setTextSize(1);
    tft.println("Health:");
    tft.setTextSize(1);
    tft.setCursor(1, text_position + 30);
    if(health==1){
      tft.setTextColor(ST7735_RED, COLOR2);
      tft.print(" Poor Health");
    }
    if(health==2){
      tft.setTextColor(ST7735_YELLOW, COLOR2);
      tft.print(" Okay Health");
    }
    if(health==3){
      tft.setTextColor(ST7735_GREEN, COLOR2);
      tft.print(" Good Health");
    }
}//end health to lcd

void fix_number_position(float number){
    if ((number >= -40) && (number < -9.9))
    {;}
    if ((number >= -9.9) && (number < 0.0)){
    tft.print(" ");}
    if ((number >= 0.0) && (number < 9.9)){
        tft.print(" ");}
    if ((number >= 9.9) && (number < 99.9)){
        tft.print(" ");}
    if ((number >= 99.9) && (number < 151)){
        tft.print("");}
}//end fix number pos