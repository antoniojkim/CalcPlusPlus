#ifndef __FUNCTION_EXPRESSIONS_H__
#define __FUNCTION_EXPRESSIONS_H__

#include "Expression.h"
#include "FunctionExpressions/FunctionDirectory.h"

class UnaryFunctionExpression: public Expression {

    const std::string& name;
    UnaryFunction f;
    // UnaryFunction fprime;
    // UnaryFunction fint;
    expression arg;
  
  public:
    UnaryFunctionExpression(const std::string& name, expression&& arg);

    EXPRESSION_OVERRIDES

};

// class NargFunctionExpression: public Expression {

//     expression arg;
  
//   public:
//     FunctionExpression(expression&& lhs, expression&&rhs);

//     EXPRESSION_OVERRIDES

// };

#endif // __FUNCTION_EXPRESSIONS_H__
