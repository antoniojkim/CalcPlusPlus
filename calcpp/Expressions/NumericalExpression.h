#pragma once

#include <string>

#include <gsl/gsl_complex.h>

#include "Expression.h"

struct NumericalExpression: public Expression {

    NumericalExpression(Scanner::Type kind);

    expression derivative(const std::string& var) override;
    expression integrate(const std::string& var) override;
};

class NumExpression: public NumericalExpression {
    double real, imag;

    NumExpression(double real, double imag);
    NumExpression(const std::string&);

    public:
        static expression construct(double real, double imag = 0);
        static expression construct(const gsl_complex& z);
        static expression construct(const std::string&);

        bool isNumber() const override { return true; }

        gsl_complex complex(const Variables& vars = emptyVars) const override;

        EXPRESSION_OVERRIDES

};

class HexExpression: public NumericalExpression {
    unsigned long long num;

    HexExpression(unsigned long long num);
    HexExpression(const std::string&);

    public:
        static expression construct(unsigned long long num);
        static expression construct(const std::string&);

        bool isNumber() const override { return true; }

        EXPRESSION_OVERRIDES

};

class BinExpression: public NumericalExpression {
    unsigned long long num;

    BinExpression(unsigned long long num);
    BinExpression(const std::string&);

    public:
        static expression construct(unsigned long long num);
        static expression construct(const std::string&);

        bool isNumber() const override { return true; }

        EXPRESSION_OVERRIDES

};
