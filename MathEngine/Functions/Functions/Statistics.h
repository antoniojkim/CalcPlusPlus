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
    const ConstStatisticsFunction __mean__ ("mean", gsl_stats_mean);

    // @Function var variance
    const ConstStatisticsFunction __var__ ("var", gsl_stats_variance);

    // @Function sd std stdev
    const ConstStatisticsFunction __sd__ ("sd", gsl_stats_sd);

    // @Function tss
    const ConstStatisticsFunction __tss__ ("tss", gsl_stats_tss);

    // @Function absdev
    const ConstStatisticsFunction __absdev__ ("absdev", gsl_stats_absdev);

    // @Function skew
    const ConstStatisticsFunction __skew__ ("skew", gsl_stats_skew);

    // @Function kurtosis kurt
    const ConstStatisticsFunction __kurtosis__ ("kurtosis", gsl_stats_kurtosis);

    // @Function lag1 autocorr
    const ConstStatisticsFunction __lag1__ ("lag1", gsl_stats_lag1_autocorrelation);

    // @Function max
    const ConstStatisticsFunction __max__ ("max", gsl_stats_max);

    // @Function min
    const ConstStatisticsFunction __min__ ("min", gsl_stats_min);

    // @Function argmax max_index
    const LongStatisticsFunction __argmax__ ("argmax", gsl_stats_max_index);

    // @Function argmin min_index
    const LongStatisticsFunction __argmin__ ("argmin", gsl_stats_min_index);

    // @Function median
    const StatisticsFunction __median__ ("median", gsl_stats_median);
}
