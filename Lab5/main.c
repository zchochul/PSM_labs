#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h> 
#include <string.h>
#include <stdlib.h>
#include "usart.h"



FILE u_stream = FDEV_SETUP_STREAM(u_putc, NULL, _FDEV_SETUP_WRITE);
uint8_t x, y;
uint8_t bufor[10];
uint8_t i;
uint8_t etap;

ISR(USART_RXC_vect){
	bufor[i]=UDR;
	if(bufor[i] == '\n' || bufor[i] == '\r'){
	/*
		if(!strncmp( (const char *) bufor, "off", 3 ))
			PORTC = 0xff;
		if(!strncmp( (const char *) bufor, "on", 2 ))
			PORTC = 0x00;
		i=0;
	*/
	
	if (etap == 0){
		
		x = atoi( (const char*) bufor);
	}
	if (etap == 1){
		y = atoi( (const char*) bufor);
	}
	if (etap == 2){
		if (bufor[0] == '+'){
			fprintf(&u_stream,"%d + %d = %d \n", x, y, x+y);
		}
		if (bufor[0] == '-'){
			fprintf(&u_stream,"%d - %d = %d \n", x, y, x-y);
		}
		if (bufor[0] == '*'){
			fprintf(&u_stream,"%d * %d = %d \n", x, y, x*y);
		}
		if (bufor[0] == '/'){
			if(y == 0)
				fprintf(&u_stream,"Nie dziel cholero przez zero! \n");
			else
				fprintf(&u_stream,"%d / %d = %d \n", x, y, x/y);
		}
	}
		i=0;
		etap++;
		if(etap == 3)
			etap = 0;
	}
	else
		i++;
	
}


int main(void){
	USART_Init(1); //500 000 baud
	DDRC = 0xff;
	PORTC = 0xff;
	sei();
	fprintf(&u_stream,"Witaj podaj pierwsza liczbe! \n");
	while(1){
		/*x = USART_Receive();
		
		if(x != 'a')
			USART_Transmit(x+1);
		else 
			fprintf(&u_stream, "Kurde to na %d prawda", 100);*/
		
	}
}
