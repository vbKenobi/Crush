// error.h
#ifndef error_H
#define error_H

#include <string> 

class Error
{
    public: 
        Error();
        void throw_error(int line, std::string message);
        void report(int line, std::string where, std::string message); 
        bool getErrorStatus(); 
        void setErrorStatus(bool newStatus); 
         
    private: 
        bool hasError; 
};

#endif