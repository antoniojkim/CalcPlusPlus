#pragma once

#include <cmath>
#include <list>
#include <memory>
#include <vector>
#include <utility>

#include <gsl/gsl_statistics_double.h>

#include "../Expressions/TupleExpression.h"
#include "../AbstractFunction.h"


namespace Function {

    struct ConstStatisticsFunction: public NamedFunction {
        typedef double(*ConstArrayFunction)(const double*, size_t, size_t);
        const ConstArrayFunction f;
        ConstStatisticsFunction(const std::string& name, const ConstArrayFunction f):
            AbstractFunction{name, "(a...,)"}, f{f} {}

        expression evaluate(Function::Args& args) override {
            auto array = args["a"].array();
            return NumExpression::construct(f(array.get(), 1, array.size()));
        }
    };

    // @Function mean
    const ConstStatisticsFunction mean ("mean", gsl_stats_mean);

    // @Function var variance
    const ConstStatisticsFunction var ("var", gsl_stats_variance);

    // @Function sd std stdev
    const ConstStatisticsFunction sd ("sd", gsl_stats_sd);

    // @Function tss
    const ConstStatisticsFunction tss ("tss", gsl_stats_tss);

    // @Function absdev
    const ConstStatisticsFunction absdev ("absdev", gsl_stats_absdev);

    // @Function skew
    const ConstStatisticsFunction skew ("skew", gsl_stats_skew);

    // @Function kurtosis kurt
    const ConstStatisticsFunction kurtosis ("kurtosis", gsl_stats_kurtosis);

    // @Function lag1 autocorr
    const ConstStatisticsFunction lag1 ("lag1", gsl_stats_lag1_autocorrelation);

    // @Function max
    const ConstStatisticsFunction max ("max", gsl_stats_max);

    // @Function min
    const ConstStatisticsFunction min ("min", gsl_stats_min);


    struct LongStatisticsFunction: public NamedFunction {
        typedef size_t(*LongArrayFunction)(const double*, size_t, size_t);
        const LongArrayFunction f;
        LongStatisticsFunction(const std::string& name, const LongArrayFunction f):
            AbstractFunction{name, "(a...,)"}, f{f} {}

        expression evaluate(Function::Args& args) override {
            auto array = args["a"].array();
            return NumExpression::construct(f(array.get(), 1, array.size()));
        }
    };

    // @Function argmax max_index
    const LongStatisticsFunction argmax ("argmax", gsl_stats_max_index);

    // @Function argmin min_index
    const LongStatisticsFunction argmin ("argmin", gsl_stats_min_index);


    struct StatisticsFunction: public AbstractFunction {
        typedef double(*ArrayFunction)(double*, size_t, size_t);
        const ArrayFunction f;
        StatisticsFunction(const std::string& name, const ArrayFunction f):
            AbstractFunction{name, "(a...,)"}, f{f} {}

        expression evaluate(Function::Args& args) override {
            auto array = args["a"].array();
            return NumExpression::construct(f(array.get(), 1, array.size()));
        }
    };

    // @Function median
    const StatisticsFunction median ("median", gsl_stats_median);
}
