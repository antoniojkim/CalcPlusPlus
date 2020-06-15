#pragma once

#include <cmath>
#include <list>
#include <memory>
#include <vector>
#include <utility>

#include <gsl/gsl_statistics_double.h>

#include "../Expressions/TupleExpression.h"
#include "AbstractFunction.h"


namespace Function {
    typedef double(*ArrayFunction)(double*, size_t, size_t);
    struct StatisticsFunction: public NamedFunction {
        const ArrayFunction f;
        constexpr StatisticsFunction(const char* name, const ArrayFunction f): NamedFunction{name}, f{f} {}

        expression evaluate(Function::Args& args) override {
            if(args.size() < 1){
                return InvalidExpression::construct(Exception(Functions::names[index], " expected an array of inputs. Got: ", args));
            }
            auto array = args.array();
            return NumExpression::construct(f(array.begin(), 1, array.size()));
        }
    };

    typedef double(*ConstArrayFunction)(const double*, size_t, size_t);
    struct ConstStatisticsFunction: public NamedFunction {
        const ConstArrayFunction f;
        constexpr ConstStatisticsFunction(const char* name, const ConstArrayFunction f): NamedFunction{name}, f{f} {}

        expression evaluate(Function::Args& args) override {
            if(args.size() < 1){
                return InvalidExpression::construct(Exception(Functions::names[index], " expected an array of inputs. Got: ", args));
            }
            auto array = args.array();
            return NumExpression::construct(f(array.begin(), 1, array.size()));
        }
    };

    typedef size_t(*LongArrayFunction)(const double*, size_t, size_t);
    struct LongStatisticsFunction: public NamedFunction {
        const LongArrayFunction f;
        constexpr LongStatisticsFunction(const char* name, const LongArrayFunction f): NamedFunction{name}, f{f} {}

        expression evaluate(Function::Args& args) override {
            if(args.size() < 1){
                return InvalidExpression::construct(Exception(Functions::names[index], " expected an array of inputs. Got: ", args));
            }
            auto array = args.array();
            return NumExpression::construct(f(array.begin(), 1, array.size()));
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

    // @Function argmax max_index
    const LongStatisticsFunction argmax ("argmax", gsl_stats_max_index);

    // @Function argmin min_index
    const LongStatisticsFunction argmin ("argmin", gsl_stats_min_index);

    // @Function median
    const StatisticsFunction median ("median", gsl_stats_median);
}
