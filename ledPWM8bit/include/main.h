#include <avr/io.h>      // this contains all the IO port definitions
#include <util/delay.h>
#include "uart.h"



#define F_CPU 8000000  // by default we have the 1MHz internal oscillator


#define OUT0  PINB0
#define OUT1  PINB4
#define OUT2  PINB5
#define OUT3  PIND2
#define OUT4  PIND4
#define OUT5  PIND7

void configurePWM();
void configureDigitalOutputs();

volatile uint16_t * getRowPtr(int col);
void setRowAndDuty(volatile uint16_t *OCRxx,int dutyCycle);
void setColOutput(int output,int val);
int setLED(int row, int col, int duty);
int testLeds(int del, int mode);


// Array to store output pins in an iterable way
int digitalOuputs[6];
int currentRow,currentCol,currentDuty;