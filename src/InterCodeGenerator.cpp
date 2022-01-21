#include "InterCodeGenerator.hpp"


using namespace std;

InterCodeGenerator::InterCodeGenerator(string kod){
	this->kod = kod;
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
    if (check(ProgramSym))
    {
        
    }
    
}

/**
 * @brief Sprawdza czy następny wczytany token jest tym podanym w argumencie
 * 
 * @param token oczekiwany token
 * @return true - jeśli następny wczytany token jest tym podanym w argumencie
 * @return false - jeśli następny wczytany token nie jest tym podanym w argumencie
 */
bool InterCodeGenerator::check(Token token)
{
    return this->lookahead == token;
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
    tmp->push_back(Token::IntSym);
    tmp->push_back(Token::RealSym);
    followSets.insert({"relationop", tmp});
}

