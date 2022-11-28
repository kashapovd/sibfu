#include "tcn75a.h"
#include "i2c.h"
#include <avr/io.h>

TCN75A::TCN75A(IIC i2c) {
   _i2c = i2c;
}

void TCN75A::init() {
	_i2c.recsnd(IIC::TWI_Start, TCN75A_ADDRESS);
	_i2c.recsnd(IIC::TWI_NACK, 1);
	_i2c.recsnd(IIC::TWI_ACK, TCN75A_CONFIG);
	_i2c.recsnd(IIC::TWI_Stop, 0);
	
}

temperature TCN75A::getTemp(tempType type) {
	uint8_t tempReg;
	switch (type)
	{
		case Limit:
			tempReg = 0x03;
			break;
		case Hyst:
			tempReg = 0x02;
			break;
		default:
			tempReg = 0;	
	}
	
	temperature temp {.main=0, .fraction=0};
	
   _i2c.recsnd(IIC::TWI_Start, TCN75A_ADDRESS);
   _i2c.recsnd(IIC::TWI_NACK, 0);
   _i2c.recsnd(IIC::TWI_Start, TCN75A_ADDRESS | 1);
   uint8_t tmp = (uint8_t)_i2c.recsnd(IIC::TWI_ACK, tempReg);
   temp.main = tmp & 0b01111111;
   if (tmp & 0x80) {
	   temp.main * -1;
   }
   tmp = _i2c.recsnd(IIC::TWI_NACK, TCN75A_ADDRESS);
   if (tmp & 0x80) {
	   temp.fraction =+ 50;
   }
   if (tmp & 0x40) {
	   temp.fraction =+ 25;
   }
   _i2c.recsnd(IIC::TWI_Stop, 0);
   return temp;
}
