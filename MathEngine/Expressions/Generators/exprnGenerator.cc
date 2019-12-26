
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_exprn_PIPE_expr_PIPE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "exprn PIPE expr PIPE");
    throw "generate_exprn_PIPE_expr_PIPE not implemented";
}
ostream& generate_exprn_LPAREN_expr_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "exprn LPAREN expr RPAREN");
    throw "generate_exprn_LPAREN_expr_RPAREN not implemented";
}
ostream& generate_exprn_ID_LPAREN_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "exprn ID LPAREN RPAREN");
    throw "generate_exprn_ID_LPAREN_RPAREN not implemented";
}
ostream& generate_exprn_ID_LPAREN_arglist_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "exprn ID LPAREN arglist RPAREN");
    throw "generate_exprn_ID_LPAREN_arglist_RPAREN not implemented";
}
ostream& generate_exprn_ID_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "exprn ID factor");
    throw "generate_exprn_ID_factor not implemented";
}
ostream& generate_exprn_exprl(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "exprn exprl");
    throw "generate_exprn_exprl not implemented";
}

map<string, GenerateFunction> generate_exprn_map = {
    {"exprn PIPE expr PIPE", generate_exprn_PIPE_expr_PIPE},
    {"exprn LPAREN expr RPAREN", generate_exprn_LPAREN_expr_RPAREN},
    {"exprn ID LPAREN RPAREN", generate_exprn_ID_LPAREN_RPAREN},
    {"exprn ID LPAREN arglist RPAREN", generate_exprn_ID_LPAREN_arglist_RPAREN},
    {"exprn ID factor", generate_exprn_ID_factor},
    {"exprn exprl", generate_exprn_exprl}
};

GenerateFunction get_exprn_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_exprn_map[nt->getRule()];
}
