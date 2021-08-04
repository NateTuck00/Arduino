# Arduino
Work's arduino files

This is my collection of code I've written for work over the summer of 2021. 
Wiring schematics and datasheets for external parts can be provided.
Both of my main projects run a real time control system. Not all code in this library is written on interrupt driven code, but all code will be on a clock in final implementation.


Projects included:
  -Using an arduino Uno to control a linear actuator testing clutches with a pressure sensor, h bridge drive for the 12V motor, button input on an LCD shield, and exporting the data to an SD card
  
  -Using an arduino Leonardo with a PID and clamping techniques to monitor and control cabin air temp in an S10 with PWM control on a Chevy Cruze heating core.


UNO: This project runs on a 25 ms clock. The uno has an LCD, SD reader, and external protoshield for CAPs, resistors, and needed ICs. 

LEONARDO: This project runs on a 25 ms clock due mainly to i2c time with the LCD screen. Without the screen a 10 ms interrupt is easily achievable, but good temperature control is easily possible without it. Overclocking the screen or i2c protocol also allows 10 ms. Writing one's own library like the https://github.com/bitbank2/BitBang_I2C library is obviously possible as well for even more speed optimization if one was using a very strong heater core in a small space with need for fast control. 

ZERO: I used an arduino Zero with Pi-Hole to reroute my DNS in my house and block all ads across our entire wifi network

TIMERS
  The timers in this code can be different for people unexperienced with Arduino Registers and timers. Basically, Arduinos come with several timers (3 or more usually) and by  setting a count number and prescaler multiple to increment your counter by. The rest of the code is standard C with the use of documented libraries. By following the guide at https://www.instructables.com/Arduino-Timer-Interrupts/ you should be able to understand and copy what I've done here. 

