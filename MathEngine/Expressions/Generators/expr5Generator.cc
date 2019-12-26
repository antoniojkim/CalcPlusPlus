
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr5_expr5_STAR_expr6(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr5 STAR expr6");
    throw "generate_expr5_expr5_STAR_expr6 not implemented";
}
ostream& generate_expr5_expr5_SLASH_expr6(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr5 SLASH expr6");
    throw "generate_expr5_expr5_SLASH_expr6 not implemented";
}
ostream& generate_expr5_expr5_SLASH_SLASH_expr6(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr5 SLASH_SLASH expr6");
    throw "generate_expr5_expr5_SLASH_SLASH_expr6 not implemented";
}
ostream& generate_expr5_expr5_PCT_expr6(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr5 PCT expr6");
    throw "generate_expr5_expr5_PCT_expr6 not implemented";
}
ostream& generate_expr5_expr6(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr6");
    throw "generate_expr5_expr6 not implemented";
}

map<string, GenerateFunction> generate_expr5_map = {
    {"expr5 expr5 STAR expr6", generate_expr5_expr5_STAR_expr6},
    {"expr5 expr5 SLASH expr6", generate_expr5_expr5_SLASH_expr6},
    {"expr5 expr5 SLASH_SLASH expr6", generate_expr5_expr5_SLASH_SLASH_expr6},
    {"expr5 expr5 PCT expr6", generate_expr5_expr5_PCT_expr6},
    {"expr5 expr6", generate_expr5_expr6}
};

GenerateFunction get_expr5_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr5_map[nt->getRule()];
}
