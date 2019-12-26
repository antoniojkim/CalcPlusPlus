
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr1_expr3(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr1 expr3");
    throw "generate_expr1_expr3 not implemented";
}

map<string, GenerateFunction> generate_expr1_map = {
    {"expr1 expr3", generate_expr1_expr3}
};

GenerateFunction get_expr1_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr1_map[nt->getRule()];
}
