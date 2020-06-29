#pragma once

#include <string>

#include "../Expression.h"

typedef double (*UnaryOperator)(double);
UnaryOperator getUnaryOperator(const std::string& name);
UnaryOperator getUnaryOperator(int functionIndex);

typedef double (*BinaryOperator)(double, double);
BinaryOperator getBinaryOperator(const std::string& name);
BinaryOperator getBinaryOperator(int functionIndex);

typedef expression (*OperatorExpr)(const expression, const expression, const Variables& vars);
OperatorExpr getOperatorExpr(const std::string& name);
OperatorExpr getOperatorExpr(int functionIndex);

typedef expression (*OperatorDerivative)(const expression, const expression, const std::string&);
OperatorDerivative getOperatorDerivative(const std::string& name);
OperatorDerivative getOperatorDerivative(int functionIndex);

typedef expression (*OperatorIntegral)(const expression, const expression, const std::string&);
OperatorIntegral getOperatorIntegral(const std::string& name);
OperatorIntegral getOperatorIntegral(int functionIndex);

typedef expression (*OperatorSimplify)(const expression, const expression);
OperatorSimplify getOperatorSimplify(const std::string& name);
OperatorSimplify getOperatorSimplify(int functionIndex);
