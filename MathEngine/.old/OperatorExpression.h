#pragma once

#include "Expression.h"
#include "OperatorExpressions/OperatorDirectory.h"

class OperatorExpression: public Expression {
    int operatorIndex;
    expression lhs;
    expression rhs;

    OperatorExpression(int operatorIndex, expression lhs, expression rhs = nullptr);

    public:
        static expression construct(const char * lexeme, expression lhs, expression rhs = nullptr);
        static expression construct(std::string& lexeme, expression lhs, expression rhs = nullptr);
        static expression construct(int operatorIndex, expression lhs, expression rhs = nullptr);

        expression evaluate(const Variables& vars) override;

        inline OperatorExpression* operatorExpr() override { return this; }

        EXPRESSION_OVERRIDES

        /*
        Used to correct the order of operations
        */
        friend expression pivot(OperatorExpression* o1, OperatorExpression* o2);
};
