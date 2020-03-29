#include "Preprocessor.h"

#include <iterator>
#include <unordered_set>

using namespace std;
using namespace Scanner;

const unordered_set<Type> preImplicit ({
    NUM, RPAREN, RSQUARE, RBRACE // , SPECIALID
});
const unordered_set<Type> postImplicit ({
    NUM, LPAREN, LSQUARE, LBRACE, ID, FUNCTION // , SPECIALID
});

void implicitMultiplication(list<Token>& tokens){
    for (auto token = tokens.begin(); token != tokens.end(); ++token){
        if (preImplicit.count(token->type) > 0 && postImplicit.count(std::next(token)->type) > 0){
            tokens.insert(std::next(token), Token{"*", STAR});
        }
    }
}

void preprocess(list<Token>& tokens){
    implicitMultiplication(tokens);
}
