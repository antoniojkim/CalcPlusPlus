#pragma once

#include <string>

#include <gsl/gsl_complex.h>

#include "Expression.h"

namespace calcpp {

    struct NumericalExpression: public Expression {
        expression derivative(const std::string& var) override;
        expression integrate(const std::string& var) override;
    };

    class NumExpression: public NumericalExpression {
        const Double val;

        NumExpression(const Double val);

      public:
        static expression construct(Double val);
        // static expression construct(const gsl_complex& z);

        EXPRESSION_OVERRIDES
    };

    class ComplexExpression: public NumericalExpression {
        const Double real, imag;

        ComplexExpression(const Double real, const Double imag);

      public:
        static expression construct(const Double real, const Double imag);
        static expression construct(const gsl_complex& z);

        Double get(const int index) override;

        EXPRESSION_OVERRIDES
    };

    class HexExpression: public NumericalExpression {
        unsigned long long num;

        HexExpression(unsigned long long num);

      public:
        static expression construct(unsigned long long num);

        EXPRESSION_OVERRIDES
    };

    class BinExpression: public NumericalExpression {
        unsigned long long num;

        BinExpression(unsigned long long num);

      public:
        static expression construct(unsigned long long num);

        EXPRESSION_OVERRIDES
    };

}  // namespace calcpp
