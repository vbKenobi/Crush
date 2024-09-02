#include "../inc/token.h"
#include <iostream> 
#include <string>

using namespace std; 

Token::Token(TokenType type, string lexeme, string literal, int line)
{
    Token::type = type; 
    Token::lexeme = lexeme; 
    Token::literal = literal; 
    Token::line = line; 
}

string Token::toString()
{
    return type + " " + lexeme + " " + literal; 
}

void Token::printToken()
{
    cout << "Token type: " << type << endl; 
    cout << "Lexeme: " << lexeme << endl; 
    cout << "Literal: " << literal << endl; 
}