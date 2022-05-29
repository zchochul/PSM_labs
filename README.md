# PSM_labs
[Strona przedmiotu](http://fizyka.if.pw.edu.pl/~labe/index.php/PSM)<br>
[Instrukcja płytki prototypowej (atmega32)](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/Instrukcja-EvB5_1-v1.pdf)<br>
[NOTA KATALOGOWA](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/Noty_katalogowe/ATmega32.pdf)<br>
![image](https://user-images.githubusercontent.com/87480906/170861805-f1ba6554-a687-4328-9200-2bf17657b390.png)<br>

## Lab0 (Zajęcia wstępne)
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab0)

## Lab1 (Porty wejścia-wyjścia GPIO)
[Instrukcja do zajęć](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/PSM_Instrukcja_1.pdf) <br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab1)
Lista poleceń (krok po kroku polecenia są w instrukcji):
1. Zaświecenie diody LED z wykorzystaniem portu mikrokontrolera.
2. Odebranie informacji z przycisku i sterowanie diodami LED.
3. Miganie diody LED.
4. Sterowanie pracą silnika krokowego.
 
### Najważniejsze informacje
**Konfiguracja portów:** <br>
DDR(X) = 0xff (wszystkie na wyjście z X) / 0x00 (wszystkie na wejście z X)<br>
PORT(X) |= (1<<PXY) (ustawienie bitu Y portu X na 1, bez modyfikacji pozostałych)<br>
PORT(X) &= ~(1 << PXY) (ustawienie bitu Y portu X na 0 bez modyfikacji pozostałych)<br>
if (!(PINA & (1 << nrbitu))) <- Sprawdzanie ustawienia bitu<br>

**Inne**:<br>
_Static_ - zmienna jest umieszczana w tej samej pamięci, co zmienna globalna i nie jest usuwana wraz z zakończeniem funkcji. <br>
MIGANIE: <br>
``` c
  for(;;) { // wieczna pętla (albo tak: while(1){})
    PORTD^=0xFF; // migamy
    _delay_ms(CZAS); // czekamy 100 milisekund
  }

```



## Lab2 (Przerwania, priorytety przerwań, przerwania zewnętrzne)
[Instrukcja do zajęć](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/PSM_Instrukcja_2.pdf)
[Kod]()
[avr-libc z przerwaniami (wektory przerwań)](https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html)

Lista poleceń:
1.  Na podstawie instrukcji mikrokontrolera (nota katalogowa ATmega32) zapoznać się z działaniem
układu przerwań.
2. Znaleźć numer wyprowadzenia układu związany z pierwszym dostępnym przerwaniem zewnętrznym (INT0) oraz w dokumentacji biblioteki interrupt.h znaleźć nazwę wektora przerwania odpowiadającą temu przerwaniu.
3. Podłączyć 8 diod LED do wyprowadzeń portu C mikrokontrolera (kolejne diody LEDS od PC0 do
PC7), a przycisk będący generatorem zdarzeń do wyprowadzenia znalezionego w punkcie 2.
4. W programie włączyć i skonfigurować pierwsze dostępne przerwanie zewnętrzne, tak aby reagować na zbocze opadające.
5. W obsłudze przerwania wykonać zliczenie wartości pojawiających się zboczy sygnału (do przechowywania liczby zdarzeń wykorzystać zmienną globalną).
6. W pętli głównej wykonać wyświetlenie się liczby zliczeń w postaci binarnej z wykorzystaniem
diody LED.

## Lab3 (Obsługa wyświetlacza alfanumerycznego LCD)
[Instrukcja do zajęć](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/PSM_Instrukcja_3.pdf)
[Kod]()

Lista poleceń:

## Lab4
[Instrukcja do zajęć]()
[Kod]()

Lista poleceń:

## Lab5
[Instrukcja do zajęć]()
[Kod]()

Lista poleceń:

## Lab6
[Instrukcja do zajęć]()
[Kod]()

Lista poleceń:


## Lab7
[Instrukcja do zajęć]()
[Kod]()


Lista poleceń:

## Lab8
[Instrukcja do zajęć]()
[Kod]()


Lista poleceń:

## Lab9
[Instrukcja do zajęć]()
[Kod]()


Lista poleceń:

## Lab10
[Instrukcja do zajęć]()
[Kod]()

Lista poleceń:
