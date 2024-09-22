#include <iostream> 
#include <fstream>
#include <string> 
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std; 

void writeVisitorClass(vector<string> classes, string base, string filePath)
{
    ofstream outFile; 
    outFile.open(filePath, ios::app);

    outFile << "template <typename T>" << endl; 
    outFile << "class Visitor {" << endl; 
    outFile << "public: " << endl; 

    for(int i = 0; i < classes.size(); i++) 
    {
        outFile << "\tvirtual T visit" << classes[i] << base << "(" << classes[i] << "* element) = 0;" << endl; 
    }

    outFile << "};" << endl << endl; 
    outFile.close();
}

void writeHeaderAndInclude(string filePath)
{
    ofstream outFile; 
    outFile.open(filePath); 
    
    if (outFile.is_open())
    {
        outFile << "#ifndef tree_h" << endl; 
        outFile << "#define tree_h" << endl;
        outFile << endl;

        outFile << "#include <iostream>" << endl;
        outFile << "#include <string>" << endl; 
        outFile << "#include \"../inc/token.h\"" << endl;

        outFile << endl;  
    }
}

void writeEndHeader(string filePath)
{
    ofstream outFile; 
    outFile.open(filePath, ios::app); 

    outFile << "#endif"; 
    outFile.close(); 
}

void writeBaseClass(string baseName, string filePath)
{
    ofstream outFile; 
    outFile.open(filePath, ios::app); 

    if (outFile.is_open()) 
    {
        outFile << "template <typename T>" << endl;
        outFile << "class " << baseName << " {" << endl; 
        outFile << "public: " << endl; 
        outFile << "\tvirtual std::string getType() const = 0;" << endl;
        outFile << "\tvirtual T accept(Visitor<T> visitor) = 0;" << endl;  
    
        outFile << "};" << endl;
        outFile << endl; 
    }

    outFile.close(); 
}

void writeInheritedClass(string inherit, string base, vector<pair<string, string>> arguments, string filePath)
{
    ofstream outFile; 
    outFile.open(filePath, ios::app); 

    if (outFile.is_open())
    {
        outFile << "template <typename T>" << endl;
        outFile << "class " << inherit << " : public " << base << "<T> {" << endl; 
        outFile << "public: " << endl; 

        // Write the constrcutor
        outFile << "\t//Class Constructor" << endl; 

        string param = ""; 
        string funcBody = "";
        string memberDeclration = ""; 

        for (int i = 0; i < arguments.size(); i++) 
        {
            param += arguments[i].first + " " + arguments[i].second;

            if (i != arguments.size()-1)
            {
                param += ", ";
            }

            funcBody += "\t\tthis->" + arguments[i].second +  " = " + arguments[i].second + ";\n";   
            memberDeclration += "\t" + arguments[i].first + " " + arguments[i].second + ";\n";
        }

        outFile << "\tinline " << inherit << "(" << param << ") {" << endl; 
        outFile << funcBody; 
        outFile << "\t}" << endl;
        outFile << endl;  

        outFile << "\tinline std::string getType() const override {" << endl; 
        outFile << "\t\treturn \"" << inherit << "\";" << endl; 
        outFile << "\t}" << endl; 
        outFile << endl;

        outFile << "\tinline T accept(Visitor<T> visitor) override {" << endl; 
        outFile << "\t\treturn visitor.visit" << inherit << base << "(this);" << endl; 
        outFile << "\t}" << endl; 
        outFile << endl;

        outFile << memberDeclration; 

        outFile << "};" << endl; 
        outFile << endl; 
    }

    outFile.close();
}

void extractInfo(string raw, string& name, vector<pair<string, string>>& args)
{
    size_t arrowPos = raw.find("->"); 

    name = raw.substr(0, arrowPos-1);
    name.erase(0, name.find_first_not_of(' '));
    name.erase(name.find_last_not_of(' ') + 1);

    // Extract the arguments part after "->"
    std::string argsPart = raw.substr(arrowPos + 2);
    // Remove leading/trailing spaces from argsPart
    argsPart.erase(0, argsPart.find_first_not_of(' '));

    // Regular expression to match key-value pairs
    std::regex rgx("([^\\s,]+)\\s+([^\\s,]+)(?:,\\s*)?");
    auto words_begin = std::sregex_iterator(argsPart.begin(), argsPart.end(), rgx);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string key = match[1].str();
        std::string value = match[2].str();

        args.push_back(std::make_pair(key, value));
    }
}

int main(int argc, char** argv)
{
    string filePath = "../syntax/tree.h"; 
    ifstream file("../syntax/grammar.txt"); 
    string line; 
    string base; 
    vector<string> classes; 

    writeHeaderAndInclude(filePath);

    if (file.is_open()) 
    {
        int count = 0; 
        while(getline(file, line))
        {
            if(count == 0)
            {
                base = line; 
                writeBaseClass(line, filePath); 
            }
            else
            {
                vector<pair<string, string>> arguments;
                string name; 
                extractInfo(line, name, arguments); 
                writeInheritedClass(name, base, arguments, filePath); 
                classes.push_back(name); 
            }
            count++; 
        }
        file.close(); 
    }

    writeVisitorClass(classes, base, filePath); 

    writeEndHeader(filePath); 
}