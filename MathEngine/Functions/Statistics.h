#pragma once

#include <cmath>
#include <list>
#include <memory>
#include <vector>
#include <utility>

#include <gsl/gsl_statistics_double.h>

#include "../Expressions/Expression.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/TupleExpression.h"
#include "../Utils/Argparse.h"
#include "AbstractFunction.h"

typedef double(*ArrayFunction)(double*, size_t, size_t);

struct StatisticsFunction: public NamedFunction {
    const ArrayFunction f;
    constexpr ValueFunction(const char* name, const ArrayFunction f): NamedFunction{name}, f{f} {}

    expression evaluate(expression arg) override {
        TupleExpression* tuple = arg->tuple();
        if(!tuple){
            return InvalidExpression::construct(Exception(name, " expected an array of inputs. Got: ", arg));
        }
        auto array = tuple->array();
        return NumExpression::construct(f(array.begin(), 1, array.size()));
    }
};

namespace Function {
    // @Function mean
    const StatisticsFunction mean ("mean", gsl_stats_mean);

    // @Function var variance
    const StatisticsFunction var ("var", gsl_stats_variance);

    // @Function sd std stdev
    const StatisticsFunction sd ("sd", gsl_stats_sd);

    // @Function tss
    const StatisticsFunction tss ("tss", gsl_stats_tss);

    // @Function absdev
    const StatisticsFunction absdev ("absdev", gsl_stats_absdev);

    // @Function skew
    const StatisticsFunction skew ("skew", gsl_stats_skew);

    // @Function kurtosis kurt
    const StatisticsFunction kurtosis ("kurtosis", gsl_stats_kurtosis);

    // @Function lag1 autocorr
    const StatisticsFunction lag1 ("lag1", gsl_stats_lag1_autocorrelation);

    // @Function max
    const StatisticsFunction max ("max", gsl_stats_max);

    // @Function min
    const StatisticsFunction min ("min", gsl_stats_min);

    // @Function argmax max_index
    const StatisticsFunction argmax ("argmax", gsl_stats_max_index);

    // @Function argmin min_index
    const StatisticsFunction argmin ("argmin", gsl_stats_min_index);

    // @Function median
    const StatisticsFunction median ("median", gsl_stats_median);
}
