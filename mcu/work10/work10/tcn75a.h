#ifndef TCN75A_H_
#define TCN75A_H_

#define TCN75A_PORT		PORTC
#define TCN75A_DDR 		DDRC
#define TCN75A_A0	 	3
#define TCN75A_A1	 	4
#define TCN75A_A2	 	5
#define A0	 		1
#define A1	 		0
#define A2	 		0
#define TCN75A_ADDRESS	(0x90 | (A0<<1) | (A1<<2) | (A2<<3))
#define TCN75A_CONFIG	0b00100000
#define TCN75A_HYST_MAIN	0b00100000
#define TCN75A_HYST_FRACT	0b00100000
#define TCN75A_LIMIT_MAIN	0b00100000
#define TCN75A_LIMIT_FRACT	0b00100000

#include "i2c.h"

struct temperature
{
	int8_t main;
	uint8_t fraction;
};

class TCN75A {
	IIC _i2c;
public:
	TCN75A(IIC i2c);
	void init();
	
	enum tempType {
		Current = 0,
		Hyst,
		Limit
	};
	temperature getTemp(tempType type=Current);

};

#endif