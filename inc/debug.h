#ifndef crush_debug_h
#define crush_debug_h

#include "chunk.h"
#include "string"

void disassembleChunk(Chunk* chunk, std::string name);
int disassembleInstruction(Chunk* chunk, int offset);  
static int simpleInstruction(std::string name, int offset);
static int constantInstruction(std::string, Chunk* chunk, int offset); 
void printValue(Value value); 

#endif