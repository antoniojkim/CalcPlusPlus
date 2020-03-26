#pragma once

#include <string>

#include "Expression.h"

class NumericalExpression: public Expression {

    double real, imag;
  
  public:
    NumericalExpression(double real, double imag = 0);
    NumericalExpression(const std::string&);

    EXPRESSION_OVERRIDES

};

