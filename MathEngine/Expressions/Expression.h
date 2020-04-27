#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_math.h>

struct Expression;
struct MatrixExpression;
struct TupleExpression;
struct BaseUnitExpression;
struct VariableExpression;

typedef std::unique_ptr<Expression> expression;
typedef std::unordered_map<std::string, expression> Variables;

double gsl_expression_function(double x, void* params);

struct Expression {

    virtual expression simplify() = 0;
    virtual expression derivative(const std::string& var) = 0;
    virtual expression integrate(const std::string& var) = 0;

    virtual bool evaluable() = 0;
    virtual expression evaluate();
    virtual expression evaluate(const Variables& vars);

    virtual gsl_function function() {
        gsl_function F;
        F.function = &gsl_expression_function;
        F.params = this;
        return F;
    }

    virtual double value();
    virtual double value(const Variables& vars) = 0;

    virtual gsl_complex complex();
    virtual gsl_complex complex(const Variables& vars);

    virtual inline MatrixExpression* matrix(){ return nullptr; }
    virtual inline TupleExpression* tuple(){ return nullptr; }
    virtual inline BaseUnitExpression* unit(){ return nullptr; }
    virtual inline VariableExpression* variable(){ return nullptr; }

    virtual bool isComplex() = 0;

    virtual expression copy() = 0;

    virtual std::ostream& print(std::ostream&) = 0;
    virtual std::ostream& postfix(std::ostream&) = 0;

};

std::ostream& operator<<(std::ostream&, expression&);

#define EXPRESSION_OVERRIDES                                       \
    expression simplify() override;                                \
    expression derivative(const std::string& var = "x") override;  \
    expression integrate(const std::string& var = "x") override;   \
    bool evaluable() override;                                     \
    double value(const Variables& vars) override;                  \
    bool isComplex() override;                                     \
    expression copy() override;                                    \
    std::ostream& print(std::ostream&) override;                   \
    std::ostream& postfix(std::ostream&) override;
