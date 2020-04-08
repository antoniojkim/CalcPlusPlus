#pragma once

#include "Expression.h"

class VariableExpression: public Expression {

    const std::string name;
    double num;
  
  public:
    VariableExpression(const std::string& name);
    VariableExpression(const std::string& name, double num);

    EXPRESSION_OVERRIDES

};
