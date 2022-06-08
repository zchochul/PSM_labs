#include <avr/io.h> 
#include  <avr/interrupt.h>
#include "lcd.h"
#include "i2c.h"
#include "usart.h"
#include <util/delay.h> 
#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h> //zeby byl progmem
FILE lcd_stream = FDEV_SETUP_STREAM(lcd_puts, NULL, _FDEV_SETUP_WRITE);
FILE u_stream = FDEV_SETUP_STREAM(u_putc, NULL, _FDEV_SETUP_WRITE);
const char tekst[] PROGMEM = "Ala ma kota"; //progmem kluczowy zeby byl we flashu
uint8_t etap;
uint8_t ustawianie;
char bufor[10];
uint8_t i; 
uint8_t wybur;
uint8_t ustaw;

struct datetime mydt = {
	//kontrola
	//.control1 = 1,
	.control2 = 0b00000010,
	//czas
	.sec = 56,
	.min = 59,
	.hour = 23,
	.day = 31,
	.weekday = 6,
	.month = 12,
	.year = 22,
	//alarm
	.amin = 0,
	.ahour = 0,
	.aday = 1,
	.aweekday = 0,
	.timercon = 0,
	.timer = 60
};


const char * tab[] = {"nd", "pn", "wt", "sr", "czw", "pt", "so"};

ISR(INT0_vect){
	//PORTB  ^= 0xff;
	rtc_get_date_time(&mydt);
	lcd_set_xy(0,0);
	fprintf(&lcd_stream, "%02d:%02d:%02d   %s", mydt.hour, mydt.min, mydt.sec, tab[mydt.weekday]);
	if(wybur ==0){
		lcd_set_xy(0,1);
		fprintf(&lcd_stream, "budzik: %02d:%02d ", mydt.ahour, mydt.amin);
	}
	if(wybur == 1){
		lcd_set_xy(0,1);
		fprintf(&lcd_stream, "stoper: %02d ", mydt.timer);
	}
	//lcd_set_xy(0,1);
	//fprintf(&lcd_stream, "%02d/%02d/%02d", mydt.day, mydt.month, 2000+ mydt.year);
}

ISR(INT1_vect){ //alarm
	PORTB = 0x00;
	_delay_ms(1000);
	PORTB = 0xff;
	if(wybur==1){
		mydt.timercon = 0;
		rtc_set_date_time(mydt);
		
	}
}

ISR(USART_RXC_vect){
	bufor[i] = UDR;
	if(bufor[i]=='\n'){
		//alarm
		
		if(strncmp(bufor, "sah", 3) == 0)// takie same
		{
			ustaw = atoi((const char*)(bufor+3));
			mydt.ahour = ustaw;
			mydt.control2 = 0b00000010;
			rtc_set_date_time(mydt);
			wybur =0;
		}
		if(strncmp(bufor, "sam", 3) == 0)// takie same
		{
			ustaw = atoi((const char*)(bufor+3));
			mydt.control2 = 0b00000010;
			mydt.amin = ustaw;
			rtc_set_date_time(mydt);
			lcd_set_xy(0,1);
			fprintf(&lcd_stream, "godz: %02d:%02d ", mydt.ahour, mydt.amin);
			wybur =0;
		}
		//stoper
		if(strncmp(bufor, "st", 2) == 0){
			ustaw = atoi((const char*)(bufor+2));
			mydt.control2 = 0b00010001;
			mydt.timercon = 0b10000010;
			mydt.timer = ustaw;
			rtc_set_date_time(mydt);
			wybur =1;
		}
		
		i=0;
	
	} else {
		i++;
	}
	
}


int main(void){
	MCUCR |= (1<<ISC01)| (1<<ISC11);//narastajace zbocze, czyli raz na sekunde 
	GICR |= (1<<INT0)|(1<<INT1);
	
	
	//bzyczek alarmowy
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	//ekran
	lcdinit();
	blinking(0);
	lcd_clear();
	
	//zegareczek
	I2C_init();
	rtc_init();
	rtc_set_date_time(mydt);
	
	//USART
	USART_Init(1); //500 000 baud
	sei();
	fprintf(&u_stream,"Jaki tryb wybierasz? Wpisz 0 jezeli chcesz ustawic budzik i 1 jezeli stoperek! \n");
	
	while(1){
		
	}
	return 0;
}
