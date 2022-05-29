#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h> 

uint16_t count;
uint8_t digits[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
uint8_t d;
ISR(TIMER1_COMPA_vect){
	count--;
	if(count == 0){
		PORTB = 0x00;
		//_delay_ms(1000);
		TCCR1B =0;
	}
		
}

ISR(TIMER0_COMP_vect){
	d++;
	if (d == 4){
		d = 0;
	}
	PORTC = ~(1<<d);
	
	if(d == 0){
		PORTD = digits[count%10];
	}
	if( d == 1){
		PORTD = digits[(count%100)/10];
	}
	if (d == 2){
		PORTD = digits[(count%1000)/100];
	}
	if ( d==3 ){
		PORTD = digits[(count%10000)/1000];
	}
}
int main(void){
	count = 1000;
	//wejscie wyjscie
	DDRC = 0xff;
	DDRD = 0xff;
	//brzeczyk
	DDRB = 0xff;
	PORTB=0xff;
	//wgm daje tryb a CS daje prescaler
	TCCR1B |= (1<<WGM12)|(1<<CS10);
	//bit porownawczy
	OCR1A = 16000; //skok o sekunde
	TIMSK |= (1<< OCIE1A); //Timer/Counter Interrupt Mask Register – TIMSK
				//OCIE1A , Output Compare A Match Interrupt Enable
	
	//drugi interrupt
	OCR0 = 39; //200 razy na sekunde
	TCCR0 |= (1<<WGM01)|(1<<CS02)|(1<<CS00); //CTC i prescaler 
							///WGM01 na 1 daje CTC
							//CS02 i CS00 na 1 daje clk / 1024
	TIMSK |=(1<<OCIE0);
	
	sei();
	
	while(1){
	
	}
}
