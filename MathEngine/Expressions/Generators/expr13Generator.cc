
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr13_expr13_PIPE_exprn(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr13 expr13 PIPE exprn");
    throw "generate_expr13_expr13_PIPE_exprn not implemented";
}
ostream& generate_expr13_exprn(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr13 exprn");
    throw "generate_expr13_exprn not implemented";
}

map<string, GenerateFunction> generate_expr13_map = {
    {"expr13 expr13 PIPE exprn", generate_expr13_expr13_PIPE_exprn},
    {"expr13 exprn", generate_expr13_exprn}
};

GenerateFunction get_expr13_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr13_map[nt->getRule()];
}
