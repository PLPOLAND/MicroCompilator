#include "InterCodeGenerator.hh"

int InterCodeGenerator::labelId = 0;

using namespace std;

InterCodeGenerator::InterCodeGenerator(string kod){
    this->scanner = new Scanner();
    scanner->addProgram(kod);
    scanner->LoadKeywords();
    scanner->ListSymbolTable();
    scanner->GetNewLine();
    lookahead = scanner->GetNextToken();


    makeFirstSets();
    for (std::pair<std::string, vector<Token>*> element : firstSets)
    {
        std::cout <<endl<< "first("<<element.first << "): " <<endl;
        for (unsigned int i = 0; i < element.second->size(); i++)
        {
            cout<<"- "<<Scanner::getTokenName(element.second->at(i))<<endl;
        }
        
    }
	makeFollowSets();
    for (std::pair<std::string, vector<Token>*> element : followSets)
    {
        std::cout <<endl<< "follow("<<element.first << "): " <<endl;
        for (unsigned int i = 0; i < element.second->size(); i++)
        {
            cout<<"- "<<Scanner::getTokenName(element.second->at(i))<<endl;
        }
        
    }

}
	
InterCodeGenerator::~InterCodeGenerator()
{
    delete this->scanner;
}

void InterCodeGenerator::run(){
    parseProgram();

    string deklaracjeZmiennych = generujTekstDeklaracjiZmiennych();
    out.flush();
    string outString = out.str();

    deklaracjeZmiennych = this->deleteZleZnaki(deklaracjeZmiennych);
    outString = this->deleteZleZnaki(outString);
    
    ofstream plik3AC;
    plik3AC.open(nazwaProgramu);
    if (plik3AC.good())
    {
        plik3AC<<deklaracjeZmiennych;
        plik3AC << outString;
        plik3AC<< "halt";
    }
    plik3AC.close();

    cout << endl
         << endl
         << "Kod programu:" << endl
         << endl
         << deklaracjeZmiennych
         << outString
         <<"halt"<<endl;
}

void InterCodeGenerator::makeFirstSets()
{
    vector<Token> *tmp;

    //first(<program>)
    tmp = new vector<Token>();
    tmp->push_back(Token::ProgramSym);
    firstSets.insert({"program", tmp});
    //first(<name>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Id);
    firstSets.insert({"name", tmp});
    //first(<optionalDeclaration>)
    tmp = new vector<Token>();
    tmp->push_back(Token::VarSym);
    tmp->push_back(Token::Null);
    firstSets.insert({"optionalDeclaration", tmp});
    //first(<declarationlist>)
    tmp = new vector<Token>();
    tmp->push_back(Token::VarSym);
    firstSets.insert({"declarationlist", tmp});
    //first(<declarationlisttail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::VarSym);
    tmp->push_back(Token::Null);
    firstSets.insert({"declarationlisttail", tmp});
    //first(<declaration>)
    tmp = new vector<Token>();
    tmp->push_back(Token::VarSym);
    firstSets.insert({"declaration", tmp});
    //first(<idlist>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Id);
    firstSets.insert({"idlist", tmp});
    //first(<idlisttail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Comma);
    tmp->push_back(Token::Null);
    firstSets.insert({"idlisttail", tmp});
    //first(<type>)
    tmp = new vector<Token>();
    tmp->push_back(Token::IntSym);
    tmp->push_back(Token::RealSym);
    firstSets.insert({"type", tmp});
    //first(<optionalstatement>)
    tmp = new vector<Token>();
    tmp->push_back(Token::BeginSym);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::ReadSym);
    tmp->push_back(Token::WriteSym);
    tmp->push_back(Token::IfSym);
    tmp->push_back(Token::WhileSym);
    firstSets.insert({"optionalstatement", tmp});
    //first(<statementlist>)
    tmp = new vector<Token>();
    tmp->push_back(Token::BeginSym);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::ReadSym);
    tmp->push_back(Token::WriteSym);
    tmp->push_back(Token::IfSym);
    tmp->push_back(Token::WhileSym);
    firstSets.insert({"statementlist", tmp});
    //first(<statementlisttail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::BeginSym);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::ReadSym);
    tmp->push_back(Token::WriteSym);
    tmp->push_back(Token::IfSym);
    tmp->push_back(Token::WhileSym);
    tmp->push_back(Token::Null);
    firstSets.insert({"statementlisttail", tmp});

    //first(<statement>)
    tmp = new vector<Token>();
    tmp->push_back(Token::BeginSym);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::ReadSym);
    tmp->push_back(Token::WriteSym);
    tmp->push_back(Token::IfSym);
    tmp->push_back(Token::WhileSym);
    firstSets.insert({"statement", tmp});
    //first(<expressionlist>)
    tmp = new vector<Token>();
    tmp->push_back(Token::LParen);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::IntSym);
    tmp->push_back(Token::RealSym);
    firstSets.insert({"expressionlist", tmp});
    //first(<expression list tail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Comma);
    tmp->push_back(Token::Null);
    firstSets.insert({"expressionlisttail", tmp});
    //first(<expression>)
    tmp = new vector<Token>();
    tmp->push_back(Token::LParen);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::IntSym);
    tmp->push_back(Token::RealSym);
    firstSets.insert({"expression", tmp});
    //first(<expressiontail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Plus);
    tmp->push_back(Token::Minus);
    tmp->push_back(Token::Null);
    firstSets.insert({"expressiontail", tmp});
    //first(<term>)
    tmp = new vector<Token>();
    tmp->push_back(Token::LParen);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::IntLiteral);
    tmp->push_back(Token::RealLiteral);
    firstSets.insert({"term", tmp});
    //first(<term tail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Multiply);
    tmp->push_back(Token::Devide);
    tmp->push_back(Token::Null);
    firstSets.insert({"termtail", tmp});
    //first(<factor>)
    tmp = new vector<Token>();
    tmp->push_back(Token::LParen);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::IntLiteral);
    tmp->push_back(Token::RealLiteral);
    firstSets.insert({"factor", tmp});
    //first(<ident>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Id);
    firstSets.insert({"ident", tmp});
    //first(<bool>)
    tmp = new vector<Token>();
    tmp->push_back(Token::LParen);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::IntLiteral);
    tmp->push_back(Token::RealLiteral);
    firstSets.insert({"bool", tmp});
    //first(<relationop>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Greater);
    tmp->push_back(Token::GreaterEq);
    tmp->push_back(Token::Equal);
    tmp->push_back(Token::Diffrent);
    tmp->push_back(Token::Less);
    tmp->push_back(Token::LessEq);
    firstSets.insert({"relationop", tmp});
}
void InterCodeGenerator::makeFollowSets()
{
    vector<Token> *tmp;

    //follow(<program>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Null);
    followSets.insert({"program", tmp});
    //follow(<name>)
    tmp = new vector<Token>();
    tmp->push_back(Token::VarSym);
    tmp->push_back(Token::BeginSym);
    followSets.insert({"name", tmp});
    //follow(<optionalDeclaration>)
    tmp = new vector<Token>();
    tmp->push_back(Token::BeginSym);
    followSets.insert({"optionaldeclaration", tmp});
    //follow(<declarationlist>)
    tmp = new vector<Token>();
    tmp->push_back(Token::BeginSym);
    followSets.insert({"declarationlist", tmp});
    //follow(<declarationlisttail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::BeginSym);
    followSets.insert({"declarationlisttail", tmp});
    //follow(<declaration>)
    tmp = new vector<Token>();
    tmp->push_back(Token::VarSym);
    tmp->push_back(Token::BeginSym);
    followSets.insert({"declaration", tmp});
    //follow(<idlist>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Colon);
    tmp->push_back(Token::RParen);
    followSets.insert({"idlist", tmp});
    //follow(<idlisttail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Colon);
    tmp->push_back(Token::RParen);
    followSets.insert({"idlisttail", tmp});
    //follow(<type>)
    tmp = new vector<Token>();
    tmp->push_back(Token::SemiColon);
    followSets.insert({"type", tmp});
    //follow(<optionalstatement>)
    tmp = new vector<Token>();
    tmp->push_back(Token::EndProgramSym);
    followSets.insert({"optionalstatement", tmp});
    //follow(<statementlist>)
    tmp = new vector<Token>();
    tmp->push_back(Token::EndProgramSym);
    tmp->push_back(Token::EndSym);
    followSets.insert({"statementlist", tmp});
    //follow(<statementlisttail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::EndProgramSym);
    tmp->push_back(Token::EndSym);
    followSets.insert({"statementlisttail", tmp});
    //follow(<statement>)
    tmp = new vector<Token>();
    tmp->push_back(Token::BeginSym);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::ReadSym);
    tmp->push_back(Token::WriteSym);
    tmp->push_back(Token::IfSym);
    tmp->push_back(Token::WhileSym);
    tmp->push_back(Token::EndProgramSym);
    tmp->push_back(Token::EndSym);
    followSets.insert({"statement", tmp});
    //follow(<expressionlist>)
    tmp = new vector<Token>();
    tmp->push_back(Token::RParen);
    followSets.insert({"expressionlist", tmp});
    //follow(<expression list tail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::RParen);
    followSets.insert({"expressionlisttail", tmp});
    //follow(<expression>)
    tmp = new vector<Token>();
    tmp->push_back(Token::SemiColon);
    tmp->push_back(Token::Comma);
    tmp->push_back(Token::Greater);
    tmp->push_back(Token::GreaterEq);
    tmp->push_back(Token::Equal);
    tmp->push_back(Token::Diffrent);
    tmp->push_back(Token::Less);
    tmp->push_back(Token::LessEq);
    followSets.insert({"expression", tmp});
    //follow(<expressiontail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::SemiColon);
    tmp->push_back(Token::Comma);
    tmp->push_back(Token::Greater);
    tmp->push_back(Token::GreaterEq);
    tmp->push_back(Token::Equal);
    tmp->push_back(Token::Diffrent);
    tmp->push_back(Token::Less);
    tmp->push_back(Token::LessEq);
    followSets.insert({"expressiontail", tmp});
    //follow(<term>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Plus);
    tmp->push_back(Token::Minus);
    tmp->push_back(Token::SemiColon);
    tmp->push_back(Token::Comma);
    tmp->push_back(Token::Greater);
    tmp->push_back(Token::GreaterEq);
    tmp->push_back(Token::Equal);
    tmp->push_back(Token::Diffrent);
    tmp->push_back(Token::Less);
    tmp->push_back(Token::LessEq);
    followSets.insert({"term", tmp});
    //follow(<term tail>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Plus);
    tmp->push_back(Token::Minus);
    tmp->push_back(Token::SemiColon);
    tmp->push_back(Token::Comma);
    tmp->push_back(Token::Greater);
    tmp->push_back(Token::GreaterEq);
    tmp->push_back(Token::Equal);
    tmp->push_back(Token::Diffrent);
    tmp->push_back(Token::Less);
    tmp->push_back(Token::LessEq);
    followSets.insert({"termtail", tmp});
    //follow(<factor>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Multiply);
    tmp->push_back(Token::Devide);
    tmp->push_back(Token::Plus);
    tmp->push_back(Token::Minus);
    tmp->push_back(Token::SemiColon);
    tmp->push_back(Token::Comma);
    tmp->push_back(Token::Greater);
    tmp->push_back(Token::GreaterEq);
    tmp->push_back(Token::Equal);
    tmp->push_back(Token::Diffrent);
    tmp->push_back(Token::Less);
    tmp->push_back(Token::LessEq);
    followSets.insert({"factor", tmp});
    //follow(<ident>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Assign);
    tmp->push_back(Token::Colon);
    tmp->push_back(Token::Multiply);
    tmp->push_back(Token::Devide);
    tmp->push_back(Token::Plus);
    tmp->push_back(Token::Minus);
    tmp->push_back(Token::SemiColon);
    tmp->push_back(Token::Comma);
    tmp->push_back(Token::Greater);
    tmp->push_back(Token::GreaterEq);
    tmp->push_back(Token::Equal);
    tmp->push_back(Token::Diffrent);
    tmp->push_back(Token::Less);
    tmp->push_back(Token::LessEq);
    followSets.insert({"ident", tmp});
    //follow(<bool>)
    tmp = new vector<Token>();
    tmp->push_back(Token::RParen);
    followSets.insert({"bool", tmp});
    //follow(<relationop>)
    tmp = new vector<Token>();
    tmp->push_back(Token::LParen);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::IntLiteral);
    tmp->push_back(Token::RealLiteral);
    followSets.insert({"relationop", tmp});
}

void InterCodeGenerator::Match(Token T)
{

    if (this->lookahead == T)
    {
        D("Matched :");
        D_LN(scanner->getTokenName(T));
        this->lookahead = scanner->GetNextToken();
    }
    else
    {
        // cout << "ERROR on Match: Symbol: ";
        // scanner->printTokenName(T);
        // cout << " expected but ";
        // scanner->printTokenName(lookahead);
        // cout << "found" << endl;
        SyntaxError(T);
        throw new ParseException(T, lookahead);
    }
}

void InterCodeGenerator::SyntaxError(Token T)
{
    cout << "Syntax Error : on line: " << scanner->LineCount << ", at token: ";
    scanner->printTokenName(T);
    cout << endl;
    scanner->ListThisLine();
    for (int i = 0; i < scanner->LinePtr; i++)
    {
        cout << "-";
    }
    cout << "^"
         << endl
         << endl;

    compilationCorrect = false;
}

void InterCodeGenerator::panicStop()
{
    cout << endl
         << "PANIC STOP!!!" << endl
         << endl
         << endl;
    exit(1);
}

bool InterCodeGenerator::checkIfContains(vector<Token> *tokens)
{
    if (find(tokens->begin(), tokens->end(), this->lookahead) == tokens->end())
    {
        return false;
    }
    return true;
}

void InterCodeGenerator::skipUntil(vector<Token> *tokens)
{

    while (find(tokens->begin(), tokens->end(), this->lookahead) == tokens->end())
    {
        this->lookahead = scanner->GetNextToken();
        if (this->lookahead == Token::EofSym)
        {
            panicStop();
        }
    }
}
void InterCodeGenerator::skipAll(vector<Token> *tokens)
{

    while (find(tokens->begin(), tokens->end(), this->lookahead) != tokens->end())
    {
        this->lookahead = scanner->GetNextToken();
        if (this->lookahead == Token::EofSym)
        {
            panicStop();
        }
    }
}

void InterCodeGenerator::doWithPanic(void (InterCodeGenerator::*todo)(Token), Token token)
{
    try
    {
        (this->*todo)(token);
    }
    catch (ParseException *ex)
    {
        compilationCorrect = false;
        std::cerr << ex->what() << '\n';
        cout << ex->getErrorMsg();
        panicStop();
    }
}
void InterCodeGenerator::doWithPanic(void (InterCodeGenerator::*todo)())
{
    try
    {
        (this->*todo)();
    }
    catch (ParseException *ex)
    {
        compilationCorrect = false;
        std::cerr << ex->what() << '\n';
        cout << ex->getErrorMsg();
        panicStop();
    }
}

void InterCodeGenerator::doWithSkip(void (InterCodeGenerator::*todo)(Token), Token token, vector<Token> *tokens)
{
    try
    {
        (this->*todo)(token);
    }
    catch (ParseException *ex)
    {
        compilationCorrect = false;
        std::cerr << ex->what() << '\n';
        cout << ex->getErrorMsg();
        //skipping
        skipUntil(tokens);
    }
}
void InterCodeGenerator::doWithSkip(void (InterCodeGenerator::*todo)(), vector<Token> *tokens)
{
    try
    {
        (this->*todo)();
    }
    catch (ParseException *ex)
    {
        compilationCorrect = false;
        std::cerr << ex->what() << '\n';
        cout << ex->getErrorMsg();
        //skipping
        skipUntil(tokens);
    }
}

void InterCodeGenerator::parseProgram()
{
    doWithPanic(&InterCodeGenerator::Match, ProgramSym);

    doWithPanic(&InterCodeGenerator::parseName);
    doWithSkip(&InterCodeGenerator::parseOptionalDeclaration, followSets.at("optionaldeclaration"));
    doWithPanic(&InterCodeGenerator::Match, BeginSym);

    doWithSkip(&InterCodeGenerator::parseOptionalStatement, followSets.at("statementlist"));
    doWithPanic(&InterCodeGenerator::Match, EndProgramSym);
    doWithPanic(&InterCodeGenerator::Match, EofSym);
    // Match(Token::EndProgramSym);
    // Match(Token::EofSym);

    scanner->ListSymbolTable();
    if (compilationCorrect)
    {
        cout << endl
             << "Compilation Successful." << endl;
    }
    else
    {
        cout << endl
             << "ERRORS occurred!" << endl;
        exit(-1);
    }
}

void InterCodeGenerator::parseIdent()
{
    if (nazwaProgramu == ".3AC")
    {
        nazwaProgramu = this->deleteZleZnaki(scanner->tokenBuffer) + nazwaProgramu;
    }
    doWithPanic(&InterCodeGenerator::Match, Token::Id);
    
}

void InterCodeGenerator::parseName()
{
    doWithPanic(&InterCodeGenerator::parseIdent);
    doWithPanic(&InterCodeGenerator::Match, Token::SemiColon);
}

void InterCodeGenerator::parseOptionalDeclaration()
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

void InterCodeGenerator::parseDeclarationList()
{
    
    doWithSkip(&InterCodeGenerator::parseDeclaration, followSets.at("declaration"));
    if (this->lookahead == Token::VarSym) //<devlaration list tail>
    {
        parseDeclarationListTail();
    }
    else
    {
        ; //NULL
    }

    if (checkIfContains(followSets.at("declarationlist")))
    {
        
        skipUntil(followSets.at("declarationlist"));
    }
}

void InterCodeGenerator::parseDeclarationListTail()
{
    doWithSkip(&InterCodeGenerator::parseDeclaration, followSets.at("declaration"));
    if (this->lookahead == Token::VarSym) //<devlaration list tail>
    {
        parseDeclarationListTail();
    }
    else
    {
        ; //NULL
    }
}

void InterCodeGenerator::parseDeclaration()
{
    vector<Variable*> zmienne_tmp;
    Match(Token::VarSym);     //VAR
    parseIdList(false, true, &zmienne_tmp); //<id list>
    parseType(&zmienne_tmp);   //:<type>
    Match(Token::SemiColon);  //;
    for(auto& zmienna : zmienne_tmp){
        this->zmienne.push_back(zmienna);
    }
    
}

void InterCodeGenerator::parseIdList(bool sprawdzZadeklarowanie, bool niePowinnaBycZadeklarowana, vector<Variable *> *zmienne)
{
    if (sprawdzZadeklarowanie == true)
    {
        if (this->sprawdzCzyZadeklarowanaWczesniej())
        {
            panicStop();
        }
    }
    if (niePowinnaBycZadeklarowana == true) //sprawdz czy dodano nową zmienną
    {
        if (this->sprawdzCzyPonownaDeklaracja())
        {
            skipUntil(followSets.at("ident"));
        }
    }

    if (checkIfContains(this->firstSets.at("idlist")))
    {
        if (zmienne!=nullptr)
        {
            zmienne->push_back(new Variable(this->scanner->tokenBuffer));
        }
        
        doWithPanic(&InterCodeGenerator::Match, Token::Id); //<ident>
    }

    // if (this->lookahead == Token::Comma)
    // {
    parseIdListTail(sprawdzZadeklarowanie, niePowinnaBycZadeklarowana, zmienne); //<id list tail>
    // }
    // else
    // {
    //     ; //NULL
    // }
}

void InterCodeGenerator::parseIdListTail(bool sprawdzZadeklarowanie, bool niePowinnaBycZadeklarowana, vector<Variable *> *zmienne)
{
    if (checkIfContains(this->firstSets.at("idlisttail")))
    {
        doWithSkip(&InterCodeGenerator::Match, Token::Comma, followSets.at("idlisttail")); //,

        if (niePowinnaBycZadeklarowana == true) //sprawdz czy dodano nową zmienną
        {
            if (this->sprawdzCzyPonownaDeklaracja())
            {
                skipUntil(followSets.at("ident"));
            }
        }
        if (sprawdzZadeklarowanie == true)
        {
            if (this->sprawdzCzyZadeklarowanaWczesniej())
            {
                panicStop();
            }
        }

        if (checkIfContains(this->firstSets.at("idlist")))
        {
            if (zmienne != nullptr)
            {
                zmienne->push_back(new Variable(this->scanner->tokenBuffer));
            }
            doWithPanic(&InterCodeGenerator::Match, Token::Id); //<ident>
        }

        // if (this->lookahead == Token::Comma)
        // {
        parseIdListTail(sprawdzZadeklarowanie, niePowinnaBycZadeklarowana, zmienne); //<id list tail>
        // }
    }
    else
    {
        ; //NULL
    }
}

void InterCodeGenerator::parseType(vector<Variable*>* zmienne)
{
    if (this->lookahead == Token::IntSym)
    { //INTEGER
        for (auto &zmienna : *zmienne) // access by reference to avoid copying
        {
            zmienna->setType(false);
        }
        doWithPanic(&InterCodeGenerator::Match, Token::IntSym);
    }
    else
    {
        for (auto &zmienna : *zmienne) // access by reference to avoid copying
        {
            zmienna->setType(true);
        }
        doWithPanic(&InterCodeGenerator::Match, Token::RealSym);
    }
}

void InterCodeGenerator::parseOptionalStatement()
{

    if (checkIfContains(this->firstSets.at("statement")))
    {
        parseStatementList(); // <statement list>
    }
    else
    {
        ; //NULL
    }
}

// bool InterCodeGenerator::isBeginOfStatemnt(Token token)
// {
//     if (token == BeginSym || token == Token::Id || token == Token::ReadSym || token == Token::WriteSym || token == Token::IfSym || token == Token::WhileSym)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

void InterCodeGenerator::parseStatementList()
{
    vector<Token> *tmp = this->followSets.at("statementlist");
    doWithSkip(&InterCodeGenerator::parseStatement, tmp); //<statement>
    parseStatementListTail();                    //<statement list tail>
}

void InterCodeGenerator::parseStatementListTail()
{
    if (checkIfContains(this->firstSets.at("statement")))
    {
        doWithSkip(&InterCodeGenerator::parseStatement, this->followSets.at("statementlist")); //<statement>
        parseStatementListTail();                                                     //<statement list tail>
    }
    else
    { //NULL
        if (checkIfContains(this->followSets.at("expression")))
        {
            SyntaxError(this->lookahead);
            skipAll(followSets.at("expression"));
        }
        if (checkIfContains(this->firstSets.at("statementlisttail")))
        {
            parseStatementListTail();
        }
    }
}

void InterCodeGenerator::parseStatement()
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
        if (this->sprawdzCzyZadeklarowanaWczesniej())
        {
            panicStop();
        }
        Variable* z = new Variable(this->scanner->tokenBuffer); //zapisz zmienną.
        
        Match(Token::Id);

        Match(Token::Assign);
        string toAssign = parseExpression();
        Match(Token::SemiColon);

        this->zapiszAssign( z, toAssign);

    }
    else if (this->lookahead == Token::ReadSym) //READ( <id list>);
    {
        Match(Token::ReadSym);
        Match(Token::LParen);

        vector<Variable*> tmp;

        parseIdList(true, false, &tmp);
        Match(Token::RParen);
        Match(Token::SemiColon);

        for(auto zmienna : tmp){
            zapiszRead(zmienna);
        }

    }
    else if (this->lookahead == Token::WriteSym) //WRITE( <expression list>);
    {
        Match(Token::WriteSym);
        Match(Token::LParen);
        vector<string*> expressions;
        parseExpressionList(&expressions);
        Match(Token::RParen);
        Match(Token::SemiColon);
        for(auto expr : expressions){
            zapiszWrite(*expr);
        }
    }
    else if (this->lookahead == Token::IfSym) //IF(<bool>) THEN <statement>
    {
        Match(Token::IfSym);
        Match(Token::LParen);
        string endLabel = parseBool();
        Match(Token::RParen);
        Match(Token::ThenSym);
        parseStatement();
        endIF(endLabel);
    }
    else if (this->lookahead == Token::WhileSym) //WHILE(<bool>) DO <statement>
    {
        string whileLabel = startWhile();
        Match(Token::WhileSym);
        Match(Token::LParen);
        string endWhileLabel = parseBool();
        Match(Token::RParen);
        Match(Token::DoSym);
        parseStatement();

        endWhile(whileLabel, endWhileLabel);
    }
    else
    {
        this->SyntaxError(this->lookahead);
    }
}

void InterCodeGenerator::parseExpressionList(vector<string *>* expressions)
{
    string* expression = new string(parseExpression());         //<experssion>
    expressions->push_back(expression);
    parseExpressionListTail(expressions); //<expression list tail>
}

void InterCodeGenerator::parseExpressionListTail(vector<string *>* expressions)
{
    if (this->lookahead == Token::Comma) // , <expression> <expression list tail>
    {
        Match(Comma);
        string *expression = new string(parseExpression()); //<experssion>
        expressions->push_back(expression);
        parseExpressionListTail(expressions);              //<expression list tail>
    }
    else //NULL
    {
        ;
    }
}

string InterCodeGenerator::parseExpression()
{
    string toReturn ="", tail = "";
    toReturn = parseTerm();
    tail = parseExpressionTail();

    if (tail == "")
    {
        return toReturn;
    }
    else{
        string expresionRightSide = toReturn + " ";
        expresionRightSide+= tail;
        Variable *zmienna1 = Variable::findZmiennaOfId(&zmienne, toReturn);
        Variable *zmienna2 = Variable::findZmiennaOfId(&zmienne, tail.substr(2));
        if (zmienna1->getType() != zmienna2->getType())
        {
            this->mismatchError();
        }
        
        int idTMP = this->getTmp(zmienna1->getType());
        string tmp = this->tmp_zmienne[idTMP]->getID(); // weź nową zmienną tymczasową 
        Variable *zmienna = this->tmp_zmienne[idTMP];

        zapiszAssign(zmienna, expresionRightSide);
        return tmp;
    }
    
}

string InterCodeGenerator::parseExpressionTail()
{
    string toReturn = "", tail = "";
    Token operacja = Token::Null;
    if (this->checkIfContains(firstSets.at("expressiontail")))
    {
        if (this->lookahead == Token::Plus) // + | -
        {
            Match(Token::Plus);
            operacja = Token::Plus;
        }
        else if (this->lookahead == Token::Minus)
        {
            Match(Token::Minus);
            operacja = Token::Minus;
        }
    }
    else
    {
        return ""; //NULL
    }
    toReturn += parseTerm();              //<term>
    tail = parseExpressionTail();    //<expression tail>
    if (tail == "")
    {
        if (operacja== Token::Minus)
        {
            return "- " + toReturn;
            
        }
        else if (operacja == Token::Plus)
        {
            return "+ " + toReturn;
        }
        else {
            return toReturn;
        }
    }
    else{

        Variable *zmienna1 = Variable::findZmiennaOfId(&zmienne, toReturn);
        Variable *zmienna2 = Variable::findZmiennaOfId(&zmienne, tail.substr(2));
        if (zmienna1->getType() != zmienna2->getType())
        {
            this->mismatchError();
        }

        int idTMP = this->getTmp(zmienna1->getType());
        string tmp = this->tmp_zmienne[idTMP]->getID(); 
        Variable *zmienna = this->tmp_zmienne[idTMP];
        toReturn +=" ";
        zapiszAssign(zmienna, toReturn + tail );
        if (operacja == Token::Minus)
        {
            return "- " + tmp;
        }
        else if (operacja == Token::Plus)
        {
            return "+ " + tmp;
        }
        else
        {
            return tmp;
        }
    }
    
}

string InterCodeGenerator::parseTerm()
{
    string toReturn = "", tail = "";
    toReturn = parseFactor(); //<factor>
    tail = parseTermTail(); //<term tail>

    if (tail == "")
    {
        return toReturn;
    }
    else
    {
        string expresionRightSide = toReturn + " ";
        expresionRightSide += tail;

        Variable *zmienna1 = Variable::findZmiennaOfId(&zmienne, toReturn);
        Variable *zmienna2 = Variable::findZmiennaOfId(&zmienne, tail.substr(2));
        if (zmienna1->getType() != zmienna2->getType())
        {
            this->mismatchError();
        }

        int idTMP = this->getTmp(zmienna1->getType());
        string tmp = this->tmp_zmienne[idTMP]->getID(); // weź nową zmienną tymczasową 
        Variable *zmienna = this->tmp_zmienne[idTMP];

        zapiszAssign(zmienna, expresionRightSide);
        return tmp;
    }
}

string InterCodeGenerator::parseTermTail()
{
    string toReturn = "", tail = "";

    Token operacja = Token::Null; //TODO uzależnić typ zmiennej!
    if (checkIfContains(firstSets.at("termtail")))
    {
        if (this->lookahead == Token::Multiply) // *
        {
            Match(Token::Multiply);
            operacja = Token::Multiply;
        }
        else if (this->lookahead == Token::Devide) // /
        {
            Match(Token::Devide);
            operacja = Token::Devide;
        }
    }
    else
    {
        return ""; //NULL
    }

    toReturn = parseFactor();
    tail = parseTermTail();
    if (tail == "")
    {
        if (operacja == Token::Multiply)
        {
            return "* " + toReturn;
        }
        else if (operacja == Token::Devide)
        {
            return "/ " + toReturn;
        }
        else
        {
            return toReturn;
        }
    }
    else
    {

        Variable *zmienna1 = Variable::findZmiennaOfId(&zmienne, toReturn);
        Variable *zmienna2 = Variable::findZmiennaOfId(&zmienne, tail.substr(2));
        if (zmienna1->getType() != zmienna2->getType())
        {
            this->mismatchError();
        }

        int idTMP = this->getTmp(zmienna1->getType());
        string tmp = this->tmp_zmienne[idTMP]->getID(); // weź nową zmienną tymczasową 
        Variable *zmienna = this->tmp_zmienne[idTMP];

        
        toReturn += " ";
        zapiszAssign(zmienna, toReturn + tail);
        if (operacja == Token::Multiply)
        {
            return "* " + tmp;
        }
        else if (operacja == Token::Devide)
        {
            return "/ " + tmp;
        }
        else
        {
            return tmp;
        }
    }
    
}

string InterCodeGenerator::parseFactor()
{
    if (checkIfContains(firstSets.at("factor")))
    {
        if (this->lookahead == Token::LParen)
        {
            Match(Token::LParen);
            string expr = parseExpression();
            Match(Token::RParen);
            return expr;
        }
        else if (this->lookahead == Token::IntLiteral)
        {
            Match(Token::IntLiteral);
            return scanner->NumLexeme;
        }
        else if (this->lookahead == Token::RealLiteral)
        {
            Match(Token::RealLiteral);
            return scanner->NumLexeme;
        }
        else if (this->lookahead == Token::Id)
        {
            if (this->sprawdzCzyZadeklarowanaWczesniej())
            {
                panicStop();
                
            }
            string id = scanner->tokenBuffer;
            Match(Token::Id);
            return id;
        }
    }
    else
    {
        throw new ParseException(this->firstSets.at("factor"));
        
    }
    panicStop();
    return "";
}

string InterCodeGenerator::parseBool()
{
    string notLabel = getLabel();
    string idLeft = parseExpression();
    Token op = parseRelationOp();
    string idRight = parseExpression();
    generateBool(notLabel,idLeft,idRight,op);
    return notLabel;
}

Token InterCodeGenerator::parseRelationOp()
{
    if (checkIfContains(this->firstSets.at("relationop")))
    {
        if (this->lookahead == Token::Less)
        {
            Match(Token::Less);
            return Token::Less;
        }
        else if (this->lookahead == Token::Equal)
        {
            Match(Token::Equal);
            return Token::Equal;
        }
        else if (this->lookahead == Token::Greater)
        {
            Match(Token::Greater);
            return Token::Greater;
        }
        else if (this->lookahead == Token::LessEq)
        {
            Match(Token::LessEq);
            return Token::LessEq;
        }
        else if (this->lookahead == Token::Diffrent)
        {
            Match(Token::Diffrent);
            return Token::Diffrent;
        }
        else
        {
            Match(Token::GreaterEq);
            return Token::GreaterEq;
        }
    }
    else
    {
        throw new ParseException(this->firstSets.at("relationop"));
        return Token::Null;
    }
}

bool InterCodeGenerator::sprawdzCzyPonownaDeklaracja()
{
    if (scanner->czyZadeklarowanoNowaZmienna == false)
    {
        cout << "##########################"
             << "##########ERROR###########"
             << "##########################" << endl;
        cout << "Zmienna: " << scanner->getSymbolFromHashTableById(scanner->lastSymbolID).name << " została już zadeklarowana!" << endl;
        this->SyntaxError(Token::Id);
        return true;
    }
    return false;
}
bool InterCodeGenerator::sprawdzCzyZadeklarowanaWczesniej()
{
    if (scanner->czyZadeklarowanoNowaZmienna == true)
    {
        cout << "##########################"
             << "##########ERROR###########"
             << "##########################" << endl;
        cout << "Zmienna: " << scanner->getSymbolFromHashTableById(scanner->lastSymbolID).name << " nie została jeszcze zadeklarowana!" << endl;
        this->SyntaxError(Token::Id);
        return true;
    }
    return false;
}


int InterCodeGenerator::getTmp(bool type){

    int id = tmp_zmienne.size();
    string sId = "temp";
    sId += to_string(id);

    Variable* zmienna = new Variable(sId);
    zmienna->setType(type);
    this->tmp_zmienne.push_back(zmienna);
    this->zmienne.push_back(zmienna);
    return id;
}

string InterCodeGenerator::getLabel(){
    return "Label" + to_string(labelId++);
}

string InterCodeGenerator::generujTekstDeklaracjiZmiennych()
{
    stringstream tmp;
    for(auto& zmienna : zmienne){
        tmp << zmienna->getDeclaration()<<endl;
    }
    tmp.flush();
    return tmp.str();
}

void InterCodeGenerator::zapiszRead(Variable *zmienna)
{
    out << "Read "<< zmienna->getID()<<endl;
}

void InterCodeGenerator::endWhile(string startwhileLabel, string endwhileLabel)
{
    out << "J " << startwhileLabel<<endl;
    out << endwhileLabel<<":"<<endl;
}

string InterCodeGenerator::startWhile()
{
    string label = getLabel();
    out << label <<":"<< endl;
    return label;
}

void InterCodeGenerator::zapiszAssign(Variable *zmienna, string toAssign)
{

    out << zmienna->getID() << " := " << toAssign << endl;
}

void InterCodeGenerator::zapiszWrite(string expression)
{
    out << "Write " << expression << endl;
}

void InterCodeGenerator::generateBool(string label, string id1, string id2, Token op)
{
    if (op == Token::Less)
    {
        out << "JGE " << id1 << " " << id2 << " "  << label << endl;
    }
    else if (op == Token::Equal)
    {
        out << "JNE " << id1 << " " << id2 << " "  << label << endl;
    }
    else if (op == Token::Greater)
    {
        out << "JLE " << id1 << " " << id2 << " "  << label << endl;
    }
    else if (op == Token::LessEq)
    {
        out << "JG " << id1 << " " << id2 << " "  << label << endl;
    }
    else if (op == Token::Diffrent)
    {
        out << "JE " << id1 << " " << id2 << " "  << label << endl;
    }
    else if (op == Token::GreaterEq)
    {
        out << "JL " << id1 << " " << id2 << " "  << label << endl;
    }
}

void InterCodeGenerator::endIF(string endIfLabel)
{
    out << endIfLabel << ":" << endl;
}

void InterCodeGenerator::mismatchError(){
    cout << "##########################"
         << "##########ERROR###########"
         << "##########################" << endl;
    cout << "Mismatch Error!";
    this->SyntaxError(Token::Id);
}

string InterCodeGenerator::deleteZleZnaki(string str)
{
    string ret = "";
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str.at(i) != 0)
        {
            ret += str.at(i);
        }
        
    }
    return ret;
}