
#include "../Expression.h"
#include "../../Utils/exceptions.h"

#include "../BinaryExpression.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"
#include "../VariableExpression.h"

#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>

using namespace std;

expression generate_first_expression(NonTerminal* nonterminal){
    return generate_expression((*nonterminal)[0]);
}

expression generate_expr_lvalue_EQUALS_expr1_expression(NonTerminal* nonterminal){
    throw Exception("expr_lvalue_EQUALS_expr1 not implemented");
}

expression generate_expr_lvalue_COLON_EQUALS_expr1_expression(NonTerminal* nonterminal){
    throw Exception("expr_lvalue_COLON_EQUALS_expr1 not implemented");
}

expression generate_expr_lvalue_L_ARROW_expr1_expression(NonTerminal* nonterminal){
    throw Exception("expr_lvalue_L_ARROW_expr1 not implemented");
}

expression generate_expr13_expr13_PIPE_expr12_expression(NonTerminal* nonterminal){
    throw Exception("expr13_expr13_PIPE_expr12 not implemented");
}

expression generate_expr12_expr12_CARET_PIPE_expr11_expression(NonTerminal* nonterminal){
    throw Exception("expr12_expr12_CARET_PIPE_expr11 not implemented");
}

expression generate_expr11_expr11_AMP_expr7_expression(NonTerminal* nonterminal){
    throw Exception("expr11_expr11_AMP_expr7 not implemented");
}

expression generate_expr7_expr7_LT_LT_expr6_expression(NonTerminal* nonterminal){
    throw Exception("expr7_expr7_LT_LT_expr6 not implemented");
}

expression generate_expr7_expr7_GT_GT_expr6_expression(NonTerminal* nonterminal){
    throw Exception("expr7_expr7_GT_GT_expr6 not implemented");
}

expression generate_expr6_expr6_PLUS_expr5_expression(NonTerminal* nonterminal){
    return make_unique<AdditionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2]) 
    );
}

expression generate_expr6_expr6_MINUS_expr5_expression(NonTerminal* nonterminal){
    return make_unique<SubtractionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2]) 
    );
}


expression generate_expr5_expr5_STAR_expr4_expression(NonTerminal* nonterminal){
    return make_unique<MultiplicationExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2]) 
    );
}

expression generate_expr5_expr5_SLASH_expr4_expression(NonTerminal* nonterminal){
    return make_unique<DivisionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr5_expr5_SLASH_SLASH_expr4_expression(NonTerminal* nonterminal){
    return make_unique<IntegerDivisionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr5_expr5_PCT_expr4_expression(NonTerminal* nonterminal){
    return make_unique<ModulusDivisionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr5_expr5_C_expr4_expression(NonTerminal* nonterminal){
    throw Exception("expr5_expr5_C_expr4 not implemented");
}

expression generate_expr5_expr5_P_expr4_expression(NonTerminal* nonterminal){
    throw Exception("expr5_expr5_P_expr4 not implemented");
}

expression generate_expr4_expr4_CARET_expr3_expression(NonTerminal* nonterminal){
    return make_unique<ExponentExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr4_expr4_STAR_STAR_expr3_expression(NonTerminal* nonterminal){
    return make_unique<ExponentExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr4_expr4_EXCL_expression(NonTerminal* nonterminal){
    throw Exception("expr4_expr4_EXCL not implemented");
}

expression generate_expr3_TILDE_exprn_expression(NonTerminal* nonterminal){
    throw Exception("expr3_TILDE_exprn not implemented");
}

expression generate_exprn_ID_exprn_expression(NonTerminal* nonterminal){
    return make_unique<UnaryFunctionExpression>(
        (*nonterminal)[0]->getTerminal()->getToken().lexeme,
        generate_expression((*nonterminal)[1])
    );
}

// arglist_expr_COMMA_arglist
inline void extract_arglist(NonTerminal* arglist, list<expression>& exprs){
    while(true){
        exprs.emplace_back(generate_expression((*arglist)[0]));
        if (arglist->size() == 1){
            break;
        }
        arglist = (*arglist)[2]->getNonTerminal();
    }
}

expression generate_exprn_ID_LPAREN_arglist_RPAREN_expression(NonTerminal* nonterminal){
    list<expression> exprs;
    extract_arglist((*nonterminal)[2]->getNonTerminal(), exprs);

    if (exprs.size() == 1){
        return make_unique<UnaryFunctionExpression>(
            (*nonterminal)[0]->getTerminal()->getToken().lexeme,
            std::move(exprs.front())
        );
    }
    throw Exception("exprn_ID_LPAREN_arglist_RPAREN not implemented");
}

expression generate_factor_NUM_expression(NonTerminal* factor){
    auto NUM = (*factor)[0]->getTerminal()->getToken().lexeme;
    istringstream in {NUM};
    double num;
    in >> num;
    // cout << NUM << " >> " << num << endl;
    return make_unique<NumericalExpression>(num);
}

expression generate_factor_X_expression(NonTerminal* nonterminal){
    return make_unique<VariableXExpression>();
}

expression generate_factor_Y_expression(NonTerminal* nonterminal){
    return make_unique<VariableYExpression>();
}

expression generate_factor_NONE__expression(NonTerminal* nonterminal){
    throw Exception("factor_NONE_ not implemented");
}

expression generate_factor_TRUE__expression(NonTerminal* nonterminal){
    throw Exception("factor_TRUE_ not implemented");
}

expression generate_factor_FALSE__expression(NonTerminal* nonterminal){
    throw Exception("factor_FALSE_ not implemented");
}

expression generate_factor_PIPE_expr_PIPE_expression(NonTerminal* nonterminal){
    throw Exception("factor_PIPE_expr_PIPE not implemented");
}

expression generate_factor_LPAREN_expr_RPAREN_expression(NonTerminal* nonterminal){
    throw Exception("factor_LPAREN_expr_RPAREN not implemented");
}

expression generate_lvalue_LPAREN_lvalue_RPAREN_expression(NonTerminal* nonterminal){
    return generate_expression((*nonterminal)[1]);
}

// expression generate_arglist_expression(NonTerminal* nonterminal){
//     throw Exception("arglist not implemented");
// }

// expression generate_arglist_expr_COMMA_arglist_expression(NonTerminal* nonterminal){
//     throw Exception("arglist_expr_COMMA_arglist not implemented");
// }

typedef expression (*GenerateFunction)(NonTerminal*);

const unordered_map<string, GenerateFunction> rules_map {
    {"statement expr", generate_first_expression},
    {"expr lvalue EQUALS expr1", generate_expr_lvalue_EQUALS_expr1_expression},
    {"expr lvalue COLON_EQUALS expr1", generate_expr_lvalue_COLON_EQUALS_expr1_expression},
    {"expr lvalue L_ARROW expr1", generate_expr_lvalue_L_ARROW_expr1_expression},
    {"expr expr1", generate_first_expression},
    {"expr1 expr13", generate_first_expression},
    {"expr13 expr13 PIPE expr12", generate_expr13_expr13_PIPE_expr12_expression},
    {"expr13 expr12", generate_first_expression},
    {"expr12 expr12 CARET_PIPE expr11", generate_expr12_expr12_CARET_PIPE_expr11_expression},
    {"expr12 expr11", generate_first_expression},
    {"expr11 expr11 AMP expr7", generate_expr11_expr11_AMP_expr7_expression},
    {"expr11 expr7", generate_first_expression},
    {"expr7 expr7 LT_LT expr6", generate_expr7_expr7_LT_LT_expr6_expression},
    {"expr7 expr7 GT_GT expr6", generate_expr7_expr7_GT_GT_expr6_expression},
    {"expr7 expr6", generate_first_expression},
    {"expr6 expr6 PLUS expr5", generate_expr6_expr6_PLUS_expr5_expression},
    {"expr6 expr6 MINUS expr5", generate_expr6_expr6_MINUS_expr5_expression},
    {"expr6 expr5", generate_first_expression},
    {"expr5 expr5 STAR expr4", generate_expr5_expr5_STAR_expr4_expression},
    {"expr5 expr5 SLASH expr4", generate_expr5_expr5_SLASH_expr4_expression},
    {"expr5 expr5 SLASH_SLASH expr4", generate_expr5_expr5_SLASH_SLASH_expr4_expression},
    {"expr5 expr5 PCT expr4", generate_expr5_expr5_PCT_expr4_expression},
    {"expr5 expr5 C expr4", generate_expr5_expr5_C_expr4_expression},
    {"expr5 expr5 P expr4", generate_expr5_expr5_P_expr4_expression},
    {"expr5 expr4", generate_first_expression},
    {"expr4 expr4 CARET expr3", generate_expr4_expr4_CARET_expr3_expression},
    {"expr4 expr4 STAR_STAR expr3", generate_expr4_expr4_STAR_STAR_expr3_expression},
    {"expr4 expr4 EXCL", generate_expr4_expr4_EXCL_expression},
    {"expr4 expr3", generate_first_expression},
    {"expr3 TILDE exprn", generate_expr3_TILDE_exprn_expression},
    {"expr3 exprn", generate_first_expression},
    {"exprn ID exprn", generate_exprn_ID_exprn_expression},
    {"exprn ID LPAREN arglist RPAREN", generate_exprn_ID_LPAREN_arglist_RPAREN_expression},
    {"exprn factor", generate_first_expression},
    {"exprn lvalue", generate_first_expression},
    {"factor NUM", generate_factor_NUM_expression},
    {"factor X", generate_factor_X_expression},
    {"factor Y", generate_factor_Y_expression},
    {"factor NONE_", generate_factor_NONE__expression},
    {"factor TRUE_", generate_factor_TRUE__expression},
    {"factor FALSE_", generate_factor_FALSE__expression},
    {"factor PIPE expr PIPE", generate_factor_PIPE_expr_PIPE_expression},
    {"factor LPAREN expr RPAREN", generate_factor_LPAREN_expr_RPAREN_expression},
    {"lvalue LPAREN lvalue RPAREN", generate_lvalue_LPAREN_lvalue_RPAREN_expression},
    // {"arglist", generate_arglist_expression},
    // {"arglist expr", generate_first_expression},
    // {"arglist expr COMMA arglist", generate_arglist_expr_COMMA_arglist_expression}
};

expression generate_expression(ParseTree* tree){
    try{
        NonTerminal* nonterminal = tree->getNonTerminal();
        if (rules_map.count(nonterminal->getRule()) > 0){
            return rules_map.at(nonterminal->getRule())(nonterminal);
        }
    } catch (Exception& e){
        cout << e.what() << endl;
        cout << tree->getRoot() << endl << endl;
        tree->print(cout);
    }
    throw Exception("Could not generate expression");
    // return nullptr;
}
