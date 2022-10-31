#ifndef LCD_H_
#define LCD_H_

#define LCD_HEIGHT_PIX 		16
#define LCD_WIDTH_PIX 		80
#define LCD_BYTES_CAPACITY  	(LCD_HEIGHT_PIX * LCD_WIDTH_PIX) / 8
#define LCD_PORT		PORTA
#define LCD_DDR 		DDRA
#define LCD_RS	 		4
#define LCD_E	 		5
#define LCD_D4	 		0
#define LCD_D5	 		1
#define LCD_D6	 		2
#define LCD_D7	 		3
#define LCD_SEND_DELAY 		1

#define LCD_CMD                      0x00
#define LCD_DATA                     0xFF

#define LCD_CTRL_SETTINGS 	0b00100000
   #define DL 			0b00010000
   #define N 			0b00001000
   #define F 			0b00000100
#define LCD_CLR 		0b00000001
#define LCD_CURSOR_SETTINGS 	0b00000100
   #define INC 			0b00000010
#define LCD_DISP_SETTINGS	0b00001000
   #define D			0b00000100
#define LCD_DDRAM_ADDR		0b10000000

class HD44780 {
   
   uint8_t column, row;
   uint8_t *framebuffer;
   void write(const uint8_t type, const uint8_t *data, uint8_t n);
   void write8(const uint8_t type, const uint8_t data);
   void write4(const uint8_t type, const uint8_t data);
   void write8_cmd(const uint8_t data);
   void write8_data(const uint8_t data);
   void _setCursor();
   uint8_t* _loadHalfRow(uint8_t *buff, uint8_t size);
   
public:
   HD44780();
   void init(void);
   void clear(void);
   void setCursor(uint8_t column, uint8_t row);
   void setCursorRow(uint8_t row);
   void setCursorColumn(uint8_t column);
   void put(char c);
   void put(uint8_t c);
   void put(char *c);
   void loadChar(uint8_t code, uint8_t *pattern);
   void drawPixel(uint8_t x, uint8_t y, uint8_t color);
   void display();
};

#endif