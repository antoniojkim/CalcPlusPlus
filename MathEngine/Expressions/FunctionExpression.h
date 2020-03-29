#pragma once

#include "Expression.h"
#include "FunctionExpressions/UnaryFunctionDirectory.h"

class UnaryFunctionExpression: public Expression {

    int functionIndex;
    UnaryFunction f;
    // UnaryFunction fprime;
    // UnaryFunction fint;
    expression arg;

  public:
    UnaryFunctionExpression(const std::string& name, expression&& arg);
    UnaryFunctionExpression(int functionIndex, expression&& arg);

    EXPRESSION_OVERRIDES

};

// class NargFunctionExpression: public Expression {

//     expression arg;
  
//   public:
//     FunctionExpression(expression lhs, expression rhs);

//     EXPRESSION_OVERRIDES

// };

