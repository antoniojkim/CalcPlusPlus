#include <cmath>
#include <iterator>
#include <list>
#include <memory>

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
#include "../Utils/MultiStack.h"
#include "modifiedShuntingYard.h"

// #define PRINT_POSTFIX

using namespace std;
using namespace calcpp;
using namespace calcpp::operators;

ModifiedShuntingYard::ModifiedShuntingYard() {}

ostream& operator<<(ostream& out, FixedStack<expression>& fs) {
    for (auto expr : fs) {
        cout << "    ";
        expr->print(cout) << endl;
    }
    return out;
}
ostream& operator<<(ostream& out, list<FixedStack<expression>>& fs) {
    for (auto& stack : fs) {
        cout << "---------------------------" << endl;
        for (auto expr : stack) {
            cout << "    ";
            expr->print(cout) << endl;
        }
    }
    return out;
}

expression postfix_to_expression(MultiStack<TokenClass*>& outputStack) {
    MultiStack<expression> expressionStack(outputStack.size());
    MultiStack<expression> expressionList(outputStack.size());

    for (auto* token : outputStack) {
        switch (token->kind) {
            case NUM:
                expressionStack.push(NumExpression::construct(token->lexeme));
                continue;
            case HEX:
                expressionStack.push(HexExpression::construct(token->lexeme));
                continue;
            case INF:
                expressionStack.push(NumExpression::construct(GSL_POSINF));
                continue;
            case BIN:
                expressionStack.push(BinExpression::construct(token->lexeme));
                continue;
            case NONE:
                expressionStack.push(NullExpression::construct());
                continue;
            case ID:
            case SPECIALID:
                expressionStack.push(VariableExpression::construct(token->lexeme));
                continue;
            case FUNCTION:
                if (expressionStack.emptyStack()) {
                    THROW_ERROR("Function '" << token->lexeme << "' found no argument");
                }
                expressionStack.push(FunctionExpression::construct(
                    token->lexeme, expressionStack.pop()));
                continue;
            case LPAREN:
            case LBRACE:
                // case LSQUARE:
                expressionStack.pushStack();
                expressionList.pushStack();
                continue;
            case COMMA:
                if (expressionList.empty()) {
                    THROW_ERROR(
                        "Cannot construct Tuple from empty list of expressions");
                }
                if (expressionStack.emptyStack()) {
                    THROW_ERROR("comma separator found no preceding expression");
                }
                expressionList.push(expressionStack.pop());
                if (!expressionStack.emptyStack()) {
                    cout << "Top Expression Stack: " << expressionStack << endl;
                    THROW_ERROR(
                        "Top Expression Stack left with more than one expression: ','");
                }
                continue;
            case RPAREN:
                if (expressionList.empty()) {
                    THROW_ERROR(
                        "Cannot construct Tuple from empty list of expressions");
                }
                if (!expressionStack.emptyStack()) {
                    expressionList.push(expressionStack.pop());
                    if (!expressionStack.emptyStack()) {
                        THROW_ERROR("Top Expression Stack left with more than one "
                                    "expression: ')'");
                    }
                }
                expressionStack.popStack();
                expressionStack.push(
                    TupleExpression::construct(expressionLists.back()));
                expressionLists.popStack();
                continue;
            case RBRACE: {
                if (!expressionStack.emptyStack()) {
                    expressionList.push(expressionStack.pop());
                    if (!expressionStack.emptyStack()) {
                        THROW_ERROR("Top Expression Stack left with more than one "
                                    "expression: '}'");
                    }
                }
                expressionStack.popStack();

                vector<expression> matrixElements;
                matrixElements.reserve(expressionList.stackSize());
                size_t numRows = 0;
                size_t numCols = expressionList.stackSize();
                for (auto matrix : expressionLists.back()) {
                    if (matrix == MATRIX) {
                        if (matrix->shape(0) != 1) {
                            THROW_ERROR("Matrix must be two dimensional");
                        } else if (numRows == 0) {
                            numRows = numCols;
                            numCols = matrix->shape(1);
                            matrixElements.reserve(
                                expressionList.stackSize() * numCols);
                        } else if (matrix->shape(1) != numCols) {
                            THROW_ERROR(
                                "Matrix expected " << numCols << " columns. Got "
                                                   << matrix->shape(1));
                        }
                        for (auto e : *matrix) { matrixElements.emplace_back(e); }
                    } else if (numRows == 0) {
                        numRows = 1;
                        matrixElements.emplace_back(matrix);
                    } else if (numRows != 1) {
                        THROW_ERROR("Matrix expected " << numRows << " rows. Got 1");
                    } else {
                        matrixElements.emplace_back(matrix);
                    }
                }
                expressionStack.push(MatrixExpression::construct(
                    std::move(matrixElements), numRows, numCols));
                expressionLists.popStack();
                continue;
            }
            default:
                break;
        }

        if (isOperator(token->kind)) {
            if (expressionStack.emptyStack()) {
                THROW_ERROR(
                    "Insufficient Number of Arguments for Unary Operator: "
                    << token->lexeme);
            }
            if (isSingleOperator(token->type)) {
                switch (token->type) {
                    case EXCL:
                        expressionStack.push(FunctionExpression::construct(
                            "fact", expressionStack.pop()));
                        break;
                    case EXCL_EXCL:
                        expressionStack.push(FunctionExpression::construct(
                            "dfact", expressionStack.pop()));
                        break;
                    case APOSTROPHE:
                        expressionStack.push(FunctionExpression::construct(
                            "diff", expressionStack.pop()));
                        break;
                    case ELLIPSIS:
                        expressionStack.push(
                            VarArgsExpression::construct(expressionStack.pop()));
                        break;
                    default:
                        THROW_ERROR("Unsupported Unary Operator: " << token->lexeme);
                }
            } else {
                if (expressionStacks.back().size() < 2) {
                    THROW_ERROR(
                        "Insufficient Number of Arguments for Binary Operator: "
                        << token->lexeme);
                }

                expression rhs = expressionStack.pop();
                expression lhs = expressionStack.pop();
                // switch(token->type){
                //     case PLUS:
                //         expressionStack.push(lhs + rhs);
                //         break;
                //     case MINUS:
                //         expressionStack.push(lhs - rhs);
                //         break;
                //     case STAR:
                //         expressionStack.push(lhs * rhs);
                //         break;
                //     case SLASH:
                //         expressionStack.push(lhs / rhs);
                //         break;
                //     case CARET:
                //     case STAR_STAR:
                //         expressionStack.push(lhs ^ rhs);
                //         break;
                //     default:
                expressionStack.push(
                    FunctionExpression::construct(token->lexeme, {lhs, rhs}));
                // break;
                // }
            }
        } else {
            THROW_ERROR("Unsupported Token type found: " << typeStrings[token->type]);
        }
    }

    if (expressionStacks.size() == 1 && expressionStacks.back().size() == 1) {
        return expressionStack.pop();
    }

    THROW_ERROR("Expression Stack left with more than one expression");
}

expression ModifiedShuntingYard::parse(TokenCollection& tokens) const {
    using namespace calcpp::Token;

    FixedStack<TokenClass*> operatorStack(tokens.size());
    MultiStack<TokenClass*> outputStack(tokens.size());

    auto current = tokens.begin();
    auto end = tokens.end();
    for (; current != end; ++current) {
        auto& token = *current;
        switch (token.kind) {
            case NUM:
            case HEX:
            case BIN:
            case INF:
            case NONE:
                outputStack.push(&token);
                continue;
            case ID:
            case GREEK:
                if (std::next(current) != end &&
                    isPostImplicit(std::next(current)->type)) {  // Implies that the ID
                                                                 // is a function call
                    operatorStack.push(&token);
                    token.type = FUNCTION;
                } else {
                    outputStack.push(&token);
                }
                continue;
            case LPAREN:
            case LBRACE:
                // case LSQUARE:
                // Create a new stack to handle the new context
                outputStack.pushStack();
                operatorStack.push(&token);
                continue;
            case COMMA: {
                while (true) {
                    if (operatorStack.empty()) { THROW_ERROR("Mismatched Comma."); }
                    if (operatorStack.peek()->type == LPAREN ||
                        operatorStack.peek()->type == LBRACE ||
                        operatorStack.peek()->type == COMMA) {
                        outputStack.push(operatorStack.pop(), 1);
                        outputStack.popStack();
                        break;
                    }
                    outputStack.push(operatorStack.pop());
                }
                operatorStack.push(&token);
                outputStack.pushStack();
                continue;
            }
            case RPAREN: {
                while (true) {
                    if (operatorStack.size() == 0) {
                        THROW_ERROR("Mismatched Parentheses: ')'");
                    }
                    if (operatorStack.peek()->type == COMMA ||
                        outputStack.emptyStack()) {
                        outputStack.push(operatorStack.pop(), 1);
                        outputStack.push(&token);
                        break;
                    }
                    if (operatorStack.peek()->type == LPAREN) {
                        operatorStack.pop();
                        outputStack.popStack();
                        break;
                    }
                    outputStack.push(operatorStack.pop());
                }
                if (!operatorStack.empty() &&
                    (operatorStack.peek()->type == ID ||
                     operatorStack.peek()->type == SPECIALID)) {
                    outputStack.push(operatorStack.pop());
                }
                continue;
            }
            case RBRACE: {
                while (true) {
                    if (operatorStack.size() == 0) {
                        THROW_ERROR("Mismatched Parentheses: '}'");
                    }
                    if (operatorStack.peek()->type == COMMA ||
                        operatorStack.peek()->type == LBRACE) {
                        outputStack.push(operatorStack.pop(), 1);
                        outputStack.push(&token);
                        break;
                    }
                    outputStack.push(operatorStack.pop());
                }
                if (!operatorStack.empty() &&
                    (operatorStack.peek()->type == ID ||
                     operatorStack.peek()->type == SPECIALID)) {
                    outputStack.push(operatorStack.pop());
                }
                continue;
            }
            default:
                break;
        }

        if (isOperator(token.kind)) {
            if (token.type == MINUS && (current == tokens.begin() ||
                                        !isPreImplicit(std::prev(current)->kind))) {
                token.lexeme = "neg";
                token.type = FUNCTION;
            } else if (!operatorStack.empty()) {
                auto type = operatorStack.peek()->type;
                while ((type == FUNCTION ||
                        (isOperator(type) &&
                         getPrecedence(type) > getPrecedence(token.type)) ||
                        (isOperator(type) &&
                         getPrecedence(type) == getPrecedence(token.type) &&
                         !isRightAssociative(token.type))) &&
                       type != LPAREN) {
                    outputStack.push(operatorStack.pop());
                    if (operatorStack.empty()) break;
                    type = operatorStack.peek()->type;
                }
            }
            operatorStack.push(&token);
        } else {
            cout << "TOKENS:  ";
            for (auto& t : tokens) { cout << t.lexeme << " "; }
            cout << endl;
            THROW_ERROR(
                "Unsupported Token: '" << token.lexeme << "' of type "
                                       << Scanner::typeStrings[token.type]);
        }
    }
    while (outputStack.numStack() > 1) { outputStack.popStack(); }
    while (!operatorStack.empty()) { outputStack.push(operatorStack.pop()); }

    return postfix_to_expression(outputStack);
}
