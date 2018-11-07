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
uint8_t getLight();

volatile uint8_t i = 0;
volatile int extraTime = 0;


int main()
{
	init_timer();
	ser_init();
	ADC_init();
	sei(); // set external interrupt
	

	//int a = 0;
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
uint8_t getLight(){
	uint8_t temp = get_adc_value();
	return temp;
}


void ADC_init()
{
	//ref = vcc, left adjust the result (8 bit resolution)
	// select channel 0 (PC0 = input)
	ADMUX = (1 << REFS0) | (1 << MUX1)| (1<<ADLAR); // port A2
	//ADMUX |= (1<<REFS0)| (1<<ADLAR);
	// enable the ADC & prescale = 128
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	DIDR0 = (1<<ADC5D); //!!Disables pin 5? not sure what it does atm
	
}

uint8_t get_adc_value()
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


/*
Work in progress.

Timerinterrupt geeft om de 30/(of2) seconden een interrupt
https://eleccelerator.com/avr-timer-calculator/
*/
ISR(TIMER0_COMPA_vect){
	
	extraTime++;
	
	if(extraTime>200){
		printf("%i intensiteit=%d\n", i, getLight());
		i++;
		
		// Resets de timer en de Totale timer ticks
		extraTime = 0;
		
		
		//OCR1A = 468750;
		//TCNT1 = 468750; // Dit was bij het testen van 8bitclock
	}
}


// Gefaalde code die ik nu even bewaar
	/*//prescale op 1024
	TCCR1B = 0x05;
	

	TCNT1 = 468750; 
	TIMSK1 |= (1 << TOIE1);*/
	
	//TIMSK1 = 1 << OCIE1A; // Timer 1 Output Compare A Match Interrupt Enable
	//OCR1A = (uint16_t)62500; // 1 sec = (256/16.000.000)*62499