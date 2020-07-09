#pragma once

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
    namespace lshift {
        expression eval(Function::Args& args) {
            double l = args.nextValue();
            double r = args.nextValue();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) << ((long long int) intpartr));
            }
            throw Exception("l << r expects integers. Got: ", args);
        }
    }


    // @Operator rshift: >>
    namespace rshift {
        expression eval(Function::Args& args) {
            double l = args.nextValue();
            double r = args.nextValue();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) >> ((long long int) intpartr));
            }
            throw Exception("l >> r expects integers. Got: ", args);
        }
    }


    // @Operator bitwise_and: &
    namespace bitwise_and {
        expression eval(Function::Args& args) {
            double l = args.nextValue();
            double r = args.nextValue();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) & ((long long int) intpartr));
            }
            throw Exception("l & r expects integers. Got: ", args);
        }
    }


    // @Operator bitwise_or: |
    namespace bitwise_or {
        expression eval(Function::Args& args) {
            double l = args.nextValue();
            double r = args.nextValue();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) | ((long long int) intpartr));
            }
            throw Exception("l | r expects integers. Got: ", args);
        }
    }


    // @Operator bitwise_xor: ^|
    namespace bitwise_xor {
        expression eval(Function::Args& args) {
            double l = args.nextValue();
            double r = args.nextValue();
            double intpartl, intpartr;
            if (modf(l, &intpartl) == 0 && modf(r, &intpartr) == 0){
                return NumExpression::construct(((long long int) intpartl) ^ ((long long int) intpartr));
            }
            throw Exception("l ^| r expects integers. Got: ", args);
        }
    }

}
