#pragma once

#include <cmath>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../OperatorDirectory.h"
#include "../../FunctionExpressions/FunctionDirectory.h"
#include "../../NumericalExpression.h"

double f_TILDE(double x){
    double intpart;
    if (modf(x, &intpart) == 0){
        return double(~((long long int) intpart));
    }
    return GSL_NAN;
}

double f_EXCL(double x){
    Variables vars;
    return get_function("fact")(NumExpression::construct(x), vars);
}

double f_EXCL_EXCL(double x){
    Variables vars;
    return get_function("dfact")(NumExpression::construct(x), vars);
}

double f_APOSTROPHE(double x){
    Variables vars;
    return get_function("diff")(NumExpression::construct(x), vars);
}
