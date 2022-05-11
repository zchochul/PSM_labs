#include <avr/io.h> 
#include  <avr/interrupt.h>
#include "lcd.h"
#include "i2c.h"
#include <avr/pgmspace.h> //zeby byl progmem
FILE lcd_stream = FDEV_SETUP_STREAM(lcd_puts, NULL, _FDEV_SETUP_WRITE);
const char tekst[] PROGMEM = "Ala ma kota"; //progmem kluczowy zeby byl we flashu



struct datetime mydt = {
	.sec = 56,
	.min = 59,
	.hour = 23,
	.day = 31,
	.weekday = 6,
	.month = 12,
	.year = 22
};

const char * tab[] = {"nd", "pn", "wt", "sr", "czw", "pt", "so"};

ISR(INT0_vect){
	rtc_get_date_time(&mydt);
	lcd_set_xy(0,0);
	fprintf(&lcd_stream, "%02d:%02d:%02d   %s", mydt.hour, mydt.min, mydt.sec, tab[mydt.weekday]);
	lcd_set_xy(0,1);
	fprintf(&lcd_stream, "%02d/%02d/%02d", mydt.day, mydt.month, 2000+ mydt.year);
}

int main(void){
	MCUCR |= (1<<ISC01);//narastajace zbocze, czyli raz na sekunde 
	GICR |= (1<<INT0);
	sei();
	
	lcdinit();
	blinking(0);
	lcd_clear();
	I2C_init();
	rtc_init();
	rtc_set_date_time(mydt);
	
	while(1){}
	return 0;
}
