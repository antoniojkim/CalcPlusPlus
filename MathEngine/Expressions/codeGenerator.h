
#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <iostream>
#include <string>
#include "../ContextSensitiveTrees/ContextSensitiveTrees.h"
#include "../Parser/parsetree.h"

typedef std::ostream& (*GenerateFunction)(ContextSensitiveTree* tree, std::ostream& out, const std::string& indent);
typedef GenerateFunction (*GetGenerateFunction)(ParseTree* tree);

GenerateFunction getCodeGenerationFunction(ParseTree* tree);

GenerateFunction get_statement_code_generation_function(ParseTree* tree);
GenerateFunction get_expr_code_generation_function(ParseTree* tree);
GenerateFunction get_expr1_code_generation_function(ParseTree* tree);
GenerateFunction get_expr3_code_generation_function(ParseTree* tree);
GenerateFunction get_expr4_code_generation_function(ParseTree* tree);
GenerateFunction get_expr5_code_generation_function(ParseTree* tree);
GenerateFunction get_expr6_code_generation_function(ParseTree* tree);
GenerateFunction get_expr7_code_generation_function(ParseTree* tree);
GenerateFunction get_expr11_code_generation_function(ParseTree* tree);
GenerateFunction get_expr12_code_generation_function(ParseTree* tree);
GenerateFunction get_expr13_code_generation_function(ParseTree* tree);
GenerateFunction get_exprn_code_generation_function(ParseTree* tree);
GenerateFunction get_exprl_code_generation_function(ParseTree* tree);
GenerateFunction get_factor_code_generation_function(ParseTree* tree);
GenerateFunction get_lvalue_code_generation_function(ParseTree* tree);
GenerateFunction get_arglist_code_generation_function(ParseTree* tree);


#endif // CODE_GENERATOR_H
