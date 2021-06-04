#include "main.h"




// Return pointer to PWM output for that column





int main(void) {


  configurePWM();
  configureDigitalOutputs();
  

  while(1)
  {
    testLeds();
  }

}

