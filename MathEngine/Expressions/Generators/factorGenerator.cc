
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_factor_NUM(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NUM");
    throw "generate_factor_NUM not implemented";
}
ostream& generate_factor_X(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor X");
    throw "generate_factor_X not implemented";
}
ostream& generate_factor_Y(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor Y");
    throw "generate_factor_Y not implemented";
}
ostream& generate_factor_NONE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NONE_");
    throw "generate_factor_NONE_ not implemented";
}
ostream& generate_factor_TRUE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor TRUE_");
    throw "generate_factor_TRUE_ not implemented";
}
ostream& generate_factor_FALSE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor FALSE_");
    throw "generate_factor_FALSE_ not implemented";
}

map<string, GenerateFunction> generate_factor_map = {
    {"factor NUM", generate_factor_NUM},
    {"factor X", generate_factor_X},
    {"factor Y", generate_factor_Y},
    {"factor NONE_", generate_factor_NONE_},
    {"factor TRUE_", generate_factor_TRUE_},
    {"factor FALSE_", generate_factor_FALSE_}
};

GenerateFunction get_factor_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_factor_map[nt->getRule()];
}
