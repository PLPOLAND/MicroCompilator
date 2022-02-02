#ifndef INTERCODEGENERATOR_H
#define INTERCODEGENERATOR_H
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "Token.h"
#include "Scanner.h"
#include "ParseException.hh"
#include "Zmienna.hh"


using namespace std;

class InterCodeGenerator  
{
private:
	///wskaźnik na obiekt realizujący funkcję skanera
	Scanner *scanner;
	///Kolejny znaleziony token
	Token lookahead;

	unordered_map<string, vector<Token> *> firstSets;
	unordered_map<string, vector<Token> *> followSets;
	///Flaga informująca o tym, że kompilacja przebiegła bez problemów.
	bool compilationCorrect = true;

	vector<Zmienna*> zmienne;
	vector<Zmienna*> tmp_zmienne;

	std::string buffor;

	static int labelId;

	std::stringstream out;

public:
	InterCodeGenerator(std::string program);
	~InterCodeGenerator();

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
		 * @param tokens 
		 */
	bool checkIfContains(vector<Token> *tokens);

	void skipUntil(vector<Token> *tokens);
	void skipAll(vector<Token> *tokens);
	void doWithPanic(void (InterCodeGenerator::*todo)(Token), Token token);
	void doWithPanic(void (InterCodeGenerator::*todo)());
	void doWithSkip(void (InterCodeGenerator::*todo)(Token), Token token, vector<Token> *tokens);
	void doWithSkip(void (InterCodeGenerator::*todo)(), vector<Token> *tokens);

	/**
		*@brief Sprawdza czy kolejny Token w kodzie jest tym który otrzymuje jako argument. Następnie prosi scanner o znalezienie kolejnego Tokena.
		*@param T Token do którego będzie porównywany następny token w kodzie
		 */
	void Match(Token);

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
	void parseIdList(bool sprawdzZadeklarowanie = false, bool niePowinnaBycZadeklarowana = false,vector<Zmienna *>* zmienne= nullptr);
	/**
		*@brief parse : <id list tail>          -> NULL | ,<ident> <id list tail>
		*
		*/
	void parseIdListTail(bool sprawdzZadeklarowanie = false, bool niePowinnaBycZadeklarowana = false, vector<Zmienna *> *zmienne = nullptr);
	/**
		*@brief parse : <type>                  -> INTEGER | REAL
		*
		*/
	void parseType(vector<Zmienna *>* zmienne);
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
	void parseRelationOp();

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

	void run();

	int getTmp(bool type);

	void zapiszDeklaracjeZmiennych();
	void zapiszRead(Zmienna* zmienna);
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

	void zapiszAssign(Zmienna * zmienna, string toAssign);

	void zapiszWrite(string expession);
};
#endif