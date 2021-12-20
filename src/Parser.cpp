#include "Parser.hh"

using namespace std;

Parser::Parser(std::string program)
{
    scanner = new Scanner();
    scanner->addProgram(program);
    scanner->LoadKeywords();
    scanner->ListSymbolTable();
    scanner->GetNewLine();
    lookahead = scanner->GetNextToken();
}

Parser::~Parser()
{
    delete scanner;
}

void Parser::Match(Token T)
{

    if (this->lookahead == T)
    {
        D("Matched :");
        D_LN(scanner->getTokenName(T));
        this->lookahead = scanner->GetNextToken();
    }
    else
    {
        cout << "ERROR on Match: Symbol: ";
        scanner->printTokenName(T);
        cout << " expected but ";
        scanner->printTokenName(lookahead);
        cout << "found" << endl;
        SyntaxError(T);
    }
}

void Parser::SyntaxError(Token T)
{
    cout << "Syntax Error : on line: " << scanner->LineCount << ", at token: ";
    scanner->printTokenName(T);
    cout <<endl;

    cout << endl
         << "PANIC STOP!!!" << endl
         << endl
         << endl;
    exit(1);
}

void Parser::parseProgram()
{
    Match(Token::ProgramSym);
    parseName();
    parseOptionalDeclaration();
    Match(Token::BeginSym);
    parseStatementList();
    Match(Token::EndProgramSym);
    Match(Token::EofSym);

    scanner->ListSymbolTable();
    cout <<endl<< "Compilation Successful." << endl;
}

void Parser::parseIdent()
{
    Match(Token::Id);
}

void Parser::parseName()
{
    parseIdent();
    Match(Token::SemiColon);
}

void Parser::parseOptionalDeclaration()
{
    if (this->lookahead == Token::VarSym) // <declaration list>
    {
        parseDeclarationList();
    }
    else
    {
        ; //NULL
    }
}

void Parser::parseDeclarationList()
{
    parseDeclaration();
    if (this->lookahead == Token::VarSym) //<devlaration list tail>
    {
        parseDeclarationListTail();
    }
    else
    {
        ; //NULL
    }
}

void Parser::parseDeclarationListTail()
{
    parseDeclaration();
    if (this->lookahead == Token::VarSym) //<devlaration list tail>
    {
        parseDeclarationListTail();
    }
    else
    {
        ; //NULL
    }
}

void Parser::parseDeclaration()
{
    Match(Token::VarSym);     //VAR
    parseIdList(false, true); //<id list>
    parseType();              //:<type>
    Match(Token::SemiColon);  //;
}

void Parser::parseIdList(bool sprawdzZadeklarowanie, bool niePowinnaBycZadeklarowana)
{
    if (sprawdzZadeklarowanie == true)
    {
        this->sprawdzCzyZadeklarowanaWczesniej();
    }
    if (niePowinnaBycZadeklarowana == true) //sprawdz czy dodano nową zmienną
    {
        this->sprawdzCzyPonownaDeklaracja();
    }

    Match(Token::Id); //<ident>

    if (this->lookahead == Token::Comma)
    {
        parseIdListTail(sprawdzZadeklarowanie, niePowinnaBycZadeklarowana); //<id list tail>
    }
    else
    {
        ; //NULL
    }
}

void Parser::parseIdListTail(bool sprawdzZadeklarowanie, bool niePowinnaBycZadeklarowana)
{
    Match(Token::Comma); //,

    if (niePowinnaBycZadeklarowana == true) //sprawdz czy dodano nową zmienną
    {
        this->sprawdzCzyPonownaDeklaracja();
    }
    if (sprawdzZadeklarowanie == true)
    {
        this->sprawdzCzyZadeklarowanaWczesniej();
    }

    Match(Token::Id); //<ident>

    if (this->lookahead == Token::Comma)
    {
        parseIdListTail(sprawdzZadeklarowanie, niePowinnaBycZadeklarowana); //<id list tail>
    }
    else
    {
        ; //NULL
    }
}

void Parser::parseType()
{
    if (this->lookahead == Token::IntSym)
    { //INTEGER
        Match(Token::IntSym);
    }
    else
        Match(Token::RealSym); //REAL
}

void Parser::parseOptionalStatement()
{
    if (this->isBeginOfStatemnt(this->lookahead))
    {
        parseStatementList(); // <statement list>
    }
    else
    {
        ; //NULL
    }
}

bool Parser::isBeginOfStatemnt(Token token)
{
    if (token == BeginSym || token == Token::Id || token == Token::ReadSym || token == Token::WriteSym || token == Token::IfSym || token == Token::WhileSym)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Parser::parseStatementList()
{
    parseStatement();         //<statement>
    parseStatementListTail(); //<statement list tail>
}

void Parser::parseStatementListTail()
{
    if (isBeginOfStatemnt(this->lookahead))
    {
        parseStatement();         //<statement>
        parseStatementListTail(); //<statement list tail>
    }
    else
    { //NULL
        ;
    }
}

void Parser::parseStatement()
{
    if (this->lookahead == Token::BeginSym) //BEGIN <statement list> END;
    {
        Match(Token::BeginSym);
        parseStatementList();
        Match(Token::EndSym);
        Match(Token::SemiColon);
    }
    else if (this->lookahead == Token::Id) //<ident> := <expression>;
    {
        this->sprawdzCzyZadeklarowanaWczesniej();
        Match(Token::Id);
        Match(Token::Assign);
        parseExpression();
        Match(Token::SemiColon);
    }
    else if (this->lookahead == Token::ReadSym) //READ( <id list>);
    {
        Match(Token::ReadSym);
        Match(Token::LParen);
        parseIdList(true);
        Match(Token::RParen);
        Match(Token::SemiColon);
    }
    else if (this->lookahead == Token::WriteSym) //WRITE( <expression list>);
    {
        Match(Token::WriteSym);
        Match(Token::LParen);
        parseExpressionList();
        Match(Token::RParen);
        Match(Token::SemiColon);
    }
    else if (this->lookahead == Token::IfSym) //IF(<bool>) THEN <statement>
    {
        Match(Token::IfSym);
        Match(Token::LParen);
        parseBool();
        Match(Token::RParen);
        Match(Token::ThenSym);
        parseStatement();
    }
    else if (this->lookahead == Token::WhileSym) //WHILE(<bool>) DO <statement>
    {
        Match(Token::WhileSym);
        Match(Token::LParen);
        parseBool();
        Match(Token::RParen);
        Match(Token::DoSym);
        parseStatement();
    }
    else{
        this->SyntaxError(this->lookahead);
    }
}

void Parser::parseExpressionList()
{
    parseExpression();         //<experssion>
    parseExpressionListTail(); //<expression list tail>
}

void Parser::parseExpressionListTail()
{
    if (this->lookahead == Token::Comma) // , <expression> <expression list tail>
    {
        Match(Comma);
        parseExpression();         //<experssion>
        parseExpressionListTail(); //<expression list tail>
    }
    else //NULL
    {
        ;
    }
}

void Parser::parseExpression()
{
    parseTerm();
    parseExpressionTail();
}

void Parser::parseExpressionTail()
{
    if (this->lookahead == Token::Plus) // + | -
    {
        Match(Token::Plus);
    }
    else if (this->lookahead == Token::Minus)
    {
        Match(Token::Minus);
    }
    else
    {
        return; //NULL
    }

    parseTerm();           //<term>
    parseExpressionTail(); //<expression tail>
}

void Parser::parseTerm()
{
    parseFactor();   //<factor>
    parseTermTail(); //<term tail>
}

void Parser::parseTermTail()
{
    if (this->lookahead == Token::Multiply) // *
    {
        Match(Token::Multiply);
    }
    else if (this->lookahead == Token::Devide) // /
    {
        Match(Token::Devide);
    }
    else
    {
        return; //NULL
    }

    parseFactor();
    parseTermTail();
}

void Parser::parseFactor()
{
    if (this->lookahead == Token::LParen)
    {
        Match(Token::LParen);
        parseExpression();
        Match(Token::RParen);
    }
    else if (this->lookahead == Token::IntLiteral)
    {
        Match(Token::IntLiteral);
    }
    else if (this->lookahead == Token::RealLiteral)
    {
        Match(Token::RealLiteral);
    }
    else if (this->lookahead == Token::Id)
    {
        this->sprawdzCzyZadeklarowanaWczesniej();
        Match(Token::Id);
    }
}

void Parser::parseBool()
{
    parseExpression();
    parseRelationOp();
    parseExpression();
}

void Parser::parseRelationOp()
{
    if (this->lookahead == Token::Less)
    {
        Match(Token::Less);
    }
    else if (this->lookahead == Token::Equal)
    {
        Match(Token::Equal);
    }
    else if (this->lookahead == Token::Greater)
    {
        Match(Token::Greater);
    }
    else if (this->lookahead == Token::LessEq)
    {
        Match(Token::LessEq);
    }
    else if (this->lookahead == Token::Diffrent)
    {
        Match(Token::Diffrent);
    }
    else
    {
        Match(Token::GreaterEq);
    }
}

void Parser::sprawdzCzyPonownaDeklaracja()
{
    if (scanner->czyZadeklarowanoNowaZmienna == false)
    {
        cout << "##########################"
             << "ERROR"
             << "##########################" << endl;
        cout << "Zmienna: " << scanner->getSymbolFromHashTableById(scanner->lastSymbolID).name << " została już zadeklarowana!" << endl;
        this->SyntaxError(Token::Id);
    }
}
void Parser::sprawdzCzyZadeklarowanaWczesniej()
{
    if (scanner->czyZadeklarowanoNowaZmienna == true)
    {
        cout << "##########################"
             << "ERROR"
             << "##########################" << endl;
        cout << "Zmienna: " << scanner->getSymbolFromHashTableById(scanner->lastSymbolID).name << " nie została jeszcze zadeklarowana!" << endl;
        this->SyntaxError(Token::Id);
    }
}