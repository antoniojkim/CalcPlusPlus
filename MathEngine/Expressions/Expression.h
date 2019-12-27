#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include <memory>
#include <string>

#include "../Parser/parsetree.h"

struct Expression;

typedef std::unique_ptr<Expression> expression;

struct Expression {
  
    virtual expression simplify() = 0;
    virtual expression derivative(const std::string& var) = 0;
    virtual expression integrate(const std::string& var) = 0;
    
    virtual bool evaluable() = 0;
    virtual expression evaluate();

    virtual double value() = 0;
    virtual double value(const double& x) = 0;
    virtual double value(const double& x, const double& y) = 0;

    virtual bool complex() = 0;

    virtual expression copy() = 0;

};

expression generate_expression(ParseTree*);

#define EXPRESSION_OVERRIDES \
    expression simplify() override; \
    expression derivative(const std::string& var = "x") override; \
    expression integrate(const std::string& var = "x") override; \
    bool evaluable() override; \
    double value() override; \
    double value(const double& x) override; \
    double value(const double& x, const double& y) override; \
    bool complex() override; \
    expression copy() override;

#endif // __EXPRESSION_H__
