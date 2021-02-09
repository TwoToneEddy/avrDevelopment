
/*  Upload using arduino as ISP:
    Upload the example ArduinoISP to the board that will be the programmer, just like any other sketch
    Connect via ISP to target
    Run:
    avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM2 -b19200 -Uflash:w:blink.hex
    Good Video: https://www.youtube.com/watch?v=9WeewNNGs5E
*/
#define F_CPU 1000000  // by default we have the 1MHz internal oscillator

#include <avr/io.h>      // this contains all the IO port definitions
#include <util/delay.h>

#define PWM_FREQ  1000

int main(void) {


  DDRB |= (1 << PINB1);
  TCCR1A |= 1 << WGM11 | 1 << COM0A1 | 1 << COM1A0;
  TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS10;
  ICR1 = F_CPU/PWM_FREQ-1;

  OCR1A = 0;
  

  while(1)
  {
    OCR1A = 0;
    for(int i = 0; i < 50; i++){
    OCR1A += ICR1/50;
    _delay_ms(100);
   }
   OCR1A = ICR1;
   _delay_ms(1000);

  }

}

