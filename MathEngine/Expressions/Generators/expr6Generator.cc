
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr6_expr6_PLUS_expr7(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr6 expr6 PLUS expr7");
    throw "generate_expr6_expr6_PLUS_expr7 not implemented";
}
ostream& generate_expr6_expr6_MINUS_expr7(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr6 expr6 MINUS expr7");
    throw "generate_expr6_expr6_MINUS_expr7 not implemented";
}
ostream& generate_expr6_expr7(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr6 expr7");
    throw "generate_expr6_expr7 not implemented";
}

map<string, GenerateFunction> generate_expr6_map = {
    {"expr6 expr6 PLUS expr7", generate_expr6_expr6_PLUS_expr7},
    {"expr6 expr6 MINUS expr7", generate_expr6_expr6_MINUS_expr7},
    {"expr6 expr7", generate_expr6_expr7}
};

GenerateFunction get_expr6_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr6_map[nt->getRule()];
}
