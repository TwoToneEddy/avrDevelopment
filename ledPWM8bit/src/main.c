#include "main.h"

int main(void) {


    char buffer[64];
    uint8_t len;
    UART_Init(9600);
    
    
    configurePWM();
    configureDigitalOutputs();

    while(1)
    {
        len = UART_RxString(buffer);
        if(len > 1){
          UART_Printf("Recieved: %s, len: %d\n",buffer,len);

          if(buffer[0] == 'T'){
            UART_Printf("Running full LED test\n");
            testLeds(1,1);
          }

          if(buffer[0] == 't'){
            UART_Printf("Running fast LED test\n");
            testLeds(10,0);
          }

        }
    }
    return (0);



}

