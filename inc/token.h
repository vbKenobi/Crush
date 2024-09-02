// token.h
#ifndef Token_H
#define Token_H

#include <string> 

enum TokenType {
    // Single Characters 
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, 
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, 

    // One or two character tokens
    BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, 
    GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, 

    // Literals
    ID, STRING, NUMBER,

    // Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, 
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, 
    
    FE
};

class Token
{
    public: 
        Token(TokenType type, std::string lexeme, std::string literal, int line); 
        std::string toString();
        void printToken();  
    private:
        TokenType type; 
        std::string lexeme; 
        std::string literal; 
        int line;  
};

#endif