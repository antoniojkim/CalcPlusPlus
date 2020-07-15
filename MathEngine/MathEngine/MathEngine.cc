
#include <cmath>
#include <iostream>

#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/VariableExpressions/Constants.h"
#include "../Expressions/VariableExpressions/GreekLetters.h"
#include "../MathEngine.h"
#include "../Parser/modifiedShuntingYard.h"
#include "../Utils/Exception.h"
#include "Preprocessor.h"

using namespace std;
using namespace Scanner;

MathEngine::MathEngine(): parser{make_unique<ModifiedShuntingYard>()} {}

std::list<Token> MathEngine::scan(const std::string& input){
    list<Token> tokens;
    if (Scanner::scan(input, tokens)){
        return tokens;
    }
    throw Exception("Unable to scan input: ", input);
}

expression MathEngine::parse(const std::string& input){
#ifndef DEBUG
    list<Token> tokens;
#else
    tokens.clear();
#endif
    if (Scanner::scan(input, tokens)) {
        preprocess(tokens);
        return parser->parse(tokens);
    }
    throw Exception("Unable to scan input: ", input);
}
expression MathEngine::operator()(const std::string& input){
    return parse(input);
}

expression MathEngine::eval(const std::string& input){
    return eval(parse(input));
}
expression MathEngine::eval(expression inputExpr){
    try {
        auto expr = inputExpr->eval(variables);

        if (expr == VAR){
            string name = expr->repr();
            if (expr->at(0) == NONE){
                if (variables.count(name) > 0){
                    variables.erase(name);
                    throw Exception("Deleted Variable: ", name);
                }
                else{
                    throw Exception("Variable does not exist: ", name);
                }
            }
            else {
                variables[name] = expr;
            }
        }

        return expr;
    } catch(const Exception& e){
        return InvalidExpression::construct(e);
    }
}



std::string MathEngine::formatInput(const std::string& input, int& cursorPosition){
    if (input.size() >= shortestGreekLetterName){
        for (int length = min(cursorPosition, longestGreekLetterName); length >= shortestGreekLetterName; --length){
            if (!isalpha(input.at(cursorPosition - length))){
                continue;
            }
            auto subinput = input.substr(cursorPosition - length, length);
            int index = getGreekLetterNameIndex(subinput);
            if (index != -1){
                auto str = input.substr(0, cursorPosition - length) + greekLetters[index] + input.substr(cursorPosition);
                cursorPosition -= length - 1;
                return str;
            }
        }
    }
    return input;
}
std::string MathEngine::evaluateOutput(const std::string& input, const std::string& output){
    if (input.empty()){
        return "";
    }
    int index = getGreekLetterIndex(input);
    if (index != -1){
        index = getConstantIndex(greekLetterNames[index]);
        if (index != -1) {
            return std::string{constantLongValues[index]};
        }
    }
    else {
        index = getConstantIndex(input);
        if (index != -1) {
            return std::string{constantLongValues[index]};
        }
    }

    try {
        auto expr = eval(input);

        ostringstream out;

        ostringstream pretty;
        expr->print(pretty, true);
        ostringstream normal;
        expr->print(normal, false);

        if (pretty.str() != normal.str()){
            out << "= " << pretty.str() << " ";
        }
        out << "= " << normal.str();
        return out.str();
    } catch(const Exception& e){
        if (!output.empty() && output.at(0) != '`'){
            ostringstream out;
            out << "` " << output << " `" << endl;
            out << e;
            return out.str();
        }
    }

    return output;
}
