#pragma once

#include <cmath>
#include <list>
#include <memory>
#include <vector>
#include <utility>

#include <gsl/gsl_statistics_double.h>

#include "../../Expressions/TupleExpression.h"
#include "../AbstractFunction.h"


namespace Function {

    template<typename StatsFunction>
    struct StatisticsFunction: public AbstractFunction {
        const StatsFunction f;
        StatisticsFunction(const std::string& name, const StatsFunction f):
            AbstractFunction{name, "(a...,)"}, f{f} {}

        expression eval(Function::Args& args) const override {
            auto array = args["a"]->array();
            return NumExpression::construct(f(array.data(), 1, array.size()));
        }
    };

    using DoubleStatsFunction = StatisticsFunction<double(*)(double*, size_t, size_t)>;
    using ConstStatsFunction = StatisticsFunction<double(*)(const double*, size_t, size_t)>;
    using LongStatsFunction = StatisticsFunction<size_t(*)(const double*, size_t, size_t)>;

    // @Function mean
    const ConstStatsFunction mean ("mean", gsl_stats_mean);

    // @Function var variance
    const ConstStatsFunction var ("var", gsl_stats_variance);

    // @Function sd std stdev
    const ConstStatsFunction sd ("sd", gsl_stats_sd);

    // @Function tss
    const ConstStatsFunction tss ("tss", gsl_stats_tss);

    // @Function absdev
    const ConstStatsFunction absdev ("absdev", gsl_stats_absdev);

    // @Function skew
    const ConstStatsFunction skew ("skew", gsl_stats_skew);

    // @Function kurtosis kurt
    const ConstStatsFunction kurtosis ("kurtosis", gsl_stats_kurtosis);

    // @Function lag1 autocorr
    const ConstStatsFunction lag1 ("lag1", gsl_stats_lag1_autocorrelation);

    // @Function max
    const ConstStatsFunction max ("max", gsl_stats_max);

    // @Function min
    const ConstStatsFunction min ("min", gsl_stats_min);

    // @Function argmax max_index
    const LongStatsFunction argmax ("argmax", gsl_stats_max_index);

    // @Function argmin min_index
    const LongStatsFunction argmin ("argmin", gsl_stats_min_index);

    // @Function median
    const DoubleStatsFunction median ("median", gsl_stats_median);
}
