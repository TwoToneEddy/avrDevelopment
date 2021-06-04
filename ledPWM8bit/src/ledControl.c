#include "main.h"


volatile uint16_t * getRowPtr(int col){
  switch (col)
  {
  case 0:
    DDRD |= 1 << PIND6;
    DDRD &= ~(1 << PIND5);
    return (volatile uint16_t *)&OCR0A;
    break;
  case 1:
    DDRD |= 1 << PIND5;
    DDRD &= ~(1 << PIND6);
    return (volatile uint16_t *)&OCR0B;
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
    DDRD &= ~(1 << PIND3);
    return (volatile uint16_t *)&OCR2A;
    break;
  case 5:
    DDRD |= 1 << PIND3;
    DDRB &= ~(1 << PINB3);
    return (volatile uint16_t *)&OCR2B;
    break;
  default:
    DDRD |= 1 << PIND6;
    return &OCR1A;
    break;
  }

}

void setRowAndDuty(volatile uint16_t *OCRxx,int dutyCycle){
  int weight = 0xFF / 100;
  *OCRxx = 0xFF - (dutyCycle*weight);
}

/*
    Sets single output to selected value, clears all other outputs
*/
void setColOutput(int output,int val)
{
    // Clear outputs
    PORTB = 0;
    PORTD = 0;


    if(val > 0){
        if(output < 3)
            PORTB |= (1 << digitalOuputs[output]);
        else
            PORTD |= (1 << digitalOuputs[output]);
    }
}

int setLED(int row, int col, int duty){

  volatile uint16_t *rowPtr;
  rowPtr = getRowPtr(row);

  setRowAndDuty(rowPtr,duty);
  setColOutput(col,duty>0);

  return 0;
}


int testLeds(){

    int del = 5;
    int duty = 0;
    for(int row = 0; row < 6; row++){
        for(int col = 0; col < 6; col++){

            while(duty < 100){
                duty++;
                setLED(row,col,duty);
                _delay_ms(del);
            }
            while(duty > 0){
                duty --;
                setLED(row,col,duty);
                _delay_ms(del);
            }
        }
    }

}