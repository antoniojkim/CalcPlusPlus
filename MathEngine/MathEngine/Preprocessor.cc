
#include <iostream>
#include <iterator>
#include <unordered_set>

#include "../Scanner/scanner.h"
#include "../Utils/FixedStack.h"
#include "../Expressions/VariableExpressions/GreekLetters.h"
#include "Preprocessor.h"

using namespace std;
using namespace Scanner;

void fixBrackets(list<Token>& tokens){
    FixedStack<Token*> brackets(tokens.size());
    for(auto token = tokens.begin(); token != tokens.end(); ++token){
        switch(token->type){
            case LPAREN:
            case LBRACE:
            case LSQUARE:
                brackets.push(&*token);
                break;
            case RPAREN:
                while(!brackets.empty() && brackets.peek()->type != LPAREN){
                    tokens.insert(token++, *(brackets.pop()));
                }
                brackets.pop();
                break;
            case RBRACE:
                while(!brackets.empty() && brackets.peek()->type != LBRACE){
                    tokens.insert(token++, *(brackets.pop()));
                }
                brackets.pop();
                break;
            case RSQUARE:
                while(!brackets.empty() && brackets.peek()->type != LSQUARE){
                    tokens.insert(token++, *(brackets.pop()));
                }
                brackets.pop();
                break;
            default:
                break;
        }
    }
}

void replaceGreekLetters(list<Token>& tokens){
    for (auto& token : tokens){
        if (token.type == SPECIALID){
            int index = getGreekLetterIndex(token.lexeme);
            if (index != -1){
                token.lexeme = greekLetterNames[index];
            }
        }
    }
}

void implicitMultiplication(list<Token>& tokens){
    for (auto token = std::next(tokens.begin()); token != tokens.end(); ++token){
        if (isPreImplicit(std::prev(token)->type) && isPostImplicit(token->type)){
            tokens.insert(token, Token{typeStrings[STAR], STAR});
        }
    }
}

void preprocess(list<Token>& tokens){
    fixBrackets(tokens);
    replaceGreekLetters(tokens);
    implicitMultiplication(tokens);
}
