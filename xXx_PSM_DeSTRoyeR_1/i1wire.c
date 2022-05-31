#include "i1wire.h"

uint8_t OW_reset(void){
	
	uint8_t result;
	
	OW_low;
	_delay_us(480);
	
	OW_high;
	_delay_us(70);
	
	result = OW_check; 
	_delay_us(410); 
	
	return result; 
}



void OWWriteBit(uint8_t bit){
	if (bit)
	{
		// Write '1' bit
		OW_low;
		_delay_us(6);
		OW_high;
		_delay_us(64); // Complete the time slot and 10us recovery
	}
	else
	{
		// Write '0' bit
		OW_low; // Drives DQ low
		_delay_us(60);
		OW_high; // Releases the bus
		_delay_us(10);
	}
}

uint8_t OWReadBit(void){
	uint8_t result;
	OW_low; // Drives DQ low
	_delay_us(6);
	OW_high; // Releases the bus
	_delay_us(9);
	result = OW_check; // Sample the bit value from the slave
	_delay_us(55);// Complete the time slot and 10us recovery
	return result;
}


void OW_send(uint8_t data){
	uint8_t tmp;
	for(int i=0; i<8; i++){
		tmp = data & 0x01;
		OWWriteBit(tmp);
		data >>= 1;
	}
}

uint8_t OW_recv(void){
	uint8_t data = 0;
	for(int i=0; i<8; i++){
		data >>= 1;
		if(OWReadBit()) data |= 0x80;
	}
	return data;
}

uint8_t DS18B20_start(void){
	OW_reset();
	OW_send(0xCC);
	OW_send(0x44);
	return 0;
}

uint16_t DS18B20_read(void){
	OW_reset();
	OW_send(0xCC);
	OW_send(0xBE);
	uint8_t a,b;
	uint16_t temp;
	b = OW_recv(); //mlodszy bajt
	a = OW_recv(); //starszy bajt
	
	temp = ( a<<8 ) + b;
	return temp;
}
