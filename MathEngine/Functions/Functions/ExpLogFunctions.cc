#include <cmath>

#include <gsl/gsl_sf_log.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NumericalExpression.h"
#include "../Functions.h"

namespace Function {
    // @Function exp(x)
    namespace exp {
        double (*value)(double) = std::exp;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::exp;
            auto x = args.next();
            return exp(x) * x->derivative(var);
        }
    }

    // @Function exp2(x)
    namespace exp2 {
        double (*value)(double) = std::exp2;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::exp2;
            auto x = args.next();
            return exp2(x) * M_LN2 * x->derivative(var);
        }
    }

    // @Function expm1(x)
    namespace expm1 {
        double (*value)(double) = std::expm1;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::expm1;
            auto x = args.next();
            return expm1(x) * x->derivative(var);
        }
    }

    // @Function ln(x)
    namespace ln {
        double (*value)(double) = std::log;
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return x->derivative(var) / x;
        }
    }

    // @Function ln2(x): log2
    namespace ln2 {
        double (*value)(double) = std::log2;
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return x->derivative(var) / (x * M_LN2);
        }
    }

    // @Function ln1p(x): log1p
    namespace ln1p {
        double (*value)(double) = std::log1p;
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return x->derivative(var) / (x + 1);
        }
    }

    // @Function log(x): log10
    namespace log {
        double (*value)(double) = std::log10;
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return x->derivative(var) / (x * M_LN10);
        }
    }

    // @Function log1pm(x)
    namespace log1pm {
        double (*value)(double) = gsl_sf_log_1plusx_mx;
    }

    // @Function logabs(x)
    namespace logabs {
        double (*value)(double) = gsl_sf_log_abs;
    }

    // @Function logn(a, b)
    namespace logn {
        expression eval(Function::Args& args) {
            auto a = args.next();
            auto b = args.next();
            return NumExpression::construct(std::log(a->value()) / std::log(b->value()));
        }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::ln;
            auto a = args.next();
            auto b = args.next();
            return a->derivative(var) / (a * ln(b));
        }
    }
}
