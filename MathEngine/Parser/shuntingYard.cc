
#include <list>

#include "shuntingYard.h"
#include "../Scanner/scanner.h"
#include "../MathEngine/Operators.h"
#include "../Utils/exceptions.h"

using namespace std;
using namespace Scanner;

ShuntingYard::ShuntingYard(){}

expression ShuntingYard::parse(const std::list<Scanner::Token>& tokens) {

    list<const Scanner::Token*> outputStack;
    list<const Scanner::Token*> operatorStack;

    for (auto& token: tokens){
        switch(token.type){
            case NUM:
            case HEX:
            case BIN:
                outputStack.emplace_back(&token);
                break;
            case ID:
            case LPAREN:
                operatorStack.emplace_back(&token);
                break;
            default:
                break;
        }

        if (isOperator(token.type)){
            auto type = operatorStack.back()->type;
            while((type == ID
                   || getPrecedence(type) > getPrecedence(token.type)
                   || (getPrecedence(type) == getPrecedence(token.type) && !isRightAssociative(token.type)))
                  && type != LPAREN) {
                outputStack.emplace_back(operatorStack.back());
                operatorStack.pop_back();
            }
            operatorStack.emplace_back(&token);
            continue;
        }
        
        if (token.type == RPAREN){
            while(true){
                if (operatorStack.size() == 0){
                    throw Exception("Mismatched Parentheses: ')'");
                }
                auto token = operatorStack.back();
                operatorStack.pop_back();
                if (token->type == LPAREN) break;
                outputStack.emplace_back(token);
            }
        }

        throw Exception("Unsupported Token: '", token.lexeme, "'");
    }
    while(!operatorStack.empty()){
        outputStack.emplace_back(operatorStack.back());
        operatorStack.pop_back();
    }

    for (auto token : outputStack){
        cout << token->lexeme << "  " << endl;
    }

    // list<expression> expressions;
    throw Exception("Unimplemented");
    
}
