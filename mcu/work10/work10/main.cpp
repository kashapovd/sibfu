#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"
#include "tcn75a.h"
#include "i2c.h"

ISR(INT0_vect){
   if (~PIND & 0b00000100) {
      PORTB &= ~(1<<PORTB3);
      PORTB |= 1<<PORTB2;
   } else {
      PORTB &= ~(1<<PORTB2);
      PORTB |= 1<<PORTB3;
   }
}

int main(void) {
   IIC i2c = IIC();
   i2c.init();

   TCN75A tcn75a = TCN75A(i2c);
   tcn75a.init();
   tcn75a.setLimitTemp(TCN75A::floatToTemp(30.50), TCN75A::Limit);
   tcn75a.setLimitTemp(TCN75A::floatToTemp(25.0), TCN75A::Hyst);
   
   HD44780 lcd = HD44780();
   lcd.init();
   
   DDRB = 1<<PORTB2 | 1<<PORTB3;
   PORTB = 1<<PORTB2 | 1<<PORTB3;
   GICR = (1 << INT0);
   MCUCR = (1 << ISC00);
   sei();
   
   while (1) {
      char buffer[5];
      
      lcd.setCursor(0,0);
      lcd.put("H:");
      temperature temp = tcn75a.getTemp(TCN75A::Hyst);
      itoa(temp.main, buffer, 10);
      lcd.put(buffer);
      lcd.put('.');
      itoa(temp.fraction, buffer, 10);
      lcd.put(buffer);
      
      lcd.setCursor(9,0);
      lcd.put("L:");
      temp = tcn75a.getTemp(TCN75A::Limit);
      itoa(temp.main, buffer, 10);
      lcd.put(buffer);
      lcd.put('.');
      itoa(temp.fraction, buffer, 10);
      lcd.put(buffer);
      
      lcd.setCursor(4,1);
      lcd.put("Tc:");
      temp = tcn75a.getTemp();
      itoa(temp.main, buffer, 10);
      lcd.put(buffer);
      lcd.put('.');
      itoa(temp.fraction, buffer, 10);
      lcd.put(buffer);
   }
}