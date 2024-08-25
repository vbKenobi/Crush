// cRush.h
#ifndef cRush_H
#define cRush_H

#include "error.h"
#include <string> 

class cRush
{
    public: 
        cRush();
        int REPL(); 
        int RunFile(std::string filePath); 
    private:
        Error errorHandle;  
};

#endif