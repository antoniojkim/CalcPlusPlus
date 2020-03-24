
#include "../MathEngine.h"
#include "../Utils/exceptions.h"
#include "Preprocessor.h"

#include <iostream>

using namespace std;
using namespace Scanner;

std::list<Token> MathEngine::scan(const std::string& input){
    list<Token> tokens;
    if (Scanner::scan(input, tokens)){
        return tokens;
    }
    throw Exception("Invalid string: ", input);
}

// expression MathEngine::eval(const std::string& input){
//     // return generate_expression(input);
//     throw "Not Implemented";
// }
// expression MathEngine::eval(const std::string& input, const double& x, const double& y){
//     auto expression = eval(input);
//     // expression->setX(x);
//     // expression->setY(y);
//     return expression;
// }
// expression MathEngine::operator()(const std::string& input){
//     return eval(input);
// }
// expression MathEngine::operator()(const std::string& input, const double& x, const double& y){
//     return eval(input, x, y);
// }
