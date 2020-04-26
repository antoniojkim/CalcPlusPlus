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

        gsl_complex complex() override;
        gsl_complex complex(const Variables& vars) override;

        EXPRESSION_OVERRIDES

};

class HexExpression: public Expression {

    unsigned long long num;

    HexExpression(unsigned long long num);
    HexExpression(const std::string&);

    public:
        static expression construct(unsigned long long num);
        static expression construct(const std::string&);

        EXPRESSION_OVERRIDES

};

class BinExpression: public Expression {

    unsigned long long num;

    BinExpression(unsigned long long num);
    BinExpression(const std::string&);

    public:
        static expression construct(unsigned long long num);
        static expression construct(const std::string&);

        EXPRESSION_OVERRIDES

};
