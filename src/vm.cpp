#include "../inc/vm.h"
#include "../inc/debug.h"

#include <iostream>

using namespace std; 

VM::VM()
{
    chunk = nullptr; 
}

VM::~VM()
{

}

InterpretResult VM::interpret(Chunk* chunk)
{
    this->chunk = chunk;
    this->ip = this->chunk->getRefCode(); 

    return run(); 
}

uint8_t VM::READ_BYTE()
{
    uint8_t inst = *ip; 
    ip++; 
    return inst; 
}

Value VM::READ_CONSTANT()
{
    return chunk->getConstants()[READ_BYTE()]; 
}

InterpretResult VM::run()
{   
    #ifdef DEBUG_TRACE_EXECUTION 
        // Does the verbose printing of the stack
        stack<Value> tempStack = stackVar; 
        vector<Value> elements; 
        while(!tempStack.empty())
        {
            elements.push_back(tempStack.top()); 
            tempStack.pop(); 
        }
        printf("            "); 
        for(int i = 0; i < elements.size(); i++)
        {
            printf("[ "); 
            printValue(elements[i]); 
            printf(" ]"); 
        }
        cout << endl; 

        disassembleInstruction(chunk, (int)(ip - chunk->getRefCode()));

    #endif

    #define BINARY_OP(op) \ 
        do { \
            double b = stackVar.top(); \
            stackVar.pop(); \
            double a = stackVar.top(); \
            stackVar.pop(); \
            stackVar.push(a op b); \ 
        } while (false)

    for (;;) 
    {
        uint8_t instruction = READ_BYTE();  
        switch (instruction)
        {
            case OP_CONSTANT: 
            {
                Value constant = READ_CONSTANT();
                stackVar.push(constant); 
                break; 
            }
            case OP_ADD: BINARY_OP(+); break; 
            case OP_SUBTRACT: BINARY_OP(-); break; 
            case OP_MULTIPLY: BINARY_OP(*); break; 
            case OP_DIVIDE: BINARY_OP(/); break; 
            case OP_NEGATE: 
            {   
                Value temp = stackVar.top(); 
                stackVar.pop(); 
                stackVar.push(-temp);
                break; 
            }
            case OP_RETURN:
            {
                printValue(stackVar.top()); 
                stackVar.pop();
                cout << endl;  
                return INTERPRET_OK; 
            } 
        }
    }

    #undef BINARY_OP
}