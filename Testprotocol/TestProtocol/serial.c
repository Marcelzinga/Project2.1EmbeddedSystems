#include <avr/io.h>
#include <util/delay.h>

// output on USB = PD1 = board pin 1
// datasheet p.190; F_OSC = 16 MHz & baud rate = 19.200
#define UBBRVAL 51

void ser_init() {
	// set the baud rate
	UBRR0H = 0;
	UBRR0L = UBBRVAL;
	// disable U2X mode
	UCSR0A = 0;
	// enable TX and RX
	UCSR0B = _BV(TXEN0) | _BV(RXEN0);
	// set frame format : asynchronous, 8 data bits, 1 stop bit, no parity
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

// Low level transmit
void ser_transmit(uint8_t data) {
	// wait for an empty transmit buffer
	// UDRE is set when the transmit buffer is empty
	loop_until_bit_is_set(UCSR0A, UDRE0);
	// send the data
	UDR0 = data;
}

// Low level receive
uint8_t ser_receive() {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}

// Hele regel schrijven

void ser_write(char *s) {
	int i=0;
	while (s[i]!='\0') {
		ser_transmit(s[i++]);
	}
}

void ser_writeln(char* s) {
	ser_write(s);
	ser_transmit('\r');
	ser_transmit('\n');
}

// Hele regel lezen
void ser_readln(char* buf, int maxlength, uint8_t echo) {
	int i=0;
	while(1) {
		uint8_t c = ser_receive();
		if (echo) ser_transmit(c);
		if (c=='\r') {
			if (echo) ser_transmit('\n');
			break; // ENTER ontvangen
		}
		if (i<maxlength-1) {
			buf[i++]=c;
		}
	}
	buf[i]='\0';
}
