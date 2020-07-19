#include <cmath>

#include <gsl/gsl_statistics_double.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/FunctionExpression.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/VariableExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {

    struct StatisticsExpression: public FunctionExpression {
        typedef double (*StatsFunction)(const double* array, size_t stride, size_t n);
        StatsFunction f;

        StatisticsExpression(int functionIndex, expression arg, StatsFunction f):
            FunctionExpression(functionIndex, arg, {{"a", EmptyVarArgs}}), f{f} {}


        expression eval(const Variables& vars = emptyVars) override {
            return NumExpression::construct(value(vars));
        }

        double value(const Variables& vars = emptyVars) const override {
            auto array = arg->at(1)->eval(vars)->array();
            return f(array.data(), 1, array.size());
        }
    };

    #define MAKE_STATS_EXPRESSION(name, f)                                              \
        expression make_fe_##name(int functionIndex, expression arg){                   \
            return std::make_shared<StatisticsExpression>(functionIndex, arg, f);       \
        }

    // @Function mean
    MAKE_STATS_EXPRESSION(mean, gsl_stats_mean)

    // @Function var: variance
    struct var: public FunctionExpression {
        var(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a..., ddof=1)
            {"a", EmptyVarArgs}, {"ddof", NumExpression::construct(1)}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            return NumExpression::construct(value(vars));
        }
        double value(const Variables& vars = emptyVars) const override {
            auto array = arg->at(1)->eval(vars)->array();
            double ddof = arg->at(2)->value(vars);
            if (ddof < 1 || trunc(ddof) != ddof){
                throw Exception("Variance expected an integer ddof >= 1. Got: ", ddof);
            }
            double N = array.size();
            if (trunc(ddof) == 1){
                return gsl_stats_variance(array.data(), 1, N);
            }
            return gsl_stats_tss(array.data(), 1, N) / (N - ddof);
        }
    };
    MAKE_FUNCTION_EXPRESSION(var)

    // @Function sd: std stdev
    struct sd: public FunctionExpression {
        sd(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a..., ddof=1)
            {"a", EmptyVarArgs}, {"ddof", NumExpression::construct(1)}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            return NumExpression::construct(value(vars));
        }
        double value(const Variables& vars = emptyVars) const override {
            auto array = arg->at(1)->eval(vars)->array();
            double ddof = arg->at(2)->value(vars);
            if (ddof < 1 || trunc(ddof) != ddof){
                throw Exception("Standard Deviation expected an integer ddof >= 1. Got: ", ddof);
            }
            double N = array.size();
            if (trunc(ddof) == 1){
                return gsl_stats_sd(array.data(), 1, N);
            }
            return std::sqrt(gsl_stats_tss(array.data(), 1, N) / (N - ddof));
        }
    };
    MAKE_FUNCTION_EXPRESSION(sd)

    // @Function tss
    MAKE_STATS_EXPRESSION(tss, gsl_stats_tss)

    // @Function absdev
    MAKE_STATS_EXPRESSION(absdev, gsl_stats_absdev)

    // @Function skew
    MAKE_STATS_EXPRESSION(skew, gsl_stats_skew)

    // @Function kurtosis: kurt
    MAKE_STATS_EXPRESSION(kurtosis, gsl_stats_kurtosis)

    // @Function lag1: autocorr
    MAKE_STATS_EXPRESSION(lag1, gsl_stats_lag1_autocorrelation)

    // @Function max
    MAKE_STATS_EXPRESSION(max, gsl_stats_max)

    // @Function min
    MAKE_STATS_EXPRESSION(min, gsl_stats_min)

    // @Function argmax: max_index
    struct argmax: public FunctionExpression {
        argmax(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a...)
            {"a", EmptyVarArgs}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            return NumExpression::construct(value(vars));
        }
        double value(const Variables& vars = emptyVars) const override {
            auto array = arg->at(1)->eval(vars)->array();
            return gsl_stats_max_index(array.data(), 1, array.size());
        }
    };
    MAKE_FUNCTION_EXPRESSION(argmax)

    // @Function argmin: min_index
    struct argmin: public FunctionExpression {
        argmin(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a...)
            {"a", EmptyVarArgs}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            return NumExpression::construct(value(vars));
        }
        double value(const Variables& vars = emptyVars) const override {
            auto array = arg->at(1)->eval(vars)->array();
            return gsl_stats_min_index(array.data(), 1, array.size());
        }
    };
    MAKE_FUNCTION_EXPRESSION(argmin)

    // @Function median
    struct median: public FunctionExpression {
        median(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a...)
            {"a", EmptyVarArgs}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            return NumExpression::construct(value(vars));
        }
        double value(const Variables& vars = emptyVars) const override {
            auto array = arg->at(1)->eval(vars)->array();
            return gsl_stats_median(array.data(), 1, array.size());
        }
    };
    MAKE_FUNCTION_EXPRESSION(median)
}
