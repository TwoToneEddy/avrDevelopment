
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

/*
void setLED(int dutyCycle){
  int weight = 0xFF / 100;
  OCR1A = 0xFF - (dutyCycle*weight);
}
*/

int main(void) {


  // Turn on the pin
  DDRB |= (1 << PINB1);

  // Set 8bit fast pwm, inverting, max 0x00FF 
  TCCR1A |= 1 << WGM10 | 1 << COM1A1 | 1 << COM1A0;
  TCCR1B |= 1 << WGM12 | 1 << CS10;
  
  // Set to zero
  OCR1A = 0;
  

  while(1)
  {

    while(OCR1A < 0xFF){
      OCR1A++;
      _delay_ms(10);
    }
    _delay_ms(2000);
    while(OCR1A > 0){
      OCR1A--;
      _delay_ms(10);
    }
  }

}

