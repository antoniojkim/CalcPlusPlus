#pragma once

#include <cmath>
#include <list>
#include <memory>

#include <gsl/gsl_rng.h>

#include "../../../Utils/exceptions.h"
#include "../../../Utils/Random.h"
#include "../../Expression.h"
#include "../FunctionDirectory.h"


double f_rseed(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        double s = args.front()->value(vars);
        if (std::trunc(s) == s && s >= 0){
            gsl_rng_set(rng.get(), (unsigned long long) s);
            return s;
        }
    }
    return GSL_NAN;
}
MultiFunction f_randseed = f_rseed;

double f_randu(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 0){
        return gsl_rng_uniform(rng.get());
    }
    if (args.size() == 1){
        return gsl_rng_uniform(rng.get()) * args.front()->value(vars);
    }
    if (args.size() == 2){
        auto arg = args.begin();
        double l = (*(arg++))->value(vars);
        double h = (*(arg++))->value(vars);
        return gsl_rng_uniform(rng.get()) * (h - l + 1) + l;
    }
    return GSL_NAN;
}
MultiFunction f_rand = f_randu;
double f_randup(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 0){
        return gsl_rng_uniform_pos(rng.get());
    }
    if (args.size() == 1){
        return gsl_rng_uniform_pos(rng.get()) * args.front()->value(vars);
    }
    if (args.size() == 2){
        auto arg = args.begin();
        double l = (*(arg++))->value(vars);
        double h = (*(arg++))->value(vars);
        return gsl_rng_uniform_pos(rng.get()) * (h - l + 1) + l;
    }
    return GSL_NAN;
}

double f_randint(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        double n = args.front()->value(vars);
        if (std::trunc(n) == n){
            return gsl_rng_uniform_int(rng.get(), (unsigned long int) n);
        }
    }
    else if (args.size() == 2){
        double l = args.front()->value(vars);
        double h = args.back()->value(vars);
        if (std::trunc(l) == l && std::trunc(h) == h){
            return gsl_rng_uniform_int(rng.get(), (unsigned long int) (h - l + 1)) + l;
        }
    }
    return GSL_NAN;
}
