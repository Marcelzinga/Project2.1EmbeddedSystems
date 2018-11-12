#include <avr/io.h>


void ADC_init()
{
	// enable the ADC & prescale = 128
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	DIDR0 = (1<<ADC5D); //!!Disables pin 5? not sure what it does atm
	
}

// Dit was om te kijken of de code wat geoptimaliseerd kon worden
// Geen succes, dus gaat het via 2 aparte get adc's
uint8_t get_adc_value(uint8_t inputPin)
{
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADCH; // 8bit resolution, left adjusted
	
	/*//ADMUX = (REFS0) |(1<<inputPin);
	if(inputPin = PB1){
		ADCSRA |= (1<<ADSC); // start conversion
		loop_until_bit_is_clear(ADCSRA, ADSC);
		return ADC;
	}
	else{
		ADCSRA |= (1<<ADSC); // start conversion
		loop_until_bit_is_clear(ADCSRA, ADSC);
		return ADCH; // 8bit resolution, left adjusted
	}*/	
}




uint8_t get_temp_adc(){
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2); // port A5
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADC;
}

uint8_t get_light_adc(){
	ADMUX = (1 << REFS0) | (1 << MUX1)| (1<<ADLAR); // port A2
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADCH; // 8bit resolution, left adjusted
}