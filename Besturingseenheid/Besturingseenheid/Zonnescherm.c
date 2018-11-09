#include <avr/io.h>
#include <util/delay.h>
#include "Protocol.h"
#include "Besturingseenheid.h"


#define DELAY_MS 1000

int j, IN, OUT = 0; //Voor knipperen van zonnescherm | Voor het kijken of hij uitgerold/opgerold is

int getIn(){
	return IN;
}

int getOut(){
	return OUT;
}

init_scherm_ports(){
	// set pin 3,4,5 of PORTB for output
	DDRB |= _BV(DDB3);
	DDRB |= _BV(DDB4);
	DDRB |= _BV(DDB5);
	
	EICRA |= 1 << ISC00;
	EIFR =  1 << INTF0;

	// LED op Portb5 aan = Zonnescherm opgerold (rode lampje)
	PORTB |= _BV(PORTB5);
}

void uitrollen(){
	OUT = (OUT + 1);
	IN = (IN + 1);
	ser_write("250 "); //Geef aan dat het commando is gelukt
	// Zet pin 5 uit (groene lampje)
	PORTB &= ~_BV(PORTB5);
	// Zet pin 3 aan (rode lampje)
	
	PORTB |= _BV(PORTB3);
	
	printf("Zonneschermuitrollen % 6.2f cm \n", getDistance());
	_delay_ms(100);
	while (getDistance()<20){
		// Laat pin 4 knippen (gele lampje)
		PORTB |= _BV(PORTB4);
		_delay_ms(DELAY_MS);
		PORTB &= ~_BV(PORTB4);
		_delay_ms(DELAY_MS);
		j += 1;
	if (j % 2 == 0){ser_write(".");}
}
j = 0;
printf("Zonneschermoprollen % 6.2f cm \n", getDistance());
ser_writeln("\n\r201 Zonnescherm is uitgerold\n");
_delay_ms(DELAY_MS);
}

void oprollen(){
	IN = (IN + 1);
	OUT = (OUT + 1);
	ser_write("250 "); //Geef aan dat het commando is gelukt
	// Zet pin 3 uit (rode lampje)
	PORTB &= ~_BV(PORTB3);
	// Zet pin 5 aan (groene lampje)
	PORTB |= _BV(PORTB5);
	
	printf("Zonneschermoprollen % 6.2f cm \n", getDistance());
	_delay_ms(100);
	while (getDistance()>5){
		// Laat pin 4 knippen (gele lampje)
		PORTB |= _BV(PORTB4);
		_delay_ms(DELAY_MS);
		PORTB &= ~_BV(PORTB4);
		_delay_ms(DELAY_MS);
		j += 1;
		if (j % 2 == 0){ser_write(".");}
		}			
		j = 0;
		printf("Zonneschermoprollen % 6.2f cm \n", getDistance());
		ser_writeln("\n\r201 Zonnescherm is opgerold\n");
		_delay_ms(DELAY_MS);
	}