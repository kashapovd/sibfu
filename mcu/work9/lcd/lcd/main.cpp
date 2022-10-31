/*
 * lcd.cpp
 *
 * Created: 31.10.2022 3:03:40
 * Author : yaroslav
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"

int main(void) {
	HD44780 lcd = HD44780();
	lcd.init();
	
	while (1) {
		lcd.setCursor(0,0);
		lcd.put('a');
		lcd.put('b');
	}
}

