// cRush.h
#ifndef cRush_H
#define cRush_H

#include "error.h"
#include "scanner.h"
#include <string> 

class cRush
{
    public: 
        cRush();
        int REPL(); 
        int RunFile(std::string filePath); 
    private:
        void run(std::string source); 
        Error errorHandle;  
        Scanner scanner; 
};

#endif