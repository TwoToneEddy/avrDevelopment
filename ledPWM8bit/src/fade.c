
#define F_CPU 8000000  // by default we have the 1MHz internal oscillator

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
    DDRD |= 1 << PIND6;
    return (volatile uint16_t *)&OCR0A;
    break;
  case 1:
    DDRD |= 1 << PIND5;
    return (volatile uint16_t *)&OCR0B;
    break;
  case 2:
    DDRB |= 1 << PINB1;
    return &OCR1A;
    break;
  case 3:
    DDRB |= 1 << PINB2;
    return &OCR1B;
    break;
  case 4:
    DDRB |= 1 << PINB3;
    return (volatile uint16_t *)&OCR2A;
    break;
  case 5:
    DDRD |= 1 << PIND3;
    return (volatile uint16_t *)&OCR2B;
    break;
  default:
    DDRD |= 1 << PIND6;
    return &OCR1A;
    break;
  }

}

/*

ATMEGA328P-AU  -  TQFP32  RS 131-0271
ATMEGA328-PU   -  PDIP28  RS 131-0277
FT232RL        -  SSOP28  RS 406-580

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

Digital OPs:
PD2
PD4
PB6 ?
PB7 ?
PD7
PB0
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


  OCR0A = 0; //PD6
  OCR0B = 0; //PD5
  OCR1A = 0; //PB1
  OCR1B = 0; //PB2
  OCR2A = 0; //PB3
  OCR2B = 0; //PD3
}


int main(void) {

  int duty = 0;
  int col = 0;
  volatile uint16_t *selectedPWMOutput;
  int state = 1;

  // Turn on the pin
  configurePWM();
  DDRB |= 1 << PINB0;
  PORTB |= (1 << PORTB0);

  while(1)
  {
    while(col < 6){
      selectedPWMOutput = getCol(col);
      //col++;

      while(duty < 100){
        duty++;
        setLED(selectedPWMOutput,duty);
        _delay_ms(10);
      }
      //_delay_ms(100);
      while(duty > 0){
        duty--;
        setLED(selectedPWMOutput,duty);
        _delay_ms(10);
      }

      if(state == 1){
        PORTB &= ~(1 << PORTB0);
        state = 0;
      }else{   
        PORTB |= (1 << PORTB0);
        state = 1;
      }
    }
    col = 0;
  }

}

