#pragma once

#include <cmath>
#include <list>
#include <vector>

#include <gsl/gsl_statistics_double.h>

#include "../../../Utils/exceptions.h"
#include "../../Expression.h"
#include "../FunctionDirectory.h"

using namespace std;

double f_mean(list<expression>& args, const Variables& vars){
    double* data = new double[args.size()];
    double* d = data;
    for (auto& arg : args){
        *(d++) = arg->value(vars);
    }
    double mean = gsl_stats_mean(data, 1, args.size());
    delete[] data;
    return mean;
}

double f_var(list<expression>& args, const Variables& vars){
    double* data = new double[args.size()];
    double* d = data;
    for (auto& arg : args){
        *(d++) = arg->value(vars);
    }
    double mean = gsl_stats_variance(data, 1, args.size());
    delete[] data;
    return mean;
}
MultiFunction f_variance = f_var;

double f_sd(list<expression>& args, const Variables& vars){
    double* data = new double[args.size()];
    double* d = data;
    for (auto& arg : args){
        *(d++) = arg->value(vars);
    }
    double mean = gsl_stats_sd(data, 1, args.size());
    delete[] data;
    return mean;
}
MultiFunction f_std = f_sd;
MultiFunction f_stdev = f_sd;
