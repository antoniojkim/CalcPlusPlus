
#include <iostream>
#include <iterator>
#include <unordered_set>

#include "../Scanner/scanner.h"
#include "../Utils/FixedStack.h"
#include "../Expressions/VariableExpressions/GreekLetters.h"
#include "Preprocessor.h"

using namespace std;
using namespace Scanner;

Type correspondingBracket(Type bracket){
    switch(bracket){
        case LPAREN: return RPAREN;
        case RPAREN: return LPAREN;
        case LBRACE: return RBRACE;
        case RBRACE: return LBRACE;
        case LSQUARE: return RSQUARE;
        case RSQUARE: return LSQUARE;
        default: throw;
    }
}

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
            case RBRACE:
            case RSQUARE: {
                Type L = correspondingBracket(token->type);
                while(!brackets.empty() && brackets.peek()->type != L){
                    Type L2 = correspondingBracket(brackets.peek()->type);
                    tokens.insert(token, Token{typeStrings[L2], L2});
                    brackets.pop();
                }
                if (!brackets.empty()){
                    brackets.pop();
                }
            }
            default:
                break;
        }
    }
    while(!brackets.empty()){
        Type R = correspondingBracket(brackets.peek()->type);
        tokens.insert(tokens.end(), Token{typeStrings[R], R});
        brackets.pop();
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
            tokens.insert(token, Token{"*", STAR});
        }
    }
}

void preprocess(list<Token>& tokens){
    fixBrackets(tokens);
    replaceGreekLetters(tokens);
    implicitMultiplication(tokens);
}
