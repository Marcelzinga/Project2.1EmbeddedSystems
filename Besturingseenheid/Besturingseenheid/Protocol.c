#include <avr/io.h>
//#define F_CPU 16E6 -> Dit moet wel als je Visual Studio gebruikt
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include "Zonnescherm.h"


char in_buf[30]; // Invoerbuffer

void protocolCom(){
	//while (1) {
		ser_write("Wat kan ik voor u doen?");
		ser_readln(in_buf, sizeof(in_buf), 1);
/**********************************************************Zonnescherm uitrollen************************************************************/
			if (strcmp("Uitrollen", in_buf) == 0){ //Wanneer uitrollen wordt gerequest
				if ((getOut() % 2) == 1){
					ser_writeln("Zonnescherm is al uitgerold!");
				} if((getOut() % 2) == 0){
					uitrollen();
				}				
			}
/*---------------------------------------------------------Zonnescherm oprollen------------------------------------------------------------*/ 
			else if(strcmp("Oprollen", in_buf) == 0){
				if ((getIn() % 2) == 0){
					ser_writeln("Zonnescherm is al opgerold!");
				} if((getIn() % 2) == 1){
					oprollen();
				}				
			} 
/**********************************************************Zonnescherm uitrollen************************************************************/
			if (strcmp("STATUS", in_buf) == 0){ //Wanneer uitrollen wordt gerequest

			}
/*--------------------------------------------------------Get Temperatuur -----------------------------------------------------------------*/
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
/*----------------------------------------------------------Afstandsensor---------------------------------------------------------------------*/
			else if(strcmp("GET_MAX_UNROLL", in_buf) == 0){

			}
			else if(strcmp("SET_MAX_UNROLL(Z)", in_buf) == 0){

			}
			else if(strcmp("GET_MIN_UNROLL", in_buf) == 0){

			}
			else if(strcmp("SET_MIN_UNROLL(Z)", in_buf) == 0){

			}
/*----------------------------------------------------------Information---------------------------------------------------------------------*/
			else if(strcmp("GET_NAME", in_buf) == 0){

			}
			else if(strcmp("SET_NAME", in_buf) == 0){

			}
			else if(strcmp("GET_LOCATION", in_buf) == 0){

			}
			else if(strcmp("SET_LOCATION(Z)", in_buf) == 0){

			}

/*****************************************************************Exit**********************************************************************/			
			else if(strcmp("Exit", in_buf) == 0){
				if ((getOut() % 2) == 1){
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

/*
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
*/