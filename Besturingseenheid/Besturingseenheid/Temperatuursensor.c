#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serial.h"

float Volt;
float ADCRes;
char ADCOut[24];
double result;		//Define ADCOut as a 6 character char

uint8_t get_adc_value();
void ADC_init();
void getTemp();


void getTemp(){
	uint8_t temp = ADCOut;
	return temp;
}



void ADC_init(){
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	DIDR0 = (1<<ADC5D);
	
}

uint8_t get_adc_value()
{
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADC; 
}