
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_lvalue_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "lvalue ID");
    throw "generate_lvalue_ID not implemented";
}
ostream& generate_lvalue_LPAREN_lvalue_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "lvalue LPAREN lvalue RPAREN");
    throw "generate_lvalue_LPAREN_lvalue_RPAREN not implemented";
}

map<string, GenerateFunction> generate_lvalue_map = {
    {"lvalue ID", generate_lvalue_ID},
    {"lvalue LPAREN lvalue RPAREN", generate_lvalue_LPAREN_lvalue_RPAREN}
};

GenerateFunction get_lvalue_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_lvalue_map[nt->getRule()];
}
