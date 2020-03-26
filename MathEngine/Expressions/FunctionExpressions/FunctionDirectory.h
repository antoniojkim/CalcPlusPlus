#pragma once

#include <string>

typedef double (*UnaryFunction)(double x);

UnaryFunction get_unary_function(const std::string& name);
