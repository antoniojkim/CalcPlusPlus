#pragma once

#include <list>
#include <string>

#include "../Expression.h"

typedef double (*UnaryFunction)(double x);
UnaryFunction get_unary_function(const std::string& name);
UnaryFunction get_unary_function(int functionIndex);

typedef expression (*UnaryFunctionExpr)(expression& arg, const Variables& vars);
UnaryFunctionExpr get_unary_function_expr(const std::string& name);
UnaryFunctionExpr get_unary_function_expr(int functionIndex);

typedef expression (*UnaryFunctionDerivative)(expression& arg, const std::string& var);
UnaryFunctionDerivative get_unary_function_derivative(const std::string& name);
UnaryFunctionDerivative get_unary_function_derivative(int functionIndex);

typedef double (*MultiFunction)(std::list<expression>& args, const Variables& vars);
MultiFunction get_multi_function(const std::string& name);
MultiFunction get_multi_function(int functionIndex);

typedef expression (*MultiFunctionExpr)(std::list<expression>& args, const Variables& vars);
MultiFunctionExpr get_multi_function_expr(const std::string& name);
MultiFunctionExpr get_multi_function_expr(int functionIndex);
