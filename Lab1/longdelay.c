#include "longdelay.h"
#include <avr/io.h> 

void longdelay(uint16_t x){
		for(int i = 0; i < x; i++){
			_delay_ms(1000);
		}
}
