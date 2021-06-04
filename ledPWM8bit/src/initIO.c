#include "main.h"

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

void configureDigitalOutputs()
{
    // Configure pins to be outputs
    DDRB |= 1 << OUT0 | 1 << OUT1 | 1 << OUT2;
    DDRD |= 1 << OUT3 | 1 << OUT4 | 1 << OUT5;
    
    // Store output pins in order of colomns
    digitalOuputs[0] = OUT0;
    digitalOuputs[1] = OUT1; 
    digitalOuputs[2] = OUT2; 
    digitalOuputs[3] = OUT3; 
    digitalOuputs[4] = OUT4; 
    digitalOuputs[5] = OUT5; 

}