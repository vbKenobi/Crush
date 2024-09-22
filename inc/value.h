#ifndef crush_value_h 
#define crush_value_h

#include "common.h"

typedef double Value; 

class ValueArray
{
    public: 
        ValueArray(); 

        void write(Value value); 
        inline int getCount() {return count;}; 
        inline std::vector<Value> getValues() {return values;}; 
        inline Value& operator[](size_t index) {return values[index];};

        ~ValueArray(); 

    private:
        int count; 
        std::vector<Value> values;  
}; 

#endif 