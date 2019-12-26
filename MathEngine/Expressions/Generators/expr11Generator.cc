
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr11_expr11_AMP_expr12(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr11 expr11 AMP expr12");
    throw "generate_expr11_expr11_AMP_expr12 not implemented";
}
ostream& generate_expr11_expr12(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr11 expr12");
    throw "generate_expr11_expr12 not implemented";
}

map<string, GenerateFunction> generate_expr11_map = {
    {"expr11 expr11 AMP expr12", generate_expr11_expr11_AMP_expr12},
    {"expr11 expr12", generate_expr11_expr12}
};

GenerateFunction get_expr11_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr11_map[nt->getRule()];
}
