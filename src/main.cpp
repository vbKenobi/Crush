#include "../inc/common.h"
#include "../inc/chunk.h"
#include "../inc/debug.h"
#include "../inc/vm.h"


int main(int argc, const char* argv[]) 
{
    VM* vm = new VM(); 
    Chunk* test = new Chunk();  
    
    int constant = test->addConstant(1.2); 
    test->write(OP_CONSTANT, 123); 
    test->write(constant, 123);
    
    constant = test->addConstant(3.4); 
    test->write(OP_CONSTANT, 123); 
    test->write(constant, 123); 

    test->write(OP_ADD, 123); 

    constant = test->addConstant(5.6); 
    test->write(OP_CONSTANT, 123); 
    test->write(constant, 123); 

    test->write(OP_DIVIDE, 123); 

    test->write(OP_NEGATE, 123); 
    test->write(OP_RETURN, 123);

    // disassembleChunk(test, "test chunk"); 
    vm->interpret(test); 

    delete vm; 
    delete test; 
    return 0; 
}