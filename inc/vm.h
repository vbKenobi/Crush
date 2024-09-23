#ifndef crush_vm_h 
#define crush_vm_h 

#include "chunk.h"
#include "common.h"

#include <stack> 

enum InterpretResult 
{
    INTERPRET_OK, 
    INTERPRET_COMPILE_ERROR, 
    INTERPRET_RUNTIME_ERROR,
};

class VM
{
    public: 
        VM(); 

        InterpretResult interpret(Chunk* chunk);
        InterpretResult interpret(const std::string source); 

        ~VM(); 

    private: 
        InterpretResult run(); 
        uint8_t READ_BYTE(); 
        Value READ_CONSTANT(); 

        Chunk* chunk; 
        std::vector<uint8_t>::iterator ip; 

        std::stack<Value> stackVar;
}; 

#endif