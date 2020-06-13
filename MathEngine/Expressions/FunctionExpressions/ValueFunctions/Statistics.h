#pragma once

#include <cmath>
#include <list>
#include <memory>
#include <vector>
#include <utility>

#include <gsl/gsl_statistics_double.h>

#include "../../../Utils/exceptions.h"
#include "../../Expression.h"
#include "../../TupleExpression.h"
#include "../FunctionDirectory.h"

double f_mean(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_mean(array.begin(), 1, array.size());

}

double f_var(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_variance(array.begin(), 1, array.size());
}
ValueFunction f_variance = f_var;

double f_sd(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_sd(array.begin(), 1, array.size());
}
ValueFunction f_std = f_sd;
ValueFunction f_stdev = f_sd;

double f_tss(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_tss(array.begin(), 1, array.size());
}

double f_absdev(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_absdev(array.begin(), 1, array.size());
}

double f_skew(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_skew(array.begin(), 1, array.size());
}

double f_kurtosis(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_kurtosis(array.begin(), 1, array.size());
}
ValueFunction f_kurt = f_kurtosis;

double f_lag_1(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_lag1_autocorrelation(array.begin(), 1, array.size());
}
ValueFunction f_autocorr = f_lag_1;

double f_max(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_max(array.begin(), 1, array.size());
}

double f_min(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_min(array.begin(), 1, array.size());
}

double f_argmax(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_max_index(array.begin(), 1, array.size());
}

double f_argmin(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_min_index(array.begin(), 1, array.size());
}

double f_median(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if(!tuple){
        return GSL_NAN;
    }
    auto array = tuple->array(vars);
    return gsl_stats_median(array.begin(), 1, array.size());
}
