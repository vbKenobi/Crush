#include "../inc/cRush.h"
#include <iostream> 
#include <string> 

using namespace std;

cRush::cRush()
{
    errorHandle = Error(); 
}

int cRush::REPL()
{
    while(true)
    {
        cout << ">>>: "; 
        string userLine; 
        cin >> userLine; 

        if (userLine == "quit()")
            break; 
        else 
            cout << endl; 
    }

    return 0; 
}

int cRush::RunFile(string filePath)
{
    cout << filePath << endl;
    return 0; 
}