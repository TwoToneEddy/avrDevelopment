
#define F_CPU 8000000  // by default we have the 1MHz internal oscillator

#include <avr/io.h>      // this contains all the IO port definitions
#include <util/delay.h>



#include "uart.h"

int main() 
{
    char buffer[64];
    uint8_t len;
    UART_Init(9600);
    
    while(1)
    {
        len = UART_RxString(buffer);
        if(len > 1){
          UART_Printf("Recieved: %s, len: %d\n",buffer,len);
        }
    }
    return (0);
}

