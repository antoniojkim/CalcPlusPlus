#pragma once

#include <string>

#include "Expression.h"

class NumExpression: public Expression {

    double real, imag;
  
  public:
    NumExpression(double real, double imag = 0);
    NumExpression(const std::string&);

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

