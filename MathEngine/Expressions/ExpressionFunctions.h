#pragma once

#include "Expression.h"
#include "FunctionExpression.h"

namespace ExpressionMath {
    #define EXPR_MATH(F) inline expression F(expression expr1){ return FunctionExpression::construct("F", expr1); }

    EXPR_MATH(abs)
    EXPR_MATH(sqr)
    EXPR_MATH(sqrt)
    EXPR_MATH(cb)
    EXPR_MATH(cbrt)

    EXPR_MATH(ln)

    // Trig Functions
    EXPR_MATH(sin)
    EXPR_MATH(cos)
    EXPR_MATH(tan)
    EXPR_MATH(csc)
    EXPR_MATH(sec)
    EXPR_MATH(cot)
    EXPR_MATH(asin)
    EXPR_MATH(acos)
    EXPR_MATH(atan)
    EXPR_MATH(acsc)
    EXPR_MATH(asec)
    EXPR_MATH(acot)
    EXPR_MATH(sinh)
    EXPR_MATH(cosh)
    EXPR_MATH(tanh)
    EXPR_MATH(csch)
    EXPR_MATH(sech)
    EXPR_MATH(coth)
    EXPR_MATH(asinh)
    EXPR_MATH(acosh)
    EXPR_MATH(atanh)
    EXPR_MATH(acsch)
    EXPR_MATH(asech)
    EXPR_MATH(acoth)

}
