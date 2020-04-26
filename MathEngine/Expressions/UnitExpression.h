#pragma once

#include <string>

#include <gsl/gsl_complex.h>

#include "Expression.h"
#include "UnitConversionExpression/Units.h"

class UnitExpression: public Expression {

    UnitType type;
    std::string abbr;
    double val;

    public:
        UnitExpression(const std::string& unit, double val = 1);
        UnitExpression(UnitType type, const std::string& unit, double val);

        expression evaluate(const Variables& vars) override;

        inline UnitExpression* unit() override { return this; }

        EXPRESSION_OVERRIDES


        friend expression operator*(UnitExpression& unit1, UnitExpression& unit2);
        friend expression operator*(UnitExpression& unit1, expression& expr);
        friend expression operator/(UnitExpression& unit1, UnitExpression& unit2);
        friend expression operator/(UnitExpression& unit1, expression& expr);
        friend expression operator^(UnitExpression& unit1, expression& expr);

        friend expression convert(UnitExpression& from, UnitExpression& to);
};
