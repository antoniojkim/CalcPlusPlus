#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {

    // @Operator lshift: <<
    struct lshift: public OperatorFunctionExpression {
        lshift(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return ((long long int) intpartl) << ((long long int) intpartr);
            }
            throw Exception("l << r expects integers. Got: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(lshift)


    // @Operator rshift: >>
    struct rshift: public OperatorFunctionExpression {
        rshift(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return ((long long int) intpartl) >> ((long long int) intpartr);
            }
            throw Exception("l >> r expects integers. Got: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(rshift)


    // @Operator bitwise_and: &
    struct bitwise_and: public OperatorFunctionExpression {
        bitwise_and(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return ((long long int) intpartl) & ((long long int) intpartr);
            }
            throw Exception("l & r expects integers. Got: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(bitwise_and)


    // @Operator bitwise_or: |
    struct bitwise_or: public OperatorFunctionExpression {
        bitwise_or(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return ((long long int) intpartl) | ((long long int) intpartr);
            }
            throw Exception("l | r expects integers. Got: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(bitwise_or)


    // @Operator bitwise_xor: ^|
    struct bitwise_xor: public OperatorFunctionExpression {
        bitwise_xor(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return ((long long int) intpartl) ^ ((long long int) intpartr);
            }
            throw Exception("l ^| r expects integers. Got: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(bitwise_xor)

}
