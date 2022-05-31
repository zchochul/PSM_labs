#include "lcd.h"
#include "usart.h"
#include "1wire.h"

FILE lcd_stream= FDEV_SETUP_STREAM(lcd_putc, NULL, _FDEV_SETUP_WRITE);
FILE u_stream= FDEV_SETUP_STREAM(u_putc, NULL, _FDEV_SETUP_WRITE);

uint16_t temp;
uint8_t  x;
uint8_t  y;
uint8_t tab[10];
uint8_t i;
uint8_t etap;
double xx, yy;

ISR(USART_RXC_vect)
{
	tab[i]=UDR;
	if(tab[i]=='\n')
	{
		if(etap==0)
		{
			x=atoi((const char*) tab);
		}
		if(etap==1)
		{
			y=atoi((const char*) tab);
		}
		
		i=0;
		etap++;
		if(etap==2)
		{
			etap=0;
		}
	}
	else
	{
		i++;
	}
	
}

int main(void)
{
	DDRC=0xff;
	PORTC=0xff;
	USART_Init(1);
	lcdinit();
	on_off_cursor(0);
	
	sei();
	while(1)
	{
		DS18B20_start();
		_delay_ms(750);
		temp=DS18B20_read();
		lcd_set_xy(0,0);
		fprintf(&lcd_stream, "%d.%04d", temp>>4, (temp&0x0f)*625);
		lcd_write_data(0b11011111);
		lcd_write_data('C');
		
		
		lcd_set_xy(1,1);
		xx=(double)((temp&0x0f)*625)/10000;
		yy=(double)(temp>>4);
		
		if(x>(xx+yy))
		{
			PORTC&=~(1<<PC0);
				
		}
		if((xx+yy)>y)
		{
				PORTC=0xff;
		}
		
		lcd_set_xy(1,1);
		fprintf(&lcd_stream, " %d", x);
		lcd_write_data(0b11011111);
		lcd_write_data('C');

		fprintf(&lcd_stream, " %d.", y);
		lcd_write_data(0b11011111);
		lcd_write_data('C');
		
	}
	return 0;
}
