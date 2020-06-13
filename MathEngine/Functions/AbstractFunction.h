#pragma once
#include <iostream>
#include <string>

#include <gsl/gsl_math.h>

#include "../Expressions/Expression.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Utils/Exception.h"
#include "FunctionDispatch.h"

struct AbstractFunction {
    virtual expression evaluate(expression arg) = 0;
    virtual double value(double x) = 0;

    virtual expression simplify(expression e){ return e; }

    virtual expression derivative(expression e, const std::string& var){
        return InvalidExpression::construct(Exception("Not Differentiable: ", e));
    }

    virtual expression integral(expression e, const std::string& var){
        return InvalidExpression::construct(Exception("Not Integrable: ", e));
    }

    virtual std::ostream& print(std::ostream& out, expression arg){
        return out << arg;
    }
};

struct NamedFunction: public AbstractFunction {
    const int index;
    constexpr NamedFunction(const char* name): index{Function::indexof(name)} {}

    virtual value(double x) override { return evaluate(NumExpression::construct(x))->value(); }

    virtual std::ostream& print(std::ostream& out, expression arg) override {
        out << Function::names[index];
        if (arg->tuple()){
            return out << arg;
        }
        return out << "(" << arg << ")";
    }
};

typedef double(*DoubleFunction)(double);

struct ValueFunction: public NamedFunction {
    const DoubleFunction f;
    constexpr ValueFunction(const char* name, const DoubleFunction f): NamedFunction{name}, f{f} {}

    expression evaluate(expression arg) override { return NumExpression::construct(value(arg->value())); }
    inline double value(double x) override { return f(x); }
};
