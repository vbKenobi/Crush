// scanner.h
#ifndef Scanner_H
#define Scanner_H

#include <vector> 
#include <string>
#include <unordered_map>
#include "token.h"
#include "error.h"

class Scanner
{
    public: 
        Scanner(std::string org_source, Error& handler); 
        std::vector<Token> scanTokens(); 
    private:
        bool isAtEnd(); 
        bool match(char expected);
        
        bool isDigit(char c);
        bool isAlpha(char c); 
        bool isAlphaNumeric(char c); 

        void scanToken(); 
        void addToken(TokenType type); 
        void addToken(TokenType type, std::string literal); 
        char advance(); 
        char peek(); 
        char peekNext(); 
        // Handles for default types 
        void stringHandler(); 
        void numbericHandler(); 
        void identifierHandler();
        
        std::string source; 
        std::vector<Token> tokens;
        std::unordered_map<std::string, TokenType> reservedWords; 
        Error errorHandle;  
        int start = 0; 
        int current = 0; 
        int line = 1;
};

#endif