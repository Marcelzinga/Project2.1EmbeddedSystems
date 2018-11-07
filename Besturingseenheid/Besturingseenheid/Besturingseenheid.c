#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serial.h"
#include "ADC.h"

float Volt;
float ADCRes;
char ADCOut[24];


volatile uint8_t i = 0;
volatile int extraTime = 0;

int main()
{
	init_timer();
	ser_init();
	ADC_init();
	sei(); // set external interrupt
	  
	printf("An interrupt should be occuring every 5 seconds\n");
	//DDRC &= ~(1<<5); // set only pin 0 of port C as input
	while(1){
		 
	 }
	  
	
}

uint8_t getTemp(){
	//uint8_t temp = ADCOut;
	//uint8_t temp = get_adc_value(PC1);
	uint8_t temp = get_temp_adc();
	return temp;
}

uint8_t getLight(){
	//uint8_t temp = get_adc_value(PC0);
	uint8_t temp = get_licht_adc();
	return temp;
}

void init_timer (void){
	//8bittimer
	TCCR0A = (1<< WGM01); // set CTC Bit
	OCR0A = 156; // Dit geeft 1/10 miliseconde
	TIMSK0 = (1<< OCIE0A);
	
	TCCR0B |= (1 << CS02) | (1 <<CS00); // start at 1024 prescaler
	
}

/*
Timerinterrupt geeft om de 1* seconden een interrupt
https://eleccelerator.com/avr-timer-calculator/
*/
ISR(TIMER0_COMPA_vect){
	
	extraTime++;
	
	if(extraTime>500){
		Volt = get_temp_adc() * 0.0048828125;
		ADCRes = (Volt - 0.5) * 100;
		itoa(ADCRes, ADCOut, 10);
		ser_write("Temperatuur: "); ser_writeln(ADCOut);
		printf("%i Temperatuur=%f \n", i, ADCOut);
		_delay_ms(100);
		printf("%i intensiteit=%d\n", i, getLight());
		i++;
		
		// Resets de timer en de Totale timer ticks
		extraTime = 0;
	}
}

/*
	De valus van de temperatuursensor worden niet correct aangegeven.
	De lichtsensor geeft nog wel de waardes die overeenkomen met de 
	
*/