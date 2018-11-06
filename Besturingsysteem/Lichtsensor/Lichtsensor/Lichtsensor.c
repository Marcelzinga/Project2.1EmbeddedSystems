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
void int_timer();
// elke seconde gebeurd de functie

volatile uint8_t i = 0;

ISR (TIMER1_OVF_vect){

	//printf("%i intensiteit=%d\n", i, getLight());
	//i++;
	//TCNT1 = 468750;
}

int main()
{
	init_timer();
	ser_init();
	ADC_init();
	
	
	//DDRC = 0xDF; // PIN5 as Input
	//DDRB = 0xFF;
	
	//DDRC &= ~(1<<5); // set only pin 0 of port C as input
	//DDRB = _BV(DDB4); // set pin 4 of PORTB for Output

	
	int i = 0;
	while(1)
	{
		printf("%i intensiteit=%d \n", i, getLight());
		i++;
		_delay_ms(50000);
	}
	
	
}

void getLight(){
	uint8_t temp = get_adc_value();
	return temp;
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

void init_timer (void){
	//prescale op 1024
	TCCR1B = 0x05;
	sei();

	TCNT1 = 468750; 
	TIMSK1 |= (1 << TOIE1);
	//TIMSK1 = 1 << OCIE1A; // Timer 1 Output Compare A Match Interrupt Enable
	//OCR1A = (uint16_t)62500; // 1 sec = (256/16.000.000)*62499
}