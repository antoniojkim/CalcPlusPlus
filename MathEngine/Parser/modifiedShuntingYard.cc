#include <cmath>
#include <iterator>
#include <list>

#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/FunctionExpression.h"
#include "../Expressions/MatrixExpression.h"
#include "../Expressions/NullExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/TupleExpression.h"
#include "../Expressions/VariableExpression.h"
#include "../Functions/Functions.h"
#include "../Functions/Operators.h"
#include "../Scanner/scanner.h"
#include "../Utils/Exception.h"
#include "../Utils/FixedStack.h"
#include "modifiedShuntingYard.h"

// #define PRINT_POSTFIX

using namespace std;
using namespace Operators;
using namespace Scanner;

ModifiedShuntingYard::ModifiedShuntingYard(){}

ostream& operator<<(ostream& out, FixedStack<expression>& fs){
    for (auto expr : fs){
        cout << "    "; expr->print(cout) << endl;
    }
    return out;
}
ostream& operator<<(ostream& out, list<FixedStack<expression>>& fs){
    for (auto& stack : fs){
        cout << "---------------------------" << endl;
        for (auto expr : stack){
            cout << "    "; expr->print(cout) << endl;
        }
    }
    return out;
}

expression postfix_to_expression(FixedStack<Token*>& outputStack){
    int stackSize = outputStack.size();

    list<FixedStack<expression>> expressionStacks;
    expressionStacks.emplace_back(FixedStack<expression>(stackSize));
    list<list<expression>> expressionLists;

    for (unsigned int i = 0; i < outputStack.size(); ++i, --stackSize){
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
            case NONE:
                expressionStacks.back().push(NullExpression::construct());
                continue;
            case ID:
            case SPECIALID:
                expressionStacks.back().push(VariableExpression::construct(token->lexeme));
                continue;
            case FUNCTION:
                if (expressionStacks.back().empty()){
                    throw Exception("Function '", token->lexeme, "' found no argument");
                }
                expressionStacks.back().push(FunctionExpression::construct(token->lexeme, expressionStacks.back().pop()));
                continue;
            case LPAREN:
            case LBRACE:
            // case LSQUARE:
                expressionStacks.emplace_back(FixedStack<expression>(stackSize));
                expressionLists.emplace_back(list<expression>());
                continue;
            case COMMA:
                if (expressionStacks.back().empty()){
                    throw Exception("comma separator found no preceding expression");
                }
                expressionLists.back().emplace_back(expressionStacks.back().pop());
                if (!expressionStacks.back().empty()){
                    cout << "Top Expression Stack: " << expressionStacks.back() << endl;
                    throw Exception("Top Expression Stack left with more than one expression: ','");
                }
                continue;
            case RPAREN:
                if (!expressionStacks.back().empty()){
                    expressionLists.back().emplace_back(expressionStacks.back().pop());
                    if (!expressionStacks.back().empty()){
                        throw Exception("Top Expression Stack left with more than one expression: ')'");
                    }
                }
                expressionStacks.pop_back();
                expressionStacks.back().push(TupleExpression::construct(expressionLists.back()));
                expressionLists.pop_back();
                continue;
            case RBRACE: {
                if (!expressionStacks.back().empty()){
                    expressionLists.back().emplace_back(expressionStacks.back().pop());
                    if (!expressionStacks.back().empty()){
                        throw Exception("Top Expression Stack left with more than one expression: '}'");
                    }
                }
                expressionStacks.pop_back();

                vector<expression> matrixElements;
                matrixElements.reserve(expressionLists.back().size());
                size_t numRows = expressionLists.back().size();
                size_t numCols = 0;
                for (auto matrix : expressionLists.back()){
                    if (matrix == MATRIX){
                        if (matrix->shape(0) != 1){
                            throw Exception("Matrix must be two dimensional");
                        }
                        else if (numCols == 0){
                            numCols = matrix->shape(1);
                            matrixElements.reserve(expressionLists.back().size() * numCols);
                        }
                        else if (matrix->shape(1) != numCols){
                            throw Exception("Matrix expected ", numCols, " columns. Got ", matrix->shape(1));
                        }
                        for (auto e : *matrix){ matrixElements.emplace_back(e); }
                    }
                    else if (numCols == 0){
                        numCols = 1;
                        matrixElements.emplace_back(matrix);
                    }
                    else if (numCols != 1){
                        throw Exception("Matrix expected ", numCols, " columns. Got 1");
                    }
                    else{
                        matrixElements.emplace_back(matrix);
                    }
                }
                if (numCols == 1){
                    expressionStacks.back().push(MatrixExpression::construct(std::move(matrixElements), 1, numRows));
                }
                else {
                    expressionStacks.back().push(MatrixExpression::construct(std::move(matrixElements), numRows, numCols));
                }
                expressionLists.pop_back();
                continue;
            }
            default:
                break;
        }

        if (isOperator(token->type)){
            if (expressionStacks.back().empty()){
                throw Exception("Insufficient Number of Arguments for Unary Operator: ", token->lexeme);
            }
            if (isSingleOperator(token->type)){
                switch(token->type){
                    case EXCL:
                        expressionStacks.back().push(FunctionExpression::construct("fact", expressionStacks.back().pop()));
                        break;
                    case EXCL_EXCL:
                        expressionStacks.back().push(FunctionExpression::construct("dfact", expressionStacks.back().pop()));
                        break;
                    case APOSTROPHE:
                        expressionStacks.back().push(FunctionExpression::construct("diff", expressionStacks.back().pop()));
                        break;
                    case ELLIPSIS:
                        expressionStacks.back().push(VarArgsExpression::construct(expressionStacks.back().pop()));
                        break;
                    default:
                        throw Exception("Unsupported Unary Operator: ", token->lexeme);
                }
            }
            else{
                if (expressionStacks.back().size() < 2){
                     throw Exception("Insufficient Number of Arguments for Binary Operator: ", token->lexeme);
                }

                expression rhs = expressionStacks.back().pop();
                expression lhs = expressionStacks.back().pop();
                expressionStacks.back().push(FunctionExpression::construct(token->lexeme, {lhs, rhs}));
            }
        }
        else{
            throw Exception("Unsupported Token type found: ", typeStrings[token->type]);
        }
    }

    if (expressionStacks.size() == 1 && expressionStacks.back().size() == 1){
        return expressionStacks.back().pop();
    }

    // cout << "Expression Stack: " << expressionStacks.size() << endl << expressionStacks << endl;

    throw Exception("Expression Stack left with more than one expression");
}

expression ModifiedShuntingYard::parse(std::list<Scanner::Token>& tokens) const {
    int stackSize = tokens.size();

    // cout << "TOKENS: " << endl;
    // for (auto& token : tokens){
    //     cout << "    " << token.lexeme << " " << Scanner::typeStrings[token.type] << endl;
    // }

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
            case NONE:
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
                        throw Exception("Mismatched Comma.");
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
                        throw Exception("Mismatched Parentheses: ')'");
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
                        throw Exception("Mismatched Parentheses: '}'");
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
            if (token.type == MINUS && (current == tokens.begin() || !isPreImplicit(std::prev(current)->type))){
                token.lexeme = "neg";
                token.type = FUNCTION;
            }
            else if (!operatorStack.empty()){
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
            cout << "TOKENS:  ";
            for (auto& t : tokens){
                cout << t.lexeme << " ";
            }
            cout << endl;
            throw Exception("Unsupported Token: '", token.lexeme, "' of type ", Scanner::typeStrings[token.type]);
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

    // cout << "Output Stack:  ";
    // for (auto token : outputStacks.back()){
    //     cout << token->lexeme << " ";
    // }
    // cout << endl;

    return postfix_to_expression(outputStacks.back());
}
