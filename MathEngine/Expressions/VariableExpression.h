#pragma once

#include "Expression.h"

class VariableExpression: public Expression {

    const std::string name;
    double num;

  public:
    VariableExpression(const std::string& name);
    VariableExpression(const std::string& name, double num);

    expression evaluate(const Variables& vars) override;

    inline VariableExpression* variable(){ return this; }
    inline const std::string& getName(){ return name; }

    EXPRESSION_OVERRIDES

};
