 /* HC-SR04
 * trigger to sensor : uno 0 (PD0) output
 * echo from sensor  : uno 3 (PD3 = INT1) input
*/
 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"
#include <stdlib.h>
#include <avr/interrupt.h>

static volatile int pulse = 0;
static volatile int i = 0;
int16_t afstand = 0;
char resultAfstand[16];

void init_ports(void){
	DDRD = 0b11110111; //set PORTD1 as INPUT
	DDRB = 0xFF;
	//PORTD |= (1 << PORTD2);// turn On the Pull-up
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
		PORTB = (1<<PINB0);
		_delay_ms(10);
		PORTB = 0x00;
		
		afstand = (pulse * 0.5) * 0.0343;
		
		itoa(afstand, resultAfstand, 10);
		ser_write(resultAfstand); ser_writeln(" cm");	 
	}
}

ISR(INT1_vect)
{
	if(i == 1)
	{
		TCCR1B = 0; //Stop de teller
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
	}

	if(i==0)
	{
		TCCR1B = (1<<CS10); //Start de teller
		i = 1;
	}
}