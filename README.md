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



## Lab3 (Obsługa wyświetlacza alfanumerycznego LCD, czyli początek pięknej przygody z wyświetlaczem LCD)
[Instrukcja do zajęć](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/PSM_Instrukcja_3.pdf) <br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab3) <br>
[Nota katalogowa wyświetlacza LCD (tzw. instrukcja czarno-biała)](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/Noty_katalogowe/LCD.pdf), czyli jak zrobić, żeby wyświetlacz wyczyścić, przesunąć kursor, wyłączyć miganie i inne takie bajery, a ponadto jak zrobić konkretne literki!<br>
[Algorytmy poszczególnych funkcji (tzw. instrukcja kolorowa)](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/Noty_katalogowe/Obsluga%20LCD.pdf)<br>

Lista poleceń:
1. Podłączyć wyświetlacz LCD do wyprowadzeń mikrokontrolera
2. W programie głównym zainicjować wyświetlacz oraz skonfigurować go do pracy w zadanym trybie.
3. Wyświetlić przykładowy znak, przesunąć kursor i wyświetlić znak w innym miejscu, wyświetlić napis znajdujący się w pamięci programu.
4. Na podstawie dokumentacji biblioteki stdio.h, stworzyć funkcję obsługującą standardowe wyjście (stdout) z wykorzystaniem wyświetlacza LCD oraz utworzyć własne standardowe wyjście i przekierować do niego stdout, tak aby używając funkcji printf wyświetlać na nim informacje.
5. Zbadać wpływ włączenia obsługi liczb zmiennoprzecinkowych na objętość programu oraz możliwości wyświetlania za pomocą funkcji printf.

### Najważniejsze informacje
Jak podpiąć to ustrojstwo? <br>
![image](https://user-images.githubusercontent.com/87480906/170863104-d2c9831c-8135-4e9e-9c67-f569ba1b0120.png) <- często będziemy to robić w przyszłości, więc warto pamiętać<br>

## Lab4 ( Liczniki i ich obsługa, czyli krótki tutorial jak zrobić stoper)
[Instrukcja do zajęć](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/file/psm/materialy/PSM_Instrukcja_4.pdf) <br>
[Wykład, który może się przydać](http://fizyka.if.pw.edu.pl/~labe/data/_uploaded/media/PSM/PSM_w3.pdf) <- druga połowa prezentacji <br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab4)<br>

Lista poleceń:<br>
_Część I_
1. Podłączenie przycisku do **PD6** i diody do **PC0**
2. Obliczenia... Skonfigurować licznik do pracy z zadana częstotliwością wejściową. Należy w tym przypadku
wyznaczyć najlepszą możliwą częstotliwość sygnały podawanego na wejście licznika Timer/Counter1 tak, aby odmierzanie czasu było jak najdokładniejsze. <br>
**UWAGA! Częstotliwość zegara mikrokontrolera dla płytek EvB 5.1 wyznacza kwarc zewnętrzny F_CPU = 16 MHz**
3. Zdefiniować w programie głównym opóźnienie realizowane przez licznik 1, a następnie zadeklarować zmienną określającą wartość początkową licznika (bądź końcową w zależności od wyboru trybu pracy) obliczaną dynamicznie na podstawie wpisanego wyżej opóźnienia.
4. Skonfigurować licznik zgodnie z założonym trybem pracy.
5. W obsłudze przerwania (generowanego w momencie przepełniania licznika bądź porównania)
wykonać sprawdzanie stanu przycisku, a informacje o włączeniu bądź wyłączeniu urządzenia
przekazać do pętli głównej programu.
6. W pętli głównej programu umieścić sterowanie (wł/wył) diody LED w zależności od stanu urządzenia.
_Część II_<br>
1. Zapoznać się ze sposobem sterowania wyświetlaczem LED dostępnym w zestawie.
2. Podłączenie katod: A-G <–> **PD0-PD6**, Dot <–> **PD7**, podłączenie anod (sterowanie przez tranzystory pnp, więc stan aktywny 0): Digit 1-4 <–> **PC3-PC0**.
3. Skonfigurować licznik (Timer/Counter0) tak aby co 2 ms wykonywał zapalenie kolejnej cyfry na
wyświetlaczu. Wartości cyfr do wyświetlenia należy przechowywać w zmiennych globalnych (np.
j,d,s,t).
4. Napisać funkcję, która przyjmować będzie jeden argument (typu np. uint16_t czyli liczbę do wyświetlenia) i na tej podstawie wyznaczać cyfry jedności, dziesiątek, setek i tysięcy oraz wpisywać
te wartości do zmiennych globalnych z punktu 3.
5. Wykorzystać w pętli głównej programu funkcję z punktu 4 tak aby kolejne liczby od 0 do 9999
pojawiały się co zadany okres czasu.

### Najważniejsze rzeczy do zapamiętania
Tutaj zrobiłam całe dwa przerwania. Ten z timer1 robi brzęczyk, w momencie w którym czas jest zerowy, ten z timer0 wyświetla czas na wyświetlacz LCD. Ten brzęczyk to jest moja wariacja na temat, w poleceniu jest żeby po prostu czas leciał do przodu, więc trzeba zmienić `count--;` na `count++;` i usunąć fragment brzęczykowy wgl xD. <br>
Kolejna ważna ściąga: <br>
![image](https://user-images.githubusercontent.com/87480906/170881094-79debde5-d741-4c1b-895a-2ad83be8a0ef.png)<br>
![image](https://user-images.githubusercontent.com/87480906/170881109-0317ad34-f840-471e-b501-66bc1a8f5602.png)<br>
![image](https://user-images.githubusercontent.com/87480906/170881131-a4969b89-5c08-416b-8658-e83a6795bf9f.png) <br>


## Lab5 (Magistrala RS232, czyli USART)
[Instrukcja do zajęć]()<br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab5)<br>

Lista poleceń:

## Lab6 (Magistrala SPI)
[Instrukcja do zajęć]()<br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab6)<br>

Lista poleceń:


## Lab7 (Wykorzystanie liczników do sterowania metodą PWM)
[Instrukcja do zajęć]()<br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab7)<br>


Lista poleceń:

## Lab8 (Magistrala I2C)
[Instrukcja do zajęć]()<br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab8)<br>


Lista poleceń:

## Lab9 (Magistrala 1-Wire)
[Instrukcja do zajęć]()<br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab9)<br>
[Kod, tzw przedsmak kolosa](https://github.com/zchochul/PSM_labs/tree/main/Lab9_dodatkowe)<br>


Lista poleceń:

## Lab10 (Obsługa kart SD)
[Instrukcja do zajęć]()<br>
[Kod](https://github.com/zchochul/PSM_labs/tree/main/Lab10)<br>

Lista poleceń:
