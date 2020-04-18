#pragma once

#include <cmath>

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../FunctionDirectory.h"

UnaryFunction f_gamma = gsl_sf_gamma;
UnaryFunction f_lngamma = gsl_sf_lngamma;
UnaryFunction f_gammastar = gsl_sf_gammastar;
UnaryFunction f_gammainv = gsl_sf_gammainv;
double f_fact(double x){
    if (x > GSL_SF_FACT_NMAX){
        return GSL_POSINF;
    }
    if (x < 0 || (std::trunc(x) != x)) {
        return gsl_sf_gamma(x + 1);
    }
    return gsl_sf_fact((unsigned int) x);
}
double f_dfact(double x){
    if (x > GSL_SF_DOUBLEFACT_NMAX){
        return GSL_POSINF;
    }
    if (x >= 0 && std::trunc(x) == x) {
        return gsl_sf_doublefact((unsigned int) x);
    }
    return GSL_NAN;
}
double f_lnfact(double x){
    if (x >= 0 && std::trunc(x) == x) {
        return gsl_sf_lnfact((unsigned int) x);
    }
    return GSL_NAN;
}
double f_lndfact(double x){
    if (x >= 0 && std::trunc(x) == x) {
        return gsl_sf_lndoublefact((unsigned int) x);
    }
    return GSL_NAN;
}
