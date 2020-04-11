
#include <iterator>
#include <unordered_set>

#include "../Scanner/scanner.h"
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

void implicitMultiplication(list<Token>& tokens){
    for (auto token = tokens.begin(); token != tokens.end(); ++token){
        if (isPreImplicit(token->type) && isPostImplicit(std::next(token)->type)){
            tokens.insert(std::next(token), Token{typeStrings[STAR], STAR});
        }
    }
}

void preprocess(list<Token>& tokens){
    addMissingRParens(tokens);
    implicitMultiplication(tokens);
}
