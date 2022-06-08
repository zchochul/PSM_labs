#ifndef _i2c_h_
#define _i2c_h_

#define dec2bcd(x) ((( (x)/10)<<4) + ((x) % 10)) //bcd to jest system przechowywania danych w zegarku 25 to jest (0010)(0101)
#define bcd2dec(x) ((( (x)>>4)*10) + ((x) & 0x0f))

struct datetime { //do przechowywania/odczytywania danych
	uint8_t control2;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint8_t day;
	uint8_t weekday;
	uint8_t month;
	uint8_t year;
	uint8_t	amin;
	uint8_t ahour;
	uint8_t aday;
	uint8_t	aweekday;
	uint8_t timer;
	uint8_t timercon;
};

void I2C_init(void);
void twistart(void);
void twistop(void);
void twiwrite(uint8_t bajt);
uint8_t twiread(uint8_t ack);

//do zegarka
void rtc_init(void);
void rtc_set_date_time(struct datetime);
void rtc_get_date_time(struct datetime*); //musi byc wskaznik bo bedziemy dopisywac
#endif
