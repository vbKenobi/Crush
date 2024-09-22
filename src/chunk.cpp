#include "../inc/chunk.h"
#include "../inc/memory.h"

#include <iostream>
using namespace std; 

Chunk::Chunk() : constants()
{
    count = 0; 
}

Chunk::~Chunk()
{}

void Chunk::write(uint8_t byte, int line)
{
    code.push_back(byte);
    lines.push_back(line);  
    count++; 
}

int Chunk::addConstant(Value value)
{
    constants.write(value); 
    // Returns the index of the newely added constant
    return constants.getCount() - 1; 
}
