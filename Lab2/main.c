
#include <avr/io.h> 
#include <avr/interrupt.h> 
#include <util/delay.h> 

uint8_t count;

ISR(INT0_vect ){
		count++;
		_delay_ms(200);
	}

int main (void){
	DDRC = 0xFF; //wszystkie nozki wyjsciowe
	
	//rezystor podciagajacy
	PORTD = 0b100;
	
	//MCUCR |= (1 << ISC01); //ustawiamy bit, zeby narastajace
	
	GICR |= (1<<INT0);
	
	sei(); //wlaczamy glowny zawor xD
	
	while(1){
		PORTC = ~count;
	}
	return 0;
} 
