#ifndef crush_compiler_h 
#define crush_compiler_h

#include "scanner.h"

#include <string> 

class Compiler 
{
    public: 
        Compiler();
        
        void compile(const std::string source);

        ~Compiler();
}; 

#endif