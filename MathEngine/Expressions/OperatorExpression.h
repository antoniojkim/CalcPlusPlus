#pragma once

#include "Expression.h"
#include "OperatorExpressions/BinaryOperatorDirectory.h"

class BinaryOperatorExpression: public Expression {
    int operatorIndex;
    expression lhs;
    expression rhs;

    BinaryOperatorExpression(const char * lexeme, expression&& lhs, expression&& rhs);
    BinaryOperatorExpression(std::string& lexeme, expression&& lhs, expression&& rhs);
    BinaryOperatorExpression(int operatorIndex, expression&& lhs, expression&& rhs);

    public:
        static expression construct(const char * lexeme, expression&& lhs, expression&& rhs);
        static expression construct(std::string& lexeme, expression&& lhs, expression&& rhs);
        static expression construct(int operatorIndex, expression&& lhs, expression&& rhs);

        expression evaluate(const Variables& vars) override;

        EXPRESSION_OVERRIDES
};
