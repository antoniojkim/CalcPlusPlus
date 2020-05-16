#pragma once

#include <cmath>
#include <list>
#include <memory>

#include <gsl/gsl_rng.h>

#include "../../../Utils/exceptions.h"
#include "../../../Utils/Random.h"
#include "../../Expression.h"
#include "../FunctionDirectory.h"


double f_rseed(expression arg, const Variables& vars){
    double s = arg->value(vars);
    if (std::trunc(s) == s && s >= 0){
        gsl_rng_set(rng.get(), (unsigned long long) s);
        return s;
    }
    return GSL_NAN;
}
ValueFunction f_randseed = f_rseed;

double f_randu(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple){
        switch(tuple->size()){
            case 0:
                return gsl_rng_uniform(rng.get());
            case 1:
                return gsl_rng_uniform(rng.get()) * tuple->front()->value(vars);
            case 2: {
                double lh[2];
                tuple->array(lh, 2, vars);
                return gsl_rng_uniform(rng.get()) * (lh[1] - lh[0] + 1) + lh[0];
            }
            default:
                return GSL_NAN;
        }
    }
    return GSL_NAN;
}
ValueFunction f_rand = f_randu;

double f_randup(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple){
        switch(tuple->size()){
            case 0:
                return gsl_rng_uniform_pos(rng.get());
            case 1:
                return gsl_rng_uniform_pos(rng.get()) * tuple->front()->value(vars);
            case 2: {
                double lh[2];
                tuple->array(lh, 2, vars);
                return gsl_rng_uniform_pos(rng.get()) * (lh[1] - lh[0] + 1) + lh[0];
            }
            default:
                return GSL_NAN;
        }
    }
    return GSL_NAN;
}

double f_randint(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple){
        switch(tuple->size()){
            case 1:{
                double n = tuple->front()->value(vars);
                if (std::trunc(n) == n){
                    return gsl_rng_uniform_int(rng.get(), (unsigned long int) n);
                }
            }
            case 2: {
                double l = tuple->front()->value(vars);
                double h = tuple->back()->value(vars);
                if (std::trunc(l) == l && std::trunc(h) == h){
                    return gsl_rng_uniform_int(rng.get(), (unsigned long int) (h - l + 1)) + l;
                }
            }
            default:
                return GSL_NAN;
        }
    }
    return GSL_NAN;
}
