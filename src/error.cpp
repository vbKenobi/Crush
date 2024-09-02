#include "../inc/error.h"
#include <iostream> 
#include <string>

using namespace std; 

Error::Error()
{
    hasError = true; 
}

void Error::throw_error(int line, string message)
{
    Error::report(line, "", message); 
}

void Error::report(int line, string where, string message)
{
    hasError = true; 
    cout << "[line " << line << " ] Error " << where << ": " << message << endl; 
}

bool Error::getErrorStatus()
{
    return hasError;
}

void Error::setErrorStatus(bool newStatus)
{
    hasError = newStatus;
}