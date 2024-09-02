#include "../inc/cRush.h"
#include <iostream> 
#include <string> 

using namespace std;

cRush::cRush() : errorHandle(), scanner("", errorHandle)
{
}

int cRush::REPL()
{
    while(true)
    {
        cout << ">>>: "; 
        string userLine; 
        getline(cin, userLine);  

        if (userLine == "quit()")
            break; 
        else
            run(userLine);  
    }

    return 0; 
}

int cRush::RunFile(string filePath)
{
    cout << filePath << endl;
    // Parse the file into a string and run 
    // run(parsedFile); 
    
    return 0; 
}

void cRush::run(string source)
{
    Scanner tempScanner = Scanner(source, errorHandle); 
    vector<Token> tokens = tempScanner.scanTokens(); 

    for(int i = 0; i < tokens.size(); i++) {
        tokens[i].printToken(); 
    }
}