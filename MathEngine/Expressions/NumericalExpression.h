#pragma once

#include <string>

#include <gsl/gsl_complex.h>

#include "Expression.h"

class NumExpression: public Expression {

    double real, imag;

    NumExpression(double real, double imag);
    NumExpression(const std::string&);

    public:
        static expression construct(double real, double imag = 0);
        static expression construct(const gsl_complex& z);
        static expression construct(const std::string&);

        expression evaluate(const Variables&) override;

        gsl_complex complex() const override;
        gsl_complex complex(const Variables& vars) const override;

        EXPRESSION_OVERRIDES

        inline const NumExpression* num() const override { return this; }

        bool prettyprint(std::ostream&) const override;

};

class HexExpression: public Expression {

    unsigned long long num;

    HexExpression(unsigned long long num);
    HexExpression(const std::string&);

    public:
        static expression construct(unsigned long long num);
        static expression construct(const std::string&);

        expression evaluate(const Variables&) override;

        EXPRESSION_OVERRIDES

        inline const HexExpression* hex() const override { return this; }

};

class BinExpression: public Expression {

    unsigned long long num;

    BinExpression(unsigned long long num);
    BinExpression(const std::string&);

    public:
        static expression construct(unsigned long long num);
        static expression construct(const std::string&);

        expression evaluate(const Variables&) override;

        EXPRESSION_OVERRIDES

        inline const BinExpression* bin() const override { return this; }

};
