#pragma once

#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/VariableExpression.h"
#include "../../Scanner/scanner.h"
#include "../Functions.h"

namespace Function {

    // @Operator eq = := <-
    const struct __eq__: public Function::OperatorFunction {
        __eq__(): OperatorFunction("=") {}
        expression eval(Function::Args& args) const override {
            using Scanner::VAR;
            auto l = args["l"];
            auto r = args["r"];
            if (l != VAR){
                throw Exception("Assignment operator expects variable. Got: ", l);
            }
            return VariableExpression::construct(l->repr(), r);
        }
    } eq;

}
