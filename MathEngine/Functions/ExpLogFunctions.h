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
    const struct exp: public Function::ValueFunction {
        exp(): ValueFunction("exp", std::exp) {}
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("exp", e);
        }
    } __exp__;

    // @Function exp2
    const struct exp2: public Function::ValueFunction {
        exp2(): ValueFunction("exp", std::exp2) {}
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("exp2", e) * M_LN2;
        }
    } __exp2__;

    // @Function expm1
    const struct expm1: public Function::ValueFunction {
        expm1(): ValueFunction("expm1", std::expm1) {}
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("expm1", e);
        }
    } __expm1__;

    // @Function ln
    const struct ln: public Function::ValueFunction {
        ln(): ValueFunction("ln", std::log) {}
        expression derivative(expression e, const std::string& var) override {
            return 1 / e;
        }
    } __ln__;

    // @Function ln2 log2
    const struct ln2: public Function::ValueFunction {
        ln2(): ValueFunction("ln2", std::log2) {}
        expression derivative(expression e, const std::string& var) override {
            return 1 / (e * M_LN2);
        }
    } __ln2__;

    // @Function ln1p log1p
    const struct ln1p: public Function::ValueFunction {
        ln1p(): ValueFunction("ln1p", std::log1p) {}
        expression derivative(expression e, const std::string& var) override {
            return 1 / (e + 1);
        }
    } __ln1p__;

    // @Function log log10
    const struct log: public Function::ValueFunction {
        log(): ValueFunction("log", std::log10) {}
        expression derivative(expression e, const std::string& var) override {
            return 1 / (e * M_LN10);
        }
    } __log__;

    // @Function log1pm
    const Function::ValueFunction log1pm ("log1pm", gsl_sf_log_1plusx_mx);

    // @Function logabs
    const Function::ValueFunction logabs ("logabs", gsl_sf_log_abs);

    // @Function logn
    const struct logn: public Function::NamedFunction {
        logn(): NamedFunction("logn") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                return NumExpression::construct(std::log(args[0]->value()) / std::log(args[1]->value()));
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
    } __logn__;
}
