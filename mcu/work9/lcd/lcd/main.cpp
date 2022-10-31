/*
 * lcd.cpp
 *
 * Created: 31.10.2022 3:03:40
 * Author : @kashapovd, @nuard
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lcd.h"
#include "game.h"

HD44780 lcd = HD44780();
int c=0;

void print_game_screen() {
	lcd.clear();
	lcd.setCursor(0, 0);
	for (int j = 0; j < game::MAP_WIDTH; j++) {
		lcd.put(game::screen[0][j]);
	}
	lcd.setCursor(0, 1);
	for (int j = 0; j < game::MAP_WIDTH; j++) {
		lcd.put(game::screen[1][j]);
	}
}

void init() {
	TCNT0 = 0;
	OCR0 = 0xff;
	TCCR0 = 1 << CS02 | 1 << CS00;
	TIMSK = (1<<OCIE0);
	GICR = (1 << INT0) | (1 << INT1);
	DDRB = 0xFF;
	PORTB = 0xFF;
	MCUCR = (1 << ISC00) | (1 << ISC01) | (1 << ISC10) | (1 << ISC11);
	sei();
}

ISR(INT0_vect) {
	if (game::state == game::menu) {
		game::update_state(game::running);
	} else if (game::state == game::gameover) {
		OCR0 = 0xff;
		c=0;
		game::update_state(game::menu);
	} else if (game::state == game::running) {
		game::player_jump();
	}
}

ISR(INT1_vect) {
	if (game::state == game::running) {
		game::player_dash();
	}
}

ISR (TIMER0_COMP_vect) {
	game::refresh();
	print_game_screen();
	
	if (game::state == game::running && c == 10) {
		OCR0 -=10;
		c=0;
	}
	c++;
}

int main(void) {
	srand(time(0));
	lcd.init();
	init();
	
	while (true) {
	}
}