#include "../inc/cRush.h"
#include "../syntax/tree.h"
#include "../syntax/visitors.h"
#include <iostream> 
#include <string> 

using namespace std;

cRush::cRush() : errorHandle(), scanner("", errorHandle)
{
}

int cRush::REPL()
{

    Expr<string>* expression = new Binary<string>(new Unary<string>(new Token(MINUS, "-", "", 1), new Literal<string>("123")), new Token(STAR, "*", "", 1), new Grouping<string>(new Literal<string>("45.67"))); 
    AstPrinter* printer = new AstPrinter(); 

    printer->print(expression);

    /*
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
    */ 
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