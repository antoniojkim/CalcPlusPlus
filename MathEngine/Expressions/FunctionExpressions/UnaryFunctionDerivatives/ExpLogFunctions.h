#pragma once

#include <cmath>

#include <gsl/gsl_math.h>

#include "../FunctionDirectory.h"
#include "../../FunctionExpression.h"
#include "../../ExpressionOperations.h"
#include "../../ExpressionFunctions.h"


expression fprime_exp(const expression arg, const std::string& var){
    return UnaryFunctionExpression::construct("exp", arg);
}
expression fprime_exp_2(const expression arg, const std::string& var){
    return UnaryFunctionExpression::construct("exp2", arg) * M_LN2;
}
expression fprime_expm1(const expression arg, const std::string& var){
    return UnaryFunctionExpression::construct("exp", arg);
}
expression fprime_ln(const expression arg, const std::string& var){
    return 1 / arg;
}
expression fprime_ln_2(const expression arg, const std::string& var){
    return 1 / (arg * M_LN2);
}
expression fprime_ln1p(const expression arg, const std::string& var){
    return 1 / (arg + 1);
}
expression fprime_log(const expression arg, const std::string& var){
    return 1 / (arg * M_LN10);
}
UnaryFunctionDerivative fprime_log_2 = fprime_ln_2;
UnaryFunctionDerivative fprime_log1p = fprime_ln1p;
