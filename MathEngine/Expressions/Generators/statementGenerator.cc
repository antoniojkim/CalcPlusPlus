
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_statement_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statement expr");
    throw "generate_statement_expr not implemented";
}

map<string, GenerateFunction> generate_statement_map = {
    {"statement expr", generate_statement_expr}
};

GenerateFunction get_statement_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_statement_map[nt->getRule()];
}
