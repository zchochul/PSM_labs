#include <util/delay.h>
#include <avr/io.h> 
#include "usart.h"
#include <avr/interrupt.h>

FILE u_stream = FDEV_SETUP_STREAM(u_putc, NULL, _FDEV_SETUP_WRITE);
uint8_t x, y;
uint8_t bufor[10];
uint8_t i;


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
	//sei(); odcinamy komunikacje z uzytkownikiem
	fprintf(&u_stream,"Witaj podaj pierwsza liczbe! \n");
	
	//okres 20ms (1 przez 1-2 ms)
	
	//do ICR1 wpisujemy 39 999
	ICR1 = 39999;
	DDRD = 0xff; //PD5 OC1A
	DDRB = 0xff; //PB3 OC

	
	//COM1A1 (1)  COM1A0 (0) zerujemy stan jak jest 0, jedynkujemy jak OCR1
	//TCCR1 jest bardziej zaawansowane
	TCCR1A |= (1<<COM1A1) | (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS11); //WGM jest od trybu, chcielismy jakis 14
	
	//TCCR0 jest uproszczona wersja
	TCCR0 |= (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<CS00); //fast PWM a com to tryb porownywania cs00 od prescalera
	
	OCR0 = 0;
	
	OCR1A = 3000; //wartosc centralna
	_delay_ms(2000);
	
	//wersja Krzysia
	TCCR2 |= (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<COM20) | (1<<CS20); //fast PWM a com to tryb porownywania cs00 od prescalera
	OCR2 = 255;
	
	while(1){
		for(int i = 0; i<255; i++){
			OCR0 = i;
			OCR2 = 255-i;
			_delay_ms(4);
		}
		for(int i = 255; i>0; i--){
			OCR0 = i;
			OCR2 = 255-i;
			_delay_ms(4);
		}
		
	}
	return 0;
}
