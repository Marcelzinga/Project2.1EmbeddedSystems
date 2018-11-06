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

volatile uint8_t i = 0;
int extraTime = 0;

/* 
Work in progress.

Op het moment werkt deze timerinterrupt niet correct. 
Hij doet er ~4 keer te lang over.(of ~8 keer tekort
*/
ISR (TIMER1_COMPA_vect){
	extraTime++;
	if(extraTime==8){
	printf("%i intensiteit=%d\n", i, get_adc_value());
	i++;
	
	// Resets de timer en de Totale timer ticks
	extraTime = 0;
	OCR1A = 468750;
	//TCNT1 = 468750; // Dit was bij het testen van 8bitclock
	}		
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

	
	int a = 0;
	_delay_ms(1000);
	printf("An interrupt should be occuring every 30 seconds\n");
	while(1)
	{
		// Dit is alleen voor het testen. Het moet via interrupt
		//printf("main %i intensiteit=%d \n", a, getLight());
		//a++;
		//_delay_ms(10000);
	}
	
	
}



/*
	Dit werdt gebruikt om de lichtintensiteit aan te roepen.
	Het werkte niet optimaal dus is het niet in gebruik
*/
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
	
	TCCR0A = (1<< WGM12); // set CTC Bit
	OCR1A = 468750;
	TIMSK1 = (1<< OCIE1A);
	
	
	sei(); // set external interrupt
	
	TCCR1B |= (1 << CS12) | (1 <<CS10); // start at 1024 prescaler
		
}


// Gefaalde code die ik nu even bewaar
	/*//prescale op 1024
	TCCR1B = 0x05;
	

	TCNT1 = 468750; 
	TIMSK1 |= (1 << TOIE1);*/
	
	//TIMSK1 = 1 << OCIE1A; // Timer 1 Output Compare A Match Interrupt Enable
	//OCR1A = (uint16_t)62500; // 1 sec = (256/16.000.000)*62499