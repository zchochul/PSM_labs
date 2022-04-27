#include <avr/io.h> 
#include <util/delay.h>
#include "lcd.h"
#include "spi.h"

FILE lcd_stream = FDEV_SETUP_STREAM(lcd_puts, NULL, _FDEV_SETUP_WRITE);
uint8_t bajt1, bajt2;
uint16_t bajcisko;
double wynikos;
double srednia_tablica[20];
uint8_t ilosc_srednich=0;
double srednia=0;
int main(void){
	lcdinit();
	blinking(0);
	SPI_MasterInit(); //SPI init
	SS_DISABLE(); //slave select to 1

	while(1)
	{
		SS_ENABLE() //slave select to 0 to start communication
		SPI_MasterTransmit(1); //start bit
		bajt1 = SPI_MasterTransmit(0b10100000);
		bajt2 = SPI_MasterTransmit(0);
		SS_DISABLE(); //slave select to 1
		bajcisko = ((bajt1 & 0x0F) << 8)|bajt2;
		wynikos = 5. * bajcisko / 4096;
		lcd_set_xy(0,0);
		fprintf(&lcd_stream,"U = %.2f V", wynikos);
		lcd_set_xy(0,1);
		
		srednia_tablica[ilosc_srednich] = wynikos;
		ilosc_srednich++;
		
		for (int i=0; i<20; i++){
			srednia += srednia_tablica[i];
		}
		srednia = srednia/20;
		_delay_ms(100);
		fprintf(&lcd_stream,"Usr = %.2f V", srednia);
		srednia = 0;
		if (ilosc_srednich == 20)
			ilosc_srednich = 0;
		
		
	}
	return 0;
}
