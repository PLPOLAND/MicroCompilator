#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H
#include "Token.h"
#include "Scanner.h"
#include <vector>
#include <istream>

using namespace std;

class ParseException: public exception
{
	private:
	Token searched;
	vector<Token>* searched_list;
	Token found;
	public:

		ParseException(Token _searched, Token _found = Token::Null);
		ParseException(vector<Token>* _searched);
		~ParseException();
		string getErrorMsg();
		Token getSerched();
		Token getFound();
		
		const char *what() const throw()
		{
			return "Didn't found expected Token!";
		}
};
#endif