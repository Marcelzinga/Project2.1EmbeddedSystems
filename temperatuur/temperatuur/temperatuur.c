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

int main() {
	ser_init();
	ADC_init();
	
	DDRC &= ~(1<<5); // set only pin 0 of port C as input
	
	while(1){
		Volt = get_adc_value() * 0.0048828125;
		ADCRes = (Volt - 0.5) * 100;
		itoa(ADCRes, ADCOut, 10);
		ser_write("Temperatuur: "); ser_writeln(ADCOut);
		_delay_ms(1000);
	}
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