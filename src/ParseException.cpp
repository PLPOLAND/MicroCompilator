#include "ParseException.hh"

ParseException::ParseException(Token _searched, Token _found)
{
    this->searched = _searched;
    this->found = _found;
}
ParseException::ParseException(vector<Token> *_searched)
{
    this->searched_list = _searched;
}

ParseException::~ParseException()
{
}

string ParseException::getErrorMsg()
{

    string tmp;
    if (this->searched == Token::Null)
    {
        tmp += "Error! Didn't found any of expected: ";
        for (unsigned int i = 0; i < searched_list->size(); i++)
        {
            tmp += Scanner::getTokenName(searched_list->at(i));
            tmp += "/";
        }
    }
    else
    {
        tmp += "Error! Expected: ";
        tmp += Scanner::getTokenName(searched);
        tmp += " but found: ";
        tmp += Scanner::getTokenName(found);
    }

    return tmp;
}

Token ParseException::getSerched()
{
    return searched;
}

Token ParseException::getFound()
{
    return found;
}
