#ifndef crush_chunk_h 
#define crush_chunk_h

#include "common.h"
#include "value.h"

enum OpCode { 
    OP_CONSTANT, 
    OP_RETURN,
};

// The Chunk Class will be a wrapper around the 
// C++ standard vector
class Chunk {
    public: 
        Chunk(); 

        void write(uint8_t byte, int line); 
        int addConstant(Value value); 
        inline int getCount() {return count;}; 
        inline std::vector<uint8_t> getCode() {return code;};
        inline std::vector<int> getLines() {return lines;};
        inline ValueArray getConstants() {return constants;};

        ~Chunk(); 

    private:
        int count;
        std::vector<uint8_t> code;
        std::vector<int> lines; 
        ValueArray constants; 
}; 

#endif