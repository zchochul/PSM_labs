#include <avr/io.h> 
#include "lcd.h"
#include <avr/pgmspace.h> //zeby byl progmem
FILE lcd_stream = FDEV_SETUP_STREAM(lcd_puts, NULL, _FDEV_SETUP_WRITE);
const char tekst[] PROGMEM = "Ala ma kota"; //progmem kluczowy zeby byl we flashu

int main(void){
	lcdinit();
	lcd_write_data('S');
	lcd_write_data('i');
	lcd_write_data('e');
	lcd_write_data('m');
	lcd_write_data('a');
	lcd_write_data(' ');
	lcd_write_data('c');
	lcd_write_data('o');
	lcd_write_data(' ');
	lcd_write_data('t');
	lcd_write_data('a');
	lcd_write_data('m');
	lcd_write_data('?');
	_delay_ms(1000);
	
	//lcd_set_xy(3,1);
	lcd_write_text_xy(2,1, "Dobrze co tam"); 
	_delay_ms(1000);
	lcd_clear();
	//fprintf(&lcd_stream, "Ala ma %d kota", 1);
	
	/*
	for(uint8_t i = 0; i<strlen_P(tekst); i++)
	{
		char znak = pgm_read_byte(&tekst[i]);
		lcd_write_data(znak);
	}
	*/
	//robimy wlasny znak
	lcd_write_instr(0x40);
	/*lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b11111);
	lcd_write_data(0b00100);
	lcd_write_data(0b01010);
	lcd_write_data(0b10001);
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	*/
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_write_data(0b11111);
	lcd_write_data(0b01010);
	lcd_write_data(0b01010);
	lcd_write_data(0b01010);
	lcd_write_data(0b00000);
	lcd_write_data(0b00000);
	lcd_set_xy(1,1);
	lcd_write_data(0);
	blinking(0);
	lcd_clear();
	lcd_set_xy(16,0);
	fprintf(&lcd_stream, "Technicznie");
	lcd_set_xy(16,1);
	fprintf(&lcd_stream, "najlepsi");
	while(1)
	{
		lcd_write_instr(0b11000);
		_delay_ms(1000);
	}
	return 0;
}
