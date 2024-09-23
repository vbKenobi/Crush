#include <iostream>
#include <iomanip> 
#include <stdio.h>

#include "../inc/debug.h"

using namespace std; 

void disassembleChunk(Chunk* chunk, string name)
{
    cout << "== " << name << " == " << endl; 

    for (int offset = 0; offset < chunk->getCount();)
    {
        offset = disassembleInstruction(chunk, offset); 
    }
}

int disassembleInstruction(Chunk* chunk, int offset) 
{ 
    cout << setw(4) << setfill('0') << offset << " "; 

    if (offset > 0 && chunk->getLine(offset) == chunk->getLine(offset-1))
    {
        cout << "\t| "; 
    }
    else 
    {
        printf("%4d ", chunk->getLine(offset)); 
    }

    uint8_t instruction = chunk->getCode()[offset];
    
    switch (instruction)
    {
        case OP_RETURN: 
            return simpleInstruction("OP_RETURN", offset); 
        case OP_CONSTANT: 
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_NEGATE: 
            return simpleInstruction("OP_NEGATE", offset); 
        case OP_ADD: 
            return simpleInstruction("OP_ADD", offset); 
        case OP_SUBTRACT: 
            return simpleInstruction("OP_SUBTRACT", offset); 
        case OP_MULTIPLY: 
            return simpleInstruction("OP_MULTIPLY", offset); 
        case OP_DIVIDE: 
            return simpleInstruction("OP_DIVIDE", offset); 
        default: 
            cout << "Uknown opcode" << instruction << endl; 
            return offset + 1; 
    }
}

static int simpleInstruction(string name, int offset)
{
    cout << name << endl; 
    return offset + 1;
}

static int constantInstruction(string name, Chunk* chunk, int offset)
{
    uint8_t constant = chunk->getCode()[offset+1];
    
    printf("%-16s %4d '", name.c_str(), constant); 
    printValue(chunk->getConstants()[constant]);
    cout << "\'" << endl; 
    return offset + 2; 
}


void printValue(Value value)
{
    cout << value; 
}