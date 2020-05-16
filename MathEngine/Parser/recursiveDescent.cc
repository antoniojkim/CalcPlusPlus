#include <utility>

#include "../Expressions/Expression.h"
#include "../Expressions/FunctionExpression.h"
#include "../Expressions/FunctionExpressions/Functions.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/MatrixExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/OperatorExpression.h"
#include "../Expressions/OperatorExpressions/Operators.h"
#include "../Expressions/TupleExpression.h"
#include "../Expressions/VariableExpression.h"
#include "../Scanner/scanner.h"
#include "../Utils/exceptions.h"
#include "../Utils/FixedStack.h"
#include "recursiveDescent.h"

using namespace std;
using namespace Scanner;

RecursiveDescent::RecursiveDescent(){}

expression toExpression(list<Token>& tokens, FixedStack<expression>& expressionStack){
    if (tokens.empty()){
        return InvalidExpression::construct(Exception("Invalid Expression."));
    }

    Token token = std::move(tokens.front());
    tokens.pop_front();
    switch(token.type){
        case NUM:
            return NumExpression::construct(token.lexeme);
        case HEX:
            return HexExpression::construct(token.lexeme);
        case BIN:
            return BinExpression::construct(token.lexeme);
        case ID: {
            if (tokens.empty() ||
                tokens.front().type == RPAREN ||
                tokens.front().type == RBRACE ||
                isOperator(tokens.front().type)){
                return VariableExpression::construct(token.lexeme);
            }
            auto expr = toExpression(tokens, expressionStack);
            if (expr->invalid()){
                return expr;
            }
            int index = Function::indexOf(token.lexeme);
            if (index != -1){
                return FunctionExpression::construct(index, expr);
            }
            return OperatorExpression::construct(STAR, VariableExpression::construct(token.lexeme), expr);
        }
        case LPAREN: {
            list<expression> tuple;
            while(true){
                if (tokens.empty()){
                    return InvalidExpression::construct(Exception("Mismatched Parentheses: ')'"));
                }
                else if (tokens.front().type == RPAREN){
                    tokens.pop_front();
                    break;
                }
                else if (tokens.front().type == COMMA){
                    tokens.pop_front();
                }
                else{
                    auto expr = toExpression(tokens, expressionStack);
                    if (expr->invalid()){
                        return expr;
                    }
                    tuple.emplace_back(expr);
                }
            }
            if (tuple.size() == 1){
                return tuple.back();
            }
            return TupleExpression::construct(std::move(tuple));
        }
        case LBRACE: {
            list<expression> matrix;
            int numCols = -1;
            while(true){
                if (tokens.empty()){
                    return InvalidExpression::construct(Exception("Mismatched Parentheses: '}'"));
                }
                else if (tokens.front().type == RBRACE){
                    tokens.pop_front();
                    break;
                }
                else if (tokens.front().type == COMMA){
                    tokens.pop_front();
                }
                else{
                    auto element = toExpression(tokens, expressionStack);
                    if (element->invalid()){
                        return element;
                    }
                    else if (element->matrix()){
                        MatrixExpression* submatrix = element->matrix();
                        if (submatrix->rows() != 1 && submatrix->cols() != 1){
                            return InvalidExpression::construct(Exception("Matrix must be two dimensional."));
                        }
                        if (numCols == -1){
                            numCols = submatrix->getMatrix().size();
                        }
                        else if (numCols != (int) submatrix->getMatrix().size()){
                            return InvalidExpression::construct(Exception("Matrix expected ", numCols, " columns. Got ", submatrix->getMatrix().size()));
                        }
                        matrix.splice(matrix.end(), submatrix->getMatrix());
                    }
                    else{
                        matrix.emplace_back(element);
                    }
                }
            }
            if (numCols == -1){
                return MatrixExpression::construct(std::move(matrix), 1, matrix.size());
            }
            return MatrixExpression::construct(std::move(matrix), matrix.size(), numCols);
        }
        case MINUS: {
            if (expressionStack.empty()){
                auto expr = toExpression(tokens, expressionStack);
                if (expr->invalid()){
                    return expr;
                }
                return FunctionExpression::construct("neg", expr);
            }
            break;
        }
        default:
            break;
    }
    if (isOperator(token.type)){
        if (isSingleOperator(token.type)){
            if (isRightAssociative(token.type)){
                auto expr = toExpression(tokens, expressionStack);
                if (expr->invalid()){
                    return expr;
                }
                return OperatorExpression::construct(token.type, expr);
            }
            else if (expressionStack.empty()){
                return InvalidExpression::construct(Exception("Insufficient Arguments for Unary Operator"));
            }
            else{
                return OperatorExpression::construct(token.type, expressionStack.pop());
            }
        }
        else if (expressionStack.empty()){
            return InvalidExpression::construct(Exception("Insufficient Arguments for Binary Operator"));
        }
        else{
            auto expr1 = expressionStack.pop();
            switch(tokens.front().type){
                case LPAREN:
                case LBRACE: {
                    auto expr2 = toExpression(tokens, expressionStack);
                    if (expr2->invalid()){
                        return expr2;
                    }
                    return OperatorExpression::construct(token.type, expr1, expr2);
                }
                default: {
                    auto expr2 = toExpression(tokens, expressionStack);
                    if (expr2->invalid()){
                        return expr2;
                    }
                    else if (expr2->operatorExpr()){
                        expr1 = OperatorExpression::construct(token.type, expr1);
                        return pivot(expr1->operatorExpr(), expr2->operatorExpr());
                    }
                    else {
                        return OperatorExpression::construct(token.type, expr1, expr2);
                    }
                }
            }
        }
    }
    return InvalidExpression::construct(Exception("Unsupported Token type found: ", typeStrings[token.type]));
}

expression RecursiveDescent::parse(std::list<Token>& tokens){
    FixedStack<expression> expressionStack(tokens.size());
    while(!tokens.empty()){
        expressionStack.push(toExpression(tokens, expressionStack));
    }

    if (expressionStack.size() == 1){
        return expressionStack.pop();
    }

    cout << "Expression Stack: " << endl;
    for (auto expr : expressionStack){
        cout << "    " << expr << endl;
    }
    return InvalidExpression::construct(Exception("Expression Stack left with more than one expression"));
}
