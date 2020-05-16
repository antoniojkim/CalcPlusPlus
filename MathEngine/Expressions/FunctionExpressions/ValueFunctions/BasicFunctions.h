#pragma once

#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>

#include "../FunctionDirectory.h"

double neg(double x){ return -x; }

ValueFunction f_neg = valueFunction<neg>;
ValueFunction f_abs = valueFunction<std::abs>;

ValueFunction f_sqr = valueFunction<gsl_pow_2>;
ValueFunction f_sqrt = valueFunction<std::sqrt>;
ValueFunction f_cb = valueFunction<gsl_pow_3>;
ValueFunction f_cbrt = valueFunction<std::cbrt>;

double rad(double x){
    return x * 180 / M_PI;
}
ValueFunction f_rad = valueFunction<rad>;

double deg(double x){
    return x * M_PI / 180;
}
ValueFunction f_deg = valueFunction<deg>;


double f_hypot(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple){
        if (tuple->size() == 2){
            double v[2];
            tuple->array(v, 2, vars);
            return gsl_hypot(v[0], v[1]);
        }
        else if (tuple->size() == 3){
            double v[3];
            tuple->array(v, 3, vars);
            return gsl_hypot3(v[0], v[1], v[2]);
        }
        else if (tuple->size() > 0){
            double sum = 0;
            for (auto& arg : *tuple){
                double x = arg->value(vars);
                sum += x*x;
            }
            return sqrt(sum);
        }
    }
    return GSL_NAN;
}

double f_ldexp(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        double xe[2];
        tuple->array(xe, 2, vars);
        if (std::trunc(xe[1]) == xe[1]){
            return gsl_ldexp(xe[0], (int) xe[1]);
        }
    }
    return GSL_NAN;
}

double f_fcmp(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() >= 2){
        switch(tuple->size()){
            case 2: {
                double xy[2];
                tuple->array(xy, 2, vars);
                return gsl_fcmp(xy[0], xy[1], 1e-8) == 0;
            }
            case 3: {
                double xye[3];
                tuple->array(xye, 3, vars);
                return gsl_fcmp(xye[0], xye[1], xye[2]) == 0;
            }
            default:
                return GSL_NAN;
        }
    }
    return GSL_NAN;
}

double f_gcd(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() >= 2){
        long long g = 0;
        for (double e : tuple->array(vars)){
            if (std::trunc(e) == e){
                if (g == 0){
                    g = e;
                }
                else{
                    g = std::gcd((long long) g, (long long) e);
                }
            }
        }
        return g;
    }
    return GSL_NAN;
}

double f_lcm(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() >= 2){
        long long g = 0;
        for (double e : tuple->array(vars)){
            if (std::trunc(e) == e){
                if (g == 0){
                    g = e;
                }
                else{
                    g = std::lcm((long long) g, (long long) e);
                }
            }
        }
        return g;
    }
    return GSL_NAN;
}
