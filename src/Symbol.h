#ifndef SYMENTRY_H
#define SYMENTRY_H
#include <iostream>
#include "Token.h"

/**
*@author Marek Pałdyna 
*
*@brief Klasa Przechowująca dane (nazwę i token) - elemnt hashtable
*
 */
class Symbol  
{
	public:
		std::string name;
		Token token;
		Symbol();
		Symbol(std::string name, Token token):name(name),token(token) {};
		~Symbol();

};
#endif