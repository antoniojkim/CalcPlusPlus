
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr3_TILDE_expr3(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr3 TILDE expr3");
    throw "generate_expr3_TILDE_expr3 not implemented";
}
ostream& generate_expr3_expr4(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr3 expr4");
    throw "generate_expr3_expr4 not implemented";
}

map<string, GenerateFunction> generate_expr3_map = {
    {"expr3 TILDE expr3", generate_expr3_TILDE_expr3},
    {"expr3 expr4", generate_expr3_expr4}
};

GenerateFunction get_expr3_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr3_map[nt->getRule()];
}
