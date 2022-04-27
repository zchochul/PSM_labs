#ifndef _spi_h_
#define _spi_h_
#include <avr/io.h>
#define MOSI PB5
#define SCK PB7
#define SS PB4

#define SS_ENABLE() {PORTB&=~(1<<SS);}
#define SS_DISABLE() {PORTB|=(1<<SS);}

void SPI_MasterInit(void);
uint8_t SPI_MasterTransmit(uint8_t bajt);

#endif
