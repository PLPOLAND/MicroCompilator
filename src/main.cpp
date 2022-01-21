#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Scanner.h"
#include "Parser.hh"
#include "parserErr.hh"
#include "InterCodeGenerator.hpp"

using namespace std;


string readFile(string path){
    string program = "";
    ifstream progFile(path);
    string line = "";
    while (getline(progFile, line))
    {
        program += line;
        // cout << line << endl;
        program += '\n';
        // cout << line << endl;
        line = "";
    }
    program += EOF;
    // program[program.length() - 1] = EOF;
    return program;
}

string toLower(string s){
    for (size_t i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

int main(int argc, char const *argv[])
{
    
    cout << argc<<endl<<endl;
    string program = "";
    // program += EOF;
    ofstream* outFile = nullptr;
    if (argc == 1)
    {
        
        string line;
        getline(cin,line);
        while (toLower(line) != "end.")
        {
            program+=line;
            program+='\n';
            getline(cin,line);
        }

        program += line;
        program += '\n';
        program+=EOF;
    }
    
    if (argc == 2)//jeśli podano nazwę pliku wejściowego, wczytaj ją
    {
        program = readFile(argv[1]); //wczytaj plik wejściowy
        D("argv[1]: ");
        D_LN(argv[1]);
    }
    if (argc == 3)//jeśli podano nazwkę pliku wyjściowego podmień strumień cout na plik
    {
        program = readFile(argv[1]);//wczytaj plik wejściowy
        D("argv[1]: ");
        D_LN(argv[1]);
        D("argv[2]: ");
        D_LN(argv[2]);
        outFile = new ofstream(argv[2]);
        cout.rdbuf(outFile->rdbuf());
    }

    /************************************************
     ************Ciało scanera***********************
     ***********************************************/
    // Scanner* scanner = new Scanner();
    // scanner->scan(program);

    /************************************************
     ***********END Ciało scanera********************
     ***********************************************/

    /************************************************
     ************Ciało Parsera***********************
     ***********************************************/

    // Parser* parser = new Parser(program);
    // parser->parseProgram();

    /************************************************
     ***********END Ciało Parsera********************
     ***********************************************/
    /************************************************
     ************Ciało Parsera ERROR*****************
     ***********************************************/

    ParserErr* parser = new ParserErr(program);
    parser->parseProgram();

    /************************************************
     ***********END Ciało Parsera ERROR**************
     ***********************************************/

    /************************************************
     ************Ciało Generatora Kodu***************
     ***********************************************/

    // InterCodeGenerator* generator = new InterCodeGenerator(program);
    // generator->run();

    /************************************************
     ***********END Ciało Generatora Kodu************
     ***********************************************/

    if (outFile != nullptr)
    {
        cout.flush();
        outFile->close();//zamknij plik;
    }
    return 0;
}
