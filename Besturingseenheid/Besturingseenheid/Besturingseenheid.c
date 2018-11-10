 /* HC-SR04
 * trigger pin: (PB0) output
 * echo pin : (PD3 = INT1) input
 *
 * LDR04
 * PC2(A2) Input + Weerstand 10 Kilo ohm
 * 
 * Temperature sensor
 * PC5(A5) input
 *
 *	Rode LED	PB3 +Weerstand 680 ohm
 *	Gele LED	PB4 +Weerstand 680 ohm
 *	Groene LED	PB5 +Weerstand 680 ohm
*/
 
 
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serial.h"
#include "ADC.h"
#include "Protocol.h"
#include "Zonnescherm.h"


double Volt;
double ADCRes;

static volatile float pulse = 0;
static volatile int i = 0;
double afstand = 0;
char resultAfstand[32];


volatile int index = 0;
volatile int extraTime = 0;
volatile int extraTime1 = 0;

volatile int timerVariable = 0;


void init_ports(void){
	DDRD = 0b11110111; //set PORTD4 as INPUT
	DDRB = 0xFF; //set PORTB as output
}

void init_ext_int(void){
	EICRA =(1<<ISC10); //setting interrupt triggering logic change
	EIMSK =(1<<INT1); //enabling interrupt1
	TCCR1A = 0;
}

int main(void)
{
	init_scherm_ports();
	init_timer();
	ser_init();
	ADC_init();
	
	init_ports();
	init_ext_int();
	sei(); // set external interrupt
	  
	//printf("An interrupt should be occuring every 30 seconds\n");
	
	
	while(1){
		protocolCom();
	 }	
}

int get_timerVariable(){
	return timerVariable;
}	


/*
	De get temp en get light gaan nu naar twee aparte ADC getters
	omdat wanneer ik een if else statement gebruikte het niet de 
	gewenste resultaten toonde.
*/

double getDistance(){
	//PORTB = (1<<PINB0); //set trigger HIGH
	PORTB |= _BV(PORTB0);
	_delay_ms(10); //10 ms delay
	//PORTB &= ~(1<<PINB0); //set trigger LOW
	PORTB &= ~_BV(PORTB0);
	_delay_ms(100);
	afstand = (pulse * 0.5) * 0.0023;
	return afstand;
}

double getTemp(){
	//uint8_t temp = get_adc_value(PC2);
	Volt = get_temp_adc() * 0.0048828125;
	ADCRes = (Volt - 0.5) * 100;
	return ADCRes;
}

uint8_t getLight(){
	//uint8_t temp = get_adc_value(PC5);
	uint8_t temp = get_light_adc();
	return temp;
}

void init_timer (void){
	//8bittimer
	TCCR0A = (1<< WGM01); // set CTC Bit
	OCR0A = 156.25; // Dit geeft 1/10 miliseconde
	TIMSK0 = (1<< OCIE0A);
	
	TCCR0B |= (1 << CS02) | (1 <<CS00); // start at 1024 prescaler
}

/*
Timerinterrupt geeft om de 5* seconden een interrupt
https://eleccelerator.com/avr-timer-calculator/
*/
ISR(TIMER0_COMPA_vect){
	extraTime1++;
	if(extraTime1>100){
		timerVariable++;
		extraTime1 = 0;
	}
	extraTime++;
	if(extraTime>6000){
		/*
		char* l = get_grensLight();
		double grenslight;
		grenslight = strtod(l, NULL);
		
		char* t = get_grensTemp();
		double grenstemp;
		grenstemp = strtod(t, NULL);
		
		if(getLight()> grenslight && getTemp() > grenstemp && (getOut() % 2) == 0)
		{
			uitrollen();
		}
		if(getLight()< grenslight && getTemp() < grenstemp && (getIn() % 2) == 1)
		{
			oprollen();
		}	
	
		index++;
		
		// Resets de timer en de Totale timer ticks*/
		extraTime = 0;
	}
}

ISR(INT1_vect)
{
	if(i == 1)
	{
		TCCR1B = 0; //Stop counter
		pulse = TCNT1; //Write duration (TCNT1) to pulse
		TCNT1 = 0; //Reset duration
		i = 0; //Reset counter
	}

	if(i==0)
	{
		TCCR1B |= (1<<CS10); //Start counter
		i = 1;
	}
}