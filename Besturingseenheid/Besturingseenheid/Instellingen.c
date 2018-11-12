#include <avr/eeprom.h>
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
int locLocatie = 50;
int locVersie = 90;
int locTemp = 106;
int locLicht = 119;
int locminUnroll = 133;
int locmaxUnroll = 146;

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


	 
	 //Zetten van naam.
	 void set_Naam(char* n){
		 for (int teller = locNaam; teller <= grensTellerNaam; teller++){
			 eeprom_update_byte((uint8_t*)teller,n[teller]);
		 }
	 }

	 //Retourneren van naam
	 char* get_Naam(){
		 for (int teller = locNaam; teller <= grensTellerNaam; teller++){
			 naamRes[teller] = eeprom_read_byte((uint8_t*)teller);
		 }
		 return naamRes;
	 }

	 //Zetten van locatie.
	 void set_Locatie(char* l){
		 for (int teller = locLocatie; (teller - locLocatie) <= grensTellerLocatie; teller++){
			 eeprom_update_byte((uint8_t*)teller,l[teller - locLocatie]);
		 }
	 }

	 //Retourneren van locatie.
	 char* get_Locatie(){
		 for (int teller = locLocatie; (teller - locLocatie) <= grensTellerLocatie; teller++){
			 locatieRes[teller - locLocatie] = eeprom_read_byte((uint8_t*)teller);
		 }
		 return locatieRes;
	 }

	 //Zetten van versienummer.
	 void set_Versie(char* v){
		 for (int teller = locVersie; (teller - locVersie) <= grensTellerVersie; teller++){
			 eeprom_update_byte((uint8_t*)teller,v[teller - locVersie]);
		 }
	 }

	 //Retourneren versie nummer.
	 char* get_Versie(){
		 for (int teller = locVersie; (teller - locVersie) <= grensTellerVersie; teller++){
			 versieRes[teller - locVersie] = eeprom_read_byte((uint8_t*)teller);
		 }
		 return versieRes;
	 }

	 //Zetten van grens_temperatuur grenswaarde.
	 void set_grensTemp(char* t){
		 for (int teller = locTemp; (teller - locTemp) <= grensTellerTemp; teller++){
			 eeprom_update_byte((uint8_t*)teller,t[teller - locTemp]);
		 }
	 }

	 //Retourneren van grenswaarde grens_temperatuur.
	 char* get_grensTemp(){
		 for (int teller = locTemp; (teller - locTemp) <= grensTellerTemp; teller++){
			 grens_temperatuurRes[teller - locTemp] = eeprom_read_byte((uint8_t*)teller);
		 }
		 //ser_write("202 GRENS_TEMP:" ), ser_writeln(grens_temperatuurRes);
		 return grens_temperatuurRes;
	 }

	 //Zetten van grens_lichtintensiteit grenswaarde.
	 void set_grensLicht(char* li){
		 for (int teller = locLicht; (teller - locLicht) <= grensTellerLicht; teller++){
			 eeprom_update_byte((uint8_t*)teller,li[teller - locLicht]);
		 }
	 }


	 //Retourneren van grenswaarde grens_lichtintensiteit.
	 char* get_grensLight(){
		 for (int teller = locLicht; (teller - locLicht) <= grensTellerLicht; teller++){
			 grens_lichtintRes[teller - locLicht] = eeprom_read_byte((uint8_t*)teller);
		 }
		 //ser_write("202 GRENS_LIGHT:" ), ser_writeln(grens_lichtintRes);
		 return grens_lichtintRes;
	 }

	 //Zetten van de maximale inrol.
	 void set_minUnroll(char* in){
		 for (int teller = locminUnroll; (teller - locminUnroll) <= grensTellerminUnroll; teller++){
			 eeprom_update_byte((uint8_t*)teller,in[teller - locminUnroll]);
		 }
		 
	 }


	 //Retourneren van de maximale inrol waarde.
	 char* get_minUnroll(){
		 for (int teller = locminUnroll; (teller - locminUnroll) <= grensTellerminUnroll; teller++){
			 minUnrollRes[teller - locminUnroll] = eeprom_read_byte((uint8_t*)teller);
		 }
		 return minUnrollRes;
	 }

	 //Zetten van de maximale uitrol.
	 void set_maxUnroll(char* uit){
		 for (int teller = locmaxUnroll; (teller - locmaxUnroll) <= grensTellermaxUnroll; teller++){
			 eeprom_update_byte((uint8_t*)teller,uit[teller - locmaxUnroll]);
		 }
	 }


	 //Retourneren van de maximale uitrol waarde.
	 char* get_maxUnroll(){
		 for (int teller = locmaxUnroll; (teller - locmaxUnroll) <= grensTellermaxUnroll; teller++){
			 maxUnrollRes[teller - locmaxUnroll] = eeprom_read_byte((uint8_t*)teller);
		 }
		 return maxUnrollRes;
	 }