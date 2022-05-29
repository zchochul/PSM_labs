# PSM_labs
[Strona przedmiotu](http://fizyka.if.pw.edu.pl/~labe/index.php/PSM)<br>
[Wykłady](http://fizyka.if.pw.edu.pl/~labe/index.php/Wyk%C5%82ad_PSM)<br>
[Materiały do laboratoriów](http://fizyka.if.pw.edu.pl/~labe/index.php/Materia%C5%82y_PSM)<br>
[Instrukcja płytki prototypowej (atmega32)](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/Instrukcja-EvB5_1-v1.pdf)<br>
[NOTA KATALOGOWA](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/Noty_katalogowe/ATmega32.pdf)<br>
![image](https://user-images.githubusercontent.com/87480906/170861805-f1ba6554-a687-4328-9200-2bf17657b390.png)<br>

## Lab0 (Zajęcia wstępne)
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab0) <br>

## Lab1 (Porty wejścia-wyjścia GPIO)
[Instrukcja do zajęć](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/PSM_Instrukcja_1.pdf) <br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab1)<br>
[Wykład, który może pomóc](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/media/PSM/PSM_w2.pdf)<br>
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

## Lab2 (Przerwania, priorytety przerwań, przerwania zewnętrzne) (zapalanie liczby zliczeń w postaci binarnej z wykorzystaniem diody led)
[Instrukcja do zajęć](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/PSM_Instrukcja_2.pdf)<br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab2)<br>
[Wykład, który może pomóc](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/media/PSM/PSM_w3.pdf)<br>
[avr-libc z przerwaniami (wektory przerwań)](https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html)<br>

Lista poleceń:<br>
1.  Na podstawie instrukcji mikrokontrolera (nota katalogowa ATmega32) zapoznać się z działaniem
układu przerwań.
2. Znaleźć numer wyprowadzenia układu związany z pierwszym dostępnym przerwaniem zewnętrznym (INT0) oraz w dokumentacji biblioteki interrupt.h znaleźć nazwę wektora przerwania odpowiadającą temu przerwaniu.
3. Podłączyć 8 diod LED do wyprowadzeń portu C mikrokontrolera (kolejne diody LEDS od PC0 do
PC7), a przycisk będący generatorem zdarzeń do wyprowadzenia znalezionego w punkcie 2.
4. W programie włączyć i skonfigurować pierwsze dostępne przerwanie zewnętrzne, tak aby reagować na zbocze opadające.
5. W obsłudze przerwania wykonać zliczenie wartości pojawiających się zboczy sygnału (do przechowywania liczby zdarzeń wykorzystać zmienną globalną).
6. W pętli głównej wykonać wyświetlenie się liczby zliczeń w postaci binarnej z wykorzystaniem
diody LED.

### Najważniejsze informacje
Żeby zrobić przerwanie trzeba dodać bibliotekę ``` #include <avr/interrupt.h> ```. Poza tym, trzeba dodać taką strukturę przed mainem:
``` c
  ISR(„nazwa wektora przerwania zdefiniowana w dokumentacji biblioteki interrupt.h”)
  {
      ....... //instrukcje wykonywane w procedurze
   }

```
Nazwy wektorów najwygodniej znaleźć w wersji html [instrukcji do biblioteki avr-libc](https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html). Trzeba pamiętać, że szukamy takiego, który wgl istnieje w atmega32 ;) <br>
Źródło, które będzie nam generować przerwanie trzeba podpiąć do odpowiedniej nóżki mikrokontrolera, w tym celu można skorzystać ze zdjęcia które pojawia się na początku tego repozytorium, albo moża mi zaufać, że wyjście INT0, które nas interesuje w tym przypadku to jest nóżka PD2 xD <br>
Ponadto chcemy reagować tutaj na zbocze opadające, a to znaczy że trzeba ustawić konkretne bity rejestru MCUCR (MCU Control Register), a oto ściąga z wykładu:<br>
![image](https://user-images.githubusercontent.com/87480906/170862700-8cb10895-05eb-4174-be61-bf8200ef7a0a.png)<br>
W tej ściądze jest informacja na temat INT0 i INT1, jeszcze z takich łatwo dostępnych jest INT2, ale polecam sobie w tym celu doczytać wykład, który załączyłam do tego ćwiczenia c: <br>
Jeszcze włączamy przerwania zewnętrzne jako ogół ustawiając dobry bit na rejestrze GICR (General Interrupt Control Register). W tym przypadku `GICR |= (1<<INT0);`.A poza tym włączamy "główny zawór przerwań" pisząc `sei();`<br>



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
