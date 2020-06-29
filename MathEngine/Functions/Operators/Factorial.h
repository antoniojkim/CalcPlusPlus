#pragma once

#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Scanner/scanner.h"
#include "../AbstractFunction.h"

namespace Function {

    // @Operator choose C
    const struct __choose__: public OperatorFunction {
        __choose__(): OperatorFunction("C") {}
        expression evaluate(Function::Args& args) override {
            double n = args["l"]->value();
            double r = args["r"]->value();
            if (n >= r && r >= 0 && std::trunc(n) == n && std::trunc(r) == r){
                return NumExpression::construct(gsl_sf_choose((unsigned int) n, (unsigned int) r));
            }
            throw Exception("nCr expects integers n >= r. Got: ", args);
        }
    } choose;


    // @Operator permute P
    const struct __permute__: public OperatorFunction {
        __permute__(): OperatorFunction("P") {}
        expression evaluate(Function::Args& args) override {
            double n = args["l"]->value();
            double r = args["r"]->value();
            if (n >= r && r >= 0 && std::trunc(n) == n && std::trunc(r) == r){
                return gsl_sf_choose((unsigned int) n, (unsigned int) r) * gsl_sf_fact((unsigned int) r);
            }
            throw Exception("nPr expects integers n >= r. Got: ", args);
        }
    } permute;

}
