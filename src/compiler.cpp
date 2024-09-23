#include <stdio.h> 

#include "../inc/common.h"
#include "../inc/compiler.h"
#include "../inc/scanner.h"

using namespace std; 

Compiler::Compiler() {}; 

Compiler::~Compiler() {}; 


void Compiler::compile(const string source) { 

    Scanner scanner = Scanner(source); 

    int line = -1; 
    for (;;)
    {
        Token token = scanner.scanToken(); 
        if (token.getLine() != line)
        {
            printf("%4d ", token.getLine()); 
            line = token.getLine(); 
        }
        else
        {
            printf("\t| "); 
        }

        printf("%2d '%s.*s'\n", token.getTokenType(), token.getLength(), token.getStart()); 

        if (token.getTokenType() == TOKEN_EOF) break; 
    }
}