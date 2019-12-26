
#include "codeGenerator.h"
#include <map>

using namespace std;


map<string, GetGenerateFunction> generateFunctionsMap = {
    {"statement", get_statement_code_generation_function},
    {"expr", get_expr_code_generation_function},
    {"expr1", get_expr1_code_generation_function},
    {"expr3", get_expr3_code_generation_function},
    {"expr4", get_expr4_code_generation_function},
    {"expr5", get_expr5_code_generation_function},
    {"expr6", get_expr6_code_generation_function},
    {"expr7", get_expr7_code_generation_function},
    {"expr11", get_expr11_code_generation_function},
    {"expr12", get_expr12_code_generation_function},
    {"expr13", get_expr13_code_generation_function},
    {"exprn", get_exprn_code_generation_function},
    {"exprl", get_exprl_code_generation_function},
    {"factor", get_factor_code_generation_function},
    {"lvalue", get_lvalue_code_generation_function},
    {"arglist", get_arglist_code_generation_function}
};

GenerateFunction getCodeGenerationFunction(ParseTree* tree){
    return generateFunctionsMap[tree->getRoot()](tree);
}
