#pragma once

#include <cmath>

#include <gsl/gsl_math.h>

#include "../FunctionDirectory.h"


double f_neg(double x){ return -x; }
UnaryFunction f_abs = std::abs;

UnaryFunction f_sqr = gsl_pow_2;
UnaryFunction f_sqrt = std::sqrt;
UnaryFunction f_cb = gsl_pow_3;
UnaryFunction f_cbrt = std::cbrt;

double f_rad(double x){
    return x * 180 / M_PI;
}
double f_deg(double x){
    return x * M_PI / 180;
}
