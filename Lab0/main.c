#include <avr/io.h> //wymagany plik (definicje)
#include <util/delay.h> 

int main(void){
	DDRC = 0xff; //konfiguracja rejestrów specjalnych
				//f to 4 jedynki 1 są wyjściowe, więc 8 WYJŚĆ
	//DDRC = 0b11111111; można nie zobaczyć, że brakuje jednej 1, dlatego wolimy szestnastkowe
	
	while(1){//pętla główna programu
		PORTC^= (1<<0); //ustawianie stanu na nóżce <- to trudne lepiej PORTC
		_delay_ms(1000);
	}
	return 0;
}
