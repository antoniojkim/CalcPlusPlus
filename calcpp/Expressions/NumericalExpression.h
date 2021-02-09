#pragma once

#include <string>

#include <gsl/gsl_complex.h>

#include "Expression.h"

namespace calcpp {

    struct NumericalExpression: public Expression {
        expression derivative(const expression var) override;
        expression integrate(const expression var) override;
    };

    class NumExpression: public NumericalExpression {
        const Double val;

        NumExpression(const Double val);

      public:
        DECLARE_TEMPLATE_CONSTRUCTOR(num);

        EXPRESSION_OVERRIDES
    };

    class ComplexExpression: public NumericalExpression {
        const Double real, imag;

        ComplexExpression(const Double real, const Double imag);
        ComplexExpression(const gsl_complex& z);

      public:
        DECLARE_TEMPLATE_CONSTRUCTOR(complex);

        Double get(const int index) override;

        EXPRESSION_OVERRIDES
    };

    class HexExpression: public NumericalExpression {
        unsigned long long num;

        HexExpression(unsigned long long num);

      public:
        DECLARE_TEMPLATE_CONSTRUCTOR(hex);

        EXPRESSION_OVERRIDES
    };

    class BinExpression: public NumericalExpression {
        unsigned long long num;

        BinExpression(unsigned long long num);

      public:
        DECLARE_TEMPLATE_CONSTRUCTOR(bin);

        EXPRESSION_OVERRIDES
    };

    /*********************************************************************
     ******************* Templated Constructor Accessors *****************
     *********************************************************************/

    DEFINE_TEMPLATE_CONSTRUCTOR(Num, num);
    DEFINE_TEMPLATE_CONSTRUCTOR(Complex, complex);
    DEFINE_TEMPLATE_CONSTRUCTOR(Hex, hex);
    DEFINE_TEMPLATE_CONSTRUCTOR(Bin, bin);

}  // namespace calcpp
