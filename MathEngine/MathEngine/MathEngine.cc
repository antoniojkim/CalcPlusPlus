
#include "../MathEngine.h"
#include "../Parser/parser.h"
#include "../Utils/exceptions.h"

using namespace std;
using namespace Scanner;

std::list<Token> MathEngine::scan(const std::string& input){
    list<Token> tokens;
    if (Scanner::scan(input, tokens)){
        return tokens;
    }
    throw Exception("Invalid string: ", input);
}

std::unique_ptr<ParseTree> MathEngine::parse(const std::string& input){
    return parser.parse(input);
}
std::unique_ptr<ParseTree> MathEngine::parse(std::list<Scanner::Token>& tokens){
    return parser.parse(tokens);
}

expression MathEngine::eval(const std::string& input){
    auto tree = parser.parse(input);
    return generate_expression(tree.get());
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
