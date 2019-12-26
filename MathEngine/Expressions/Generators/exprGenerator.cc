
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr_lvalue_EQUALS_expr1(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr lvalue EQUALS expr1");
    throw "generate_expr_lvalue_EQUALS_expr1 not implemented";
}
ostream& generate_expr_lvalue_COLON_EQUALS_expr1(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr lvalue COLON_EQUALS expr1");
    throw "generate_expr_lvalue_COLON_EQUALS_expr1 not implemented";
}
ostream& generate_expr_lvalue_L_ARROW_expr1(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr lvalue L_ARROW expr1");
    throw "generate_expr_lvalue_L_ARROW_expr1 not implemented";
}
ostream& generate_expr_expr1(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr expr1");
    throw "generate_expr_expr1 not implemented";
}

map<string, GenerateFunction> generate_expr_map = {
    {"expr lvalue EQUALS expr1", generate_expr_lvalue_EQUALS_expr1},
    {"expr lvalue COLON_EQUALS expr1", generate_expr_lvalue_COLON_EQUALS_expr1},
    {"expr lvalue L_ARROW expr1", generate_expr_lvalue_L_ARROW_expr1},
    {"expr expr1", generate_expr_expr1}
};

GenerateFunction get_expr_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr_map[nt->getRule()];
}
