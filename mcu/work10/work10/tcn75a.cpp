#include "tcn75a.h"
#include "i2c.h"
#include <avr/io.h>
#include <stdlib.h>
#include <math.h>

TCN75A::TCN75A(IIC i2c) {
   _i2c = i2c;
}

void TCN75A::init() {
   // load tcn75a config
   _i2c.recsnd(IIC::TWI_Start, TCN75A_ADDRESS);
   _i2c.recsnd(IIC::TWI_NACK, 1);
   _i2c.recsnd(IIC::TWI_ACK, TCN75A_CONFIG);
   _i2c.recsnd(IIC::TWI_Stop, 0);
}

temperature TCN75A::floatToTemp(float d) {
   temperature temp;
   float whole, fraction;
   if (signbit(d)) {
      fraction = modff(fabs(d), &whole);
      temp.main = (int8_t)whole*-1;
   } else {
      fraction = modff(d, &whole);
      temp.main = (int8_t)whole;
   }
   temp.fraction = round(fraction*pow(10,2));
   return temp;
}

void TCN75A::setLimitTemp(temperature t, tempType type) {
   uint8_t tempReg;
   switch (type) {
      case Hyst:
	 tempReg = 0x02;
	 break;
      default:
	 tempReg = 0x03;	
   }
   
   uint8_t fraction_code;
   
   switch (t.fraction / 25) {
      case 3:
	 fraction_code = 0b11000000;
	 break;
      case 2: 
	 fraction_code = 0b10000000;
	 break;
      case 1: 
	 fraction_code = 0b01000000;
	 break;
      default:
	 fraction_code = 0;
   }
   
   _i2c.recsnd(IIC::TWI_Start, TCN75A_ADDRESS);
   _i2c.recsnd(IIC::TWI_NACK, tempReg);
   _i2c.recsnd(IIC::TWI_ACK, t.main);
   
   _i2c.recsnd(IIC::TWI_ACK, fraction_code);
   _i2c.recsnd(IIC::TWI_Stop, 0);
}

temperature TCN75A::getTemp(tempType type) {
   uint8_t tempReg;
   switch (type) {
      case Limit:
	 tempReg = 0x03;
	 break;
      case Hyst:
	 tempReg = 0x02;
	 break;
      default:
	 tempReg = 0;	
   }
	
   temperature temp;
   temp.main = 0;
   temp.fraction = 0;
	
   _i2c.recsnd(IIC::TWI_Start, TCN75A_ADDRESS);
   _i2c.recsnd(IIC::TWI_NACK, tempReg);
   _i2c.recsnd(IIC::TWI_Start, TCN75A_ADDRESS | 1);
   temp.main = (int8_t)_i2c.recsnd(IIC::TWI_ACK, 0);

   uint8_t fraction_code = _i2c.recsnd(IIC::TWI_NACK, TCN75A_ADDRESS);
   if (fraction_code & 0x80) {
	   temp.fraction =+ 50;
   }
   if (fraction_code & 0x40) {
	   temp.fraction =+ 25;
   }
   _i2c.recsnd(IIC::TWI_Stop, 0);
   return temp;
}