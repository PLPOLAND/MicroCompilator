#ifndef PARSERERR_H
#define PARSERERR_H
#include <iostream>
#include <algorithm>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "ParseException.hh"

using namespace std;

/**
 * @brief Klasa realizująca funkcje parsera kodu Micro z zaawansowanymi metodami "wyjścia" z błędu
 * 
 */
class ParserErr
{
	private:
		///wskaźnik na obiekt realizujący funkcję skanera
		Scanner *scanner;
		///Kolejny znaleziony token
		Token lookahead;

		unordered_map<string,vector<Token>*> firstSets;
		unordered_map<string,vector<Token>*> followSets; 
		///Flaga informująca o tym, że kompilacja przebiegła bez problemów.
		bool compilationCorrect = true;
	public:
		ParserErr(std::string program);
		~ParserErr();

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

		void skipUntil(vector<Token>* tokens);
		void skipAll(vector<Token>* tokens);
		void doWithPanic(void (ParserErr::*todo)(Token), Token token);
		void doWithPanic(void (ParserErr::*todo)());
		void doWithSkip(void (ParserErr::*todo)(Token), Token token, vector<Token> *tokens);
		void doWithSkip(void (ParserErr::*todo)(), vector<Token> *tokens);



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
		bool sprawdzCzyZadeklarowanaWczesniej();


		/**
		*@brief Sprawdza czy następna napotkana zmienna była już zadeklarowana i następuje jej ponowna deklaracja. Jeśli tak, to wypisuje error i kończy parser
		*
		*/
		bool sprawdzCzyPonownaDeklaracja();
};
#endif