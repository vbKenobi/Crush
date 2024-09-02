#include "../inc/scanner.h"
#include "../inc/token.h"
#include "../inc/error.h"
#include <iostream> 
#include <string>
#include <vector> 
#include <unordered_map>

using namespace std; 

/*
Scanner Class Init Function
*/
Scanner::Scanner(string org_source, Error& handler)
{
    source = org_source; 
    errorHandle = handler;
    start = 0; 
    current = 0;  

    reservedWords["and"] = AND; 
    reservedWords["class"] = CLASS; 
    reservedWords["else"] = ELSE; 
    reservedWords["false"] = FALSE; 
    reservedWords["for"] = FOR;
    reservedWords["fun"] = FUN; 
    reservedWords["if"] = IF; 
    reservedWords["nil"] = NIL; 
    reservedWords["or"] = OR; 
    reservedWords["print"] = PRINT; 
    reservedWords["return"] = RETURN; 
    reservedWords["super"] = SUPER; 
    reservedWords["this"] = THIS; 
    reservedWords["true"] = TRUE; 
    reservedWords["var"] = VAR; 
    reservedWords["while"] = WHILE;  
}

/*
Function to handle iteration of scanner 
*/
vector<Token> Scanner::scanTokens() {
    while(!isAtEnd()) {
        start = current; 
        scanToken(); 
    }

    tokens.push_back(Token(FE, "", "", line)); 
    return tokens; 
}

void Scanner::scanToken()
{
    char c = advance(); 
    switch (c)
    {
        // Casework for single characters
        case '(': 
            addToken(LEFT_PAREN); 
            break; 
        case ')': 
            addToken(RIGHT_PAREN);  
            break; 
        case '{':
            addToken(LEFT_BRACE); 
            break; 
        case '}': 
            addToken(RIGHT_BRACE);
            break; 
        case ',': 
            addToken(COMMA); 
            break; 
        case '.': 
            addToken(DOT); 
            break; 
        case '-': 
            addToken(MINUS); 
            break; 
        case '+': 
            addToken(PLUS); 
            break; 
        case ';': 
            addToken(SEMICOLON); 
            break; 
        case '*': 
            addToken(STAR); 
            break; 
        // Casework for two characters or possible single characters
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG); 
            break; 
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL); 
            break; 
        case '<': 
            addToken(match('=') ? LESS_EQUAL : LESS); 
            break; 
        case '>': 
            addToken(match('=') ? GREATER_EQUAL : GREATER); 
            break; 
        
        // Hanlde Comments
        case '/': 
            if(match('/'))
            {
                while(peek() != '\n' && !isAtEnd())
                {
                    advance(); 
                }
            }
            else 
            {
                addToken(SLASH); 
            }
            break; 

        // Hanlde blank spaces, tabs, return and new line
        case ' ': 
            break; 
        case '\t': 
            break; 
        case '\r': 
            break; 
        case '\n': 
            line += 1; 
            break;

        // Lets handle types, such as strings, int, bool
        case '"': 
            stringHandler(); 
            break; 
        case '1': 
        case '2': 
        case '3': 
        case '4': 
        case '5': 
        case '6': 
        case '7':
        case '8': 
        case '9':
            numbericHandler(); 
            break; 

        default:
            // Handle the code for an Identifier
            if(isAlpha(c))
            {
                identifierHandler(); 
                break;
            }
            string errorMessage = "Unexpected character: " + c; 
            errorHandle.throw_error(line, errorMessage);
            break; 
    }
}

/*
Types Handlers
*/
void Scanner::stringHandler()
{
    while(peek() != '"' && !isAtEnd())
    {
        if(peek() == '\n' )
            line += 1; 
        advance(); 
    }

    if (isAtEnd())
    {
        errorHandle.throw_error(line, "Unterminated String");
        return; 
    }

    // Handle the closing "
    advance(); 
    string value = source.substr(start+1, current-start-2); 
    addToken(STRING, value); 
}

void Scanner::identifierHandler()
{
    string text = source.substr(start, current-start-1); 
    if(reservedWords.find(text) == reservedWords.begin())
    {
        addToken(reservedWords[text]); 
        return;
    }

    while(isAlphaNumeric(peek()))
    {
        advance();
    }

    addToken(ID);  
}

void Scanner::numbericHandler()
{
    while(isDigit(peek()))
        advance(); 

    if(peek() == '.' && isDigit(peekNext()))
    {
        advance(); 
        while(isDigit(peek()))
        {
            advance(); 
        }
    }
    
    addToken(NUMBER, source.substr(start, current-start)); 
}

// Move window functions
char Scanner::advance()
{
    current += 1; 
    return source[current - 1]; 
}
char Scanner::peek()
{
    if(isAtEnd())
        return '\0'; 
    return source[current]; 
}
char Scanner::peekNext()
{
    if(current + 1 >= source.length())
        return '\0'; 
    return source[current+1]; 
}

// Token functions
void Scanner::addToken(TokenType type)
{
    addToken(type, ""); 
}

void Scanner::addToken(TokenType type, string literal)
{
    string text = source.substr(start, current-start); 
    tokens.push_back(Token(type, text, literal, line));  
}

// Character based helper functions
bool Scanner::isAtEnd()
{
    return current >= source.length(); 
}

bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9'; 
}

bool Scanner::isAlpha(char c) 
{
    return (c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            c == '_'; 
}

bool Scanner::isAlphaNumeric(char c) 
{
    return isAlpha(c) || isDigit(c);
}

bool Scanner::match(char expected)
{
    if(isAtEnd())
        return false; 
    if(source[current] != expected)
        return false; 
    
    current++; 
    return true; 
}