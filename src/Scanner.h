#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <cstring>
#include <unordered_map>
#include "Stale.h"
#include "Token.h"
#include "Symbol.h"

/**
*@author Marek Pałdyna
*@brief Klasa realizująca funkcje skanera kodu
*
 */
class Scanner  
{
	public:

		///zacachowany kod programu.
		std::string programString = "";
		/// Przechowuje index kolejnego znaku do wczytania do buforuLini
		int programStringPointer = 0;

		///Buffor uzywany do znajdywania kolejnych tokenów
		std::string tokenBuffer;

		///używany do przechowywania kolejnych linii programu
		char LineBuffer[MAX_LINE_LENGTH + 1];

		///Przechowuje długość aktualnie zbuforowanej linii
		int LineLength;

		int LinePtr;
		///Numer szeregowy aktualnej linii
		int LineCount;
		///Ostatni zbuforowany znak
		char lastChar;

		///Zmienna przechowująca id(w hashTable) ostatnio znaleziony symbol 
		int lastSymbolID = 0;
		///Do tymczasowego przechowawania wartości zmiennej numerycznej (w postaci stringa)
		std::string NumLexeme = "";

		///Zmienna przechowująca czy ostatnio znalezione id zostało dodane do listy(true), czy była już wcześniej dodana (false)
		bool czyZadeklarowanoNowaZmienna = false;	
		///hash tablica 
		//TODO czy to na pewno o to chodziło???
		std::unordered_map<int, Symbol> *hashtable;

		Scanner();
		~Scanner();

		/**
		*	@brief Convert characters to lower case characters 
		*
		 */
		void ToLowerCase();

		/**
		*	@brief produce a listing of the source program
		 */
		void ListThisLine();

		/**
		*	@brief get a new line from cached program
		*
		*/
		void GetNewLine();

		/**
		*	@brief Pobiera kolejny znak z zbuforowanej linii, jeśli brak takich to buforuje kolejną linie i podaje jej pierwszy znak
		*
		*	@param c zmienna do której zostaje przypisany kolejny znak
		 */
		void GetNextChar(char *c);

		/**
		*	@brief Zmniejsza znacznik pozycji zbuforowanego znaku
		*
		 */
		void PutNextChar();

		/**
		*	@brief Czyści bufor przeznaczony do bufforowania Tokenów
		*
		 */
		void ClearBuffer();

		/**
		*	@brief Dodaje znak z parametru do bufora tokenBuffer 
		*	@see tokenBuffer
		*
		*	@param c znak do dodania do bufora
		 */
		void BufferChar(char c);
		/**
		*@brief Wypisuje informacje o błędzie lexykalnym na podanym znaku
		*
		*@param c 
		 */
		void LexicalError(char c);

		/**
		*@brief Bufforuje wyraz, (wyraz składa się ze znaków alfanumerycznych lub '_' lub '.' )
		*
		*@param c znak od którego zaczy się buforowane słowo
		 */
		void BufferName(char c);
		
		/**
		*@brief Bufforuje liczby, (liczba składa się z cyfry lub '.')
		*
		*@param c - pierwsza cyfra/znak
		*@return int - 1 jeśli liczba jest typu REAL, 0 jeśli liczba jest typu INTEGER
		 */
		int BufferNumLiterals(char c);

		/**
		*@brief Check is the symbol into already reserved Symbols
		*
		*@return Token::ID jeśli nie znaleziono wśród słów już zarezerowanych w przeciwnym razie zwraca Typ zarezerwowanego słowa
		 */
		Token CheckReserved();

		/**
		*@brief Znajduje kolejny Token w tekscie programu
		*
		*@return Token 
		 */
		Token GetNextToken();

		/**
		*@brief Przeprowadza procedurę skanowania podanego programu.
		*@warning program musi kończyć się znakiem EOF!
		*@param program zmienna typu string z wczytanym kodem programu
		 */
		void scan(std::string program);

		/**
		*@brief Put S unconditionally into the symbol table and returns index of the entry for S 
		*
		*@param S Name
		*@param Code Token
		*@return int id wpisu w hashLiście
		 */
		int Enter(std::string S, Token Code);

		/**
		*@brief Dodaje Słowa kluczowe do hashListy
		*
		 */
		void LoadKeywords();

		/**
		*@brief Wypisuje wszystkie Symbole przechowywane w HashTable
		*
		 */
		void ListSymbolTable();

		/**
		*@brief Returns id in hashTable of the entry for S, or 0 if it is not found
		*
		*@param S Entry
		*@return int 
		 */
		int LookUp(std::string S);
		/**
		*@brief Wypisuje kod programu z ponumerowanymi liniamii
		*
		 */
		void printOutProgramCodeWithLines();

		void printTokenName(Token token);
		/**
		*@brief Zwraca podany token jako string
		*	Służy do zmiany tokena na string zawierający jego nazwę.
		*@param token 
		*@return std::string 
		 */
		static std::string getTokenName(Token token);

		Symbol getSymbolFromHashTableById(int id);

		void addProgram(std::string program);
};
#endif