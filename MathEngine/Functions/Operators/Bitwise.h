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

    // @Operator lshift <<
    const struct __lshift__: public OperatorFunction {
        __lshift__(): OperatorFunction("<<") {}
        expression eval(Function::Args& args) const override {
            double l = args["l"]->value();
            double r = args["r"]->value();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) << ((long long int) intpartr));
            }
            throw Exception("l << r expects integers. Got: ", args);
        }
    } lshift;


    // @Operator rshift >>
    const struct __rshift__: public OperatorFunction {
        __rshift__(): OperatorFunction(">>") {}
        expression eval(Function::Args& args) const override {
            double l = args["l"]->value();
            double r = args["r"]->value();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) >> ((long long int) intpartr));
            }
            throw Exception("l >> r expects integers. Got: ", args);
        }
    } rshift;


    // @Operator bitwise_and &
    const struct __and__: public OperatorFunction {
        __and__(): OperatorFunction("&") {}
        expression eval(Function::Args& args) const override {
            double l = args["l"]->value();
            double r = args["r"]->value();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) & ((long long int) intpartr));
            }
            throw Exception("l & r expects integers. Got: ", args);
        }
    } bitwise_and;


    // @Operator bitwise_or |
    const struct __or__: public OperatorFunction {
        __or__(): OperatorFunction("|") {}
        expression eval(Function::Args& args) const override {
            double l = args["l"]->value();
            double r = args["r"]->value();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) | ((long long int) intpartr));
            }
            throw Exception("l | r expects integers. Got: ", args);
        }
    } bitwise_or;


    // @Operator bitwise_xor ^|
    const struct __xor__: public OperatorFunction {
        __xor__(): OperatorFunction("^|") {}
        expression eval(Function::Args& args) const override {
            double l = args["l"]->value();
            double r = args["r"]->value();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) ^ ((long long int) intpartr));
            }
            throw Exception("l ^| r expects integers. Got: ", args);
        }
    } bitwise_xor;

}
