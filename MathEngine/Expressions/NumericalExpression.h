#pragma once

#include "Expression.h"

class NumericalExpression: public Expression {

    double num;
  
  public:
    NumericalExpression(double);

    EXPRESSION_OVERRIDES

};

