
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

expression generate_first_expression(NonTerminalTree* nonterminal){
    return generate_expression((*nonterminal)[0]);
}

expression generate_expr_lvalue_EQUALS_expr1_expression(NonTerminalTree* nonterminal){
    throw Exception("expr_lvalue_EQUALS_expr1 not implemented");
}

expression generate_expr_lvalue_COLON_EQUALS_expr1_expression(NonTerminalTree* nonterminal){
    throw Exception("expr_lvalue_COLON_EQUALS_expr1 not implemented");
}

expression generate_expr_lvalue_L_ARROW_expr1_expression(NonTerminalTree* nonterminal){
    throw Exception("expr_lvalue_L_ARROW_expr1 not implemented");
}

expression generate_expr13_expr13_PIPE_expr12_expression(NonTerminalTree* nonterminal){
    throw Exception("expr13_expr13_PIPE_expr12 not implemented");
}

expression generate_expr12_expr12_CARET_PIPE_expr11_expression(NonTerminalTree* nonterminal){
    throw Exception("expr12_expr12_CARET_PIPE_expr11 not implemented");
}

expression generate_expr11_expr11_AMP_expr7_expression(NonTerminalTree* nonterminal){
    throw Exception("expr11_expr11_AMP_expr7 not implemented");
}

expression generate_expr7_expr7_LT_LT_expr6_expression(NonTerminalTree* nonterminal){
    throw Exception("expr7_expr7_LT_LT_expr6 not implemented");
}

expression generate_expr7_expr7_GT_GT_expr6_expression(NonTerminalTree* nonterminal){
    throw Exception("expr7_expr7_GT_GT_expr6 not implemented");
}

expression generate_expr6_expr6_PLUS_expr5_expression(NonTerminalTree* nonterminal){
    return make_unique<AdditionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2]) 
    );
}

expression generate_expr6_expr6_MINUS_expr5_expression(NonTerminalTree* nonterminal){
    return make_unique<SubtractionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2]) 
    );
}


expression generate_expr5_expr5_STAR_expr4_expression(NonTerminalTree* nonterminal){
    return make_unique<MultiplicationExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2]) 
    );
}

expression generate_expr5_expr5_SLASH_expr4_expression(NonTerminalTree* nonterminal){
    return make_unique<DivisionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr5_expr5_SLASH_SLASH_expr4_expression(NonTerminalTree* nonterminal){
    return make_unique<IntegerDivisionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr5_expr5_PCT_expr4_expression(NonTerminalTree* nonterminal){
    return make_unique<ModulusDivisionExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr5_expr5_C_expr4_expression(NonTerminalTree* nonterminal){
    throw Exception("expr5_expr5_C_expr4 not implemented");
}

expression generate_expr5_expr5_P_expr4_expression(NonTerminalTree* nonterminal){
    throw Exception("expr5_expr5_P_expr4 not implemented");
}

expression generate_expr4_expr4_CARET_expr3_expression(NonTerminalTree* nonterminal){
    return make_unique<ExponentExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr4_expr4_STAR_STAR_expr3_expression(NonTerminalTree* nonterminal){
    return make_unique<ExponentExpression>(
        generate_expression((*nonterminal)[0]),
        generate_expression((*nonterminal)[2])
    );
}

expression generate_expr4_expr4_EXCL_expression(NonTerminalTree* nonterminal){
    throw Exception("expr4_expr4_EXCL not implemented");
}

expression generate_expr3_TILDE_exprn_expression(NonTerminalTree* nonterminal){
    throw Exception("expr3_TILDE_exprn not implemented");
}

expression generate_exprn_ID_exprn_expression(NonTerminalTree* nonterminal){
    return make_unique<UnaryFunctionExpression>(
        (*nonterminal)[0]->getTerminalTree()->getToken().lexeme,
        generate_expression((*nonterminal)[1])
    );
}

// arglist_expr_COMMA_arglist
inline void extract_arglist(NonTerminalTree* arglist, list<expression>& exprs){
    while(true){
        exprs.emplace_back(generate_expression((*arglist)[0]));
        if (arglist->size() == 1){
            break;
        }
        arglist = (*arglist)[2]->getNonTerminalTree();
    }
}

expression generate_exprn_ID_LPAREN_arglist_RPAREN_expression(NonTerminalTree* nonterminal){
    list<expression> exprs;
    extract_arglist((*nonterminal)[2]->getNonTerminalTree(), exprs);

    if (exprs.size() == 1){
        return make_unique<UnaryFunctionExpression>(
            (*nonterminal)[0]->getTerminalTree()->getToken().lexeme,
            std::move(exprs.front())
        );
    }
    throw Exception("exprn_ID_LPAREN_arglist_RPAREN not implemented");
}

expression generate_factor_NUM_expression(NonTerminalTree* factor){
    auto NUM = (*factor)[0]->getTerminalTree()->getToken().lexeme;
    istringstream in {NUM};
    double num;
    in >> num;
    // cout << NUM << " >> " << num << endl;
    return make_unique<NumericalExpression>(num);
}

expression generate_factor_X_expression(NonTerminalTree* nonterminal){
    return make_unique<VariableXExpression>();
}

expression generate_factor_Y_expression(NonTerminalTree* nonterminal){
    return make_unique<VariableYExpression>();
}

expression generate_factor_NONE__expression(NonTerminalTree* nonterminal){
    throw Exception("factor_NONE_ not implemented");
}

expression generate_factor_TRUE__expression(NonTerminalTree* nonterminal){
    throw Exception("factor_TRUE_ not implemented");
}

expression generate_factor_FALSE__expression(NonTerminalTree* nonterminal){
    throw Exception("factor_FALSE_ not implemented");
}

expression generate_factor_PIPE_expr_PIPE_expression(NonTerminalTree* nonterminal){
    throw Exception("factor_PIPE_expr_PIPE not implemented");
}

expression generate_factor_LPAREN_expr_RPAREN_expression(NonTerminalTree* nonterminal){
    throw Exception("factor_LPAREN_expr_RPAREN not implemented");
}

expression generate_lvalue_LPAREN_lvalue_RPAREN_expression(NonTerminalTree* nonterminal){
    return generate_expression((*nonterminal)[1]);
}

// expression generate_arglist_expression(NonTerminalTree* nonterminal){
//     throw Exception("arglist not implemented");
// }

// expression generate_arglist_expr_COMMA_arglist_expression(NonTerminalTree* nonterminal){
//     throw Exception("arglist_expr_COMMA_arglist not implemented");
// }

typedef expression (*GenerateFunction)(NonTerminalTree*);

const GenerateFunction rules_map[] = {
    generate_first_expression,
    generate_expr_lvalue_EQUALS_expr1_expression,
    generate_expr_lvalue_COLON_EQUALS_expr1_expression,
    generate_expr_lvalue_L_ARROW_expr1_expression,
    generate_first_expression,
    generate_first_expression,
    generate_expr13_expr13_PIPE_expr12_expression,
    generate_first_expression,
    generate_expr12_expr12_CARET_PIPE_expr11_expression,
    generate_first_expression,
    generate_expr11_expr11_AMP_expr7_expression,
    generate_first_expression,
    generate_expr7_expr7_LT_LT_expr6_expression,
    generate_expr7_expr7_GT_GT_expr6_expression,
    generate_first_expression,
    generate_expr6_expr6_PLUS_expr5_expression,
    generate_expr6_expr6_MINUS_expr5_expression,
    generate_first_expression,
    generate_expr5_expr5_STAR_expr4_expression,
    generate_expr5_expr5_SLASH_expr4_expression,
    generate_expr5_expr5_SLASH_SLASH_expr4_expression,
    generate_expr5_expr5_PCT_expr4_expression,
    generate_expr5_expr5_C_expr4_expression,
    generate_expr5_expr5_P_expr4_expression,
    generate_first_expression,
    generate_expr4_expr4_CARET_expr3_expression,
    generate_expr4_expr4_STAR_STAR_expr3_expression,
    generate_expr4_expr4_EXCL_expression,
    generate_first_expression,
    generate_expr3_TILDE_exprn_expression,
    generate_first_expression,
    generate_exprn_ID_exprn_expression,
    generate_exprn_ID_LPAREN_arglist_RPAREN_expression,
    generate_first_expression,
    generate_first_expression,
    generate_factor_NUM_expression,
    generate_factor_X_expression,
    generate_factor_Y_expression,
    generate_factor_NONE__expression,
    generate_factor_TRUE__expression,
    generate_factor_FALSE__expression,
    generate_factor_PIPE_expr_PIPE_expression,
    generate_factor_LPAREN_expr_RPAREN_expression,
    generate_lvalue_LPAREN_lvalue_RPAREN_expression,
    // generate_arglist_expression,
    // generate_first_expression,
    // generate_arglist_expr_COMMA_arglist_expression
};

expression generate_expression(ParseTree* tree){
    try{
        NonTerminalTree* nonterminal = tree->getNonTerminalTree();
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
