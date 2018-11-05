/*
 * Lichtsensor.c
 *
 * Created: 01/11/2018 10:24:16
 *  Author: Marc Elzinga
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"

//prototypes
uint8_t get_adc_value();
void init_adc();

#define DELAY_MS 400

ISR(ADC_vect){
	ser_write(ADC);
	ser_write(get_adc_value());
}



int main()
{
	ser_init();
	ADC_init();
	//DDRC = 0xDF; // PIN5 as Input
	//DDRB = 0xFF;
	
	DDRC &= ~(1<<5); // set only pin 5 of port C as input
	// set pin 4 of PORTB for Output
	DDRB = _BV(DDB4);
	
	
	while(1)
	{
		uint8_t temp = get_adc_value();
		uint8_t x = PINC & (1<<5);
		
		if(temp > 100){
			PORTB |= _BV(PORTB4);
		}
		else{
			PORTB &= ~_BV(PORTB4);
			ser_writeln(temp);
		}
		_delay_ms(DELAY_MS);
	}
	
	
}


void ADC_init()
{
	//ref = vcc, left adjust the result (8 bit resolution)
	// select channel 0 (PC0 = input)
	ADMUX |= (1<<REFS0) | (1<<ADLAR);
	// enable the ADC & prescale = 128
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	sei();
	
}

uint8_t get_adc_value()
{
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADCH; // 8bit resolution, left adjusted
}