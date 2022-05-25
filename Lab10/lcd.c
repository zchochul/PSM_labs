#include "lcd.h"

void lcd_write_instr(uint8_t data) //funkcja wysyłająca pojedynczą instrukcję do wyświetlacza↪→
{
	LCD_PORT &= ~(1<<LCD_RS); // zrobilismy zapis 
	
	//wysylamy starsza
	LCD_PORT |= (1<<LCD_E); //ustawiamy 1 na E
	LCD_PORT = (data & 0xF0) | (LCD_PORT & 0x0F);
	_delay_ms(1);
	LCD_PORT &= ~(1<<LCD_E);
	_delay_ms(1);
	
	//wysylamy mlodsza
	LCD_PORT |= (1<<LCD_E); //ustawiamy 1 na E
	LCD_PORT = (data << 4) | (LCD_PORT & 0x0F);
	_delay_ms(1);
	LCD_PORT &= ~(1<<LCD_E);
	_delay_ms(1);
	
	
}


void lcd_write_data(uint8_t data) //funkcja wysyłająca pojedynczą daną do wyświetlacza↪→
{
	LCD_PORT |= (1<<LCD_RS); // ustawiamy 1 
	
	LCD_PORT |= (1<<LCD_E); //ustawiamy 1 na E
	LCD_PORT = (data & 0xF0) | (LCD_PORT & 0x0F);
	_delay_ms(1);
	LCD_PORT &= ~(1<<LCD_E);
	_delay_ms(1);
	
	LCD_PORT |= (1<<LCD_E); //ustawiamy 1 na E
	LCD_PORT = (data << 4) | (LCD_PORT & 0x0F);
	_delay_ms(1);
	LCD_PORT &= ~(1<<LCD_E);
	_delay_ms(1);
}

void lcdinit(void) //inicjalizacja wyswietlacza
{	
	LCD_DDR = 0xff; //ca;y port wyjsciowy
	_delay_ms(45);
	lcd_write_instr(0x33);
	lcd_write_instr(0x32);
	
	lcd_write_instr(0x28); //konfiguruje wyswietlacz
	lcd_write_instr(0x08);
	lcd_write_instr(0x01); //czysci
	lcd_write_instr(0x06);
	lcd_write_instr(0x0f);
	
}

void lcd_clear(void)
{
	lcd_write_instr(0x01);
}

void lcd_set_xy(uint8_t x, uint8_t y)
{
	lcd_write_instr(0x80 + x + y * 0x40);
}

void lcd_write_text_xy(uint8_t x, uint8_t y, char *text)
{
	lcd_set_xy(x,y);
	while(*text){
		lcd_write_data(*text);
		text++;
	}
}

int lcd_puts(char c, FILE *unused)
{
	lcd_write_data(c);
	return 0;
}

void blinking(uint8_t t){
	if(t == 0 )
		lcd_write_instr(0b1100);
	if(t == 1)
		lcd_write_instr(0b1111);
}
