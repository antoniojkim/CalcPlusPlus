#pragma once

#include "Expression.h"

class VariableExpression: public Expression {

    const std::string& name;
    double num;
  
  public:
    VariableExpression(const std::string& name);
    VariableExpression(const std::string& name, const double& num);

    EXPRESSION_OVERRIDES

};

#define VARIABLE_EXPRESSION(var)                                \
    class Variable ## var ## Expression: public Expression {    \
      public:                                                   \
        Variable ## var ## Expression();                        \
                                                                \
        EXPRESSION_OVERRIDES                                    \
                                                                \
    };

VARIABLE_EXPRESSION(X)
VARIABLE_EXPRESSION(Y)
// VARIABLE_EXPRESSION(Z)

