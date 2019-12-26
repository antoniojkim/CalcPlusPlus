
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr12_expr12_CARET_PIPE_expr13(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr12 expr12 CARET_PIPE expr13");
    throw "generate_expr12_expr12_CARET_PIPE_expr13 not implemented";
}
ostream& generate_expr12_expr13(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr12 expr13");
    throw "generate_expr12_expr13 not implemented";
}

map<string, GenerateFunction> generate_expr12_map = {
    {"expr12 expr12 CARET_PIPE expr13", generate_expr12_expr12_CARET_PIPE_expr13},
    {"expr12 expr13", generate_expr12_expr13}
};

GenerateFunction get_expr12_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr12_map[nt->getRule()];
}
