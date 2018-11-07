 /* HC-SR04
 * trigger pin: (PB0) output
 * echo pin : (PD3 = INT1) input
*/
 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "serial.h"
#include <stdlib.h>
#include <avr/interrupt.h>

static volatile float pulse = 0;
static volatile int i = 0;
double afstand = 0;
char resultAfstand[32];

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
	ser_init();
	init_ports();
	init_ext_int();
	
	sei();
	
	while(1)
	{
		PORTB = (1<<PINB0); //set trigger HIGH
		_delay_ms(10); //10 ms delay
		PORTB &= ~(1<<PINB0); //set trigger LOW
		
		afstand = (pulse * 0.5) * 0.0023; 
		sprintf(resultAfstand, "% 6.2f", afstand);
		ser_write(resultAfstand); ser_writeln(" cm");	 
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