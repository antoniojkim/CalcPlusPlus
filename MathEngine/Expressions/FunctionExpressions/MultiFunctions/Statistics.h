#pragma once

#include <cmath>
#include <list>
#include <memory>
#include <vector>

#include <gsl/gsl_statistics_double.h>

#include "../../../Utils/exceptions.h"
#include "../../Expression.h"
#include "../../TupleExpression.h"
#include "../FunctionDirectory.h"

using namespace std;

unique_ptr<double[]> to_array(list<expression>& args, size_t& size, const Variables& vars){
    if (args.size() == 1){
        auto tuple = args.back()->tuple();
        if (tuple){
            unique_ptr<double[]> data (new double[tuple->data.size()]);
            double* d = data.get();
            for (auto& expr : tuple->data){
                *(d++) = expr->value(vars);
            }
            size = tuple->data.size();
            return std::move(data);
        }
    }

    unique_ptr<double[]> data (new double[args.size()]);
    double* d = data.get();
    for (auto& arg : args){
        *(d++) = arg->value(vars);
    }
    size = args.size();
    return std::move(data);
}

double f_mean(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_mean(data.get(), 1, size);

}

double f_var(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_variance(data.get(), 1, size);
}
MultiFunction f_variance = f_var;

double f_sd(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_sd(data.get(), 1, size);
}
MultiFunction f_std = f_sd;
MultiFunction f_stdev = f_sd;

double f_tss(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_tss(data.get(), 1, size);
}

double f_absdev(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_absdev(data.get(), 1, size);
}

double f_skew(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_skew(data.get(), 1, size);
}

double f_kurtosis(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_kurtosis(data.get(), 1, size);
}
MultiFunction f_kurt = f_kurtosis;

double f_lag1(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_lag1_autocorrelation(data.get(), 1, size);
}
MultiFunction f_autocorr = f_lag1;

double f_max(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_max(data.get(), 1, size);
}

double f_min(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_min(data.get(), 1, size);
}

double f_argmax(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_max_index(data.get(), 1, size);
}

double f_argmin(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_min_index(data.get(), 1, size);
}

double f_median(list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_median(data.get(), 1, size);
}
