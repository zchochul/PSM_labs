#ifndef _lcd_h
#define _lcd_h

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LCD_PORT PORTA
#define LCD_DDR DDRA
#define LCD_E 3
#define LCD_RS 2

void lcdinit(void); //inicjalizacja wyswietlacza
void lcd_write_instr(uint8_t data); //funkcja wysyłająca pojedynczą instrukcję do wyświetlacza↪→
void lcd_clear(void); //funkcja realizująca instrukcję "czyść wyświetlacz"
void lcd_write_data(uint8_t data); //funkcja wysyłająca pojedynczą daną do wyświetlacza↪→
void lcd_set_xy(uint8_t x, uint8_t y); //funkcja ustawiająca kursor na pozycji xy↪→
void lcd_write_text_xy(uint8_t x, uint8_t y, char *text); 
int lcd_putc(char c, FILE *unused);
void blink(int on);

#endif
