
#include <cmath>
#include <iostream>

#include "../Expressions/InvalidExpression.h"
#include "../Expressions/VariableExpressions/Constants.h"
#include "../Expressions/VariableExpressions/GreekLetters.h"
#include "../MathEngine.h"
#include "../Parser/shuntingYard.h"
#include "../Utils/exceptions.h"
#include "Preprocessor.h"

using namespace std;
using namespace Scanner;

MathEngine::MathEngine(): parser{make_unique<ShuntingYard>()} {}

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

        if (tokens.size() >= 3 && (tokens.front().type == ID || tokens.front().type == SPECIALID)){
            auto& second = *std::next(tokens.begin());
            if (second.type == EQUALS || second.type == COLON_EQUALS || second.type == L_ARROW){
                string name = tokens.front().lexeme;
                tokens.pop_front(); tokens.pop_front();
                variables[name] = parser->parse(tokens);
                return variables[name];
            }
        }
        else if (tokens.size() == 2 && tokens.front().type == POUND){
            auto& second = *std::next(tokens.begin());
            if (second.type == ID || second.type == SPECIALID){
                if (variables.count(second.lexeme) > 0){
                    variables.erase(second.lexeme);
                    return InvalidExpression::construct(Exception("Deleted Variable: ", second.lexeme));
                }
                else{
                    return InvalidExpression::construct(Exception("Variable does not exist: ", second.lexeme));
                }
            }
        }

        return parser->parse(tokens);
    }
    return InvalidExpression::construct(Exception("Unable to scan input: ", input));
}
expression MathEngine::operator()(const std::string& input){
    return parse(input);
}

expression MathEngine::evaluate(const std::string& input){
    auto expr = parse(input);
    if (expr->invalid()){
        return expr;
    }
    return expr->evaluate(variables);
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

    auto expr = evaluate(input);
    if (!expr->invalid()){
        ostringstream out;
        out << "= ";
        if (expr->prettyprint(out)){
            out << " = ";
        }
        out << expr;
        return out.str();
    }

    if (!output.empty() && output.at(0) != '`'){
        ostringstream out;
        out << "` " << output << " `";
        return out.str();
    }

    return output;
}
