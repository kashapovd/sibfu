#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"
#include "tcn75a.h"
#include "i2c.h"

int main(void) {
   IIC i2c = IIC();
   i2c.init();

   TCN75A tcn75a = TCN75A(i2c);
   tcn75a.init();
   
   HD44780 lcd = HD44780();
   lcd.init();
   
   while (1) {
	  char buffer[12];
      lcd.setCursor(0,0);
	  lcd.put("T: ");
	  temperature temp = tcn75a.getTemp();
	  itoa(temp.main, buffer, 10);
      lcd.put(buffer);
	  lcd.put('.');
	  memset(buffer, 0, 12);
	  itoa(temp.fraction, buffer, 10);
	  lcd.put(buffer);
	  lcd.put(" Th: ");
	  temp = tcn75a.getTemp(TCN75A::Limit);
	  itoa(temp.main, buffer, 10);
	  lcd.put(buffer);
	  lcd.put('.');
	  memset(buffer, 0, 12);
	  itoa(temp.fraction, buffer, 10);
	  lcd.put(buffer);
	  
	  
	  
	  _delay_ms(50);
   }
}

