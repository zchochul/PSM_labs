#include <avr/io.h> 
#include "i2c.h"

//procedura inicjalizujaca
void I2C_init(void){//ustawiamy predkosc transmisji
	TWBR = 72;
}

// procedura transmisji sygnału START
void twistart(void)
{
TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while (!(TWCR & (1<<TWINT)));
}

// procedura transmisji sygnału STOP
void twistop(void)
{
TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
while ((TWCR & (1<<TWSTO)));
}

// procedura transmisji bajtu danych
void twiwrite(uint8_t bajt)
{
TWDR = bajt;
TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR & (1<<TWINT)));
}
//procedura odczytu bajtu danych
uint8_t twiread(uint8_t ack)
{
TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
while (!(TWCR & (1<<TWINT)));
return TWDR;
}


//DO ZEGARKA
void rtc_init(void){
	twistart(); //bajt start
	twiwrite(0xA2); //adres slave zeby zapisac
	twiwrite(0x0D);//adres komorki na ktorym chcemy wskaznik
	twiwrite(0b10000011); //na wyjsciu sygnal co sekunde
	twistop();
}
void rtc_set_date_time(struct datetime mydt){
	twistart();
	twiwrite(0xA2); //zeby zapisac
	twiwrite(0x01); //wskaznik na control2  // <- alarm control
	twiwrite(mydt.control2);
	//twiwrite(0x02); //ustawiamy wskaznik na sekundy
	twiwrite(dec2bcd(mydt.sec)); //ustawiamy sekundy faktycznie
	twiwrite(dec2bcd(mydt.min)); //ustawiamy sekundy minuty
	twiwrite(dec2bcd(mydt.hour)); 
	twiwrite(dec2bcd(mydt.day));
	twiwrite(dec2bcd(mydt.weekday));
	twiwrite(dec2bcd(mydt.month));
	twiwrite(dec2bcd(mydt.year));
	// alarm moment
	twiwrite(dec2bcd(mydt.amin));
	twiwrite(dec2bcd(mydt.ahour));
	twiwrite(dec2bcd(mydt.aday));
	twiwrite(dec2bcd(mydt.aweekday));
	//stoper
	twistart();
	twiwrite(0xA2);
	twiwrite(0x0E);
	twiwrite(mydt.timercon);
	twiwrite(mydt.timer);
	twistop();    
}
void rtc_get_date_time(struct datetime* mydt){
	twistart();
	twiwrite(0xA2);
	twiwrite(0x02);
	twistart();
	twiwrite(0xA3);
	uint8_t x;
	x = twiread(1) & (0b01111111);
	mydt->sec = bcd2dec(x);
	x = twiread(1) & (0b01111111);
	mydt->min = bcd2dec(x);
	x = twiread(1) & (0b00111111);
	mydt->hour = bcd2dec(x);
	x = twiread(1) & (0b00111111);
	mydt->day = bcd2dec(x);
	x = twiread(1) & (0b00000111);
	mydt->weekday = bcd2dec(x);
	x = twiread(1) & (0b00011111);
	mydt->month = bcd2dec(x);
	x = twiread(1) & (0b11111111);
	mydt->year = bcd2dec(x);
	x = twiread(1);
	x = twiread(1);
	x = twiread(1);
	x = twiread(1);
	x = twiread(1);
	x = twiread(1);
	x = twiread(0) & (0b11111111);
	mydt->timer = x;
	twistop();
}
