#include <avr/io.h>
//#define F_CPU 16E6 -> Dit moet wel als je Visual Studio gebruikt
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"
#include <stdlib.h>
#include <avr/interrupt.h>

#define DELAY_MS 1000

int i, IN, OUT = 0; //Voor knipperen van zonnescherm | Voor het kijken of hij uitgerold/opgerold is

char in_buf[30]; // Invoerbuffer

void protocolCom(){
	// set pin 3,4,5 of PORTB for output
	DDRB |= _BV(DDB3); 
	DDRB |= _BV(DDB4); 
	DDRB |= _BV(DDB5); 
	//DDRD = 0xff; //													DELETE AFTER
	
	//EIMSK = 1 << INT0;//													DELETE AFTER
	EICRA |= 1 << ISC00;
	EIFR =  1 << INTF0;

	// LED op Portb5 aan = Zonnescherm opgerold (rode lampje)
	PORTB |= _BV(PORTB5);
	//while (1) {
		ser_write("Wat kan ik voor u doen?");
		ser_readln(in_buf, sizeof(in_buf), 1);
/**********************************************************Zonnescherm uitrollen************************************************************/
			if (strcmp("Uitrollen", in_buf) == 0){ //Wanneer uitrollen wordt gerequest
				if ((OUT % 2) == 1){
					ser_writeln("Zonnescherm is al uitgerold!");
				} if((OUT % 2) == 0){
					uitrollen();
				}				
			}
/*---------------------------------------------------------Zonnescherm oprollen------------------------------------------------------------*/ 
			else if(strcmp("Oprollen", in_buf) == 0){
				if ((IN % 2) == 0){
					ser_writeln("Zonnescherm is al opgerold!");
				} if((IN % 2) == 1){
					oprollen();
				}				
			} 
/***********************************************************Get Temperatuur ******************************************************************/
			else if(strcmp("GET_TEMP", in_buf) == 0){
				printf("202 TEMP= % 6.2f \n", getTemp());
				/*double ADCRes = getTemp();
				char ADCOut[24];
				sprintf(ADCOut, "% 6.2f", ADCRes);
				printf("%f", ADCRes);
				ser_write("202 TEMP: "); ser_writeln(ADCOut);*/
			}
			else if(strcmp("GET_GRENS_TEMP", in_buf) == 0){
				
			}
			else if(strcmp("SET_GRENS_TEMP(Z)", in_buf) == 0){
				
			}
/*----------------------------------------------------------Get Lichtintensiteit---------------------------------------------------------------------*/
			else if(strcmp("GET_LIGHT", in_buf) == 0){
				printf("202 LIGHT %i \n", getLight());
			}
			
			else if(strcmp("GET_GRENS_LIGHT", in_buf) == 0){

			}
			else if(strcmp("SET_GRENS_LIGHT(Z)", in_buf) == 0){

			}


/*****************************************************************Exit**********************************************************************/			
			else if(strcmp("Exit", in_buf) == 0){
				if ((OUT % 2) == 1){
					uitrollen();					
				}
				ser_writeln("221 Bye!"); //Groeting wanneer je het programma sluit
				abort();
			}

/*----------------------------------------------------------------Help---------------------------------------------------------------------*/
			else if(strcmp("Help", in_buf) == 0){
				ser_writeln(
				"------------------Zonnescherm------------------\n\r"
				"UNROLL\t\tLaat het zonnescherm uitrollen\n\r"
				"ROLLUP\t\tLaat het zonnescherm oprollen\n\n\r"
				"STATUS"
				"--------------------Sensors---------------------\n\r"
				"GET_TEMP\t\tGeeft temperatuur van dat moment terug\n\n\r"
				"GET_GRENS_TEMP"
				"SET_GRENS_TEMP(Z)"
				"GET_LIGHT"
				"GET_GRENS_LIGHT"
				"SET_GRENS_LIGHT(Z)"
				"GET_MAX_UNROLL"
				"SET_MAX_UNROLL(Z)"
				"GET_MIN_UNROLL"
				"SET_MIN_UNROLL(Z)"
				"-------------------Information------------------\n\r"
				"GET_NAME"
				"SET_NAME(Z)"
				"GET_LOCATION"
				"SET_LOCATION(Z)"
				"-------------------Overige------------------\n\r"
				"Help\t\t\tWeergeeft alle commando's\n\r"
				"Exit\t\t\tSluit het programma\n"
				);
			}
/*********************************************************Commando niet gevonden************************************************************/		
			else{
				ser_writeln("510 Commando niet gevonden! Type Help voor alle commando's\n");
			}		
}


void uitrollen(){
	OUT = (OUT + 1);
	IN = (IN + 1);
	ser_write("250 "); //Geef aan dat het commando is gelukt
	// Zet pin 5 uit (groene lampje)
	PORTB &= ~_BV(PORTB5);
	//PORTD = 0xff; //													DELETE AFTER
	// Zet pin 3 aan (rode lampje)
	PORTB |= _BV(PORTB3);
	while (i < 25){
		// Laat pin 4 knippen (gele lampje)
		PORTB |= _BV(PORTB4);
		_delay_ms(DELAY_MS);
		PORTB &= ~_BV(PORTB4);
		_delay_ms(DELAY_MS);
		i += 1;
		if (i % 2 == 0){ser_write(".");}
	}
	i = 0;
	ser_writeln("\n\r201 Zonnescherm is uitgerold\n");
	_delay_ms(DELAY_MS);
}

void oprollen(){
	IN = (IN + 1);
	OUT = (OUT + 1);
	ser_write("250 "); //Geef aan dat het commando is gelukt
	// Zet pin 3 uit (rode lampje)
	PORTB &= ~_BV(PORTB3);
	//PORTD = 0x00; //													DELETE AFTER
	// Zet pin 5 aan (groene lampje)
	PORTB |= _BV(PORTB5);
	while (i < 25){
		// Laat pin 4 knippen (gele lampje)
		PORTB |= _BV(PORTB4);
		_delay_ms(DELAY_MS);
		PORTB &= ~_BV(PORTB4);
		_delay_ms(DELAY_MS);
		i += 1;
	if (i % 2 == 0){ser_write(".");}
	}
	i = 0;
	ser_writeln("\n\r201 Zonnescherm is opgerold\n");
	_delay_ms(DELAY_MS);	
}

ISR(INT0_vect)
{
	_delay_ms(50);
	ser_writeln("Interupt werk!");
}