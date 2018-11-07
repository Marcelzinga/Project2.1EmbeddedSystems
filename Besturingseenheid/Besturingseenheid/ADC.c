#include <avr/io.h>


void ADC_init()
{
	//ref = vcc, left adjust the result (8 bit resolution)
	// select channel 0 (PC0 = input)
	ADMUX |= (1<<REFS0) | (1<<ADLAR);
	// enable the ADC & prescale = 128
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	DIDR0 = (1<<ADC5D); //!!Disables pin 5? not sure what it does atm
	
}

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
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADC;
}

uint8_t get_licht_adc(){
	ADCSRA |= (1<<ADSC); // start conversion
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADCH; // 8bit resolution, left adjusted
}