#include "ParserErr.hh"

ParserErr::ParserErr(std::string program)
{

    scanner = new Scanner();
    scanner->addProgram(program);
    scanner->LoadKeywords();
    scanner->ListSymbolTable();
    scanner->GetNewLine();
    lookahead = scanner->GetNextToken();
    
    makeFirstSets();
    for (std::pair<std::string, vector<Token>*> element : firstSets)
    {
        // D(endl<< "first("<<element.first << "): " <<endl);
        // for (unsigned int i = 0; i < element.second->size(); i++)
        // {
        //     D("- "<<Scanner::getTokenName(element.second->at(i))<<endl);
        // }
        
    }
	makeFollowSets();
    for (std::pair<std::string, vector<Token>*> element : followSets)
    {
        // D(endl<< "follow("<<element.first << "): " <<endl);
        // for (unsigned int i = 0; i < element.second->size(); i++)
        // {
        //     D("- "<<Scanner::getTokenName(element.second->at(i))<<endl);
        // }
        
    }

}
	
ParserErr::~ParserErr()
{
	delete scanner;
}

void ParserErr::makeFirstSets(){
    vector<Token>* tmp;

    //first(<program>)
    tmp = new vector<Token>();
    tmp->push_back(Token::ProgramSym);
    firstSets.insert({"program",tmp});
    //first(<name>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Id);
    firstSets.insert({"name",tmp});
    //first(<optionalDeclaration>)
    tmp = new vector<Token>();
    tmp->push_back(Token::VarSym);
    tmp->push_back(Token::Null);
    firstSets.insert({"optionalDeclaration",tmp});
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
    tmp->push_back(Token::IntSym);
    tmp->push_back(Token::RealSym);
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
    tmp->push_back(Token::IntSym);
    tmp->push_back(Token::RealSym);
    firstSets.insert({"factor", tmp});
    //first(<ident>)
    tmp = new vector<Token>();
    tmp->push_back(Token::Id);
    firstSets.insert({"ident", tmp});
    //first(<bool>)
    tmp = new vector<Token>();
    tmp->push_back(Token::LParen);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::IntSym);
    tmp->push_back(Token::RealSym);
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
void ParserErr::makeFollowSets(){
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
    tmp->push_back(Token::IntSym);//ponieważ scanner rozpoznaje :INT od razu jako INTSYM zamiast najpierw ":", a później INTSYM  
    tmp->push_back(Token::RealSym);//ponieważ scanner rozpoznaje :FLOAT od razu jako INTSYM zamiast najpierw ":", a później INTSYM  
    followSets.insert({"ident", tmp});
    //follow(<bool>)
    tmp = new vector<Token>();
    tmp->push_back(Token::RParen);
    followSets.insert({"bool", tmp});
    //follow(<relationop>)
    tmp = new vector<Token>();
    tmp->push_back(Token::LParen);
    tmp->push_back(Token::Id);
    tmp->push_back(Token::IntSym);
    tmp->push_back(Token::RealSym);
    followSets.insert({"relationop", tmp});
}


void ParserErr::Match(Token T)
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

void ParserErr::SyntaxError(Token T)
{
    cout << "Syntax Error : on line: " << scanner->LineCount << ", at token: ";
    scanner->printTokenName(T);
    cout << endl;
    scanner->ListThisLine();
    for (int i = 0; i < scanner->LinePtr; i++)
    {
        cout<< "-";
    }
    cout << "^" 
         << endl
         << endl;

    compilationCorrect = false;

    
}

void ParserErr::panicStop(){
    cout << endl
         << "PANIC STOP!!!" << endl
         << endl
         << endl;
    exit(1);
}


bool ParserErr::checkIfContains(vector<Token> * tokens){
    if (find(tokens->begin(), tokens->end(), this->lookahead) == tokens->end())
    {
        return false;
    }
    return true;
}

void ParserErr::skipUntil(vector<Token> *tokens){

    while (find(tokens->begin(), tokens->end(), this->lookahead) == tokens->end())
    {
        this->lookahead = scanner->GetNextToken();
        if (this->lookahead == Token::EofSym)
        {
            panicStop();
        }
    }
}
void ParserErr::skipAll(vector<Token> *tokens){

    while (find(tokens->begin(), tokens->end(), this->lookahead) != tokens->end())
    {
        this->lookahead = scanner->GetNextToken();
        if (this->lookahead == Token::EofSym)
        {
            panicStop();
        }
    }
}


void ParserErr::doWithPanic(void (ParserErr::*todo)(Token), Token token){
    try
    {
        (this->*todo)(token);
    }
    catch(ParseException* ex)
    {
        compilationCorrect = false;
        std::cerr << ex->what() << '\n';
        cout<<ex->getErrorMsg();
        panicStop();
    }
    
}
void ParserErr::doWithPanic(void (ParserErr::*todo)()){
    try
    {
        (this->*todo)();
    }
    catch(ParseException* ex)
    {
        compilationCorrect = false;
        std::cerr << ex->what() << '\n';
        cout<<ex->getErrorMsg();
        panicStop();
    }
    
}

void ParserErr::doWithSkip(void (ParserErr::*todo)(Token), Token token, vector<Token> *tokens)
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
void ParserErr::doWithSkip(void (ParserErr::*todo)(), vector<Token> *tokens)
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


void ParserErr::parseProgram()
{
    doWithPanic(&ParserErr::Match, ProgramSym);

    doWithPanic(&ParserErr::parseName);
    doWithSkip(&ParserErr::parseOptionalDeclaration,followSets.at("optionaldeclaration"));
    doWithPanic(&ParserErr::Match, BeginSym);
    
    doWithSkip(&ParserErr::parseOptionalStatement,followSets.at("statementlist"));
    doWithPanic(&ParserErr::Match, EndProgramSym);
    doWithPanic(&ParserErr::Match, EofSym);
    // Match(Token::EndProgramSym);
    // Match(Token::EofSym);

    scanner->ListSymbolTable();
    if (compilationCorrect)
    {
        cout << endl
             << "Compilation Successful." << endl;
    }
    else{
        cout << endl
             << "ERRORS occurred!"<< endl;
             exit(-1);
    }
    
}

void ParserErr::parseIdent()
{
    doWithPanic(&ParserErr::Match, Token::Id);
}

void ParserErr::parseName()
{
    doWithPanic(&ParserErr::parseIdent);
    doWithPanic(&ParserErr::Match, Token::SemiColon);
}

void ParserErr::parseOptionalDeclaration()
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

void ParserErr::parseDeclarationList()
{
    doWithSkip(&ParserErr::parseDeclaration, followSets.at("declaration"));
    if (this->lookahead == Token::VarSym) //<devlaration list tail>
    {
        parseDeclarationListTail();
    }
    else
    {
        ; //NULL
    }
    
    if(checkIfContains(followSets.at("declarationlist"))){
        //TODO?
        skipUntil(followSets.at("declarationlist"));
    }
    

}

void ParserErr::parseDeclarationListTail()
{
    doWithSkip(&ParserErr::parseDeclaration,followSets.at("declaration"));
    if (this->lookahead == Token::VarSym) //<devlaration list tail>
    {
        parseDeclarationListTail();
    }
    else
    {
        ; //NULL
    }
}

void ParserErr::parseDeclaration()
{
    Match(Token::VarSym);     //VAR
    parseIdList(false, true); //<id list>
    parseType();              //:<type>
    Match(Token::SemiColon);  //;
}

void ParserErr::parseIdList(bool sprawdzZadeklarowanie, bool niePowinnaBycZadeklarowana)
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
        if(this->sprawdzCzyPonownaDeklaracja()){
            skipUntil(followSets.at("ident"));
        }
    }

    if (checkIfContains(this->firstSets.at("idlist")))
    {
        doWithPanic(&ParserErr::Match,Token::Id); //<ident>
    }
    

    // if (this->lookahead == Token::Comma)
    // {
        parseIdListTail(sprawdzZadeklarowanie, niePowinnaBycZadeklarowana); //<id list tail>
    // }
    // else
    // {
    //     ; //NULL
    // }
}

void ParserErr::parseIdListTail(bool sprawdzZadeklarowanie, bool niePowinnaBycZadeklarowana)
{
    if (checkIfContains(this->firstSets.at("idlisttail")))
    {
        doWithSkip(&ParserErr::Match,Token::Comma,followSets.at("idlisttail")); //,

        if (niePowinnaBycZadeklarowana == true) //sprawdz czy dodano nową zmienną
        {
            if (this->sprawdzCzyPonownaDeklaracja())
            {
                skipUntil(followSets.at("ident"));
            }
        }
        if (sprawdzZadeklarowanie == true)
        {
            if(this->sprawdzCzyZadeklarowanaWczesniej()){
                panicStop();
            }
        }

        if (checkIfContains(this->firstSets.at("idlist")))
        {
            doWithPanic(&ParserErr::Match, Token::Id); //<ident>
        }

                // if (this->lookahead == Token::Comma)
                // {
                parseIdListTail(sprawdzZadeklarowanie, niePowinnaBycZadeklarowana); //<id list tail>
        // }
    }
    else
    {
        ; //NULL
    }
    
}

void ParserErr::parseType()
{
    if (this->lookahead == Token::IntSym)
    { //INTEGER
        doWithPanic(&ParserErr::Match, Token::IntSym);
    }
    else
        doWithPanic(&ParserErr::Match, Token::RealSym);
}

void ParserErr::parseOptionalStatement()
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

// bool ParserErr::isBeginOfStatemnt(Token token)
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

void ParserErr::parseStatementList()
{
    vector<Token> *tmp = this->followSets.at("statementlist");
    doWithSkip(&ParserErr::parseStatement, tmp); //<statement>
    parseStatementListTail(); //<statement list tail>
}

void ParserErr::parseStatementListTail()
{
    if (checkIfContains(this->firstSets.at("statement")))
    {
        doWithSkip(&ParserErr::parseStatement, this->followSets.at("statementlist")); //<statement>
        parseStatementListTail(); //<statement list tail>
    }
    else
    { //NULL
        if(checkIfContains(this->followSets.at("expression"))){
            SyntaxError(this->lookahead);
            skipAll(followSets.at("expression"));
        }
        if (checkIfContains(this->firstSets.at("statementlisttail")))
        {
            parseStatementListTail();
        }
    }
}

void ParserErr::parseStatement()
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
        if(this->sprawdzCzyZadeklarowanaWczesniej()){
            panicStop();
        }
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
    else
    {
        this->SyntaxError(this->lookahead);
    }
}

void ParserErr::parseExpressionList()
{
    parseExpression();         //<experssion>
    parseExpressionListTail(); //<expression list tail>
}

void ParserErr::parseExpressionListTail()
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

void ParserErr::parseExpression()
{
    parseTerm();
    parseExpressionTail();
}

void ParserErr::parseExpressionTail()
{
    if (this->checkIfContains(firstSets.at("expressiontail")))
    {
        if (this->lookahead == Token::Plus) // + | -
        {
            Match(Token::Plus);
        }
        else if (this->lookahead == Token::Minus)
        {
            Match(Token::Minus);
        }
    }
    else
    {
        return; //NULL
    }

    parseTerm();           //<term>
    parseExpressionTail(); //<expression tail>
}

void ParserErr::parseTerm()
{
    parseFactor();   //<factor>
    parseTermTail(); //<term tail>
}

void ParserErr::parseTermTail()
{
    if (checkIfContains(firstSets.at("termtail")))
    {
        if (this->lookahead == Token::Multiply) // *
        {
            Match(Token::Multiply);
        }
        else if (this->lookahead == Token::Devide) // /
        {
            Match(Token::Devide);
        }
    }
    else
    {
        return; //NULL
    }

    parseFactor();
    parseTermTail();
}

void ParserErr::parseFactor()
{
    if(checkIfContains(firstSets.at("factor"))){
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
            if (this->sprawdzCzyZadeklarowanaWczesniej())
            {
                panicStop();
            }
            Match(Token::Id);
        }
    }
    else{
        throw new ParseException(this->firstSets.at("factor"));
    }
}

void ParserErr::parseBool()
{
    parseExpression();
    parseRelationOp();
    parseExpression();
}

void ParserErr::parseRelationOp()
{
    if (checkIfContains(this->firstSets.at("relationop"))){
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
    else{
        throw new ParseException(this->firstSets.at("relationop"));
    }
}

bool ParserErr::sprawdzCzyPonownaDeklaracja()
{
    if (scanner->czyZadeklarowanoNowaZmienna == false)
    {
        cout << "##########################"
             << "ERROR"
             << "##########################" << endl;
        cout << "Zmienna: " << scanner->getSymbolFromHashTableById(scanner->lastSymbolID).name << " została już zadeklarowana!" << endl;
        this->SyntaxError(Token::Id);
        return true;
    }
    return false;
}
bool ParserErr::sprawdzCzyZadeklarowanaWczesniej()
{
    if (scanner->czyZadeklarowanoNowaZmienna == true)
    {
        cout << "##########################"
             << "ERROR"
             << "##########################" << endl;
        cout << "Zmienna: " << scanner->getSymbolFromHashTableById(scanner->lastSymbolID).name << " nie została jeszcze zadeklarowana!" << endl;
        this->SyntaxError(Token::Id);
        return true;
    }
    return false;
}