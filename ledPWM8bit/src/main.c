#include "main.h"


int main(void) {


  configurePWM();
  configureDigitalOutputs();
  

  while(1)
  {
    testLeds();
  }

}

