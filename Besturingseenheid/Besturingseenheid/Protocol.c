#include <avr/io.h>
//#define F_CPU 16E6 -> Dit moet wel als je Visual Studio gebruikt
#include <stdio.h>
#include <string.h>
#include "serial.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "Zonnescherm.h"
#include "Besturingseenheid.h"




// Prototypes
char* get_grensLight();
char* get_grensTemp();
char* get_minUnroll();
char* get_maxUnroll();
char* get_Naam();
char* get_Locatie();
char* get_Versie();

char in_buf[30]; // Invoerbuffer

char *substring;
char *temporaryget;

char HANDSHAKE[10] = {'k', 'e', 'r', 's', 't', 'h', 'a', 'a', 'n', '\0'};

int AUT = 0;

int get_automatishStatus(){
	return AUT;
}
// De handshakeprocedure is niet compleet. Wanneer 
void protocolCom(){
	/*ser_write("201 Please enter ID");
	ser_readln(in_buf, sizeof(in_buf), 1);
	int ret;
	ret = strcmp(HANDSHAKE, in_buf);
	if(ret |= 0){
		ser_writeln("504: Verkeerde ID");
	}
	else{
		// groeneotter is het antwoord op de handshake
		printf("201 groeneotter \n");
		ser_writeln("200 Handshake bevestigt");*/
		while (1) {
			ser_write("204 Wat kan ik voor u doen");
			ser_readln(in_buf, sizeof(in_buf), 1);
/**********************************************************Zonnescherm uitrollen************************************************************/
			if (strcmp("UNROLL", in_buf) == 0){ //Wanneer uitrollen wordt gerequest
				if ((get_unrollStatus() % 2) == 1){
					ser_writeln("501 Zonnescherm is al uitgerold!");
				} if((get_unrollStatus() % 2) == 0){
					uitrollen();
				}				
			}
/*---------------------------------------------------------Zonnescherm oprollen------------------------------------------------------------*/ 
			else if(strcmp("ROLLUP", in_buf) == 0){
				if ((get_unrollStatus() % 2) == 0){
					ser_writeln("501 Zonnescherm is al opgerold!");
				} if((get_unrollStatus() % 2) == 1){
					oprollen();
				}				
			} 
/**********************************************************Zonnescherm uitrollen************************************************************/
			if (strcmp("STATUS", in_buf) == 0){ //Wanneer uitrollen wordt gerequest
				printf("202 Status: %i", get_unrollStatus());
			}
			
			if (strcmp("TOGGLEAUT", in_buf) == 0){ //Wanneer uitrollen wordt gerequest

			if ((get_automatishStatus()%2)==1){
				printf("202 AUT UIT \n");
			}
			else{
				printf("202 AUT AAN \n");
			}	
			AUT = AUT + 1;	
		}
			
/*--------------------------------------------------------Get Temperatuur -----------------------------------------------------------------*/
			else if(strcmp("GET_TEMP", in_buf) == 0){
				printf("202 TEMP= % 6.2f \n", getTemp());
			
			}
			else if(strcmp("GET_GRENS_TEMP", in_buf) == 0){
				//printf("202 GRENS_TEMP: % 6.2f \n", grens_temperatuurRes);
				ser_write("202 GRENS_TEMP:" ), ser_writeln(get_grensTemp());
			}
			else if(strncmp("SET_GRENS_TEMP(Z)", in_buf, 14) == 0){
				//printf("203 GRENS_TEMP: %6.2f -> %6.2f ", grens_temperatuurRes, in_buf);
				/*
				if(sizeof in_buf> 20){
					int temp = sizeof in_buf;
					printf("504 Ongeldige temperatuur");
				}*				
				
				else{*/
				ser_write("203 GRENS_TEMP: "), ser_write(get_grensTemp()), ser_write(" -> ");
				set_substring();
				set_grensTemp(substring);
				ser_writeln(get_grensTemp());
				//}
			}
		else if(strcmp("GET_ALL", in_buf) == 0)
		{
			printf("202 TEMP%6.2f \n", getTemp());
			printf("202 LIGHT %i \n", getLight());
			printf("204 AFSTAND%6.2fcm \n", getDistance());
			ser_write("205 MAX_UNROLL "), ser_writeln(get_maxUnroll());
			ser_write("206 MIN_UNROLL "), ser_writeln(get_minUnroll());
			ser_write("207 GRENS_LIGHT " ), ser_writeln(get_grensLight());
			ser_write("208 GRENS_TEMP " ), ser_writeln(get_grensTemp());
			ser_write("205 "),  ser_writeln(get_Naam());
			ser_write("206 "), ser_writeln(get_Locatie());
			
		}				
/*----------------------------------------------------------Get Lichtintensiteit---------------------------------------------------------------------*/
			else if(strcmp("GET_LIGHT", in_buf) == 0){
				printf("202 LIGHT %i \n", getLight());
			}
			
			else if(strcmp("GET_GRENS_LIGHT", in_buf) == 0){
				//printf("202 GRENS_LIGHT: % 6.2f \n", grens_lichtint);
				ser_write("202 GRENS_LIGHT:" ), ser_writeln(get_grensLight());
				
			}
			else if(strncmp("SET_GRENS_LIGHT(Z)", in_buf, 15) == 0){
				//printf("203 GRENS_LIGHT: %6.2f -> %6.2f ", grens_lichtintRes, in_buf);
				/*if(sizeof in_buf> 20){
					printf("504 Ongeldige lichtintensiteit");
				}
				else{*/
				ser_write("203 GRENS_LIGHT: "), ser_write(get_grensLight()), ser_write(" -> ");
				set_substring();
				set_grensLicht(substring);
				ser_writeln(get_grensLight());
				//}				
			}
/*----------------------------------------------------------Afstandsensor---------------------------------------------------------------------*/
			else if(strcmp("GET_MAX_UNROLL", in_buf) == 0){
				//printf("202 MAX_UNROLL= % 6.2f \n", max_unroll);
				ser_write("203 MAX_UNROLL: "), ser_writeln(get_maxUnroll());
			}
			else if(strncmp("SET_MAX_UNROLL(Z)", in_buf, 15) == 0){
				//printf("203 MAX_UNROLL: %6.2f -> %6.2f ", maxUnrollRes, in_buf);
				
				/*if(sizeof in_buf> 19){
					printf("504 Ongeldige uitrolwaarde");
				}
				else{*/
				ser_write("203 MAX_UNROLL: "), ser_write(get_maxUnroll()), ser_write(" -> ");
				set_substring();
				set_maxUnroll(substring);
				ser_writeln(get_maxUnroll());
				//}
			}				
			else if(strcmp("GET_MIN_UNROLL", in_buf) == 0){
				//printf("202 MIN_UNROLL= % 6.2f \n", minUnrollRes);
				ser_write("203 MIN_UNROLL: "), ser_writeln(get_minUnroll());
				
			}
			else if(strncmp("SET_MIN_UNROLL(Z)", in_buf, 15) == 0){
				//printf("203 MIN_UNROLL: %6.2f -> %6.2f ", minUnrollRes, in_buf);
				
				/*if(sizeof in_buf> 19){
					printf("504 Ongeldige inrolwaarde");
				}
				else{*/
				ser_write("203 MIN_UNROLL: "), ser_write(get_minUnroll()), ser_write(" -> ");
				set_substring();
				set_minUnroll(substring);
				ser_writeln(get_minUnroll());
				//}				
			}
/*----------------------------------------------------------Information---------------------------------------------------------------------*/
			else if(strcmp("GET_NAME", in_buf) == 0){
				ser_write("202 "),  ser_writeln(get_Naam());
			}
				
			else if(strncmp("SET_NAME(Z)", in_buf, 8) == 0){
				/*if(sizeof in_buf> 49){
					printf("504 Te lange naam");
				}
				else{*/
				set_substring();
				set_Naam(substring);
				printf("200 OK \n");
				//}				
			}
			
			else if(strcmp("GET_LOCATION", in_buf) == 0){
				//printf("202 NAME %s", locatieRes);
				ser_write("202 "), ser_writeln(get_Locatie());
			}
			else if(strncmp("SET_LOCATION(Z)", in_buf, 12) == 0){
				/*if(sizeof in_buf> 53){
					printf("504 Te lange naam voor locatie");
				}
				else{*/
				set_substring();
				set_Locatie(substring);
				
				printf("200 OK \n");
				//}				
			}
			
				else if(strcmp("GET_VERSION", in_buf) == 0){
					//printf("202 NAME %s", versieRes);
					ser_write("202 versie: "), ser_writeln(get_Versie());
				}
				else if(strncmp("SET_VERSION(Z)", in_buf, 12) == 0){
					/*if(sizeof in_buf> 19){
						printf("504 Te groot nummer");
					}
					else{*/
					set_substring();
					set_Versie(substring);
					
					printf("200 OK \n");
					//}					
				}

/*****************************************************************Exit**********************************************************************/			
			else if(strcmp("Exit", in_buf) == 0){
				if ((get_unrollStatus() % 2) == 1){
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
				"TOGGLEAUT"
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
			//}					
			

//_______________________________________________________________________________________________//
	

void set_substring(){
	char * p1 = strstr (in_buf, "(");
	p1[strlen(p1) -1] = '\0';
	substring = p1 +1;
}