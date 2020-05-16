#pragma once

#include <cmath>

#include <gsl/gsl_math.h>

#include "../FunctionDirectory.h"
#include "../../FunctionExpression.h"
#include "../../ExpressionOperations.h"
#include "../../ExpressionFunctions.h"
#include "../../InvalidExpression.h"
#include "../../OperatorExpressions/OperatorDirectory.h"
#include "../../TupleExpression.h"


expression fprime_exp(const expression arg, const std::string& var){
    return FunctionExpression::construct("exp", arg);
}
expression fprime_exp_2(const expression arg, const std::string& var){
    return FunctionExpression::construct("exp2", arg) * M_LN2;
}
expression fprime_expm1(const expression arg, const std::string& var){
    return FunctionExpression::construct("exp", arg);
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
DerivativeFunction fprime_log_2 = fprime_ln_2;
DerivativeFunction fprime_log1p = fprime_ln1p;

expression fprime_logn(const expression arg, const std::string& var){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        return getOperatorDerivative("/")(tuple->front(), tuple->back(), var);
    }
    return InvalidExpression::construct(Exception("Invalid number of arguments for fprime_logn"));
}
