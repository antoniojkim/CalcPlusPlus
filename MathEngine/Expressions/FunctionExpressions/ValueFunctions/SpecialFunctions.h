#pragma once

#include <cmath>

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../../TupleExpression.h"
#include "../FunctionDirectory.h"

ValueFunction f_gamma = valueFunction<gsl_sf_gamma>;
ValueFunction f_lngamma = valueFunction<gsl_sf_lngamma>;
ValueFunction f_gammastar = valueFunction<gsl_sf_gammastar>;
ValueFunction f_gammainv = valueFunction<gsl_sf_gammainv>;

static double fact(double x){
    if (x > GSL_SF_FACT_NMAX){
        return GSL_POSINF;
    }
    if (x < 0 || (std::trunc(x) != x)) {
        return gsl_sf_gamma(x + 1);
    }
    return gsl_sf_fact((unsigned int) x);
}
ValueFunction f_fact = valueFunction<fact>;

static double dfact(double x){
    if (x > GSL_SF_DOUBLEFACT_NMAX){
        return GSL_POSINF;
    }
    if (x >= 0 && std::trunc(x) == x) {
        return gsl_sf_doublefact((unsigned int) x);
    }
    return GSL_NAN;
}
ValueFunction f_dfact = valueFunction<dfact>;

static double lnfact(double x){
    if (x >= 0 && std::trunc(x) == x) {
        return gsl_sf_lnfact((unsigned int) x);
    }
    return GSL_NAN;
}
ValueFunction f_lnfact = valueFunction<lnfact>;

static double lndfact(double x){
    if (x >= 0 && std::trunc(x) == x) {
        return gsl_sf_lndoublefact((unsigned int) x);
    }
    return GSL_NAN;
}
ValueFunction f_lndfact = valueFunction<lndfact>;


static double f_choose(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double n = (*(arg++))->value(vars);
        double m = (*arg)->value(vars);
        if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
            return gsl_sf_choose((unsigned int) n, (unsigned int) m);
        }
    }
    return GSL_NAN;
}
static double f_lnchoose(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double n = (*(arg++))->value(vars);
        double m = (*arg)->value(vars);
        if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
            return gsl_sf_lnchoose((unsigned int) n, (unsigned int) m);
        }
    }
    return GSL_NAN;
}
static double f_permute(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double n = (*(arg++))->value(vars);
        double m = (*arg)->value(vars);
        if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
            return gsl_sf_choose((unsigned int) n, (unsigned int) m) * gsl_sf_fact((unsigned int) m);
        }
    }
    return GSL_NAN;
}
static double f_lnpermute(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double n = (*(arg++))->value(vars);
        double m = (*arg)->value(vars);
        if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
            return gsl_sf_lnchoose((unsigned int) n, (unsigned int) m) + gsl_sf_lnfact((unsigned int) m);
        }
    }
    return GSL_NAN;
}
static double f_taylorcoeff(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double n = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        if (x >= 0 && n >= 0 && std::trunc(n) == n){
            return gsl_sf_taylorcoeff((int) n, x);
        }
    }
    return GSL_NAN;
}
static double f_poch(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_poch(a, x);
    }
    return GSL_NAN;
}
static double f_lnpoch(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_lnpoch(a, x);
    }
    return GSL_NAN;
}
static double f_pochrel(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_pochrel(a, x);
    }
    return GSL_NAN;
}
static double f_gammainc(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_gamma_inc(a, x);
    }
    return GSL_NAN;
}
static double f_gammaincq(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_gamma_inc_Q(a, x);
    }
    return GSL_NAN;
}
static double f_gammaincp(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_gamma_inc_P(a, x);
    }
    return GSL_NAN;
}
static double f_beta(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double b = (*arg)->value(vars);
        if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
            return gsl_sf_beta(a, b);
        }
    }
    return GSL_NAN;
}
static double f_lnbeta(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double b = (*arg)->value(vars);
        if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
            return gsl_sf_lnbeta(a, b);
        }
    }
    return GSL_NAN;
}
static double f_betainc(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 3){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double b = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        if (x >= 0 && x <= 1){
            return gsl_sf_beta_inc(a, b, x);
        }
    }
    return GSL_NAN;
}
