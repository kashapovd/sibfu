#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

HD44780::HD44780() {
   framebuffer = (uint8_t*) malloc(LCD_BYTES_CAPACITY);
}

void HD44780::write4(const uint8_t state, const uint8_t byte) {
  LCD_DDR |= 1<<LCD_D4 | 1<<LCD_D5 | 1<<LCD_D6 | 1<<LCD_D7 | 1<<LCD_RS | 1<<LCD_E;
  if (state == LCD_DATA) {
	LCD_PORT |= 1<<LCD_RS;
  } else {
    LCD_PORT &= ~(1<<LCD_RS);
  }
  LCD_PORT |= 1<<LCD_E;
  LCD_PORT &= 0xf0;
  LCD_PORT |= byte & 0x0f;
  _delay_us(15);
  LCD_PORT &= ~(1<<LCD_E);
}

void HD44780::write8(const uint8_t state, const uint8_t byte) {
  _delay_ms(LCD_SEND_DELAY);
  write4(state, byte>>4);          
  write4(state, byte); 
}

void HD44780::write8_cmd(const uint8_t byte) {
   write8(LCD_CMD, byte);
}

void HD44780::write8_data(const uint8_t byte) {
  write8(LCD_DATA, byte);
}

void HD44780::init(void) {
  write8_cmd(0b00000010);
  write8_cmd(0b00101000);
  write8_cmd(0b00000001);
  write8_cmd(0b00000110);
  write8_cmd(0b00001100);
}

void HD44780::clear(void) {
  write8_cmd(0b00000001);
}

void HD44780::setCursor(uint8_t column, uint8_t row) {
  write8_cmd((0b10000000 | ((0x40 * row) + column)));
}

void HD44780::put(char c) {
    write8_data(c);
}

void HD44780::put(uint8_t c) {
    write8_data(c);
}

void HD44780::put(char *str) {
   while(*str)
      write8_data(*str++);
}

void HD44780::loadChar(uint8_t code, uint8_t *pattern) {
  write8_cmd((code<<3) | 0b01000000);
  for (char i = 0; i < 8; i++){
    write8_data(*pattern++);
  }
  write8_cmd(0b10000000);
}

void HD44780::drawPixel(uint8_t x, uint8_t y, 
                     uint8_t color) {

    if ((x >= 0 && x < LCD_WIDTH_PIX) 
    && (y >= 0 && y < LCD_HEIGHT_PIX)) {

        color ?
        framebuffer[x + (y/8) * LCD_HEIGHT_PIX] |= (1 << y%8)
        :
        framebuffer[x + (y/8) * LCD_WIDTH_PIX] &= ~(1 << y%8);
    }
}

void HD44780::display() {
   clear();
   uint8_t* next = _loadHalfRow(framebuffer, LCD_WIDTH_PIX/2);
   setCursor(0,0);
   for (uint8_t i = 0; i < 8; i++){
      put(i);
   }
   next =_loadHalfRow(next, LCD_WIDTH_PIX/2);
   setCursor(8,0);
   for (uint8_t i = 0; i < 8; i++){
      put(i);
   }
   next =_loadHalfRow(next, LCD_WIDTH_PIX/2);
   setCursor(0,1);
   for (uint8_t i = 0; i < 8; i++){
      put(i);
   }
   _loadHalfRow(next, LCD_WIDTH_PIX/2);
   setCursor(8,1);
   for (uint8_t i = 0; i < 8; i++){
      put(i);
   }
}

uint8_t* HD44780::_loadHalfRow(uint8_t *buff, uint8_t size) {   
   for (uint8_t i = 0; i < size/5; i++){
      loadChar(i, buff);
      buff += 5;
   }
   return buff;
}
