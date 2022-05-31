#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "i1wire.h"
#include "usart.h"

FILE u_stream = FDEV_SETUP_STREAM(u_putc, NULL, _FDEV_SETUP_WRITE);
FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putc, NULL, _FDEV_SETUP_WRITE);

uint8_t tab[10];
uint8_t i;
uint8_t etap = 0;
int x,y; 
float T1, T2;


ISR(USART_RXC_vect){
	tab[i] = UDR;
	if(tab[i]=='\n'){
		if(etap==0){
			T1 = atof((const char*)tab);
			fprintf(&u_stream, "Tmin = %.1f\n", T1);
			fprintf(&u_stream, "Podaj Tmax: ");
		}
		if(etap==1){
			T2 = atof((const char*)tab);
			fprintf(&u_stream, "Tmax = %.1f\n", T2);
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
	
	DDRD = 0xFF;
	PORTD = 0xFF; 
	
	lcdinit();
	blink(0);	
	
	USART_Init(1);
	
	OW_reset();
	uint16_t temp;
	float T;
	
	//Poczatkowe wartosci Tmin i Tmax
	T1=26.0;
	T2=28.0;
	
	sei();
	
	fprintf(&u_stream, "\tPodaj Tmin: ");
	while(1){
		DS18B20_start();
		_delay_ms(750);
		temp = DS18B20_read();
		lcd_clear();
		T = (float) temp * 0.0625;
		fprintf(&lcd_stream, "T = %.4f", T);
		
		lcd_set_xy(11,0);
		lcd_write_data(0b11011111);
		lcd_write_text_xy(12,0,"C");
		lcd_set_xy(0,1);
		fprintf(&lcd_stream, "T1=%.1f,T2=%.1f", T1, T2);
		
		if(T>T2) PORTD = 0xFF;
		if(T<T1) PORTD = 0x00;
	}
	return 1;
}
