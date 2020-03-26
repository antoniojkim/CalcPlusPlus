#pragma once

#include "Expression.h"

#define BINARY_EXPRESSION(TYPE)                                   \
  class TYPE ## Expression: public Expression {                   \
      expression lhs;                                             \
      expression rhs;                                             \
                                                                  \
    public:                                                       \
      TYPE ## Expression(expression lhs, expression rhs);     \
                                                                  \
      EXPRESSION_OVERRIDES                                        \
  };                                                              \
  bool TYPE ## Expression::evaluable(){ return lhs->evaluable() && rhs->evaluable(); } \
  bool TYPE ## Expression::complex(){ return lhs->complex() || rhs->complex(); }


BINARY_EXPRESSION(Addition)
BINARY_EXPRESSION(Subtraction)
BINARY_EXPRESSION(Multiplication)
BINARY_EXPRESSION(Division)
BINARY_EXPRESSION(IntegerDivision)
BINARY_EXPRESSION(ModulusDivision)
BINARY_EXPRESSION(Exponent)


expression operator+(expression&& expr1, expression&&expr2);
expression operator-(expression&& expr1, expression&&expr2);
expression operator*(expression&& expr1, expression&&expr2);
expression operator/(expression&& expr1, expression&&expr2);
expression operator^(expression&& expr1, expression&&expr2);
