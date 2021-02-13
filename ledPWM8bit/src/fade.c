
/*  Upload using arduino as ISP:
    Upload the example ArduinoISP to the board that will be the programmer, just like any other sketch
    Connect via ISP to target
    Run:
    avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM2 -b19200 -Uflash:w:blink.hex
    Good Video: https://www.youtube.com/watch?v=9WeewNNGs5E
*/

/*
dip chip
8mhz internal
board_fuses.lfuse = 0xF2
board_fuses.hfuse = 0xDE
board_fuses.efuse = 0xFD

1mhz internal
board_fuses.lfuse = 0x72
board_fuses.hfuse = 0xDE
board_fuses.efuse = 0xFD

smt
from factory:
board_fuses.lfuse = 0x62
board_fuses.hfuse = 0xD9
board_fuses.efuse = 0xFF

*/

#define F_CPU 1000000  // by default we have the 1MHz internal oscillator

#include <avr/io.h>      // this contains all the IO port definitions
#include <util/delay.h>

#define PWM_FREQ  1000


void setLED(volatile uint16_t *OCRxx,int dutyCycle){
  int weight = 0xFF / 100;
  *OCRxx = 0xFF - (dutyCycle*weight);
}

// Return pointer to PWM output for that column
volatile uint16_t * getCol(int col){
  if( col == 0)
    return &OCR1A;
  else
    return &OCR1B;

}

void configurePWM(){

  // Turn on the 6 PWM outputs
  DDRB |= 1 << PINB1 | 1 << PINB2 | 1 << PINB3;
  DDRD |= 1 << PIND3 | 1 << PIND5 | 1 << PIND6;

  // For OCR1A and OCR1B, set 8bit fast pwm, inverting, max 0x00FF 
  TCCR1A |= 1 << WGM10 | 1 << COM1A1 | 1 << COM1A0 | 1 << COM1B1 | 1 << COM1B0;
  TCCR1B |= 1 << WGM12;

  
  TCCR1B |= 1 << CS10;
  OCR1A = 0;
  OCR1B = 0;
}


int main(void) {

  int duty = 0;
  volatile uint16_t *selectedPWMOutput;

  // Turn on the pin
  configurePWM();
  selectedPWMOutput = getCol(1);

  while(1)
  {

    while(duty < 100){
      duty++;
      setLED(selectedPWMOutput,duty);
      _delay_ms(10);
    }
    _delay_ms(2000);
    while(duty > 0){
      duty--;
      setLED(selectedPWMOutput,duty);
      _delay_ms(10);
    }
  }

}

