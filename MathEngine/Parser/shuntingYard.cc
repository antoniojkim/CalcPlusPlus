
#include <list>

#include "../Expressions/FunctionExpression.h"
#include "../Expressions/FunctionExpressions/Functions.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/OperatorExpression.h"
#include "../Expressions/OperatorExpressions/Operators.h"
#include "../Expressions/VariableExpression.h"
#include "../Scanner/scanner.h"
#include "../Utils/exceptions.h"
#include "shuntingYard.h"

using namespace std;
using namespace Scanner;

ShuntingYard::ShuntingYard(){}

ostream& operator<<(ostream& out, list<Scanner::Token*> l){
    for (auto e : l){
        out << e->lexeme << " ";
    }
    return out;
}

expression postfix_to_expression(list<Scanner::Token*>& outputStack){
    list<expression> expressionStack;
    list<expression> argumentQueue;
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
            case ID:
                expressionStack.push_back(make_unique<VariableExpression>(token->lexeme));
                continue;
            default:
                break;
        }
        
        if (token->type == FUNCTION){
            int functionIndex = getFunctionIndex(token->lexeme);
            if (functionIndex == -1){
                return make_unique<InvalidExpression>(Exception("Invalid Function: ", token->lexeme));
            }
            if (expressionStack.empty()){
                return make_unique<InvalidExpression>(Exception("Insufficient Number of Arguments for Function: ", token->lexeme));
            }
            int numArgs = getFunctionNumArgs(functionIndex);
            if (numArgs != -1 && numArgs != (int) argumentQueue.size() + 1){
                return make_unique<InvalidExpression>(Exception(
                    "Invalid Number of Arguments for Function. Expected: ", numArgs,
                    "  Got: ", argumentQueue.size() + 1
                ));
            }
            if (numArgs == 1){
                auto expr = make_unique<UnaryFunctionExpression>(functionIndex, std::move(expressionStack.back()));
                expressionStack.pop_back();
                expressionStack.push_back(std::move(expr));
            }
            else {
                argumentQueue.emplace_front(std::move(expressionStack.back()));
                expressionStack.pop_back();
                expressionStack.push_back(
                    make_unique<MultiFunctionExpression>(functionIndex, std::move(argumentQueue))
                );
                argumentQueue.clear();
            }
            continue;
        }

        if (token->type == COMMA){
            if (expressionStack.empty()){
                return make_unique<InvalidExpression>(Exception("Insufficient Number of Arguments for Function: ", token->lexeme));
            }
            argumentQueue.emplace_front(std::move(expressionStack.back()));
            expressionStack.pop_back();
            continue;
        }

        if (isOperator(token->type)){
            if (expressionStack.empty()){
                return make_unique<InvalidExpression>(Exception("Insufficient Number of Arguments for Unary Operator"));
            }
            expression expr1 = std::move(expressionStack.back());
            expressionStack.pop_back();
            if (isSingleOperator(token->type)){
                return make_unique<InvalidExpression>(Exception("Unary Operator not yet supported: ", typeStrings[token->type]));
            }
            else{
                if (expressionStack.empty()){
                    return make_unique<InvalidExpression>(Exception("Insufficient Number of Arguments for Binary Operator"));
                }
                expression expr2 = std::move(expressionStack.back());
                expressionStack.pop_back();
                expressionStack.push_back(
                    make_unique<BinaryOperatorExpression>(token->type, std::move(expr2), std::move(expr1))
                );
            }
            continue;
        }

        return make_unique<InvalidExpression>(Exception("Unsupported Token type found: ", typeStrings[token->type]));
    }

    if (expressionStack.size() == 1){
        expression expr = std::move(expressionStack.back());
        expressionStack.pop_back();
        return std::move(expr);
    }

    cout << outputStack << endl;
    return make_unique<InvalidExpression>(Exception("Expression Stack left with more than one expression"));
}

expression ShuntingYard::parse(std::list<Scanner::Token>& tokens) {

    list<Scanner::Token*> outputStack;
    list<Scanner::Token*> operatorStack;

    for (auto& token: tokens){
        switch(token.type){
            case NUM:
            case HEX:
            case BIN:
            case ID:
                outputStack.push_back(&token);
                continue;
            case COMMA:
                while(!operatorStack.empty()
                    && operatorStack.back()->type != LPAREN
                    && operatorStack.back()->type != COMMA){
                    outputStack.push_back(operatorStack.back());
                    operatorStack.pop_back();
                }
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

        return make_unique<InvalidExpression>(Exception("Unsupported Token: '", token.lexeme, "'"));
    }
    while(!operatorStack.empty()){
        outputStack.push_back(operatorStack.back());
        operatorStack.pop_back();
    }

#ifdef DEBUG
    auto expr = postfix_to_expression(outputStack);
    list<Token> other_tokens;
    for (auto t : outputStack){
        other_tokens.emplace_back(std::move(*t));
    }
    tokens.clear();
    tokens = std::move(other_tokens);
    return expr;
#else
    return postfix_to_expression(outputStack);
#endif
}
