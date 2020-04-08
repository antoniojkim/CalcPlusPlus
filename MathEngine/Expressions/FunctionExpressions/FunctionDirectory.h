#pragma once

#include <list>
#include <string>

#include "../Expression.h"

typedef double (*UnaryFunction)(double x);
UnaryFunction get_unary_function(const std::string& name);
UnaryFunction get_unary_function(int functionIndex);

typedef double (*MultiFunction)(std::list<expression>& args);
MultiFunction get_multi_function(const std::string& name);
MultiFunction get_multi_function(int functionIndex);
