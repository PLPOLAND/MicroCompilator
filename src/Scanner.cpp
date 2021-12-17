#include "Scanner.h"  
	
Scanner::Scanner()
{
    hashtable = new std::unordered_map<int, Symbol>();
    for (int i = 0; i < MAX_LINE_LENGTH + 1; i++)
    {
        LineBuffer[i] = 0;
    }
}
	
Scanner::~Scanner()
{
	delete hashtable;
}

void Scanner::ToLowerCase()
{

    for (int i = 0; i < LineLength; i++)
        LineBuffer[i] = tolower(LineBuffer[i]);
}

void Scanner::ListThisLine()
{
    /* produce a listing of the source program */
    
    std::cout <<std::endl;
    for (int i = 0; i < LineLength; i++)
        std::cout<< LineBuffer[i];
    std::cout <<std::endl;
}

void Scanner::GetNewLine()
/* get a new input line */
{
    LineCount++;

    LineLength = 0;
    for (int i = 0; i < MAX_LINE_LENGTH + 1; i++)//wyczyśc bufor linii
    {
        LineBuffer[i] = 0;
    }
    do
    {
        lastChar = programString[programStringPointer++];
        LineBuffer[LineLength++] = lastChar;

    } while (lastChar != EOL && lastChar != EOF && programStringPointer<=(int)programString.length());

    LineBuffer[LineLength++] = ' ';
    if (programString[programStringPointer-1] == EOF)
    {
        lastChar = EOF;
    }

    ListThisLine();

    LinePtr = -1;

    ToLowerCase();
}

void Scanner::GetNextChar(char *c)
{
    if (LinePtr + 1 >= LineLength)//jeśli linia się skończyła to pobierz kolejną
        GetNewLine();
    *c = LineBuffer[LinePtr + 1];
    LinePtr = LinePtr + 1;
}

void Scanner::PutNextChar()
{
    LinePtr = LinePtr - 1;
}

void Scanner::ClearBuffer()
{
    tokenBuffer = "";
}

void Scanner::BufferChar(char c)
{
    if (tokenBuffer == "")//if buffer is empty
        tokenBuffer = c;
    else
        tokenBuffer+= c;
}

void Scanner::LexicalError(char c)
{
    std::cout << "\n***** Lexical error: line "<<LineCount<< ":"<<LinePtr << " at : \""<< c <<"\"\n";
}

void Scanner::BufferName(char c)
{
    char Inspect;

    BufferChar(c);
    GetNextChar(&Inspect);
    while (isalnum(Inspect) || Inspect == '_' || Inspect == '.')
    {
        BufferChar(Inspect);
        GetNextChar(&Inspect);
    }
    PutNextChar();
    BufferChar(EOS);
}

int Scanner::BufferNumLiterals(char c)
{
    char Inspect;
    bool wasDot = false;
    if (c == '.') //jeśli słowo "liczbowe" zaczyna się na . to dodajemy zero na początu
    {
        BufferChar('0');
        wasDot = true;
    }
    BufferChar(c);
    GetNextChar(&Inspect);
    while (isdigit(Inspect) || Inspect == '.')
    {
        if (wasDot && Inspect == '.')//nie może być więcej niż jedna "." w zapisie liczby
        {
            LexicalError(Inspect);
        }
        BufferChar(Inspect);
        if (Inspect == '.')//jeśli zbuforowana jest "." to zapisz o tym informację
        {
            wasDot = true;
        }
        GetNextChar(&Inspect);
    }
    PutNextChar();
    if (tokenBuffer.back() == '.')//jeśli liczba kończy się kropką dodaj 0 dla poprawnej pisowani
    {
        tokenBuffer += "0";
    }
    BufferChar(EOS);
    if (wasDot)
        return 1;
    else
        return 0;
}

Token Scanner::CheckReserved()
{
    for (auto &item : *hashtable)//dla wszystkich elementów hashTable
    {
        if (tokenBuffer == item.second.name)
        {
            lastSymbolID = item.first;
            return item.second.token;
        }
        
    }
    return Id;
}

int Scanner::LookUp(std::string S)
{
    for (auto &item : *hashtable)
    {
        if (S == (item.second.name))
        {
            return item.first;
        }
        
    }

    return 0;
}

Token Scanner::GetNextToken()
{
    char CurrentChar, Inspect;

    int IdVal = NONE;
    ClearBuffer();

    while (lastChar != EOF)
    {
        GetNextChar(&CurrentChar);
        if (isspace(CurrentChar) || !isprint(CurrentChar))//pomija znaki spacji i tabulacji, oraz znaki które nie są znakami drukowalnymi
            ; 
        else if (isalpha(CurrentChar))
        {
            BufferName(CurrentChar);
            if ((IdVal = LookUp(tokenBuffer)) == 0) /* a new identifier */
                IdVal = Enter(tokenBuffer, Id);
            
            return CheckReserved();
        }
        else if (isdigit(CurrentChar))
        {
            int tmp = BufferNumLiterals(CurrentChar);
            NumLexeme = tokenBuffer;
            if (tmp == 0)
            {
                return IntLiteral;
            }
            else
            {
                return RealLiteral;
            }
        }
        else
        {
            switch (CurrentChar)
            { /* other tokens */
            case '(':
                return LParen;
            case ')':
                return RParen;
            case ';':
                return SemiColon;
            case ',':
                return Comma;
            case ':':
                GetNextChar(&Inspect);//Pobierz kolejny znak żeby sprawdzić czy to przypisanie wartości czy deklaracja nowej zmiennej
                if (Inspect == '=')
                    return Assign;
                else if (isspace(Inspect))
                {
                    GetNextChar(&Inspect);
                    if (isalpha(Inspect))
                    {
                        BufferName(Inspect);
                        if (CheckReserved() == IntSym)
                            return IntSym;
                        else if (CheckReserved() == RealSym)
                            return RealSym;
                    }
                }
                    LexicalError(CurrentChar);
                    return ErrorSym;
            case '+':
                return Plus;
            case '*':
                return Multiply;
            case '/':
                return Devide;
            case '<':
                GetNextChar(&Inspect);//zbuforuj kolejny znak żeby sprawdzić czy znak występuje samodzielnie, czy w towarzystwie
                if (Inspect == '=')
                {
                    return LessEq;
                }
                else if (Inspect == '>')
                {
                    return Diffrent;
                }
                else
                {
                    PutNextChar();
                    return Less;
                }
            case '>':
                GetNextChar(&Inspect);
                if (Inspect == '=')
                {
                    return GreaterEq;
                }
                else
                {
                    PutNextChar();
                    return Greater;
                }
            case '=':
                return Equal;
            case '-':
                GetNextChar(&Inspect);
                if (Inspect == '-')
                {
                    GetNewLine(); /* skip rest of input line */
                    break;
                }
                else
                {
                    PutNextChar();
                    return Minus;
                }
            case '.':
                BufferNumLiterals(CurrentChar);// zbuferuj liczbę REAL
                NumLexeme = tokenBuffer;
                return RealLiteral;
            default:
                LexicalError(CurrentChar);
                return ErrorSym;
            }
        }
    }
    return EofSym; /* lastChar == EOF */
}

int Scanner::Enter(std::string S, Token Code)

{
    if (hashtable->size() < MAX_SYMBOL)
    {
        if (S.back() != EOS)// jeśli dodawana nazwa nie kończy się na EOS dodajemy go...
        {
            S+=EOS;
        }
        Symbol sym(S,Code);//utwórz element listy
        int id = hashtable->size()+1;//używane do Hashowania
        lastSymbolID = (hashtable->emplace(id, sym)).first->first;

        return hashtable->size();
    }
    else
    {
        std::cout<<"Symbol Table Overflow";
        return (MAX_SYMBOL + 1);
    }
}

void Scanner::LoadKeywords()
{
    Enter("program", ProgramSym);
    Enter("begin", BeginSym);
    Enter("end.", EndProgramSym);
    Enter("end", EndSym);
    Enter("read", ReadSym);
    Enter("write", WriteSym);
    Enter("var", VarSym);
    Enter("integer", IntSym);
    Enter("real", RealSym);
    Enter("if", IfSym);
    Enter("then", ThenSym);
    Enter("while", WhileSym);
    Enter("do", DoSym);
}

void Scanner::ListSymbolTable()
{
    std::cout << "\n--------- Symbol Table ----------\n";
    for (auto &item : *hashtable)
    {
        std::cout << "-> " <<item.second.name.c_str()<<std::endl;
    }
    std::cout <<std::endl<< "Total: " << hashtable->size() << "\n ";
    std::cout <<std::endl<< "----- END Symbol Table ----------\n";

    std::cout.flush();
}

void Scanner::printOutProgramCodeWithLines(){
    int lineCount = 1;
    std::cout << lineCount++ << ": ";
    for (long unsigned int i = 0; i < programString.length(); i++)
    {
        char c = programString[i];
        if (programString[i+1] == EOF)
        {
            break;
        }
        else if (c!= '\n')
        {
            std::cout << c;
        }
        else if (c=='\n')
        {
            std::cout << c << lineCount++<< ": ";
        }
        
    }
    std::cout.flush();
}

void Scanner::printTokenName(Token token){
    std::cout << getTokenName(token);
}

std::string Scanner::getTokenName(Token token){
    switch (token)
    {
    case ProgramSym:
        return "ProgramSym";
        break;
        ///"BEGIN"
    case BeginSym:
        return "BeginSym";
        break;
        ///"END."
    case EndProgramSym:
        return "EndProgramSym";
        break;
        ///"END"
    case EndSym:
        return "EndSym";
        break;
        ///"READ"
    case ReadSym:
        return "ReadSym";
        break;
        ///"WRITE"
    case WriteSym:
        return "WriteSym";
        break;
        ///"VAR"
    case VarSym:
        return "VarSym";
        break;
        ///"IF"
    case IfSym:
        return "IfSym";
        break;
        ///"THEN"
    case ThenSym:
        return "ThenSym";
        break;
        ///"WHILE"
    case WhileSym:
        return "WhileSym";
        break;
        ///"DO"
    case DoSym:
        return "DoSym";
        break;
    case Id:
        return "Id";
        break;
        ///"INTEGER"
    case IntSym:
        return "IntSym";
        break;
    case IntLiteral:
        return "IntLiteral";
        break;
        ///"REAL"
    case RealSym:
        return "RealSym";
        break;
    case RealLiteral:
        return "RealLiteral";
        break;
        ///"+"
    case Plus:
        return "Plus";
        break;
        ///"-"
    case Minus:
        return "Minus";
        break;
        ///"*"
    case Multiply:
        return "Multiply";
        break;
        ///"/"
    case Devide:
        return "Devide";
        break;
        ///"<"
    case Less:
        return "Less";
        break;
        ///"<="
    case LessEq:
        return "LessEq";
        break;
        ///">"
    case Greater:
        return "Greater";
        break;
        ///">="
    case GreaterEq:
        return "GreaterEq";
        break;
        /// "="
    case Equal:
        return "Equal";
        break;
        ///"<>"
    case Diffrent:
        return "Diffrent";
        break;
        ///"("
    case LParen:
        return "LParen";
        break;
        ///")"
    case RParen:
        return "RParen";
        break;
        ///":="
    case Assign:
        return "Assign";
        break;
        ///";"
    case SemiColon:
        return "SemiColon";
        break;
        ///","
    case Comma:
        return "Comma";
        break;
    case EofSym:
        return "EofSym";
        break;
    case ErrorSym:
        return "ErrorSym";
        break;
    default:
        return "NOT VALID TOKEN!";
    }
}

void Scanner::scan(std::string program) 
{
    this->programString = program;//zapisz do pamięci kod programu 
    printOutProgramCodeWithLines();
    Token cur_token;

    LoadKeywords(); /* Load reserved words */
    ListSymbolTable();
    GetNewLine(); /* Read the first line */

    cur_token = GetNextToken();
    do //rób puki nie skończy się treść pliku
    {
        if (cur_token == EofSym)//sprawdź czy nie napotkano już końca pliku
            break;
        std::cout<<"<";
        printTokenName(cur_token);
        std::cout << ", ";
        if (cur_token == Id){ // jeśli napotkano token typu ID to wypisujemy nazwę ID
            std::cout << hashtable->find(lastSymbolID)->second.name.c_str();
        }
        else if (cur_token == IntLiteral || cur_token == RealLiteral) // lub jeśli jest to liczba to też ją należy wypisać.
            std::cout << NumLexeme.c_str();
        std::cout<< "> ";
        cur_token = GetNextToken();//szukamy kolejnego tokena
    } while (cur_token != EofSym);

    std::cout<<"<";
    printTokenName(cur_token);
    std::cout<<", "<<"> "; //wyupisujemy informację o znalezieniu końca pliku.

    ListSymbolTable();
}


void Scanner::addProgram(std::string program){
    this->programString = program;
    printOutProgramCodeWithLines();
}