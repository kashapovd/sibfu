#include "i2c.h"
#include <avr/io.h>

IIC::IIC() {}

void IIC::init() {
   IIC_PORT |= 1 << IIC_SCL | 1 << IIC_SDA;
   IIC_DDR &= ~(1 << IIC_SCL | 1 << IIC_SDA);
   TWBR = 0x80;
   TWSR = 0x00;
}

uint8_t IIC::recsnd(_sec s, uint8_t data) {
   switch (s) {
      case TWI_Start: 
	 TWCR = 1<<TWSTA | 1<<TWEN | 1<<TWINT;
	 while(!(TWCR&(1<<TWINT)));
	 TWDR = data;
	 TWCR = 1<<TWEN | 1<<TWINT;
	 while(!(TWCR&(1<<TWINT)));
	 break;
      case TWI_ACK:
	 TWDR = data;
	 TWCR = 1<<TWEN | 1<<TWINT | 1<<TWEA;
	 while(!(TWCR&(1<<TWINT)));
	 break;
      case TWI_NACK:
	 TWDR = data;
	 TWCR = 1<<TWEN | 1<<TWINT;
	 while(!(TWCR&(1<<TWINT)));
	 break;
      case TWI_Stop:
	 TWDR = data;
	 TWCR = 1<<TWSTO | 1<<TWEN | 1<<TWINT;
	 break;
   }
   return TWDR;
}