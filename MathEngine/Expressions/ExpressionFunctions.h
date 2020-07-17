#pragma once

#include "Expression.h"
#include "FunctionExpression.h"

namespace ExpressionMath {
    #define EXPR_MATH(F, S) inline expression F(expression expr1){ return FunctionExpression::construct(S, expr1); }

    EXPR_MATH(abs, "abs")
    EXPR_MATH(sqr, "sqr")
    EXPR_MATH(sqrt, "sqrt")
    EXPR_MATH(cb, "cb")
    EXPR_MATH(cbrt, "cbrt")

    EXPR_MATH(exp, "exp")
    EXPR_MATH(exp2, "exp2")
    EXPR_MATH(expm1, "expm1")
    EXPR_MATH(ln, "ln")

    // Trig Functions
    EXPR_MATH(sin, "sin")
    EXPR_MATH(cos, "cos")
    EXPR_MATH(tan, "tan")
    EXPR_MATH(csc, "csc")
    EXPR_MATH(sec, "sec")
    EXPR_MATH(cot, "cot")
    EXPR_MATH(asin, "asin")
    EXPR_MATH(acos, "acos")
    EXPR_MATH(atan, "atan")
    EXPR_MATH(acsc, "acsc")
    EXPR_MATH(asec, "asec")
    EXPR_MATH(acot, "acot")
    EXPR_MATH(sinh, "sinh")
    EXPR_MATH(cosh, "cosh")
    EXPR_MATH(tanh, "tanh")
    EXPR_MATH(csch, "csch")
    EXPR_MATH(sech, "sech")
    EXPR_MATH(coth, "coth")
    EXPR_MATH(asinh, "asinh")
    EXPR_MATH(acosh, "acosh")
    EXPR_MATH(atanh, "atanh")
    EXPR_MATH(acsch, "acsch")
    EXPR_MATH(asech, "asech")
    EXPR_MATH(acoth, "acoth")

}
