#include "spi.h"

void SPI_MasterInit(void){
	//ustawienie kierunku wyjś ciowego dla linii MOSI, SCK i SS
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);
	//aktywacja SPI, tryb Master, prę dkoś ć zegara Fosc/64
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}
uint8_t SPI_MasterTransmit(uint8_t bajt){
	SPDR = bajt;
	//czekamy na ustawienie flagi SPIF po zakończeniu transmisji
	while( !(SPSR&(1<<SPIF)) );
	return SPDR;
}
