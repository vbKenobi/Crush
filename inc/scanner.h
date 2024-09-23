#ifndef crush_scanner_h 
#define crush_scanner_h

#include "common.h"
#include <string>

enum TokenType {
    // Single Character Tokens
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN, 
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
    TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS, 
    TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,

    // One or two character tokens
    TOKEN_BANG, TOKEN_BANG_EQUAL, 
    TOKEN_EQUAL, TOKEN_EQUAL_EQUAL, 
    TOKEN_GREATER, TOKEN_GREATER_EQUAL, 
    TOKEN_LESS, TOKEN_LESS_EQUAL,

    // Literals 
    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER, 

    // Keyowrds
    TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE, 
    TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR, 
    TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
    TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE, 

    TOKEN_ERROR, 
    TOKEN_EOF
};

class Token
{
    public: 
        Token(TokenType type, int start, int length, int line, std::string message); 
        inline TokenType getTokenType() {return type;}; 
        inline int getStart() {return start;}; 
        inline int getLength() {return length;}; 
        inline int getLine() {return line;}; 
        inline std::string getMessage() {return message;}; 
    private: 
        TokenType type; 
        int start; 
        int length; 
        int line; 
        std::string message; 
};

class Scanner 
{
    public: 
        Scanner(const std::string source); 
        Token scanToken(); 

    private: 
        // Private Helper Function 
        bool isAtEnd(); 
        char advance(); 
        bool match(char exepcted); 
        char peek(); 
        char peekNext(); 
        bool isDigit(char c); 
        bool isAlpha(char c); 

        void skipWhitespace(); 
        Token string(); 
        Token number();
        Token identifier();  

        Token makeToken(TokenType type); 
        Token errorToken(std::string message);
        
        TokenType identifierType();  
        TokenType checkKeyword(int start, int length, std::string part, TokenType type);

        int start; 
        int current; 
        int line; 
        std::string source; 
};

#endif