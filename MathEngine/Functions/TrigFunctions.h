#pragma once

#include <cmath>

#include <gsl/gsl_math.h>

#include "../Expressions/Expression.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/TupleExpression.h"
#include "AbstractFunction.h"
#include "Argparse.h"

namespace Function {
    // @Function sin
    const ValueFunction sin ("sin", std::sin);

    // @Function cos
    const ValueFunction cos ("cos", std::cos);

    // @Function tan
    const ValueFunction tan ("tan", std::tan);

    // @Function asin arcsin arsin
    const ValueFunction asin ("asin", std::asin);

    // @Function acos arccos arcos
    const ValueFunction acos ("acos", std::acos);

    // @Function atan arctan artan
    const ValueFunction atan ("atan", std::atan);

    // @Function sinh
    const ValueFunction sinh ("sinh", std::sinh);

    // @Function cosh
    const ValueFunction cosh ("cosh", std::cosh);

    // @Function tanh
    const ValueFunction tanh ("tanh", std::tanh);

    // @Function asinh arcsinh arsinh
    const ValueFunction asinh ("asinh", std::asinh);

    // @Function acosh arccosh arcosh
    const ValueFunction acosh ("acosh", std::acosh);

    // @Function atanh arctanh artanh
    const ValueFunction atanh ("atanh", std::atanh);

    // @Function csc
    const ValueFunction csc ("csc", [](double x) -> double { return 1.0 / std::sin(x); });

    // @Function sec
    const ValueFunction sec ("sec", [](double x) -> double { return 1.0 / std::cos(x); });

    // @Function cot
    const ValueFunction cot ("cot", [](double x) -> double { return 1.0 / std::tan(x); });

    // @Function acsc arccsc arcsc
    const ValueFunction acsc ("acsc", [](double x) -> double { return std::asin(1.0 / x); });

    // @Function asec arcsec arsec
    const ValueFunction asec ("asec", [](double x) -> double { return std::acos(1.0 / x); });

    // @Function acot arccot arcot
    const ValueFunction acot ("acot", [](double x) -> double { return (x > 0 ? M_PI_2 : -M_PI_2) - std::atan(x); });

    // @Function csch
    const ValueFunction csch ("csch", [](double x) -> double { return 1.0 / std::sinh(x); });

    // @Function sech
    const ValueFunction sech ("sech", [](double x) -> double { return 1.0 / std::cosh(x); });

    // @Function coth
    const ValueFunction coth ("coth", [](double x) -> double { return 1.0 / std::tanh(x); });

    // @Function acsch arccsch arcsch
    const ValueFunction acsch ("acsch", [](double x) -> double {
        if (x == 0){
            return GSL_NAN;
        }
        return std::log(1 / x + std::sqrt(1 / (x * x) + 1));
    });

    // @Function asech arcsech arsech
    const ValueFunction asech ("asech", [](double x) -> double {
        if (x <= 0 || x > 1){
            return GSL_NAN;
        }
        return std::log(1 / x + std::sqrt(1 / (x * x) - 1));
    });

    // @Function acoth arccoth arcoth
    const ValueFunction acoth ("acoth", [](double x) -> double {
        if (x >= -1 && x <= 1){
            return GSL_NAN;
        }
        return std::log((x + 1) / (x - 1)) / 2;
    });
}
