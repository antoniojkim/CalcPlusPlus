#pragma once

#include <string>

#include <gsl/gsl_complex.h>

#include "Expression.h"

class NumExpression: public Expression {

    double real, imag;

  public:
    NumExpression(double real, double imag = 0);
    NumExpression(const gsl_complex& z);
    NumExpression(const std::string&);

    gsl_complex complex() override;
    gsl_complex complex(const Variables& vars) override;

    EXPRESSION_OVERRIDES

};

class HexExpression: public Expression {

    unsigned long long num;

  public:
    HexExpression(unsigned long long num);
    HexExpression(const std::string&);

    EXPRESSION_OVERRIDES

};

class BinExpression: public Expression {

    unsigned long long num;

  public:
    BinExpression(unsigned long long num);
    BinExpression(const std::string&);

    EXPRESSION_OVERRIDES

};
