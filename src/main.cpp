#include "../inc/common.h"
#include "../inc/chunk.h"
#include "../inc/debug.h"


int main(int argc, const char* argv[]) 
{
    Chunk* test = new Chunk();  
    
    int constant = test->addConstant(1.2); 
    test->write(OP_CONSTANT, 123); 
    test->write(constant, 123);

    test->write(OP_RETURN, 123); 

    disassembleChunk(test, "test chunk"); 

    delete test; 
    return 0; 
}