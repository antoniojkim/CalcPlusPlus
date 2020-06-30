#pragma once
#include <iostream>
#include <string>

#include <gsl/gsl_math.h>

#include "../Expressions/Expression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Utils/Argparse.h"

namespace Function {
    struct AbstractFunction {
        const int index;
        const Function::Signature signature;
        AbstractFunction(const std::string& name, const std::string& signature);

        expression eval(expression e, const Variables& vars = emptyVars) const;
        virtual expression eval(Function::Args& args) const = 0;
        inline expression operator()(expression e) const { return eval(e); }

        double value(expression e, const Variables& vars = emptyVars) const;
        double value(Function::Args& args) const;
        virtual double value(double x) const { return eval(NumExpression::construct(x))->value(); }
        inline double operator()(double x) const { return value(x); }

        virtual expression simplify(expression e) const { return e; }

        expression derivative(expression e, const std::string& var) const;
        virtual expression derivative(Function::Args& args, const std::string& var) const;

        expression integrate(expression e, const std::string& var) const;
        virtual expression integrate(Function::Args& args, const std::string& var) const;

        std::ostream& print(std::ostream& out, expression e) const;
        virtual std::ostream& print(std::ostream& out, Function::Args& args) const;
    };

    struct ValueFunction: public AbstractFunction {
        typedef double(*DoubleFunction)(double);
        const DoubleFunction f;
        ValueFunction(const std::string& name, DoubleFunction f = nullptr);

        expression eval(Function::Args& args) const override;
        inline double value(double x) const override { return f(x); }
    };

    struct OperatorFunction: public AbstractFunction {
        OperatorFunction(const char* name);

        double value(double x) const override { return GSL_NAN; }

        virtual std::ostream& print(std::ostream& out, Function::Args& args) const override;
    };
}
