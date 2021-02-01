#include <cmath>
#include <iostream>

#include <gsl/gsl_statistics_double.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/FunctionExpression.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/VariableExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace calcpp {

    namespace fexpr {

        struct StatisticsExpression: public FunctionExpression {
            typedef double (*StatsFunction)(
                const double* array, size_t stride, size_t n);
            StatsFunction f;

            StatisticsExpression(const std::string& name, StatsFunction f) :
                FunctionExpression(name, {vararg("a")}), f{f} {}

            expression call(expression args) const override {
                auto array = args->at(0)->array();
                return num(f(array.data(), 1, array.size()));
            }
        };

#define MAKE_STATS_EXPRESSION(name, f)                                                 \
    struct name: public StatisticsExpression {                                         \
        name() : StatisticsExpression("name", f) {}                                    \
    }

        // @Function mean
        MAKE_STATS_EXPRESSION(mean, gsl_stats_mean);

        // @Function var: variance
        struct var: public FunctionExpression {
            var() : FunctionExpression("var", {vararg("a"), kwarg("ddof", 1)}) {}
            expression call(expression args) const override {
                auto array = args->at(0)->array();
                double ddof = (double) args->get(1);
                if (ddof < 1 || !IS_INT(ddof)) {
                    THROW_ERROR(
                        "Variance expected an integer ddof >= 1. Got: " << ddof);
                }
                size_t N = array.size();
                if (trunc(ddof) == 1) {
                    return num(gsl_stats_variance(array.data(), 1, N));
                }
                return num(gsl_stats_tss(array.data(), 1, N) / (N - ddof));
            }
        };

        // @Function sd: std stdev
        struct sd: public FunctionExpression {
            sd() : FunctionExpression("sd", {vararg("a"), kwarg("ddof", 1)}) {}
            expression call(expression args) const override {
                auto array = args->at(0)->array();
                double ddof = (double) args->get(1);

                if (ddof < 1 || !IS_INT(ddof)) {
                    THROW_ERROR(
                        "Standard Deviation expected an integer ddof >= 1. Got: "
                        << ddof);
                }
                size_t N = array.size();
                if (trunc(ddof) == 1) { return num(gsl_stats_sd(array.data(), 1, N)); }
                return num(std::sqrt(gsl_stats_tss(array.data(), 1, N) / (N - ddof)));
            }
        };

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
            argmax() : FunctionExpression("argmax", {vararg("a")}) {}
            expression call(expression args) const override {
                auto array = args->at(0)->array();
                return num(gsl_stats_max_index(array.data(), 1, array.size()));
            }
        };

        // @Function argmin: min_index
        struct argmin: public FunctionExpression {
            argmin() : FunctionExpression("argmin", {vararg("a")}) {}
            expression call(expression args) const override {
                auto array = args->at(0)->array();
                return num(gsl_stats_min_index(array.data(), 1, array.size()));
            }
        };

        // @Function median
        struct median: public FunctionExpression {
            median() : FunctionExpression("median", {vararg("a")}) {}
            expression call(expression args) const override {
                auto array = args->at(0)->array();
                return num(gsl_stats_median(array.data(), 1, array.size()));
            }
        };
    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression absdev = std::shared_ptr<fexpr::absdev>(new fexpr::absdev());
        const expression argmax = std::shared_ptr<fexpr::argmax>(new fexpr::argmax());
        const expression argmin = std::shared_ptr<fexpr::argmin>(new fexpr::argmin());
        const expression kurtosis = std::shared_ptr<fexpr::kurtosis>(new fexpr::kurtosis());
        const expression lag1 = std::shared_ptr<fexpr::lag1>(new fexpr::lag1());
        const expression max = std::shared_ptr<fexpr::max>(new fexpr::max());
        const expression mean = std::shared_ptr<fexpr::mean>(new fexpr::mean());
        const expression median = std::shared_ptr<fexpr::median>(new fexpr::median());
        const expression min = std::shared_ptr<fexpr::min>(new fexpr::min());
        const expression sd = std::shared_ptr<fexpr::sd>(new fexpr::sd());
        const expression skew = std::shared_ptr<fexpr::skew>(new fexpr::skew());
        const expression tss = std::shared_ptr<fexpr::tss>(new fexpr::tss());
        const expression var = std::shared_ptr<fexpr::var>(new fexpr::var());
        // end sourcegen
    }  // namespace functions
}  // namespace calcpp
