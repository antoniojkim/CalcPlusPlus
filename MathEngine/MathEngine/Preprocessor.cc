
#include <iostream>
#include <iterator>
#include <unordered_set>

#include "../Scanner/scanner.h"
#include "../Expressions/VariableExpressions/GreekLetters.h"
#include "Preprocessor.h"

using namespace std;
using namespace Scanner;

void addMissingRParens(list<Token>& tokens){
    int lparenCount = 0;
    for(auto& token : tokens){
        switch(token.type){
            case LPAREN:
                ++lparenCount;
                break;
            case RPAREN:
                --lparenCount;
                break;
            default:
                break;
        }
    }
    for (int i = 0; i < lparenCount; ++i){
        tokens.emplace_back(Token{typeStrings[RPAREN], RPAREN});
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
    addMissingRParens(tokens);
    replaceGreekLetters(tokens);
    implicitMultiplication(tokens);
}
