 #include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"

//prototypes
uint8_t get_adc_value();
void init_adc();
void int_timer();
uint8_t getLight();


/*
	Dit werdt gebruikt om de lichtintensiteit aan te roepen.
	Het werkte niet optimaal dus is het niet in gebruik
*/
uint8_t getLight(){
	uint8_t temp = get_adc_value();
	return temp;
}


void init_adc()
{
	//ref = vcc, left adjust the result (8 bit resolution)
	// select channel 0 (PC0 = input)
	ADMUX |= (1<<REFS0) | (1<<ADLAR);
	// enable the ADC & prescale = 128
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

	
}

uint8_t get_adc_value1()
{
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADCH; // 8bit resolution, left adjusted
}

void init_timer (void){
	//8bittimer
	TCCR0A = (1<< WGM01); // set CTC Bit
	OCR0A = 156; // Dit geeft 1/10 miliseconde
	TIMSK0 = (1<< OCIE0A);
	
	TCCR0B |= (1 << CS02) | (1 <<CS00); // start at 1024 prescaler	
}
