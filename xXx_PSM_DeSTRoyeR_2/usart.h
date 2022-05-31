#ifndef _usart_h
#define _usart_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void USART_Init( unsigned int baud );

void USART_Transmit( unsigned char data );

unsigned char USART_Receive( void );

int u_putc(char c, FILE* unused);
#endif
