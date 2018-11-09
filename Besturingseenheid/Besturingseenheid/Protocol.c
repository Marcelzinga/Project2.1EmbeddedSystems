#include <avr/io.h>
//#define F_CPU 16E6 -> Dit moet wel als je Visual Studio gebruikt
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "Zonnescherm.h"
#include "Besturingseenheid.h"

int teller;

//Hoevaak de "for-loop" uitgevoerd wordt.
int grensTellerNaam = 40;
int grensTellerLocatie = 40;
int grensTellerVersie = 8;
int grensTellerTemp = 3;
int grensTellerLicht = 4;
int grensTellerminUnroll = 4;
int grensTellermaxUnroll = 4;


//Start locaties van de variabelen in de EEPROM register.
int locNaam = 0;
int locLocatie = 40;
int locVersie = 80;
int locTemp = 88;
int locLicht = 91;
int locminUnroll = 95;
int locmaxUnroll = 99;


//Breedte van de string instellen.
char naam[40];
char naamRes[40];

char locatie[40];
char locatieRes[40];

char versie[8];
char versieRes[8];

char grens_temperatuur[3];
char grens_temperatuurRes[3];

char grens_lichtint[4];
char grens_lichtintRes[4];

char minUnroll[4];
char minUnrollRes[4];

char maxUnroll[4];
char maxUnrollRes[4];



char in_buf[30]; // Invoerbuffer


//-----------------------Deze instellingen worden gereplaced
double grens_temp= 25;
uint8_t grens_light = 180;
double max_unroll= 20;
double min_unroll= 4;

uint8_t get_grens_light(){
	return grens_light;
}	

double get_grens_temp(){
	return grens_temp;
}

double get_max_unroll(){
	return max_unroll;
}
double get_min_unroll(){
	return min_unroll;
}
//---------------------------
void protocolCom(){
	while (1) {
		ser_write("Wat kan ik voor u doen? ");
		ser_readln(in_buf, sizeof(in_buf), 1);
/**********************************************************Zonnescherm uitrollen************************************************************/
			if (strcmp("UNROLL", in_buf) == 0){ //Wanneer uitrollen wordt gerequest
				if ((getOut() % 2) == 1){
					ser_writeln("999 Zonnescherm is al uitgerold!");
				} if((getOut() % 2) == 0){
					uitrollen();
				}				
			}
/*---------------------------------------------------------Zonnescherm oprollen------------------------------------------------------------*/ 
			else if(strcmp("ROLLUP", in_buf) == 0){
				if ((getIn() % 2) == 0){
					ser_writeln("999 Zonnescherm is al opgerold!");
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
			
			}
			else if(strcmp("GET_GRENS_TEMP", in_buf) == 0){
				return_grensTemp();
				//printf("202 GRENS_TEMP: % 6.2f \n", grens_temperatuurRes);
			}
			else if(strcmp("SET_GRENS_TEMP(Z)", in_buf) == 0){
				//printf("203 GRENS_TEMP: %6.2f -> %6.2f ", grens_temperatuurRes, in_buf);
				ser_writeln("600 Zet de temperatuur grenswaarde van uw zonnepaneel");
				ser_readln(grens_temperatuur, sizeof(grens_temperatuur), 1);
				set_grensTemp(grens_temperatuur);
				
			}
/*----------------------------------------------------------Get Lichtintensiteit---------------------------------------------------------------------*/
			else if(strcmp("GET_LIGHT", in_buf) == 0){
				printf("202 LIGHT %i \n", getLight());
			}
			
			else if(strcmp("GET_GRENS_LIGHT", in_buf) == 0){
				//printf("202 GRENS_LIGHT: % 6.2f \n", grens_lichtint);
				return_grensLicht();
			}
			else if(strcmp("SET_GRENS_LIGHT(Z)", in_buf) == 0){
				//printf("203 GRENS_LIGHT: %6.2f -> %6.2f ", grens_lichtintRes, in_buf);
				ser_writeln("600 Zet de lichtintensiteit grenswaarde van uw zonnepaneel");
				ser_readln(grens_lichtint, sizeof(grens_lichtint), 1);
				set_grensLicht(grens_lichtint);
			}
/*----------------------------------------------------------Afstandsensor---------------------------------------------------------------------*/
			else if(strcmp("GET_MAX_UNROLL", in_buf) == 0){
				//printf("202 MAX_UNROLL= % 6.2f \n", max_unroll);
				return_maxUnroll();
			}
			else if(strcmp("SET_MAX_UNROLL(Z)", in_buf) == 0){
				//printf("203 MAX_UNROLL: %6.2f -> %6.2f ", maxUnrollRes, in_buf);G
				ser_writeln("600 Zet tot hoever de scherm kan inrollen in (cm)");
				ser_readln(maxUnroll, sizeof(maxUnroll), 1);
				set_maxUnroll(maxUnroll);
			}
			else if(strcmp("GET_MIN_UNROLL", in_buf) == 0){
				//printf("202 MIN_UNROLL= % 6.2f \n", minUnrollRes);
				return_minUnroll();
				
			}
			else if(strcmp("SET_MIN_UNROLL(Z)", in_buf) == 0){
				//printf("203 MIN_UNROLL: %6.2f -> %6.2f ", minUnrollRes, in_buf);
				ser_writeln("600 Zet tot hoever de scherm kan inrollen in (cm)");
				ser_readln(minUnroll, sizeof(minUnroll), 1);
				set_minUnroll(minUnroll);
			}
/*----------------------------------------------------------Information---------------------------------------------------------------------*/
			else if(strcmp("GET_NAME", in_buf) == 0){
				return_Naam();
			}
			else if(strcmp("SET_NAME(Z)", in_buf) == 0){
				
				ser_writeln("600 Zet de naam van uw zonnescherm");
				ser_readln(naam, sizeof(naam), 1);
				set_Naam(naam);
				
				printf("200 OK ");
			}
			
			else if(strcmp("GET_LOCATION", in_buf) == 0){
				//printf("202 NAME %s", locatieRes);
				return_Locatie();
			}
			else if(strcmp("SET_LOCATION(Z)", in_buf) == 0){
				
				ser_writeln("600 Zet de locatie van uw zonnescherm");
				ser_readln(locatie, sizeof(locatie), 1);
				set_Locatie(locatie);
				
				printf("200 OK ");
			}
			
				else if(strcmp("GET_VERSION", in_buf) == 0){
					//printf("202 NAME %s", versieRes);
					return_Versie();
				}
				else if(strcmp("SET_VERSION(Z)", in_buf) == 0){
					
					ser_writeln("600 Zet de versie van uw zonnepaneel");
					ser_readln(versie, sizeof(versie), 1);
					set_Versie(versie);
					
					printf("200 OK ");
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
				"999 \n\r"
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
			}
			
			
	//________________________________________________________________________________________//
	//Zetten van naam.
	void set_Naam(char* n){
		for (int teller = locNaam; teller <= grensTellerNaam; teller++){
			eeprom_update_byte((uint8_t*)teller,n[teller]);
		}
	}

	//Retourneren van naam
	void return_Naam(){
		for (int teller = locNaam; teller <= grensTellerNaam; teller++){
			naamRes[teller] = eeprom_read_byte((uint8_t*)teller);
		}
		ser_write("202 "),  ser_writeln(naamRes);
	}

	//Zetten van locatie.
	void set_Locatie(char* l){
		for (int teller = locLocatie; (teller - locLocatie) <= grensTellerLocatie; teller++){
			eeprom_update_byte((uint8_t*)teller,l[teller - locLocatie]);
		}
	}

	//Retourneren van locatie.
	void return_Locatie(){
		for (int teller = locLocatie; (teller - locLocatie) <= grensTellerLocatie; teller++){
			locatieRes[teller - locLocatie] = eeprom_read_byte((uint8_t*)teller);
		}
		ser_write("202 "), ser_writeln(locatieRes);
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
		ser_write("202 versie: "), ser_writeln(versieRes);
	}

	//Zetten van grens_temperatuur grenswaarde.
	void set_grensTemp(char* t){
		for (int teller = locTemp; (teller - locTemp) <= grensTellerTemp; teller++){
			eeprom_update_byte((uint8_t*)teller,t[teller - locTemp]);
		}
	}

	//Retourneren van grenswaarde grens_temperatuur.
	void return_grensTemp(void){
		for (int teller = locTemp; (teller - locTemp) <= grensTellerTemp; teller++){
			grens_temperatuurRes[teller - locTemp] = eeprom_read_byte((uint8_t*)teller);
		}
		ser_write("202 GRENS_TEMP:" ), ser_writeln(grens_temperatuurRes);
	}

	//Zetten van grens_lichtintensiteit grenswaarde.
	void set_grensLicht(char* li){
		for (int teller = locLicht; (teller - locLicht) <= grensTellerLicht; teller++){
			eeprom_update_byte((uint8_t*)teller,li[teller - locLicht]);
		}
	}


	//Retourneren van grenswaarde grens_lichtintensiteit.
	void return_grensLicht(void){
		for (int teller = locLicht; (teller - locLicht) <= grensTellerLicht; teller++){
			grens_lichtintRes[teller - locLicht] = eeprom_read_byte((uint8_t*)teller);
		}
		ser_write("202 licht_TEMP:" ), ser_writeln(grens_lichtintRes);
	}

	//Zetten van de maximale inrol.
	void set_minUnroll(char* in){
		for (int teller = locminUnroll; (teller - locminUnroll) <= grensTellerminUnroll; teller++){
			eeprom_update_byte((uint8_t*)teller,in[teller - locminUnroll]);
		}
		
	}


	//Retourneren van de maximale inrol waarde.
	void return_minUnroll(void){
		for (int teller = locminUnroll; (teller - locminUnroll) <= grensTellerminUnroll; teller++){
			minUnrollRes[teller - locminUnroll] = eeprom_read_byte((uint8_t*)teller);
		}
		ser_write("203, MIN_UNROLL: "), ser_writeln(minUnrollRes);
	}

	//Zetten van de maximale uitrol.
	void set_maxUnroll(char* uit){
		for (int teller = locmaxUnroll; (teller - locmaxUnroll) <= grensTellermaxUnroll; teller++){
			eeprom_update_byte((uint8_t*)teller,uit[teller - locmaxUnroll]);
		}
	}


	//Retourneren van de maximale uitrol waarde.
	void return_maxUnroll(void){
		for (int teller = locmaxUnroll; (teller - locmaxUnroll) <= grensTellermaxUnroll; teller++){
			maxUnrollRes[teller - locmaxUnroll] = eeprom_read_byte((uint8_t*)teller);
		}
		ser_write("203 MAX_UNROLL: "), ser_writeln(maxUnrollRes);
	}	