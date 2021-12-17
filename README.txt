Kompilowanie projektu : make (wymagany g++)
Usunięcie plików .o : make clean

Dokumentacja kodu (automatycznie wygenerowana) w folderze:
PDF -> ./doc/latex/autoGanerated.pdf
HTML -> ./doc/html/index.html

Komentarz:

"Przepisałem" cały kod na C++. 
Klasa Scanner realizuje całą funkcjonalność Scanner.
Program bez podanych argumentów uruchomi się i przeskanuje kod programu zapisany ręczenie w zmiennej program w main.cpp;
Program może wczytać plik tekstowy (podać jako pierwszy argument sciezke do pliku);
Program może wypisać wyjście na konsole do pliku (podać jako drugi argument sciezke do pliku)(UWAGA! foldery w ścieżce muszą już istnieć!);

W folderze ./out znajdują się wyjścia dla przeskanowanych wcześniej odpowiednich plików znajdujących się w folderze ./samples

Plik ./scanner to plik wynikowy (skompilowany program) gotowy do uruchomienia.