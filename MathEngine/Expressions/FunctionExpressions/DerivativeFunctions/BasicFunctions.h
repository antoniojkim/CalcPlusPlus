#pragma once

#include <cmath>

#include <gsl/gsl_math.h>

#include "../FunctionDirectory.h"
#include "../../FunctionExpression.h"
#include "../../ExpressionOperations.h"
#include "../../ExpressionFunctions.h"
#include "../../NumericalExpression.h"

using namespace ExpressionMath;

expression fprime_neg(const expression arg, const std::string& var){
    return NumExpression::construct(-1);
}
expression fprime_abs(const expression arg, const std::string& var){
    return arg / abs(arg);
}

expression fprime_sqr(const expression arg, const std::string& var){
    return 2 * arg;
}
expression fprime_sqrt(const expression arg, const std::string& var){
    return 0.5 / sqrt(arg);
}

expression fprime_cb(const expression arg, const std::string& var){
    return 3 * sqr(arg);
}
expression fprime_cbrt(const expression arg, const std::string& var){
    return (1.0 / 3) / sqr(cbrt(arg));
}
