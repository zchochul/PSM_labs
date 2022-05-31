#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>




void USART_Init( unsigned int baud );

void USART_Transmit( unsigned char data );

unsigned char USART_Receive( void );

int u_putc(char c, FILE *unused);
