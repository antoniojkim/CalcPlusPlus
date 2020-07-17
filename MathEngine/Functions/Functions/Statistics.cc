#include <cmath>

#include <gsl/gsl_statistics_double.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {

    #define STAT_EVAL(F)                                                        \
        expression eval(Function::Args& args) {                                 \
            auto array = args.next()->array();                                  \
            return NumExpression::construct(F(array.data(), 1, array.size()));  \
        }

    // @Function mean(a...)
    namespace mean {
        STAT_EVAL(gsl_stats_mean)
    }

    // @Function var(a..., ddof=1): variance
    namespace var {
        expression eval(Function::Args& args) {
            auto array = args.next()->array();
            double ddof = args.nextValue();
            if (ddof < 1 || trunc(ddof) != ddof){
                throw Exception("Variance expected an integer ddof >= 1. Got: ", ddof);
            }
            if (trunc(ddof) == 1){
                return NumExpression::construct(gsl_stats_variance(array.data(), 1, array.size()));
            }
            double N = array.size();
            return NumExpression::construct(gsl_stats_tss(array.data(), 1, array.size()) / (N - ddof));
        }
    }

    // @Function sd(a..., ddof=1): std stdev
    namespace sd {
        expression eval(Function::Args& args) {
            auto array = args.next()->array();
            double ddof = args.nextValue();
            if (ddof < 1 || trunc(ddof) != ddof){
                throw Exception("Standard Deviation expected an integer ddof >= 1. Got: ", ddof);
            }
            if (trunc(ddof) == 1){
                return NumExpression::construct(gsl_stats_sd(array.data(), 1, array.size()));
            }
            double N = array.size();
            return NumExpression::construct(std::sqrt(gsl_stats_tss(array.data(), 1, array.size()) / (N - ddof)));
        }
    }

    // @Function tss(a...)
    namespace tss {
        STAT_EVAL(gsl_stats_tss)
    }

    // @Function absdev(a...)
    namespace absdev {
        STAT_EVAL(gsl_stats_absdev)
    }

    // @Function skew(a...)
    namespace skew {
        STAT_EVAL(gsl_stats_skew)
    }

    // @Function kurtosis(a...): kurt
    namespace kurtosis {
        STAT_EVAL(gsl_stats_kurtosis)
    }

    // @Function lag1(a...): autocorr
    namespace lag1 {
        STAT_EVAL(gsl_stats_lag1_autocorrelation)
    }

    // @Function max(a...)
    namespace max {
        STAT_EVAL(gsl_stats_max)
    }

    // @Function min(a...)
    namespace min {
        STAT_EVAL(gsl_stats_min)
    }

    // @Function argmax(a...): max_index
    namespace argmax {
        STAT_EVAL(gsl_stats_max_index)
    }

    // @Function argmin(a...): min_index
    namespace argmin {
        STAT_EVAL(gsl_stats_min_index)
    }

    // @Function median(a...)
    namespace median {
        STAT_EVAL(gsl_stats_median)
    }
}
