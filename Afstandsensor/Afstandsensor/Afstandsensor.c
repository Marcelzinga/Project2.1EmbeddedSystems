 /* HC-SR04
 * trigger to sensor : uno 0 (PD0) output
 * echo from sensor  : uno 3 (PD3 = INT1) input
*/
 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "serial.h"
#include <stdlib.h>
#include <avr/interrupt.h>

static volatile int pulse = 0;
static volatile int i = 0;
double afstand = 0;
char resultAfstand[32];

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
		PORTB &= ~(1<<PINB0);
		
		//afstand = pulse * 0.0172413793103448;
		//afstand = (pulse * 0.5) * 0.00343;
		//afstand = (pulse * 0.0010869565217391); //30 = 29
		//afstand = (pulse * 0.0012106537530266); //30 = 32/33
		//afstand = (pulse * 0.5) * 0.0023; // 20 = 21
		//afstand = (pulse * 0.5) * 0.0022; // 20 = 20 10 = 9
		afstand = (pulse * 0.5) * 0.0023; 
		//afstand = (pulse);
		//itoa(afstand, resultAfstand, 10);
		sprintf(resultAfstand, "% 6.2f", afstand);
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
		TCCR1B |= (1<<CS10); //Start de teller
		i = 1;
	}
}