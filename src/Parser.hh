#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "Token.h"
#include "Scanner.h"





using namespace std;
	

/**
*@brief Klasa realizująca funkcje parsera kodu Micro
*
 */
class Parser  
{
	private:
	///wskaźnik na obiekt realizujący funkcję skanera
	Scanner* scanner;

	///Kolejny znaleziony token
	Token lookahead;
	
	public :
		Parser(std::string program);
		~Parser();
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
		void parseIdList(bool sprawdzZadeklarowanie = false, bool niePowinnaBycZadeklarowana = false);
		/**
		*@brief parse : <id list tail>          -> NULL | ,<ident> <id list tail>
		*
		*/
		void parseIdListTail(bool sprawdzZadeklarowanie = false, bool niePowinnaBycZadeklarowana = false);
		/**
		*@brief parse : <type>                  -> INTEGER | REAL
		*
		*/
		void parseType();
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
		void parseExpressionList();
		/**
		*@brief parse : <expression list tail>  -> NULL | , <expression> <expression list tail>
		*
		*/
		void parseExpressionListTail();
		/**
		*@brief parse : <expression>            -> <term> <expression tail>
		*
		*/
		void parseExpression();
		/**
		*@brief parse : <expression tail>       -> NULL | + <term> <expression tail> | -<term> <expression tail>
		*
		*/
		void parseExpressionTail();
		/**
		*@brief parse : <term>                  -> <factor> <term tail>
		*
		*/
		void parseTerm();
		/**
		*@brief parse : <term tail>             -> NULL | * <factor> <term tail> | / <factor> <term tail>
		*
		*/
		void parseTermTail();
		/**
		*@brief parse : <factor>                -> ( <expression> ) | <ident> | INTNUM | FLOATNUM
		*
		*/
		void parseFactor();
		/**
		*@brief parse : <ident>                 -> ID
		*
		*/
		void parseIdent();
		/**
		*@brief parse : <bool>                  -> <expression> <relation op> <expression>
		*
		*/
		void parseBool();
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
		void sprawdzCzyZadeklarowanaWczesniej();


		/**
		*@brief Sprawdza czy następna napotkana zmienna była już zadeklarowana i następuje jej ponowna deklaracja. Jeśli tak, to wypisuje error i kończy parser
		*
		*/
		void sprawdzCzyPonownaDeklaracja();
};
#endif