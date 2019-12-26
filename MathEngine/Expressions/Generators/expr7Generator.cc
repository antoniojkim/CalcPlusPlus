
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr7_expr7_LT_LT_expr11(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr7 expr7 LT_LT expr11");
    throw "generate_expr7_expr7_LT_LT_expr11 not implemented";
}
ostream& generate_expr7_expr7_GT_GT_expr11(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr7 expr7 GT_GT expr11");
    throw "generate_expr7_expr7_GT_GT_expr11 not implemented";
}
ostream& generate_expr7_expr11(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr7 expr11");
    throw "generate_expr7_expr11 not implemented";
}

map<string, GenerateFunction> generate_expr7_map = {
    {"expr7 expr7 LT_LT expr11", generate_expr7_expr7_LT_LT_expr11},
    {"expr7 expr7 GT_GT expr11", generate_expr7_expr7_GT_GT_expr11},
    {"expr7 expr11", generate_expr7_expr11}
};

GenerateFunction get_expr7_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr7_map[nt->getRule()];
}
