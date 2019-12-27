#ifndef __BINARY_EXPRESSIONS_H__
#define __BINARY_EXPRESSIONS_H__

#include "Expression.h"

class AdditionExpression: public Expression {

    expression lhs;
    expression rhs;
  
  public:
    AdditionExpression(expression&& lhs, expression&&rhs);

    EXPRESSION_OVERRIDES

};

#endif // __BINARY_EXPRESSIONS_H__
