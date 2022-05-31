#include "1wire.h"


uint8_t OW_reset(void)
{
	//zamiana funkcji ktora byla w pliku on wire protocol w materialach na stronie
	uint8_t result;
	_delay_us(0);
	OW_low;
	_delay_us(480);
	OW_high; 
	_delay_us(70);
	result = OW_check;
	_delay_us(410); 
	return result; 
}
void OWWriteBit(uint8_t bit)
{
	if(bit)
	{
		// Write '1' bit
		OW_low; 
		_delay_us(6);
		OW_high; 
		_delay_us(64); 
	}
	else
	{
		// Write '0' bit
		OW_low;
		_delay_us(60);
		OW_high; 
		_delay_us(10);
	}
}
uint8_t OWReadBit(void)
{
	uint8_t result;
	OW_low; 
	_delay_us(6);
	OW_high;
	_delay_us(9);
	result = OW_check; 
	_delay_us(55);
	return result;
}

void OW_send(uint8_t data)
{
	int loop;
	for (loop = 0; loop < 8; loop++)
	{
		OWWriteBit(data & 0x01);
		data >>= 1;
	}
}

uint8_t OW_recv(void)
{
	int loop, result=0;
	for (loop = 0; loop < 8; loop++)
	{
		result >>= 1;
		if(OWReadBit())
			result |= 0x80;
	}
	return result;
}

uint8_t DS18B20_start(void)
{
	//przedstawienie się
	OW_reset();
	OW_send(0xcc);
	OW_send(0x44);
	return 0;
	
}
uint16_t DS18B20_read(void)
{
	uint8_t a, b;
	uint16_t c;
	OW_reset();
	OW_send(0xcc);
	OW_send(0xbe);
	a=OW_recv();
	b=OW_recv();
	c=(b<<8)|a;
	return c;
}

