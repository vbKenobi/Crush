#include "../inc/common.h"
#include "../inc/chunk.h"
#include "../inc/debug.h"
#include "../inc/vm.h"

#include <iostream> 
#include <fstream> 
#include <sstream>
#include <stdlib.h> 
#include <string> 
using namespace std; 

static void repl(VM* vm)
{
    string userLine; 
    for (;;) 
    {
        cout << ">>>: "; 
        getline(cin, userLine); 
        
        if (userLine == "quit()")
            break; 
        else 
            vm->interpret(userLine);
    }
}

std::string readFileToString(const std::string& filePath) {
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Read the whole file into the stringstream

    return buffer.str();  // Convert the stringstream to a string
}

static void runFile(const string path, VM* vm)
{
    string source = readFileToString(path);  
    InterpretResult result = vm->interpret(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65); 
    if (result == INTERPRET_RUNTIME_ERROR) exit(70); 
}

int main(int argc, const char* argv[]) 
{
    VM* vm = new VM(); 

    if (argc == 1)
    {
        repl(vm); 
    }
    else if (argc == 2)
    {
        runFile(argv[1], vm); 
    }
    else
    {
        cout << "Usage: cRush [path]" << endl; 
        delete vm; 
        exit(64); 
    }

    delete vm;  
    return 0; 
}