#ifndef INTERCODEGENERATOR_H
#define INTERCODEGENERATOR_H
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "ParseException.hh"

using namespace std;

class InterCodeGenerator  
{
	private:

	Scanner* scanner;
	Token lookahead;
	string kod;

	unordered_map<string, vector<Token> *> firstSets;
	unordered_map<string, vector<Token> *> followSets;

public:
	InterCodeGenerator(string kod);
	~InterCodeGenerator();
	void makeFirstSets();
	void makeFollowSets();

	bool check(Token token);

	void run();
};
#endif