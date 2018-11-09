/*
 * keuze.c
 *
 * Created: 9-11-2018 16:44:42
 *  Author: Jurian
 */

#include <avr/io.h>
#include <stdio.h>
#include "keuze.h"
#include <avr/eeprom.h>
#include "serial.h"

int tellerNaam;
int tellerLocatie;

int grensTellerNaam = 40;
int grensTellerLocatie = 40;

char naam[40];
char naamRes[40];

char locatie[40];
char locatieRes[40];

char opdracht[25];

void geef_Opdracht(void){
	
	ser_writeln("Geef uw opdracht");
	ser_readln(opdracht, sizeof(opdracht), 1);
	
	if(strcmp("set_Naam", opdracht) == 0){
		ser_writeln("Zet de naam van uw zonnescherm");
		ser_readln(naam, sizeof(naam), 1);
		set_Naam(naam);
	}
	
	else if(strcmp("return_Naam", opdracht) == 0){
		return_Naam();
	}
	
	else if(strcmp("set_Locatie", opdracht) == 0){
		ser_writeln("Zet de locatie van uw zonnescherm");
		ser_readln(locatie, sizeof(locatie), 1);
		set_Locatie(locatie);
	}
	
	else if(strcmp("return_Locatie", opdracht) == 0){
		return_Locatie();
	}
	
	else{
		ser_writeln("Waarde is onjuist");
	}
}

void set_Naam(char* n){
	for (int tellerNaam = 0; tellerNaam <= grensTellerNaam; tellerNaam++){
		eeprom_update_byte((uint8_t*)tellerNaam,n[tellerNaam]);
	}
}

void return_Naam(void){
	for (int tellerNaam = 0; tellerNaam <= grensTellerNaam; tellerNaam++){
		naamRes[tellerNaam] = eeprom_read_byte((uint8_t*)tellerNaam);
	}
	ser_writeln(naamRes);
}

void set_Locatie(char* l){
	for (int tellerLocatie = 41; (tellerLocatie - 41) <= grensTellerLocatie; tellerLocatie++){
		eeprom_update_byte((uint8_t*)tellerLocatie,l[tellerLocatie - 41]);
	}
}

void return_Locatie(void){
	for (int tellerLocatie = 41; (tellerLocatie - 41) <= grensTellerLocatie; tellerLocatie++){
		locatieRes[tellerLocatie - 41] = eeprom_read_byte((uint8_t*)tellerLocatie);
	}
	ser_writeln(locatieRes);
}