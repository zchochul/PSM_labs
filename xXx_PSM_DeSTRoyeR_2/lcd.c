#include "lcd.h"



void lcd_write_instr(uint8_t data)
{
	LCD_PORT&=~(1<<LCD_RS);
	LCD_PORT|=(1<<LCD_E);
	
	LCD_PORT=(data&0xf0)|(LCD_PORT&0x0f);
	
	_delay_ms(5);
	
	LCD_PORT&=~(1<<LCD_E);
	
	_delay_ms(5);
	
	LCD_PORT|=(1<<LCD_E);
	
	LCD_PORT=(data<<4)|(LCD_PORT&0x0f);
	
	_delay_ms(5);
	
	LCD_PORT&=~(1<<LCD_E);
	
	_delay_ms(5);
}

void lcd_write_data(uint8_t data)
{
	LCD_PORT|=(1<<LCD_RS);
	LCD_PORT|=(1<<LCD_E);
	
	LCD_PORT=(data&0xf0)|(LCD_PORT&0x0f);
	
	_delay_ms(1);
	
	LCD_PORT&=~(1<<LCD_E);
	
	_delay_ms(1);
	
	LCD_PORT|=(1<<LCD_E);
	
	LCD_PORT=(data<<4)|(LCD_PORT&0x0f);
	
	_delay_ms(1);
	
	LCD_PORT&=~(1<<LCD_E);
	
}
void lcdinit(void)
{
	LCD_DDR=0xff;
	_delay_ms(45);
	
	lcd_write_instr(0x33);
	lcd_write_instr(0x32);
	
	lcd_write_instr(0x28);
	lcd_write_instr(0x08);
	lcd_write_instr(0x01);
	lcd_write_instr(0x06);
	lcd_write_instr(0x0f);
}

void lcd_clear(void)
{
	lcd_write_instr(1);
}

void lcd_set_xy(uint8_t x, uint8_t y)
{
	lcd_write_instr(0x80+x+y*0x40);
}

void lcd_write_text_xy(uint8_t x, uint8_t y, char *text)
{
	lcd_set_xy(x, y);
	while(*text)
	{
		lcd_write_data(*text);
		text++;
	}
}

int lcd_putc(char c, FILE* unused)
{
	lcd_write_data(c);
	return 0;
}

void on_off_cursor(uint8_t o)
{
	if(o==0)
	{	
		lcd_write_instr(0b00001100);
	}
	if(o==1)
	{	
		lcd_write_instr(0b00001111);
	}
}

