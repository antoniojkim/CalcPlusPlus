#pragma once

#include <string>

#include "../Expression.h"

typedef double (*BinaryOperator)(double, double);
typedef expression (*BinaryOperatorDerivative)(expression&, expression&, const std::string&);
typedef expression (*BinaryOperatorIntegral)(expression&, expression&, const std::string&);
typedef expression (*BinaryOperatorSimplify)(expression&, expression&);

BinaryOperator getBinaryOperator(const std::string& name);
BinaryOperator getBinaryOperator(int functionIndex);
