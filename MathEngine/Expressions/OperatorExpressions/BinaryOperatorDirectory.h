#pragma once

#include <string>

#include "../Expression.h"

typedef double (*BinaryOperator)(double, double);
BinaryOperator getBinaryOperator(const std::string& name);
BinaryOperator getBinaryOperator(int functionIndex);

typedef expression (*BinaryOperatorExpr)(expression&, expression&, const Variables& vars);
BinaryOperatorExpr getBinaryOperatorExpr(const std::string& name);
BinaryOperatorExpr getBinaryOperatorExpr(int functionIndex);

typedef expression (*BinaryOperatorDerivative)(expression&, expression&, const std::string&);
BinaryOperatorDerivative getBinaryOperatorDerivative(const std::string& name);
BinaryOperatorDerivative getBinaryOperatorDerivative(int functionIndex);

typedef expression (*BinaryOperatorIntegral)(expression&, expression&, const std::string&);
BinaryOperatorIntegral getBinaryOperatorIntegral(const std::string& name);
BinaryOperatorIntegral getBinaryOperatorIntegral(int functionIndex);

typedef expression (*BinaryOperatorSimplify)(expression&, expression&);
BinaryOperatorSimplify getBinaryOperatorSimplify(const std::string& name);
BinaryOperatorSimplify getBinaryOperatorSimplify(int functionIndex);
