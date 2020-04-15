#pragma once

#include <list>

#include "Expression.h"
#include "FunctionExpressions/FunctionDirectory.h"

class UnaryFunctionExpression: public Expression {

    int functionIndex;
    // UnaryFunction fprime;
    // UnaryFunction fint;
    expression arg;

  public:
    UnaryFunctionExpression(const std::string& name, expression&& arg);
    UnaryFunctionExpression(int functionIndex, expression&& arg);

    expression evaluate(const Variables& vars) override;

    EXPRESSION_OVERRIDES

};

class MultiFunctionExpression: public Expression {

    int functionIndex;
    std::list<expression> args;

  public:
    MultiFunctionExpression(const std::string& name, std::list<expression>&& args);
    MultiFunctionExpression(int functionIndex, std::list<expression>&& args);

    expression evaluate(const Variables& vars) override;

    EXPRESSION_OVERRIDES

};
