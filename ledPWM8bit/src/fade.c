
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
  switch (col)
  {
  case 0:
    DDRB = 0x00;
    DDRD = 0x40;
    return (volatile uint16_t *)&OCR0A;
    break;
  case 1:
    DDRB = 0x00;
    DDRD = 0x20;
    return (volatile uint16_t *)&OCR0B;
    break;
  case 2:
    DDRB = 0x02;
    DDRD = 0x00;
    return &OCR1A;
    break;
  case 3:
    DDRB = 0x04;
    DDRD = 0x00;
    return &OCR1B;
    break;
  case 4:
    DDRB = 0x08;
    DDRD = 0x00;
    return (volatile uint16_t *)&OCR2A;
    break;
  case 5:
    DDRB = 0x00;
    DDRD = 0x08;
    return (volatile uint16_t *)&OCR2B;
    break;
  default:
    return &OCR1A;
    break;
  }

}

/*
PWM outputs:
TCCR0 & TCCR0B
  COL0  PD6   OCR0A
  COL1  PD5   OCR0B
TCCR1A & TCCR1B
  COL2  PB1   OCR1A
  COL3  PB2   OCR1B
TCCR2A & TCCR2B
  COL4  PB3   OCR2A
  COL5  PD3   OCR2B   (spare)
*/
void configurePWM(){

  // Turn on the 6 PWM outputs
  //DDRB |= 1 << PINB1 | 1 << PINB2 | 1 << PINB3;
  //DDRD |= 1 << PIND3 | 1 << PIND5 | 1 << PIND6;

  // For OCR0A and OCR0B, set 8bit fast pwm, inverting, max 0xFF (8-bit)
  TCCR0A |= 1 << WGM00 | 1 << WGM01 | 1 << COM0A1 | 1 << COM0A0 | 1 << COM0B1 | 1 << COM0B0;

  // For OCR1A and OCR1B, set 8bit fast pwm, inverting, max 0x00FF 
  TCCR1A |= 1 << WGM10 | 1 << COM1A1 | 1 << COM1A0 | 1 << COM1B1 | 1 << COM1B0;
  TCCR1B |= 1 << WGM12;

  // For OCR0A and OCR0B, set 8bit fast pwm, inverting, max 0xFF (8-bit)
  TCCR2A |= 1 << WGM20 | 1 << WGM21 | 1 << COM2A1 | 1 << COM2A0 | 1 << COM2B1 | 1 << COM2B0;

  TCCR0B |= 1 << CS00;
  TCCR1B |= 1 << CS10;
  TCCR2B |= 1 << CS20;

  OCR0A = 0;
  OCR0B = 0;
  OCR1A = 0;
  OCR1B = 0;
  OCR2A = 0;
  OCR2B = 0;
}


int main(void) {

  int duty = 0;
  int col = 0;
  volatile uint16_t *selectedPWMOutput;

  // Turn on the pin
  configurePWM();

  while(1)
  {
    while(col < 6){
      selectedPWMOutput = getCol(col);
      col++;

      while(duty < 100){
        duty++;
        setLED(selectedPWMOutput,duty);
        _delay_ms(1);
      }
      //_delay_ms(100);
      while(duty > 0){
        duty--;
        setLED(selectedPWMOutput,duty);
        _delay_ms(1);
      }
    }
    col = 0;
  }

}

