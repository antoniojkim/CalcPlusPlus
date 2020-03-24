
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

expression MathEngine::eval(const std::string& input){
    list<Token> tokens;
    Scanner::scan(input, tokens);
    return parser.parse(tokens);
}
expression MathEngine::eval(const std::string& input, const double& x, const double& y){
    auto expression = eval(input);
    // expression->setX(x);
    // expression->setY(y);
    return expression;
}
expression MathEngine::operator()(const std::string& input){
    return eval(input);
}
expression MathEngine::operator()(const std::string& input, const double& x, const double& y){
    return eval(input, x, y);
}
