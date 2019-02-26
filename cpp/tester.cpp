#include <iostream>
#include <pigpio.h>

int main()
{
   if (gpioInitialise() < 0) return 1;

   // if inItialized, start stuff here
   
   int pin = 18;

   gpioSetMode (pin, PI_OUTPUT);

   gpioWrite( pin, 1 );

   // sleep ( 500 );

   gpioSleep (PI_TIME_RELATIVE, 200, 0);






   gpioTerminate();

   return 0;
}
