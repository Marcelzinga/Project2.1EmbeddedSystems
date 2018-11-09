/*
 * keuze.c
 *
 * Created: 9-11-2018 16:44:42
 *  Author: Jurian
 */

#include <avr/io.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include "keuze.h"
#include "serial.h"


int teller;

//Hoevaak de "for-loop" uitgevoerd wordt.
int grensTellerNaam = 40;
int grensTellerLocatie = 40;
int grensTellerVersie = 8;
int grensTellerTemp = 3;
int grensTellerLicht = 4;
int grensTellerMaxInrol = 4;
int grensTellerMaxUitrol = 4;


//Start locaties van de variabelen in de EEPROM register.
int locNaam = 0;
int locLocatie = 40;
int locVersie = 80;
int locTemp = 88;
int locLicht = 91;
int locMaxInrol = 95;
int locMaxUitrol = 99;


//Breedte van de string instellen.
char naam[40];
char naamRes[40];

char locatie[40];
char locatieRes[40];

char versie[8];
char versieRes[8];

char temperatuur[3];
char temperatuurRes[3];

char lichtint[4];
char lichtintRes[4];

char maxInrol[4];
char maxInrolRes[4];

char maxUitrol[4];
char maxUitrolRes[4];

char opdracht[25];

//Starten van de keuze/
void geef_Opdracht(void){
	
	ser_writeln("Geef uw opdracht");
	ser_readln(opdracht, sizeof(opdracht), 1);
	
	//Functie oproepen om het zonnescherm een naam te geven.
	if(strcmp("set naam", opdracht) == 0){
		ser_writeln("Zet de naam van uw zonnescherm");
		ser_readln(naam, sizeof(naam), 1);
		set_Naam(naam);
	}
	
	//Functie oproepen om de naam van het zonnescherm te ontvangen.
	else if(strcmp("return naam", opdracht) == 0){
		return_Naam();
	}
	
	//Functie oproepen om een locatie aan het zonnescherm toe te wijzen.
	else if(strcmp("set locatie", opdracht) == 0){
		ser_writeln("Zet de locatie van uw zonnescherm");
		ser_readln(locatie, sizeof(locatie), 1);
		set_Locatie(locatie);
	}
	
	//Functie oproepen om de locatie van het zonnescherm te ontvangen.
	else if(strcmp("return locatie", opdracht) == 0){
		return_Locatie();
	}
	
	//Functie oproepen om een versie nummer aan het zonnescherm te koppelen.
	else if(strcmp("set versie", opdracht) == 0){
		ser_writeln("Zet de versie van uw zonnepaneel");
		ser_readln(versie, sizeof(versie), 1);
		set_Versie(versie);
	}
	
	//Functie oproepen om de versie nummer van het zonnescherm te ontvangen.
	else if(strcmp("return versie", opdracht) == 0){
		return_Versie();
	}
	
	//Functie oproepen om temperatuur grenswaarde aan het zonnescherm te koppelen.
	else if(strcmp("set temp", opdracht) == 0){
		ser_writeln("Zet de temperatuur grenswaarde van uw zonnepaneel");
		ser_readln(temperatuur, sizeof(temperatuur), 1);
		set_Temp(temperatuur);
	}
	
	//Functie oproepen om de temperatuur grenswaarde van het zonnescherm te ontvangen.
	else if(strcmp("return temp", opdracht) == 0){
		return_Temp();
	}
	
	//Functie oproepen om lichtintensiteit grenswaarde aan het zonnescherm te koppelen.
	else if(strcmp("set licht", opdracht) == 0){
		ser_writeln("Zet de lichtintensiteit grenswaarde van uw zonnepaneel");
		ser_readln(lichtint, sizeof(lichtint), 1);
		set_Licht(lichtint);
	}
	
	//Functie oproepen om de lichtintensiteit grenswaarde van het zonnescherm te ontvangen.
	else if(strcmp("return licht", opdracht) == 0){
		return_Licht();
	}
	
	//Functie oproepen om de maximale inrol waarde te geven.
	else if(strcmp("set inrol", opdracht) == 0){
		ser_writeln("Zet tot hoever de scherm kan inrollen in (cm)");
		ser_readln(maxInrol, sizeof(maxInrol), 1);
		set_MaxInrol(maxInrol);
	}
	
	//Functie oproepen om de maximale inrol waarde te ontvangen.
	else if(strcmp("return inrol", opdracht) == 0){
		return_MaxInrol();
	}
	
	//Functie oproepen om de maximale uitrol waarde te geven.
	else if(strcmp("set uitrol", opdracht) == 0){
		ser_writeln("Zet tot hoever de scherm kan inrollen in (cm)");
		ser_readln(maxUitrol, sizeof(maxUitrol), 1);
		set_MaxUitrol(maxUitrol);
	}
	
	//Functie oproepen om de maximale uitrol waarde te ontvangen.
	else if(strcmp("return uitrol", opdracht) == 0){
		return_MaxUitrol();
	}
	
	//Invoer voldoet niet aan de eisen
	else{
		ser_writeln("Waarde is onjuist");
	}
	
}

/*
void checker(char* inv, char* chk){
	if(strcmp(inv, chk) > 1{
		
	}	
}
*/
//________________________________________________________________________________________//
//Zetten van naam.
void set_Naam(char* n){
	for (int teller = locNaam; teller <= grensTellerNaam; teller++){
		eeprom_update_byte((uint8_t*)teller,n[teller]);
	}
}

//Retourneren van naam
void return_Naam(void){
	for (int teller = locNaam; teller <= grensTellerNaam; teller++){
		naamRes[teller] = eeprom_read_byte((uint8_t*)teller);
	}
	ser_writeln(naamRes);
}

//Zetten van locatie.
void set_Locatie(char* l){
	for (int teller = locLocatie; (teller - locLocatie) <= grensTellerLocatie; teller++){
		eeprom_update_byte((uint8_t*)teller,l[teller - locLocatie]);
	}
}

//Retourneren van locatie.
void return_Locatie(void){
	for (int teller = locLocatie; (teller - locLocatie) <= grensTellerLocatie; teller++){
		locatieRes[teller - locLocatie] = eeprom_read_byte((uint8_t*)teller);
	}
	ser_writeln(locatieRes);
}

//Zetten van versienummer.
void set_Versie(char* v){
	for (int teller = locVersie; (teller - locVersie) <= grensTellerVersie; teller++){
		eeprom_update_byte((uint8_t*)teller,v[teller - locVersie]);
	}
}

//Retourneren versie nummer.
void return_Versie(void){
	for (int teller = locVersie; (teller - locVersie) <= grensTellerVersie; teller++){
		versieRes[teller - locVersie] = eeprom_read_byte((uint8_t*)teller);
	}
	ser_writeln(versieRes);
}

//Zetten van temperatuur grenswaarde.
void set_Temp(char* t){
	for (int teller = locTemp; (teller - locTemp) <= grensTellerTemp; teller++){
		eeprom_update_byte((uint8_t*)teller,t[teller - locTemp]);
	}
}

//Retourneren van grenswaarde temperatuur.
void return_Temp(void){
	for (int teller = locTemp; (teller - locTemp) <= grensTellerTemp; teller++){
		temperatuurRes[teller - locTemp] = eeprom_read_byte((uint8_t*)teller);
	}
	ser_writeln(temperatuurRes);
}

//Zetten van lichtintensiteit grenswaarde.
void set_Licht(char* li){
	for (int teller = locLicht; (teller - locLicht) <= grensTellerLicht; teller++){
		eeprom_update_byte((uint8_t*)teller,li[teller - locLicht]);
	}
}


//Retourneren van grenswaarde lichtintensiteit.
void return_Licht(void){
	for (int teller = locLicht; (teller - locLicht) <= grensTellerLicht; teller++){
		lichtintRes[teller - locLicht] = eeprom_read_byte((uint8_t*)teller);
	}
	ser_writeln(lichtintRes);
}

//Zetten van de maximale inrol.
void set_MaxInrol(char* in){
	for (int teller = locMaxInrol; (teller - locMaxInrol) <= grensTellerMaxInrol; teller++){
		eeprom_update_byte((uint8_t*)teller,in[teller - locMaxInrol]);
	}
}


//Retourneren van de maximale inrol waarde.
void return_MaxInrol(void){
	for (int teller = locMaxInrol; (teller - locMaxInrol) <= grensTellerMaxInrol; teller++){
		maxInrolRes[teller - locMaxInrol] = eeprom_read_byte((uint8_t*)teller);
	}
	ser_writeln(maxInrolRes);
}

//Zetten van de maximale uitrol.
void set_MaxUitrol(char* uit){
	for (int teller = locMaxUitrol; (teller - locMaxUitrol) <= grensTellerMaxUitrol; teller++){
		eeprom_update_byte((uint8_t*)teller,uit[teller - locMaxUitrol]);
	}
}


//Retourneren van de maximale uitrol waarde.
void return_MaxUitrol(void){
	for (int teller = locMaxUitrol; (teller - locMaxUitrol) <= grensTellerMaxUitrol; teller++){
		maxUitrolRes[teller - locMaxUitrol] = eeprom_read_byte((uint8_t*)teller);
	}
	ser_writeln(maxUitrolRes);
}