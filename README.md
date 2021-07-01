# Arduino
Work's arduino files

This is my collection of code I've written for Holley Performance Products over the summer of 2021. 
Wiring schematics and datasheets for external parts can be found by contacting me at nathantucker@holley.com
Both of my main projects run a real time control system. Not all code in this library is written on interrupt driven code, but all code will be on a clock in final implementation.


Projects included:
  -Using an arduino Uno to control a linear actuator testing clutches with a pressure sensor, h bridge drive for the 12V motor, button input on an LCD shield, and exporting the data to an SD card
  
  -Using an arduino Leonardo with a PID and clamping techniques to monitor and control cabin air temp in an S10 with PWM control on a Chevy Cruze heating core.


UNO: This project runs on a 25 ms clock. The uno has an LCD, SD reader, and external protoshield for CAPs, resistors, and needed ICs. 

LEONARDO: This project runs on a 25 ms clock due mainly to display.display() with the LCD screen. Without the screen a 10 ms interrupt is easily achievable. 


TIMERS
  The timers in this code can be different for people unexperienced with Arduino Registers and timers. Basically, Arduinos come with several timers (3 or more usually) and by  setting a count number and prescaler multiple to increment your counter by. The rest of the code is standard C with the use of documented libraries. By following the guide at https://www.instructables.com/Arduino-Timer-Interrupts/ you should be able to understand and copy what I've done here. 

