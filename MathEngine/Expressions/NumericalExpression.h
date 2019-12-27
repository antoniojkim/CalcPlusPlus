#ifndef __NUMERICAL_EXPRESSIONS_H__
#define __NUMERICAL_EXPRESSIONS_H__

#include "Expression.h"

class NumericalExpression: public Expression {

    double num;
  
  public:
    NumericalExpression(double);

    EXPRESSION_OVERRIDES

};

#endif // __NUMERICAL_EXPRESSIONS_H__
