
/*  Upload using arduino as ISP:
    Upload the example ArduinoISP to the board that will be the programmer, just like any other sketch
    Connect via ISP to target
    Run:
    avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM2 -b19200 -Uflash:w:blink.hex
*/
#define F_CPU 16000000  // by default we have the 1MHz internal oscillator

#include <avr/io.h>      // this contains all the IO port definitions
#include <util/delay.h>

int main(void) {
  DDRB = (1 << 5);  // set PORTB5 to an output

  while (1) {
    PORTB |= 1 << 5;  // turn LED on
    _delay_ms(1000);
    PORTB &= ~(1 << 5);  // turn LED on
    _delay_ms(1000);
  }
}

