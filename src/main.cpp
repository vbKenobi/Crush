#include "../inc/cRush.h"

#include <iostream> 
#include <string> 

using namespace std; 

int main(int argc, char** argv)
{
    if( argc > 2)
    {
        cout << "Usage: ./cRush [file]" << endl; 
        return 64;
    }

    // Init our cRush object 
    cRush runtimeInstance = cRush(); 
    if (argc == 2) 
    {
        return runtimeInstance.RunFile(argv[0]); 
    }
    else 
    {
        return runtimeInstance.REPL(); 
    }
}