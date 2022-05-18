#include <avr/io.h> 
#include "lcd.h"
#include "i1wire.h"
#include <avr/pgmspace.h> //zeby byl progmem
FILE lcd_stream = FDEV_SETUP_STREAM(lcd_puts, NULL, _FDEV_SETUP_WRITE);
const char tekst[] PROGMEM = "Ala ma kota"; //progmem kluczowy zeby byl we flashu

int main(void){
	//Filozofia trochę inna niż zazwyczaj, bo zmieniamy kierunek DDR
	lcdinit();
	blinking(0);
	
	while(1)
	{
		OW_reset();
		//skip rom to jest hej wy termometry
		OW_send(0xCC); //SKIP ROM
		OW_send(0x44); //CONVERT T mierzcie temperature
		_delay_ms(750);
		
		OW_reset();
		OW_send(0xCC);//hej wy
		OW_send(0xBE); //dajta temperature
		uint8_t mlodsze = OW_recv();
		uint8_t starsze = OW_recv();
		uint16_t temperatura = (starsze<<8)|(mlodsze);
		
		uint8_t star = temperatura >> 4;
		uint16_t mlod = (temperatura & (0x0f))*625;
		
		lcd_set_xy(0,0);
		fprintf(&lcd_stream, "T = %d.%04d %c C", star, mlod, 0b11011111);
	}
	return 0;
}
