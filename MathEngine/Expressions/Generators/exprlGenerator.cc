
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_exprl_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "exprl factor");
    throw "generate_exprl_factor not implemented";
}
ostream& generate_exprl_lvalue(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "exprl lvalue");
    throw "generate_exprl_lvalue not implemented";
}

map<string, GenerateFunction> generate_exprl_map = {
    {"exprl factor", generate_exprl_factor},
    {"exprl lvalue", generate_exprl_lvalue}
};

GenerateFunction get_exprl_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_exprl_map[nt->getRule()];
}
