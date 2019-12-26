
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr4_expr4_CARET_expr5(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr4 expr4 CARET expr5");
    throw "generate_expr4_expr4_CARET_expr5 not implemented";
}
ostream& generate_expr4_expr4_EXCL(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr4 expr4 EXCL");
    throw "generate_expr4_expr4_EXCL not implemented";
}
ostream& generate_expr4_expr5(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr4 expr5");
    throw "generate_expr4_expr5 not implemented";
}

map<string, GenerateFunction> generate_expr4_map = {
    {"expr4 expr4 CARET expr5", generate_expr4_expr4_CARET_expr5},
    {"expr4 expr4 EXCL", generate_expr4_expr4_EXCL},
    {"expr4 expr5", generate_expr4_expr5}
};

GenerateFunction get_expr4_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr4_map[nt->getRule()];
}
