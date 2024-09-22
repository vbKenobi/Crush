#include <iostream> 

#include "../inc/memory.h"
#include "../inc/value.h"

ValueArray::ValueArray()
{
    count = 0; 
}

ValueArray::~ValueArray()
{}

void ValueArray::write(Value value)
{
    values.push_back(value); 
    count++; 
}