#include <avr/io.h> 
#include "lcd.h"
#include "i1wire.h"
#include "usart.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h> //zeby byl progmem
FILE lcd_stream = FDEV_SETUP_STREAM(lcd_puts, NULL, _FDEV_SETUP_WRITE);
FILE u_stream = FDEV_SETUP_STREAM(u_putc, NULL, _FDEV_SETUP_WRITE);
const char tekst[] PROGMEM = "Ala ma kota"; //progmem kluczowy zeby byl we flashu

uint8_t Tmin, Tmax;
uint8_t bufor[10];
uint8_t i;
uint8_t star;
uint16_t mlod;
uint8_t etap;

ISR(USART_RXC_vect){
	bufor[i] = UDR;
	if(bufor[i]=='\n'){
		if(etap==0){
			Tmin = atoi((const char*)bufor);
			fprintf(&u_stream, "Tmin = %d\n", Tmin);
			fprintf(&u_stream, "Podaj Tmax: ");
		}
		if(etap==1){
			Tmax = atoi((const char*)bufor);
			fprintf(&u_stream, "Tmax = %d\n", Tmax);
			fprintf(&u_stream, "Podaj Tmin: ");
		}
		if(etap==1) {
			etap=0;
		}
		else etap++;
		i=0;
	} else {
		i++;
	}
}

int main(void){
	//grzejnik
	DDRD = 0xFF;
	PORTD = 0xFF;
	//Filozofia trochę inna niż zazwyczaj, bo zmieniamy kierunek DDR
	lcdinit();
	blinking(0);
	
	//USART //czesc dodatkowa
	USART_Init(1); //500 000 baud
	 
	 Tmin = 22;
	 Tmax = 23;
	
	sei();
	fprintf(&u_stream,"Wpisz Tmin \n");
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
		
		star = temperatura >> 4;
		mlod = (temperatura & (0x0f))*625;
		
		//to co na wyswietlaczu
		lcd_set_xy(0,0);
		fprintf(&lcd_stream, "T = %d.%04d %c C", star, mlod, 0b11011111);
		lcd_set_xy(0,1);
		fprintf(&lcd_stream, "min =%d,max=%d", Tmin, Tmax);
		
		//a co z grzejnikiem
		if( (double) star + (double) mlod/10000> Tmax) PORTD = 0xFF;
		if( (double) star + (double) mlod/10000<  Tmin) PORTD = 0x00;
		
	}
	return 0;
}
