#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Scanner.h"
#include "Parser.hh"

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

int main(int argc, char const *argv[])
{
    
    cout << argc<<endl<<endl;
    string program = "PROGRAM assign; \n VAR a : integer;\n BEGIN \n a: = 0;\n END.";
    program += EOF;
    ofstream* outFile = nullptr;
    if (argc == 2)//jeśli podano nazwę pliku wejściowego, wczytaj ją
    {
        program = readFile(argv[1]);//wczytaj plik wejściowy
    }
    if (argc == 3)//jeśli podano nazwkę pliku wyjściowego podmień strumień cout na plik
    {
        program = readFile(argv[1]);//wczytaj plik wejściowy
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

    Parser* parser = new Parser(program);
    parser->parseProgram();

    /************************************************
     ***********END Ciało Parsera********************
     ***********************************************/

    if (outFile != nullptr)
    {
        cout.flush();
        outFile->close();//zamknij plik;
    }
    return 0;
}
