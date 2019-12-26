
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_arglist_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "arglist expr");
    throw "generate_arglist_expr not implemented";
}
ostream& generate_arglist_expr_COMMA_arglist(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "arglist expr COMMA arglist");
    throw "generate_arglist_expr_COMMA_arglist not implemented";
}

map<string, GenerateFunction> generate_arglist_map = {
    {"arglist expr", generate_arglist_expr},
    {"arglist expr COMMA arglist", generate_arglist_expr_COMMA_arglist}
};

GenerateFunction get_arglist_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_arglist_map[nt->getRule()];
}
