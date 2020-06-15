#pragma once
#include <iostream>
#include <string>

#include <gsl/gsl_math.h>

#include "../Expressions/Expression.h"
#include "../Expressions/FunctionExpression.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Utils/Argparse.h"
#include "../Utils/exceptions.h"
#include "FunctionDispatch.h"

namespace Function {
    struct AbstractFunction {
        expression evaluate(expression e){
            Function::Args args(e->evaluate());
            return evaluate(args);
        }
        expression evaluate(expression e, const Variables& vars){
            Function::Args args(e->evaluate(vars));
            return evaluate(args);
        }
        virtual expression evaluate(Function::Args& args) = 0;
        virtual double value(double x) = 0;

        inline expression operator()(expression e){ return evaluate(e); }
        inline double operator()(double x){ return value(x); }

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
        constexpr NamedFunction(const char* name): index{Functions::indexOf(name)} {}

        virtual double value(double x) override { return evaluate(NumExpression::construct(x))->value(); }

        virtual std::ostream& print(std::ostream& out, expression arg) override {
            out << Functions::names[index];
            if (arg->tuple()){
                return out << arg;
            }
            return out << "(" << arg << ")";
        }
    };

    typedef double(*DoubleFunction)(double);

    struct ValueFunction: public NamedFunction {
        const DoubleFunction f;
        constexpr ValueFunction(const char* name, const DoubleFunction f = nullptr): NamedFunction{name}, f{f} {}

        expression evaluate(Function::Args& args) override {
            if (args.size() == 1){
                if (args[0]->variable()){
                    return FunctionExpression::construct(index, args[0]);
                }
                return NumExpression::construct(value(args[0]->value()));
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments. Expected 1. Got: ", args));
        }
        inline double value(double x) override { return f(x); }
    };
}
