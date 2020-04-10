#pragma once

#include <list>
#include <string>

#include "../Expression.h"

typedef double (*UnaryFunction)(double x);
UnaryFunction get_unary_function(const std::string& name);
UnaryFunction get_unary_function(int functionIndex);

typedef double (*MultiFunction)(std::list<expression>& args, const Variables& vars);
MultiFunction get_multi_function(const std::string& name);
MultiFunction get_multi_function(int functionIndex);

typedef expression (*MultiFunctionExpr)(std::list<expression>& args, const Variables& vars);
MultiFunctionExpr get_multi_function_expr(const std::string& name);
MultiFunctionExpr get_multi_function_expr(int functionIndex);
