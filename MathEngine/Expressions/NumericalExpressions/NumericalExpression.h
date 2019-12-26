#ifndef __NUMERICAL_EXPRESSIONS_H__
#define __NUMERICAL_EXPRESSIONS_H__

#include "../Expression.h"

class NumericalExpression: public Expression {

    double num;
  
    expression simplify() override;
    expression derivative() override;
    expression integrate() override;
    
    expression evaluate() override;
    double value() override;

    void setX() override;
    void setY() override;

};

#endif // __NUMERICAL_EXPRESSIONS_H__
