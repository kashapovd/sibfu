#ifndef IIC_H_
#define IIC_H_

#define IIC_PORT	PORTC
#define IIC_DDR 	DDRC
#define IIC_SCL	 	0
#define IIC_SDA	 	1

#include <inttypes.h>

class IIC {

public:
   IIC();
   enum _sec {
      TWI_Start=0,
      TWI_ACK,
      TWI_NACK,
      TWI_Stop
   };

   void init();
   uint8_t recsnd(_sec s, uint8_t data);
   

};

#endif