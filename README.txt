Kompilowanie projektu : make (wymagany g++)
Usunięcie plików .o : make clean

Dokumentacja kodu (automatycznie wygenerowana) w folderze:
HTML -> ./doc/html/index.html

Komentarz:


Kod napisany w C++;
gramatyka LL(1) z actionSymbols , First()/Follow() sety znajdują się w pliku grammar.txt

Klasa InterCodeGenerator realizuje całą funkcjonalność translator kodu Micro.

Program bez podanych argumentów po uruchomieniu będzie oczekiwał na podanie programu w standardowym wejsciu, i będzie wczytywał kolejne linie, tak długo, aż nie napotka lini zawierającej tylko "end." lub "END.", po czym zacznie parsowanie programu.
Program może wczytać plik tekstowy (podać jako pierwszy argument sciezke do pliku);
Program może wypisać wyjście na konsole do pliku (podać jako drugi argument sciezke do pliku)(UWAGA! foldery w ścieżce muszą już istnieć!);

Program po wykonaniu się, zapisze wygenerowany kod do pliku .3AC o nazwie podanej w deklaracji "program <name> ..."

W folderze ./out znajdują się wyjścia dla przeskanowanych wcześniej odpowiednich plików znajdujących się w folderze ./samples
Plik ./parser to plik wynikowy (skompilowany program) gotowy do uruchomienia.

Dodatkowo bezpośrednio w kodzie została zaprogramowana opcja debug (wypisuje kolejne linie kodu i komunikaty o prawidłowym dopasowaniu słów), domyślnie jest ona włączona,
ale można ją wyłączyć w pliku "Stale.h" zakomentowując linię kodu 17 :"#define DEBUG".
