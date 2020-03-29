#pragma once

#include "Expression.h"
#include "OperatorExpressions/BinaryOperatorDirectory.h"

class BinaryOperatorExpression: public Expression {
    int operatorIndex;
    BinaryOperator f;
    BinaryOperatorDerivative fprime = nullptr;
    BinaryOperatorDerivative fint = nullptr;
    BinaryOperatorSimplify fsimplify = nullptr;
    expression lhs;
    expression rhs;

    public:
        BinaryOperatorExpression(const std::string& lexeme, expression&& lhs, expression&& rhs);
        BinaryOperatorExpression(int operatorIndex, expression&& lhs, expression&& rhs);

        EXPRESSION_OVERRIDES
};

expression operator+(expression&& expr1, expression&&expr2);
expression operator-(expression&& expr1, expression&&expr2);
expression operator*(expression&& expr1, expression&&expr2);
expression operator/(expression&& expr1, expression&&expr2);
expression operator^(expression&& expr1, expression&&expr2);
