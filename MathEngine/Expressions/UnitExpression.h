#pragma once

#include <string>

#include <gsl/gsl_complex.h>

#include "Expression.h"
#include "UnitConversionExpression/Units.h"

class BaseUnitExpression: public Expression {

    UnitType type;
    std::string abbr;
    double val;

    BaseUnitExpression(const std::string& unit, double val);
    BaseUnitExpression(UnitType type, const std::string& unit, double val);

    public:
        static expression construct(const std::string& unit, double val = 1);
        static expression construct(UnitType type, const std::string& unit, double val);

        expression evaluate(const Variables& vars) override;

        inline BaseUnitExpression* unit() override { return this; }

        EXPRESSION_OVERRIDES


        friend expression operator*(BaseUnitExpression& unit1, BaseUnitExpression& unit2);
        friend expression operator*(BaseUnitExpression& unit1, expression& expr);
        friend expression operator/(BaseUnitExpression& unit1, BaseUnitExpression& unit2);
        friend expression operator/(BaseUnitExpression& unit1, expression& expr);
        friend expression operator^(BaseUnitExpression& unit1, expression& expr);

        friend expression convert(BaseUnitExpression& from, BaseUnitExpression& to);
};

class ConvertedUnitExpression: public Expression {

    UnitType type;
    std::string abbr;
    double val;

    ConvertedUnitExpression(UnitType type, const std::string& unit, double val);

    public:
        static expression construct(UnitType type, const std::string& unit, double val);

        expression evaluate(const Variables& vars) override;

        EXPRESSION_OVERRIDES
};
