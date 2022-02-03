#ifndef INTERCODEGENERATOR_H
#define INTERCODEGENERATOR_H
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "Token.h"
#include "Scanner.h"
#include "ParseException.hh"
#include "Variable.hh"


using namespace std;
/**
 * @brief Klasa odpowiadająca za Parsowanie i Generowanie kodu 3AC
 * 
 */
class InterCodeGenerator  
{
private:
	///wskaźnik na obiekt realizujący funkcję skanera
	Scanner *scanner;
	///Kolejny znaleziony token
	Token lookahead;
		///Przechowuje zbiory danych zawierające tokeny wchodzące w skład FirstSetów
	unordered_map<string, vector<Token> *> firstSets;
	///Przechowuje zbiory danych zawierające tokeny wchodzące w skład FollowSetów
	unordered_map<string, vector<Token> *> followSets;
	///Flaga informująca o tym, że kompilacja przebiegła bez problemów.
	bool compilationCorrect = true;

	///Przechowuje zmienne zadeklarowane w trakcie generowania kodu (wszystkie)
	vector<Variable*> zmienne;
	///Przechowuje zmienne zadeklarowane w trakcie generowania kodu (tylko zmienne tymczasowe)
	vector<Variable*> tmp_zmienne;

	std::string buffor;

	///Zmienna iteracyjna przechowująca numer szeregowy kolejnego "Label" w wygenerowanym kodzie
	static int labelId;
	///Przechowuje wygenerowany kod, do dalszego zapisania w pliku.
	std::stringstream out;

	std::string nazwaProgramu = ".3AC";
public:
	/**
	 * @brief Construct a new Inter Code Generator object
	 * 
	 * @param program kod programu do przetłumaczenia
	 */
	InterCodeGenerator(std::string program);
	~InterCodeGenerator();
	/**
	 * @brief Zatrzymuje działanie prsera z efekten natychmiastowym.
	 * 
	 */
	void panicStop();

	/**
		 * @brief Dodaje firstSety do kontenera
		 */
	void makeFirstSets();
	/**
		 * @brief Dodaje followSety do kontenera
		 */
	void makeFollowSets();

	/**
		 * @brief Sprawdza czy token przetrzymywany w lookahead jest przetrzymywany w podanej liście.
		 * 
		 * @param tokens poszukiwane tokeny
		 * @return true jeśli lookahead został znaleziony w "tokens"
		 */
	bool checkIfContains(vector<Token> *tokens);
	/**
	 * @brief Skipuje kolejne tokeny aż do natrafienia na token podany w kontenerze w argumentach
	 * 
	 * @param tokens tokeny do których Scanner będzie skipował
	 */
	void skipUntil(vector<Token> *tokens);
	/**
	 * @brief Skipuje wszystkie natrafione tokeny, do puki znajdują się one w kontenerze w argumencie
	 * 
	 * @param tokens tokeny które zostaną przeskipowane.
	 */
	void skipAll(vector<Token> *tokens);

	/**
	 * @brief Próbuje wykonać podaną funkcję przyjmującą "Token" i zwaracającą void. Jeśli napotka wyjątek, wywoła panicStop()
	 * @see InterCodeGenerator::panicStop();
	 * @param todo funkcja do wykonania
	 * @param token token podawany w argumencie do funkcji todo
	 */
	void doWithPanic(void (InterCodeGenerator::*todo)(Token), Token token);
	/**
	 * @brief Próbuje wykonać podaną funkcję przyjmującą "Token" i zwaracającą void. Jeśli napotka wyjątek, wywoła panicStop()
	 * @see InterCodeGenerator::panicStop();
	 * @param todo funkcja do wykonania
	 */
	void doWithPanic(void (InterCodeGenerator::*todo)());
	/**
	 * @brief Próbuje wykonać podaną funkcję przyjmującą "Token" i zwaracającą void. Jeśli napotka wyjątek, skipuje aż do natrafienia na jeden z tokenów w "tokens"
	 * @see InterCodeGenerator::skipUntil();
	 * @param todo funkcja do wykonania
	 * @param token token podawany w argumencie do funkcji todo
	 * @param tokens tokeny do, których zostanie wyskipowany kod programu
	 */
	void doWithSkip(void (InterCodeGenerator::*todo)(Token), Token token, vector<Token> *tokens);
	/**
	 * @brief Próbuje wykonać podaną funkcję przyjmującą "Token" i zwaracającą void. Jeśli napotka wyjątek, skipuje aż do natrafienia na jeden z tokenów w "tokens"
	 * @see InterCodeGenerator::skipUntil();
	 * @param todo funkcja do wykonania
	 * @param tokens tokeny do, których zostanie wyskipowany kod programu
	 */
	void doWithSkip(void (InterCodeGenerator::*todo)(), vector<Token> *tokens);

	/**
		*@brief Sprawdza czy kolejny Token w kodzie jest tym który otrzymuje jako argument. Następnie prosi scanner o znalezienie kolejnego Tokena.
		*@param T Token do którego będzie porównywany następny token w kodzie
		 */
	void Match(Token);
	/**
	 * @brief Funkcja wypisująca informację o błędzie, miejscu jego wystąpienia i zapisująca informację o błędzie kompilacji.
	 * 
	 * @param T Token
	 */
	void SyntaxError(Token T);
	/**
		*@brief parse <program> -> PROGRAM <name> <optional declaration> BEGIN <optional statement> END.
		*
		 */
	void parseProgram();

	/**
		*@brief parse <name> -> <ident>;
		*
		 */
	void parseName();
	/**
		*@brief parse :  <optional declaration>  -> <declaration list> | NULL
		*
		 */
	void parseOptionalDeclaration();

	/**
		*@brief parse : <declaration list>      -> <declaration> <declaration list tail>
		*
		 */
	void parseDeclarationList();

	/**
		*@brief parse : <declaration list tail> -> NULL | <declaration> <declaration list>
		*
		*/
	void parseDeclarationListTail();
	/**
		*@brief parse : <declaration>           -> VAR <id list> : <type> ;
		*
		*/
	void parseDeclaration();
	/**
		*@brief parse : <id list>               -> <ident> <id list tail>
		*
		*/
	void parseIdList(bool sprawdzZadeklarowanie = false, bool niePowinnaBycZadeklarowana = false,vector<Variable *>* zmienne= nullptr);
	/**
		*@brief parse : <id list tail>          -> NULL | ,<ident> <id list tail>
		*
		*/
	void parseIdListTail(bool sprawdzZadeklarowanie = false, bool niePowinnaBycZadeklarowana = false, vector<Variable *> *zmienne = nullptr);
	/**
		*@brief parse : <type>                  -> INTEGER | REAL
		*
		*/
	void parseType(vector<Variable *>* zmienne);
	/**
		*@brief parse : <optional statement>    -> <statement list> <statement> | NULL
		*
		*/
	void parseOptionalStatement();
	/**
		*@brief parse : <statement list>        -> <statement> <statement list tail> 
		*
		*/
	void parseStatementList();
	/**
		*@brief parse : <statement list tail>   -> NULL | <statement> <statement list tail> 
		*
		*/
	void parseStatementListTail();
	/**
		*@brief parse : <statement>             -> BEGIN <statement list> END; \n
                         						| <ident> := <expression>;
												| READ( <id list>);
												| WRITE( <expression list>);
												| IF(<bool>) THEN <statement>
												| WHILE(<bool>) DO <statement>
		*
		*/
	void parseStatement();
	/**
		*@brief parse : <expression list>       -> <expression> <expression list tail>
		*
		*/
	void parseExpressionList(vector<string *>* expressions);
	/**
		*@brief parse : <expression list tail>  -> NULL | , <expression> <expression list tail>
		*
		*/
	void parseExpressionListTail(vector<string *>* expressions);
	/**
		*@brief parse : <expression>            -> <term> <expression tail>
		*@return id of token
		*/
	string parseExpression();
	/**
		*@brief parse : <expression tail>       -> NULL | + <term> <expression tail> | -<term> <expression tail>
		*
		*/
	string parseExpressionTail();
	/**
		*@brief parse : <term>                  -> <factor> <term tail>
		*
		*/
	string parseTerm();
	/**
		*@brief parse : <term tail>             -> NULL | * <factor> <term tail> | / <factor> <term tail>
		*
		*/
	string parseTermTail();
	/**
		*@brief parse : <factor>                -> ( <expression> ) | <ident> | INTNUM | FLOATNUM
		*
		*/
	string parseFactor();
	/**
		*@brief parse : <ident>                 -> ID
		*
		*/
	void parseIdent();
	/**
		*@brief parse : <bool>                  -> <expression> <relation op> <expression>
		*@return Label name to skip Code
		*/
	string parseBool();
	/**
		*@brief parse : <relation op>           -> < | = | > | <= | <> | >=
		*
		*/
	Token parseRelationOp();

	/**
		*@brief sprawdza czy token jest jednym z tokenów rozpoczynających <statemnt>
		*
		*@param token token do sprawdzenia
		*@return true jest jednym z tokenów rozpoczynających <statemnt>
		*@return false nie jest jednym z tokenów rozpoczynających <statemnt>
		 */
	bool isBeginOfStatemnt(Token token);

	/**
		*@brief Sprawdza czy następna napotkana zmienna była już zadeklarowana wcześniej. Jeśli tak to wypisuje error, i kończy parser
		*
		 */
	bool sprawdzCzyZadeklarowanaWczesniej();

	/**
		*@brief Sprawdza czy następna napotkana zmienna była już zadeklarowana i następuje jej ponowna deklaracja. Jeśli tak, to wypisuje error i kończy parser
		*
		*/
	bool sprawdzCzyPonownaDeklaracja();
	/**
	 * @brief Funkcja wykonująca translator. Parsuje i generuje kod 3AC.
	 * 
	 */
	void run();

	/**
	 * @brief generuje zmienną tymczasową i zwaraca jej index w tmp_zmienne
	 * 
	 * @param type typ generowanej zmiennej (true dla REAL, false dla INTEGER)
	 * @return int index w tmp_zmienne
	 */
	int getTmp(bool type);
	/**
	 * @brief generuje string zawierający deklaracje wszystkich zmiennych w kodzie 3AC
	 * 
	 * @return string 
	 */
	string generujTekstDeklaracjiZmiennych();

	/**
	 * @brief Zapisuje "READ" do strumienia z wygenerowanym kodem 3AC
	 * 
	 * @param zmienna 
	 */
	void zapiszRead(Variable* zmienna);
	/**
	 * @brief Get the Label 
	 * 
	 * @return string - "label" + nextNumber eg.: label1
	 */
	string getLabel();
	/**
	 * @brief Wypisuje kod Kończący while w 3AC
	 * 
	 * @param startwhileLabel - label wypisany na początku while-a
	 * @param endwhileLabel - label kończący while-a
	 */
	void endWhile(string startwhileLabel, string endwhileLabel);
	/**
	 * @brief Wypisuje kod początkowy while
	 * 
	 * @return string - label początkujący while
	 */
	string startWhile();

	/**
	 * @brief Zapisuje do strumienia wygenerowany ciąg oznaczający przypisanie wartosći w kodzie 3AC
	 * 
	 * @param zmienna zmienna do której ma być przypisana wartość
	 * @param toAssign to co ma być przypisane
	 */
	void zapiszAssign(Variable * zmienna, string toAssign);
	/**
	 * @brief Zapisuje "WRITE" do strumienia z wygenerowanym kodem 3AC
	 * 
	 * @param expession to co ma być po słowie WRITE w kodzie 3AC
	 */
	void zapiszWrite(string expession);

	/**
	 * @brief Generuje cały kod 3AC odpowiadający za sprawdzanie warunku "bool" w wersji odwróconej
	 * 
	 * @param label label do którego ma być wykonywany skok w przypadku zajścia warunku
	 * @param id1 id zmiennej nr 1
	 * @param id2 id zmiennej nr 2 
	 * @param op rodzaj boola
	 */
	void generateBool(string label, string id1, string id2, Token op);

	/**
	 * @brief Generuje kod kończący IF w 3AC
	 * 
	 * @param endIfLabel label który ma znaleźć się po IF-ie
	 */
	void endIF(string endIfLabel);

	/**
	 * @brief Generuje informacje o niezgadzających się typach zmiennych w działaniu
	 * 
	 */
	void mismatchError();

	/**
	 * @brief Funkcja pomocnicza, usuwająca znaki '\0' generowane w kodzie, a które powodują późniejsze problemy z otwieraniem plików itp.
	 * 
	 * @param str string do przefiltorwania
	 * @return string przefiltrowany string
	 */
	string deleteZleZnaki(string str);
};
#endif