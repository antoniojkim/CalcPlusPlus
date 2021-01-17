#pragma once

#include "Expression.h"

class PolynomialExpression: public Expression {

    PolynomialExpression(const std::vector<expression>& coefficients);

    public:
        expression construct(const std::vector<expression>& coefficients);

        EXPRESSION_OVERRIDES
};
