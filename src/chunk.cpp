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

    if (lines.size() != 0 && line == lines[lines.size()-1].first)
    {
        lines[lines.size()-1].second += 1; 
    }
    else 
    {
        lines.push_back(make_pair(line, 1)); 
    }
    count++; 
}

int Chunk::addConstant(Value value)
{
    constants.write(value); 
    // Returns the index of the newely added constant
    return constants.getCount() - 1; 
}

int Chunk::getLine(int index)
{
    int counter = 0; 
    for(size_t i = 0; i < lines.size(); i++)
    {
        counter += lines[i].second; 
        if(index < counter)
            return lines[i].first; 
    }

    return -1; 
}