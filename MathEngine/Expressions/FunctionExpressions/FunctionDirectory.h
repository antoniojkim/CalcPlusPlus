#pragma once

#include <list>
#include <string>

#include "../Expression.h"

typedef double (*ValueFunction)(expression arg, const Variables& vars);
ValueFunction get_function(const std::string& name);
ValueFunction get_function(int functionIndex);

template<double F(double)>
double valueFunction(expression arg, const Variables& vars){ return F(arg->value(vars)); }

typedef expression (*ExprFunction)(const expression arg, const Variables& vars);
ExprFunction get_function_expr(const std::string& name);
ExprFunction get_function_expr(int functionIndex);

typedef expression (*DerivativeFunction)(const expression arg, const std::string& var);
DerivativeFunction get_function_derivative(const std::string& name);
DerivativeFunction get_function_derivative(int functionIndex);
