
#include "../MathEngine.h"
#include "../Parser/shuntingYard.h"
#include "../Utils/exceptions.h"
#include "Preprocessor.h"

#include <iostream>

using namespace std;
using namespace Scanner;

MathEngine::MathEngine(): parser{make_unique<ShuntingYard>()} {}

std::list<Token> MathEngine::scan(const std::string& input){
    list<Token> tokens;
    if (Scanner::scan(input, tokens)){
        return tokens;
    }
    throw Exception("Invalid string: ", input);
}

expression MathEngine::parse(const std::string& input){
    list<Token> tokens;
    Scanner::scan(input, tokens);
    preprocess(tokens);
    return parser->parse(tokens);
}
expression MathEngine::operator()(const std::string& input){
    return parse(input);
}
