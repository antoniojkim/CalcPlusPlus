
#include <list>

#include "../Expressions/FunctionExpression.h"
#include "../Expressions/FunctionExpressions/FunctionDirectory.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/OperatorExpression.h"
#include "../Expressions/OperatorExpressions/Operators.h"
#include "../Scanner/scanner.h"
#include "../Utils/exceptions.h"
#include "shuntingYard.h"

using namespace std;
using namespace Scanner;

ShuntingYard::ShuntingYard(){}

#ifdef DEBUG
ostream& operator<<(ostream& out, list<Scanner::Token*> l){
    for (auto e : l){
        out << e->lexeme << " ";
    }
    return out;
}
#endif // DEBUG

expression ShuntingYard::parse(std::list<Scanner::Token>& tokens) {

    list<Scanner::Token*> outputStack;
    list<Scanner::Token*> operatorStack;

    for (auto& token: tokens){
        switch(token.type){
            case NUM:
            case HEX:
            case BIN:
                outputStack.push_back(&token);
                continue;
            case ID:
            case FUNCTION:
            case LPAREN:
                operatorStack.push_back(&token);
                continue;
            default:
                break;
        }

        if (isOperator(token.type)){
            if (!operatorStack.empty()){
                auto type = operatorStack.back()->type;
                while((type == FUNCTION
                       || (isOperator(type) && getPrecedence(type) > getPrecedence(token.type))
                       || (isOperator(type) && getPrecedence(type) == getPrecedence(token.type) && !isRightAssociative(token.type)))
                      && type != LPAREN) {
                    outputStack.push_back(operatorStack.back());
                    operatorStack.pop_back();
                    if (operatorStack.empty()) break;
                    type = operatorStack.back()->type;
                }
            }
            operatorStack.push_back(&token);
            continue;
        }
        
        if (token.type == RPAREN){
            while(true){
                if (operatorStack.size() == 0){
                    throw Exception("Mismatched Parentheses: ')'");
                }
                Scanner::Token* topOperator = operatorStack.back();
                operatorStack.pop_back();
                if (topOperator->type == LPAREN) break;
                outputStack.push_back(topOperator);
            }
            continue;
        }

        throw Exception("Unsupported Token: '", token.lexeme, "'");
    }
    while(!operatorStack.empty()){
        outputStack.push_back(operatorStack.back());
        operatorStack.pop_back();
    }

#ifdef DEBUG
    cout << outputStack << endl;
#endif // DEBUG

    list<expression> expressionStack;
    for (auto token : outputStack){
        switch(token->type){
            case NUM:
                expressionStack.push_back(make_unique<NumExpression>(token->lexeme));
                continue;
            case HEX:
                expressionStack.push_back(make_unique<HexExpression>(token->lexeme));
                continue;
            case BIN:
                expressionStack.push_back(make_unique<BinExpression>(token->lexeme));
                continue;
            default:
                break;
        }

        if (isOperator(token->type)){
            expression expr1 = std::move(expressionStack.back());
            expressionStack.pop_back();
            if (isSingleOperator(token->type)){
                throw Exception("Unary Operator not yet supported: ", typeStrings[token->type]);
            }
            else{
                expression expr2 = std::move(expressionStack.back());
                expressionStack.pop_back();
                expressionStack.push_back(
                    make_unique<BinaryOperatorExpression>(token->type, std::move(expr2), std::move(expr1))
                );
            }
            continue;
        }
        
        if (token->type == FUNCTION){
            int functionIndex = getFunctionIndex(token->lexeme);
            if (functionIndex == -1){
                throw Exception("Invalid Function: ", token->lexeme);
            }
            if (getFunctionNumArgs(functionIndex) == 1){
                expression expr = std::move(expressionStack.back());
                expressionStack.pop_back();
                expressionStack.push_back(
                    make_unique<UnaryFunctionExpression>(functionIndex, std::move(expr))
                );
                continue;
            }
            throw Exception("Unsupported Function: ", token->lexeme);
        }

        throw Exception("Unsupported Token type found: ", typeStrings[token->type]);
    }

    if (expressionStack.size() == 1){
        expression expr = std::move(expressionStack.back());
        expressionStack.pop_back();
        return std::move(expr);
    }
    throw Exception("Expression Stack left with more than one expression");    
}
