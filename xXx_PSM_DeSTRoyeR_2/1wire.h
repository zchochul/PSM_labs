#ifndef _1wire_h
#define _1wire_h
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define OW_PIN PB3
#define OW_DIR DDRB
#define OW_OUT PORTB
#define OW_IN PINB

#define OW_low OW_DIR |= 1 << OW_PIN	//zmienia na wyjsciowa
#define OW_high OW_DIR &= ~( 1 << OW_PIN ) //zmienia na wejsciowa
#define OW_check ( OW_IN & ( 1 << OW_PIN ) )	//stan nozki 

void OWWriteBit(uint8_t bit);
uint8_t OWReadBit(void);
uint8_t OW_reset(void);
void OW_send(uint8_t byte);
uint8_t OW_recv(void);
//obsluga termometru
uint8_t DS18B20_start(void);
uint16_t DS18B20_read(void);


#endif
