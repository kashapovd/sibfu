/*
 * PMWs
 * work8.c
 * Author : @kashapovd, @nuark
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define true 1
#define false 0
typedef unsigned char uint8;
typedef unsigned char bool;

uint8 mode = 0;
bool isStarted = false;

void configurePWM() {
	OCR0 = 127;
	TIMSK =(1<<OCIE0)|(1<<TOIE0);
	switch(mode) {
		case 1:
			TCCR0 = 1 << CS00 | 1 << CS02; // normal
			break;
		case 2:
			TCCR0 = 1 << COM01| 1 << COM00 | 1 << WGM00 | 1 << CS02; // phase
			break;
		case 3:
			TCCR0 = 1 << WGM01 | 1 << CS00 | 1 << CS01;
			break;
		default:
			TCCR0 = 1 << COM01| 1 << COM00 | 1 << WGM01 | 1 << WGM00 | 1 << CS00 | 1 << CS01; // fast
			break;
	}
}

ISR(INT0_vect) {
	if (isStarted) {
		} else {
		mode = mode < 3 ? ++mode : 0;
		PORTB = ~mode;
	}
}

ISR (TIMER0_OVF_vect) {
	PORTB &= ~(1<<3);
}

ISR (TIMER0_COMP_vect) {
	switch(mode) {
		case 3:
			PORTB ^= (1<<3);
			break;
		default:
			PORTB |= (1<<3);
			break;
	}
}

ISR(INT1_vect){
	if (isStarted == false) {
		isStarted = true;
		PORTB = 0xFF;
		configurePWM();

	}
	else {
		TCCR0 = 0;
		TCNT0 = 0;
		TIMSK = 0;
		isStarted = false;
		PORTB = ~mode;
	}
	
}

void setup() {
	DDRB = 0xFF;
	PORTB = 0xFF;
	TCNT0 = 0;
	TIFR = (1<<OCIE0);
	GICR = 1 << INT0 | 1 << INT1;
	MCUCR = 1 << ISC00 | 1 << ISC01 | 1 << ISC10 | 1 << ISC11;
	sei();
}

int main(void) {
	setup();
	while(1) {
		if (~PIND & 0b00000001) {
			OCR0 = OCR0 + 1;
			_delay_ms(50);
		}
		if (~PIND & 0b00000010) {
			OCR0 = OCR0 - 1;
			_delay_ms(50);
		}
	};
}
