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

std::unique_ptr<double[]> to_array(const std::list<expression>& args, size_t& size, const Variables& vars){
    if (args.size() == 1){
        auto tuple = args.back()->tuple();
        if (tuple){
            std::unique_ptr<double[]> data (new double[tuple->data().size()]);
            double* d = data.get();
            for (auto& expr : tuple->data()){
                *(d++) = expr->value(vars);
            }
            size = tuple->data().size();
            return data;
        }
    }

    std::unique_ptr<double[]> data (new double[args.size()]);
    double* d = data.get();
    for (auto& arg : args){
        *(d++) = arg->value(vars);
    }
    size = args.size();
    return data;
}

double f_mean(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_mean(data.get(), 1, size);

}

double f_var(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_variance(data.get(), 1, size);
}
MultiFunction f_variance = f_var;

double f_sd(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_sd(data.get(), 1, size);
}
MultiFunction f_std = f_sd;
MultiFunction f_stdev = f_sd;

double f_tss(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_tss(data.get(), 1, size);
}

double f_absdev(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_absdev(data.get(), 1, size);
}

double f_skew(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_skew(data.get(), 1, size);
}

double f_kurtosis(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_kurtosis(data.get(), 1, size);
}
MultiFunction f_kurt = f_kurtosis;

double f_lag1(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_lag1_autocorrelation(data.get(), 1, size);
}
MultiFunction f_autocorr = f_lag1;

double f_max(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_max(data.get(), 1, size);
}

double f_min(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_min(data.get(), 1, size);
}

double f_argmax(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_max_index(data.get(), 1, size);
}

double f_argmin(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_min_index(data.get(), 1, size);
}

double f_median(const std::list<expression>& args, const Variables& vars){
    size_t size;
    auto data = to_array(args, size, vars);
    return gsl_stats_median(data.get(), 1, size);
}
