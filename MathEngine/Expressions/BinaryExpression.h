#ifndef __BINARY_EXPRESSIONS_H__
#define __BINARY_EXPRESSIONS_H__

#include "Expression.h"

#define BINARY_EXPRESSION(TYPE)                                   \
  class TYPE ## Expression: public Expression {                   \
      expression lhs;                                             \
      expression rhs;                                             \
                                                                  \
    public:                                                       \
      TYPE ## Expression(expression&& lhs, expression&& rhs);     \
                                                                  \
      EXPRESSION_OVERRIDES                                        \
  };                                                              

BINARY_EXPRESSION(Addition)
BINARY_EXPRESSION(Subtraction)
BINARY_EXPRESSION(Multiplication)
BINARY_EXPRESSION(Division)
BINARY_EXPRESSION(IntegerDivision)
BINARY_EXPRESSION(ModulusDivision)
BINARY_EXPRESSION(Exponent)

#endif // __BINARY_EXPRESSIONS_H__
