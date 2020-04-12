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

        if (token->type == TUPLE){
            istringstream tupleLexeme {token->lexeme};
            char c;
            size_t size;
            while ((tupleLexeme >> c) && c != '_');
            tupleLexeme >> size;
            if (size > expressionStack.size()){
                return make_unique<InvalidExpression>(Exception("Tuple Expected ", size, " elements. Got: ", expressionStack.size()));
            }
            for (size_t i = 0; i < size; ++i){
                argumentQueue.emplace_front(std::move(expressionStack.back()));
                expressionStack.pop_back();
            }
            expressionStack.push_back(
                make_unique<TupleExpression>(std::move(argumentQueue))
            );
            argumentQueue.clear();
            continue;
        }

        if (token->type == MATRIX){
            istringstream matrixLexeme {token->lexeme};
            char c;
            size_t numRows, numCols, size;
            while ((matrixLexeme >> c) && c != '_');
            matrixLexeme >> numRows >> c >> numCols;
            size = numRows * numCols;
            if (size > expressionStack.size()){
                return make_unique<InvalidExpression>(Exception("Matrix Expected ", size, " elements. Got: ", expressionStack.size()));
            }
            for (size_t i = 0; i < size; ++i){
                argumentQueue.emplace_front(std::move(expressionStack.back()));
                expressionStack.pop_back();
            }
            expressionStack.push_back(
                make_unique<MatrixExpression>(std::move(argumentQueue), numRows, numCols)
            );
            argumentQueue.clear();
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
    list<Scanner::Token> newTokens;

    int lbraceCount = 0;
    int matrixRowCount = 0;
    int matrixColCount = 0;

    auto current = tokens.begin();
    auto end = tokens.end();
    for (; current != end; ++current){
        auto& token = *current;
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
                    && operatorStack.back()->type != LBRACE
                    && operatorStack.back()->type != COMMA){
                    outputStack.push_back(operatorStack.back());
                    operatorStack.pop_back();
                }
                operatorStack.push_back(&token);
                continue;
            case LBRACE:
                ++lbraceCount;
                if (lbraceCount > 2){
                    throw Exception("Unsupported matrix of rank: ", lbraceCount);
                }
            case LPAREN:
            case FUNCTION:
                operatorStack.push_back(&token);
                continue;
            default:
                break;
        }

        if (isOperator(token.type)){
            if (token.type == MINUS && (current == tokens.begin() || !isPreImplicit(std::prev(current)->type))){
                newTokens.emplace_back(Token{"neg", FUNCTION});
                operatorStack.push_back(&newTokens.back());
                continue;
            }
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
            list<Scanner::Token*> commaList;
            while(true){
                if (operatorStack.size() == 0){
                    throw Exception("Mismatched Parentheses: ')'");
                }
                Scanner::Token* topOperator = operatorStack.back();
                operatorStack.pop_back();
                if (topOperator->type == LPAREN){
                    if (!commaList.empty()
                        && (operatorStack.empty()
                            || (operatorStack.back()->type != FUNCTION
                                && !isOperator(operatorStack.back()->type)))){
                        ostringstream tupleLexeme;
                        tupleLexeme << "tuple_" << (commaList.size() + 1);
                        newTokens.emplace_back(Token{tupleLexeme.str(), TUPLE});
                        outputStack.push_back(&newTokens.back());
                    }
                    else{
                        for(auto comma : commaList){
                            outputStack.push_back(comma);
                        }
                    }
                    break;
                }
                if (topOperator->type == COMMA){
                    commaList.push_back(topOperator);
                }
                else{
                    outputStack.push_back(topOperator);
                }
            }
            continue;
        }

        if (token.type == RBRACE){
            --lbraceCount;
            int numCols = 1;
            while(true){
                if (operatorStack.size() == 0){
                    throw Exception("Mismatched Parentheses: '}'");
                }
                Scanner::Token* topOperator = operatorStack.back();
                operatorStack.pop_back();
                if (topOperator->type == COMMA){
                    ++numCols;
                }
                else if (topOperator->type == LBRACE){
                    break;
                }
                else{
                    outputStack.push_back(topOperator);
                }
            }
            if (lbraceCount == 0){
                if (matrixColCount == 0){
                    matrixColCount = numCols;
                    matrixRowCount = 1;
                }
                else{
                    matrixRowCount = numCols;
                }
                ostringstream matrixLexeme;
                matrixLexeme << "matrix_" << matrixRowCount << "x" << matrixColCount;
                newTokens.emplace_back(Token{matrixLexeme.str(), MATRIX});
                outputStack.push_back(&newTokens.back());
                matrixRowCount = 0;
                matrixColCount = 0;
            }
            else if (matrixColCount == 0){
                matrixColCount = numCols;
            }
            else if (matrixColCount != numCols){
                return make_unique<InvalidExpression>(Exception("Row Expected ", matrixColCount, " columns. Got: ", numCols));
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
