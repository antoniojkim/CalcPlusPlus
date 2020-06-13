#pragma once

#include <cmath>

#include <gsl/gsl_sf_log.h>

#include "../Expressions/Expression.h"
#include "../Expressions/InvalidExpression.h"
#include "AbstractFunction.h"
#include "Argparse.h"
#include "Math.h"

namespace Function {
    // @Function exp
    const ValueFunction exp ("exp", std::exp);

    // @Function exp2
    const ValueFunction exp2 ("exp2", std::exp2);

    // @Function expm1
    const ValueFunction expm1 ("expm1", std::expm1);

    // @Function ln
    const ValueFunction ln ("ln", std::log);

    // @Function ln2
    const ValueFunction ln2 ("ln2", std::log2);

    // @Function ln1p
    const ValueFunction ln1p ("ln1p", std::log1p);

    // @Function log
    const ValueFunction log ("log", std::log10);

    // @Function log2
    const ValueFunction log2 ("log2", std::log2);

    // @Function log1p
    const ValueFunction log1p ("log1p", std::log1p);

    // @Function log1pm
    const ValueFunction log1p ("log1pm", gsl_sf_log_1plusx_mx);

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
    } logn ("logn");
}
