#pragma once

#include <cmath>

#include "../FunctionDirectory.h"

ValueFunction f_exp = valueFunction<std::exp>;
ValueFunction f_exp_2 = valueFunction<std::exp2>;
ValueFunction f_expm1 = valueFunction<std::expm1>;
ValueFunction f_ln = valueFunction<std::log>;
ValueFunction f_ln_2 = valueFunction<std::log2>;
ValueFunction f_ln1p = valueFunction<std::log1p>;
ValueFunction f_log = valueFunction<std::log10>;
ValueFunction f_log_2 = valueFunction<std::log2>;
ValueFunction f_log1p = valueFunction<std::log1p>;

double f_logn(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 2){
        double ab[2];
        tuple->array(ab, 2, vars);
        return log(ab[0]) / log(ab[1]);
    }
    return GSL_NAN;
}
