#include <util/delay.h>
#include <avr/io.h> 
#include "usart.h"
#include <avr/interrupt.h>

FILE u_stream = FDEV_SETUP_STREAM(u_putc, NULL, _FDEV_SETUP_WRITE);
uint8_t x, y;
uint8_t bufor[10];
uint8_t i;
uint8_t etap;

ISR(USART_RXC_vect){
	bufor[i]=UDR;
	if(bufor[i] == '\n' || bufor[i] == '\r'){
		x = atoi( (const char*) bufor);
		OCR1A = 2000/90*x + 2000;
		i=0;
	}
	else
		i++;
	
}

int main(void){
	//USART
	USART_Init(1); //500 000 baud
	sei();
	fprintf(&u_stream,"Witaj podaj pierwsza liczbe! \n");
	
	//okres 20ms (1 przez 1-2 ms)
	
	//do ICR1 wpisujemy 39 999
	ICR1 = 39999;
	DDRD = 0xff;
	
	//COM1A1 (1)  COM1A0 (0) zerujemy stan jak jest 0, jedynkujemy jak OCR1
	TCCR1A |= (1<<COM1A1) | (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS11); //WGM jest od trybu, chcielismy jakis 14
	
	OCR1A = 3000; //wartosc centralna
	_delay_ms(2000);
	
	while(1){
	}
	return 0;
}
