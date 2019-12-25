
#include "../MathEngine.h"
#include "../Parser/parser.h"
#include "../Utils/exceptions.h"

using namespace std;
using namespace Scanner;

std::list<Token> MathEngine::scan(const std::string& str){
    list<Token> tokens;
    if (Scanner::scan(str, tokens)){
        return tokens;
    }
    throw Exception("Invalid string: ", str);
}
