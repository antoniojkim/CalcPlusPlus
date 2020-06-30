#pragma once

#include <cmath>

#include <gsl/gsl_sf_log.h>

#include "../Expressions/Expression.h"
#include "../Expressions/ExpressionFunctions.h"
#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/InvalidExpression.h"
#include "../Utils/Argparse.h"
#include "../AbstractFunction.h"

namespace Function {
    // @Function exp
    const struct __exp__: public Function::ValueFunction {
        __exp__(): ValueFunction("exp", std::exp) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::exp;
            auto x = args["x"];
            return exp(x) * x->derivative(var);
        }
    } __exp__;

    // @Function exp2
    const struct __exp2__: public Function::ValueFunction {
        __exp2__(): ValueFunction("exp", std::exp2) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::exp2;
            auto x = args["x"];
            return exp2(x) * M_LN2 * x->derivative(var);
        }
    } exp2;

    // @Function expm1
    const struct __expm1__: public Function::ValueFunction {
        __expm1__(): ValueFunction("expm1", std::expm1) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::expm1;
            auto x = args["x"];
            return expm1(x) * x->derivative(var);
        }
    } expm1;

    // @Function ln
    const struct __ln__: public Function::ValueFunction {
        __ln__(): ValueFunction("ln", std::log) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            auto x = args["x"];
            return x->derivative(var) / x;
        }
    } ln;

    // @Function ln2 log2
    const struct __ln2__: public Function::ValueFunction {
        __ln2__(): ValueFunction("ln2", std::log2) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            auto x = args["x"];
            return x->derivative(var) / (x * M_LN2);
        }
    } ln2;

    // @Function ln1p log1p
    const struct __ln1p__: public Function::ValueFunction {
        __ln1p__(): ValueFunction("ln1p", std::log1p) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            auto x = args["x"];
            return x->derivative(var) / (x + 1);
        }
    } ln1p;

    // @Function log log10
    const struct __log__: public Function::ValueFunction {
        __log__(): ValueFunction("log", std::log10) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            auto x = args["x"];
            return x->derivative(var) / (x * M_LN10);
        }
    } log;

    // @Function log1pm
    const Function::ValueFunction log1pm ("log1pm", gsl_sf_log_1plusx_mx);

    // @Function logabs
    const Function::ValueFunction logabs ("logabs", gsl_sf_log_abs);

    // @Function logn
    const struct __logn__: public Function::AbstractFunction {
        __logn__(): AbstractFunction("logn", "(a, b)") {}
        expression evaluate(Function::Args& args) override {
            auto a = args["a"];
            auto a = args["b"];
            return NumExpression::construct(std::log(a->value()) / std::log(b->value()));
        }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::ln;
            auto a = args["a"];
            auto a = args["b"];
            return a->derivative(var) / (a * ln(b));
        }
    } logn;
}
