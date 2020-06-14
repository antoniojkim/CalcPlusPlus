#pragma once

#include <cmath>

#include <gsl/gsl_sf_log.h>

#include "../Expressions/Expression.h"
#include "../Expressions/ExpressionFunctions.h"
#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/InvalidExpression.h"
#include "../Utils/Argparse.h"
#include "AbstractFunction.h"

namespace Function {
    // @Function exp
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("exp", e);
        }
    } exp ("exp", std::exp);

    // @Function exp2
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("exp2", e) * M_LN2;
        }
    } exp2 ("exp2", std::exp2);

    // @Function expm1
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("expm1", e);
        }
    } expm1 ("expm1", std::expm1);

    // @Function ln
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / e;
        }
    } ln ("ln", std::log);

    // @Function ln2 log2
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / (e * M_LN2);
        }
    } ln2 ("ln2", std::log2);

    // @Function ln1p log1p
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / (e + 1);
        }
    } ln1p ("ln1p", std::log1p);

    // @Function log log10
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / (e * M_LN10);
        }
    } log ("log", std::log10);

    // @Function log1pm
    const ValueFunction log1pm ("log1pm", gsl_sf_log_1plusx_mx);

    // @Function logabs
    const ValueFunction logabs ("logabs", gsl_sf_log_abs);

    // @Function logn
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 2){
                return std::log(args[0]->value()) / std::log(args[1]->value());
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: logn. Expected 2. Got ", args.size()));
        }
        // expression derivative(expression e, const std::string& var) override {
        //     ParsedArgs args(e);
        //     if (args.size() == 2){
        //         return getOperatorDerivative("/")(tuple->front(), tuple->back(), var);
        //     }
        //     return InvalidExpression::construct(Exception("Invalid number of arguments for fprime_logn"));
        // }
    } logn ("logn");
}
