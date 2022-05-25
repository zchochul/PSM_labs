#include <avr/io.h> 
#include "lcd.h"
#include "i1wire.h"
#include "ff.h"
#include "diskio.h"
#include "ffconf.h"
#include <string.h> // do f_write
#include <avr/pgmspace.h> //zeby byl progmem

FILE lcd_stream = FDEV_SETUP_STREAM(lcd_puts, NULL, _FDEV_SETUP_WRITE);
const char tekst[] PROGMEM = "Ala ma kota"; //progmem kluczowy zeby byl we flashu
FATFS FatFs;	/* Work area (filesystem object) for logical drive */
FRESULT fr;		/* FatFs return code */
FIL fil;        /* File object */
char buffer[20];   /* File copy buffer */
UINT bw;         /* File read/write count */
FILINFO fno; //not used but argument wanted for a function
uint8_t count;
int main(void){
	//Filozofia trochę inna niż zazwyczaj, bo zmieniamy kierunek DDR
	lcdinit();
	blinking(0);
	
	//KARTA SD SECTION
			/* Give a work area to the default drive */
			fr = f_mount(&FatFs, "", 1);
			if (fr == 0){
				lcd_set_xy(0,0);
				fprintf(&lcd_stream, "Zamontowano");
			}
				
			else{
				lcd_set_xy(0,0);
				fprintf(&lcd_stream, "Klopoty");
			}
			_delay_ms(2000);
			
			//Checking if file exists
			sprintf(buffer, "data%d.txt", count);
			fr = f_stat(buffer, &fno);
			while(!fr){
				count++;
				sprintf(buffer, "data%d.txt", count);
				fr = f_stat(buffer, &fno);
			}
			
			/* Open a text file */
			fr = f_open(&fil, buffer, FA_CREATE_ALWAYS | FA_WRITE); 
			if (fr == 0){
				lcd_set_xy(0,0);
				fprintf(&lcd_stream, "Wzieto otwarto plik c:");
			}
				
			else{
				lcd_set_xy(0,0);
				fprintf(&lcd_stream, "Nie otwarto pliku :c");
			}
			
			PORTD |= (1<<7);
			count = 0;	
	//END SECTION SD
		
	while(1)
	{
		OW_reset();
		//skip rom to jest hej wy termometry
		OW_send(0xCC); //SKIP ROM
		OW_send(0x44); //CONVERT T mierzcie temperature
		_delay_ms(1000); //co sekunde pomiar temperatury
		
		
		
		OW_reset();
		OW_send(0xCC);//hej wy
		OW_send(0xBE); //dajta temperature
		uint8_t mlodsze = OW_recv();
		uint8_t starsze = OW_recv();
		uint16_t temperatura = (starsze<<8)|(mlodsze);
		
		uint8_t star = temperatura >> 4;
		uint16_t mlod = (temperatura & (0x0f))*625;
		
		lcd_set_xy(0,1);
		fprintf(&lcd_stream, "T = %d.%04d %c C", star, mlod, 0b11011111);
		sprintf(buffer, "%d \t %d.%04d\n", count, star, mlod);
		f_write(&fil, buffer, strlen(buffer), &bw);
		count ++;
		if(!(PIND&(1<<7))){
			f_close(&fil);
			f_unmount("");
			lcd_set_xy(0,0);
			fprintf(&lcd_stream, "Zegnaj.... :c");
			while(1);
		}
		
	}
	return 0;
}
