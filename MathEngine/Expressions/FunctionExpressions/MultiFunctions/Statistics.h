#pragma once

#include <cmath>
#include <list>
#include <memory>
#include <vector>

#include <gsl/gsl_statistics_double.h>

#include "../../../Utils/exceptions.h"
#include "../../Expression.h"
#include "../FunctionDirectory.h"

using namespace std;

unique_ptr<double> to_array(list<expression>& args, const Variables& vars){
    unique_ptr<double> data (new double[args.size()]);
    double* d = data.get();
    for (auto& arg : args){
        *(d++) = arg->value(vars);
    }
    return std::move(data);
}

double f_mean(list<expression>& args, const Variables& vars){
    return gsl_stats_mean(to_array(args, vars).get(), 1, args.size());

}

double f_var(list<expression>& args, const Variables& vars){
    return gsl_stats_variance(to_array(args, vars).get(), 1, args.size());
}
MultiFunction f_variance = f_var;

double f_sd(list<expression>& args, const Variables& vars){
    return gsl_stats_sd(to_array(args, vars).get(), 1, args.size());
}
MultiFunction f_std = f_sd;
MultiFunction f_stdev = f_sd;

double f_tss(list<expression>& args, const Variables& vars){
    return gsl_stats_tss(to_array(args, vars).get(), 1, args.size());
}

double f_absdev(list<expression>& args, const Variables& vars){
    return gsl_stats_absdev(to_array(args, vars).get(), 1, args.size());
}

double f_skew(list<expression>& args, const Variables& vars){
    return gsl_stats_skew(to_array(args, vars).get(), 1, args.size());
}

double f_kurtosis(list<expression>& args, const Variables& vars){
    return gsl_stats_kurtosis(to_array(args, vars).get(), 1, args.size());
}
MultiFunction f_kurt = f_kurtosis;

double f_lag1(list<expression>& args, const Variables& vars){
    return gsl_stats_lag1_autocorrelation(to_array(args, vars).get(), 1, args.size());
}
MultiFunction f_autocorr = f_lag1;

double f_max(list<expression>& args, const Variables& vars){
    return gsl_stats_max(to_array(args, vars).get(), 1, args.size());
}

double f_min(list<expression>& args, const Variables& vars){
    return gsl_stats_min(to_array(args, vars).get(), 1, args.size());
}

double f_argmax(list<expression>& args, const Variables& vars){
    return gsl_stats_max_index(to_array(args, vars).get(), 1, args.size());
}

double f_argmin(list<expression>& args, const Variables& vars){
    return gsl_stats_min_index(to_array(args, vars).get(), 1, args.size());
}

double f_median(list<expression>& args, const Variables& vars){
    return gsl_stats_median(to_array(args, vars).get(), 1, args.size());
}


