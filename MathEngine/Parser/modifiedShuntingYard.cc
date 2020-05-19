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

ostream& operator<<(ostream& out, FixedStack<expression>& fs){
    for (auto expr : fs){
        cout << "    "; expr->print(cout) << endl;
    }
    return out;
}
ostream& operator<<(ostream& out, list<expression>& fs){
    for (auto expr : fs){
        cout << "    "; expr->print(cout) << endl;
    }
    return out;
}

expression postfix_to_expression(FixedStack<Token*>& outputStack){
    int stackSize = outputStack.size();

    list<FixedStack<expression>> expressionStacks;
    expressionStacks.emplace_back(FixedStack<expression>(stackSize));
    list<list<expression>> expressionLists;

    for (int i = 0; i < outputStack.size(); ++i, --stackSize){
        auto token = outputStack[i];
        switch(token->type){
            case NUM:
                expressionStacks.back().push(NumExpression::construct(token->lexeme));
                continue;
            case HEX:
                expressionStacks.back().push(HexExpression::construct(token->lexeme));
                continue;
            case BIN:
                expressionStacks.back().push(BinExpression::construct(token->lexeme));
                continue;
            case ID:
            case SPECIALID:
                expressionStacks.back().push(VariableExpression::construct(token->lexeme));
                continue;
            case FUNCTION:
                expressionStacks.back().push(FunctionExpression::construct(token->lexeme, expressionStacks.back().pop()));
                continue;
            case LPAREN:
            case LBRACE:
            // case LSQUARE:
                expressionStacks.emplace_back(FixedStack<expression>(stackSize));
                expressionLists.emplace_back(list<expression>());
                continue;
            case COMMA:
                expressionLists.back().emplace_back(expressionStacks.back().pop());
                if (!expressionStacks.back().empty()){
                    return InvalidExpression::construct(Exception("Top Expression Stack left with more than one expression: ','"));
                }
                continue;
            case RPAREN:
                if (!expressionStacks.back().empty()){
                    expressionLists.back().emplace_back(expressionStacks.back().pop());
                    if (!expressionStacks.back().empty()){
                        return InvalidExpression::construct(Exception("Top Expression Stack left with more than one expression: ')'"));
                    }
                }
                expressionStacks.pop_back();
                expressionStacks.back().push(TupleExpression::construct(std::move(expressionLists.back())));
                expressionLists.pop_back();
                continue;
            case RBRACE: {
                expressionLists.back().emplace_back(expressionStacks.back().pop());
                if (!expressionStacks.back().empty()){
                    return InvalidExpression::construct(Exception("Top Expression Stack left with more than one expression: '}'"));
                }
                expressionStacks.pop_back();

                list<expression> matrixElements;
                int numCols = 0;
                for (auto expr : expressionLists.back()){
                    auto matrix = expr->matrix();
                    if (matrix){
                        if (matrix->rows() != 1){
                            return InvalidExpression::construct(Exception("Matrix must be two dimensional"));
                        }
                        else if (numCols == 0){
                            numCols = matrix->cols();
                        }
                        else if (matrix->cols() != numCols){
                            return InvalidExpression::construct(Exception("Matrix expected ", numCols, " columns. Got ", matrix->cols()));
                        }
                        matrixElements.splice(matrixElements.end(), matrix->getMatrix());
                    }
                    else if (numCols == 0){
                        numCols = 1;
                    }
                    else if (numCols != 1){
                        return InvalidExpression::construct(Exception("Matrix expected ", numCols, " columns. Got 1"));
                    }
                }
                if (numCols == 1){
                    expressionStacks.back().push(MatrixExpression::construct(std::move(expressionLists.back()), 1, expressionLists.back().size()));
                }
                else {
                    expressionStacks.back().push(MatrixExpression::construct(std::move(matrixElements), expressionLists.back().size(), numCols));
                }
                expressionLists.pop_back();
                continue;
            }
            default:
                break;
        }

        if (isOperator(token->type)){
            if (expressionStacks.back().empty()){
                return InvalidExpression::construct(Exception("Insufficient Number of Arguments for Unary Operator: ", token->lexeme));
            }
            if (isSingleOperator(token->type)){
                if (token->type == EXCL){
                    expressionStacks.back().push(FunctionExpression::construct("fact", expressionStacks.back().pop()));
                }
                else if (token->type == EXCL_EXCL){
                    expressionStacks.back().push(FunctionExpression::construct("dfact", expressionStacks.back().pop()));
                }
                else {
                    return InvalidExpression::construct(Exception("Unsupported Unary Operator: ", token->lexeme));
                }
            }
            else{
                if (expressionStacks.back().size() < 2){
                    if (token->type == MINUS){
                        expressionStacks.back().push(-(expressionStacks.back().pop()));
                    }
                    else{
                        return InvalidExpression::construct(Exception("Insufficient Number of Arguments for Binary Operator: ", token->lexeme));
                    }
                }
                else{
                    expression rhs = expressionStacks.back().pop();
                    expression lhs = expressionStacks.back().pop();
                    expressionStacks.back().push(OperatorExpression::construct(token->type, lhs, rhs));
                }
            }
        }
        else{
            return InvalidExpression::construct(Exception("Unsupported Token type found: ", typeStrings[token->type]));
        }
    }

    if (expressionStacks.size() == 1 && expressionStacks.back().size() == 1){
        return expressionStacks.back().pop();
    }

    // cout << "Expression Stack: " << endl << expressionStack << endl;

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
                    token.type = FUNCTION;
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
                if (!operatorStack.empty() &&
                    (operatorStack.peek()->type == ID ||
                     operatorStack.peek()->type == SPECIALID)){
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
                if (!operatorStack.empty() &&
                    (operatorStack.peek()->type == ID ||
                     operatorStack.peek()->type == SPECIALID)){
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

#ifdef DEBUG
    cout << "Postfix:  ";
    for (auto t : outputStacks.back()){
        cout << t->lexeme << " ";
    }
    cout << endl;
#endif

    return postfix_to_expression(outputStacks.back());
}
