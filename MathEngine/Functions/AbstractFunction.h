#pragma once
#include <iostream>
#include <string>

#include <gsl/gsl_math.h>

#include "../Expressions/Expression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Utils/Argparse.h"
#include "FunctionDispatch.h"

namespace Function {
    struct AbstractFunction {
        const int index;
        Function::Signature signature;
        AbstractFunction(const std::string& name, const std::string& signature);

        expression eval(expression e, const Variables& vars = emptyVars);
        virtual expression eval(Function::Args& args) = 0;
        inline expression operator()(expression e){ return eval(e); }

        double value(expression e, const Variables& vars = emptyVars);
        double value(Function::Args& args);
        virtual double value(double x) { return eval(NumExpression::construct(x))->value(); }
        inline double operator()(double x){ return value(x); }

        virtual expression simplify(expression e){ return e; }

        expression derivative(expression e, const std::string& var);
        virtual expression derivative(Function::Args& args, const std::string& var);

        virtual expression integral(expression e, const std::string& var);

        virtual std::ostream& print(std::ostream& out, expression e);
        virtual std::ostream& print(std::ostream& out, Function::Args& args);
    };

    struct ValueFunction: public AbstractFunction {
        typedef double(*DoubleFunction)(double);
        const DoubleFunction f;
        ValueFunction(const std::string& name, DoubleFunction f = nullptr);

        expression eval(Function::Args& args) override;
        inline double value(double x) override { return f(x); }
    };

    struct OperatorFunction: public AbstractFunction {
        OperatorFunction(const char* name);

        double value(double x) override { return GSL_NAN; }

        virtual std::ostream& print(std::ostream& out, Function::Args& args) override;
    };
}
