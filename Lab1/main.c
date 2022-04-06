
#include <avr/io.h> 
#include "longdelay.h"
int main(void){
	DDRC = 0xff; // wszystkie na wyjscie
	//PORTC = ~(0b11001110);
	DDRD = 0x00; //mocno opcjonalne, bo wszystkie z miejsca sa wejsciowe
	PORTD = 0xff;
	PORTC = 0b0001;
	int x=0;
		while(1){
		/*	if(!(PIND&(1<<0)))	
				PORTC = 0x00;
			else
				PORTC = 0xff;
		*/
	/*	PORTC = 0x00;
		longdelay(1);
		PORTC = 0xff;
		longdelay(1);
	*/
	/*	PORTC = 0b0001;
		_delay_ms(5);
		PORTC = 0b0010;
		_delay_ms(5);
		PORTC = 0b0100;
		_delay_ms(5);
		PORTC = 0b1000;
		_delay_ms(5);
	*/
	if(!(PIND&(1<<0))){
		x^= 0xff;
		_delay_ms(200);
	}
		
	
	if(x==0){
		PORTC = (PORTC <<1) | (PORTC>>3);
		_delay_ms(5);
	}
	
	}
	return 1;
}
