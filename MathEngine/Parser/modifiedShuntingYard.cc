#include <cmath>
#include <iterator>
#include <list>

#include "../Expressions/FunctionExpression.h"
#include "../Expressions/FunctionExpressions/Functions.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/MatrixExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/OperatorExpression.h"
#include "../Expressions/OperatorExpressions/Operators.h"
#include "../Expressions/TupleExpression.h"
#include "../Expressions/VariableExpression.h"
#include "../Expressions/ExpressionOperations.h"
#include "../Scanner/scanner.h"
#include "../Utils/exceptions.h"
#include "../Utils/FixedStack.h"
#include "modifiedShuntingYard.h"

using namespace std;
using namespace Scanner;

ModifiedShuntingYard::ModifiedShuntingYard(){}

expression postfix_to_expression(FixedStack<Token*>& outputStack){
    FixedStack<expression> expressionStack(outputStack.size());
    list<expression> expressionList;

    for (int i = 0; i < outputStack.size(); ++i){
        auto token = outputStack[i];
        switch(token->type){
            case NUM:
                expressionStack.push(NumExpression::construct(token->lexeme));
                continue;
            case HEX:
                expressionStack.push(HexExpression::construct(token->lexeme));
                continue;
            case BIN:
                expressionStack.push(BinExpression::construct(token->lexeme));
                continue;
            case ID:
            case SPECIALID:
                if (expressionStack.empty()){
                    expressionStack.push(VariableExpression::construct(token->lexeme));
                }
                else{
                    expressionStack.push(FunctionExpression::construct(token->lexeme, expressionStack.pop()));
                }
                continue;
            case LPAREN:
            case LBRACE:
            // case LSQUARE:
                continue;
            case COMMA:
                expressionList.emplace_back(expressionStack.pop());
                continue;
            case RPAREN:
                if (!expressionStack.empty()){
                    expressionList.emplace_back(expressionStack.pop());
                }
                expressionStack.push(TupleExpression::construct(std::move(expressionList)));
                expressionList.clear();
                continue;
            case RBRACE:{
                list<expression> matrixElements;
                int numCols = 1;
                for (auto expr : expressionList){
                    auto matrix = expr->matrix();
                    if (matrix){
                        if (matrix->rows() != 1){
                            return InvalidExpression::construct(Exception("Matrix must be two dimensional"));
                        }
                        else if (numCols == 1){
                            numCols = matrix->cols();
                        }
                        else if (matrix->cols() != numCols){
                            return InvalidExpression::construct(Exception("Matrix expected ", numCols, " columns. Got ", matrix->cols()));
                        }
                        matrixElements.splice(matrixElements.end(), matrix->getMatrix());
                    }
                    else if (numCols != 1){
                        return InvalidExpression::construct(Exception("Matrix expected ", numCols, " columns. Got 1"));
                    }
                }
                if (numCols == 1){
                    expressionStack.push(MatrixExpression::construct(std::move(expressionList), 1, expressionList.size()));
                }
                else {
                    expressionStack.push(MatrixExpression::construct(std::move(matrixElements), expressionList.size(), numCols));
                }
                expressionList.clear();
                continue;
            }
            default:
                break;
        }

        if (isOperator(token->type)){
            if (expressionStack.empty()){
                return InvalidExpression::construct(Exception("Insufficient Number of Arguments for Unary Operator: ", token->lexeme));
            }
            if (isSingleOperator(token->type)){
                if (token->type == EXCL){
                    return FunctionExpression::construct("fact", expressionStack.pop());
                }
                if (token->type == EXCL_EXCL){
                    return FunctionExpression::construct("dfact", expressionStack.pop());
                }
                return InvalidExpression::construct(Exception("Unsupported Unary Operator: ", token->lexeme));
            }
            else{
                if (expressionStack.size() < 2){
                    if (token->type == MINUS){
                        expressionStack.push(-expressionStack.pop());
                    }
                    else{
                        return InvalidExpression::construct(Exception("Insufficient Number of Arguments for Binary Operator: ", token->lexeme));
                    }
                }
                else{
                    expression rhs = expressionStack.pop();
                    expression lhs = expressionStack.pop();
                    expressionStack.push(OperatorExpression::construct(token->type, lhs, rhs));
                }
            }
        }
        else{
            return InvalidExpression::construct(Exception("Unsupported Token type found: ", typeStrings[token->type]));
        }
    }

    if (expressionStack.size() == 1){
        return expressionStack.pop();
    }

    cout << "Expression Stack: " << endl;
    for (auto expr : expressionStack){
        cout << "    "; expr->print(cout) << endl;
    }
    cout << endl;

    return InvalidExpression::construct(Exception("Expression Stack left with more than one expression"));
}

expression ModifiedShuntingYard::parse(std::list<Scanner::Token>& tokens) {
    int stackSize = tokens.size();

    FixedStack<Token*> operatorStack(stackSize);
    list<FixedStack<Token*>> outputStacks;
    outputStacks.emplace_back(FixedStack<Token*>(stackSize));

    auto current = tokens.begin();
    auto end = tokens.end();
    for (; current != end; ++current, --stackSize){
        auto& token = *current;
        switch(token.type){
            case NUM:
            case HEX:
            case BIN:
                outputStacks.back().push(&token);
                continue;
            case ID:
            case SPECIALID:
            // case FUNCTION:
                if (std::next(current) != end &&
                    isPostImplicit(std::next(current)->type)){  // Implies that the ID is a function call
                    operatorStack.push(&token);
                }
                else{
                    outputStacks.back().push(&token);
                }
                continue;
            case LPAREN:
            case LBRACE:
            // case LSQUARE:
                outputStacks.emplace_back(FixedStack<Token*>(stackSize));
                operatorStack.push(&token);
                continue;
            case COMMA: {
                while (true) {
                    if (operatorStack.size() == 0){
                        return InvalidExpression::construct(Exception("Mismatched Comma."));
                    }
                    if (operatorStack.peek()->type == LPAREN ||
                        operatorStack.peek()->type == LBRACE ||
                        operatorStack.peek()->type == COMMA){
                        auto stack = std::move(outputStacks.back());
                        outputStacks.pop_back();
                        outputStacks.back().push(operatorStack.pop());
                        outputStacks.back().push(std::move(stack));
                        break;
                    }
                    outputStacks.back().push(operatorStack.pop());
                }
                operatorStack.push(&token);
                outputStacks.emplace_back(FixedStack<Token*>(stackSize));
                continue;
            }
            case RPAREN: {
                while (true) {
                    if (operatorStack.size() == 0){
                        return InvalidExpression::construct(Exception("Mismatched Parentheses: ')'"));
                    }
                    if (operatorStack.peek()->type == COMMA ||
                        outputStacks.back().empty()){
                        auto stack = std::move(outputStacks.back());
                        outputStacks.pop_back();
                        outputStacks.back().push(operatorStack.pop());
                        outputStacks.back().push(std::move(stack));
                        outputStacks.back().push(&token);
                        break;
                    }
                    if (operatorStack.peek()->type == LPAREN){
                        operatorStack.pop();
                        auto stack = std::move(outputStacks.back());
                        outputStacks.pop_back();
                        outputStacks.back().push(std::move(stack));
                        break;
                    }
                    outputStacks.back().push(operatorStack.pop());
                }
                if (operatorStack.peek()->type == ID ||
                    operatorStack.peek()->type == SPECIALID){
                    outputStacks.back().push(operatorStack.pop());
                }
                continue;
            }
            case RBRACE: {
                while (true) {
                    if (operatorStack.size() == 0){
                        return InvalidExpression::construct(Exception("Mismatched Parentheses: '}'"));
                    }
                    if (operatorStack.peek()->type == COMMA ||
                        operatorStack.peek()->type == LBRACE){
                        auto stack = std::move(outputStacks.back());
                        outputStacks.pop_back();
                        outputStacks.back().push(operatorStack.pop());
                        outputStacks.back().push(std::move(stack));
                        outputStacks.back().push(&token);
                        break;
                    }
                    outputStacks.back().push(operatorStack.pop());
                }
                continue;
            }
            default:
                break;
        }

        if (isOperator(token.type)){
            if (!operatorStack.empty()){
                auto type = operatorStack.peek()->type;
                while((type == FUNCTION
                    || (isOperator(type) && getPrecedence(type) > getPrecedence(token.type))
                    || (isOperator(type) && getPrecedence(type) == getPrecedence(token.type) && !isRightAssociative(token.type)))
                    && type != LPAREN) {
                    outputStacks.back().push(operatorStack.pop());
                    if (operatorStack.empty()) break;
                    type = operatorStack.peek()->type;
                }
            }
            operatorStack.push(&token);
        }
        else{
            return InvalidExpression::construct(Exception("Unsupported Token: '", token.lexeme, "'"));
        }
    }
    while(outputStacks.size() > 1){
        auto stack = std::move(outputStacks.back());
        outputStacks.pop_back();
        outputStacks.back().push(std::move(stack));
    }
    while(!operatorStack.empty()){
        outputStacks.back().push(operatorStack.pop());
    }

// #ifdef DEBUG
    cout << "Postfix:  ";
    for (auto t : outputStacks.back()){
        cout << t->lexeme << " ";
    }
    cout << endl;
// #endif

    return postfix_to_expression(outputStacks.back());
}
