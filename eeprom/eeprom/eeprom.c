/*
 * eeprom.c
 *
 * Created: 8-11-2018 13:45:35
 *  Author: Jurian
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "serial.h"
#include "keuze.h"

int main(void){
	ser_init();
	
    while(1)
    {
		geef_Opdracht();						
    }
}