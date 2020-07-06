#include <cmath>

#include <gsl/gsl_math.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/InvalidExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../Functions.h"

namespace Function {

    // @Function sin(x)
    namespace sin {
        double (*value)(double) = std::sin;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::cos;
            auto x = args.next();
            return cos(x);
        }
    }

    // @Function cos(x)
    namespace cos {
        double (*value)(double) = std::cos;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::cos;
            auto x = args.next();
            return -cos(x);
        }
    }

    // @Function tan(x)
    namespace tan {
        double (*value)(double) = std::tan;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sec;
            auto x = args.next();
            return sec(x) ^ 2;
        }
    }

    // @Function asin(x): arcsin arsin
    namespace asin {
        double (*value)(double) = std::asin;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = args.next();
            return 1 / sqrt(1 - (x ^ 2));
        }
    }

    // @Function acos(x): arccos arcos
    namespace acos {
        double (*value)(double) = std::acos;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = args.next();
            return -1 / sqrt(1 - (x ^ 2));
        }
    }

    // @Function atan(x): arctan artan
    namespace atan {
        double (*value)(double) = std::atan;
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return 1 / (1 + (x ^ 2));
        }
    }

    // @Function sinh(x)
    namespace sinh {
        double (*value)(double) = std::sinh;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::cosh;
            auto x = args.next();
            return cosh(x);
        }
    }

    // @Function cosh(x)
    namespace cosh {
        double (*value)(double) = std::cosh;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sinh;
            auto x = args.next();
            return sinh(x);
        }
    }

    // @Function tanh(x)
    namespace tanh {
        double (*value)(double) = std::tanh;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sech;
            auto x = args.next();
            return sech(x) ^ 2;
        }
    }

    // @Function asinh(x): arcsinh arsinh
    namespace asinh {
        double (*value)(double) = std::asinh;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = args.next();
            return 1 / sqrt((x ^ 2) + 1);
        }
    }

    // @Function acosh(x): arccosh arcosh
    namespace acosh {
        double (*value)(double) = std::acosh;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = args.next();
            return 1 / sqrt((x ^ 2) - 1);
        }
    }

    // @Function atanh(x): arctanh artanh
    namespace atanh {
        double (*value)(double) = std::atanh;
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return 1 / (1 - (x ^ 2));
        }
    }

    // @Function csc(x)
    namespace csc {
        double value(double x) { return 1.0 / std::sin(x); }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::cot, ExpressionMath::csc;
            auto x = args.next();
            return -cot(x) * csc(x);
        }
    }

    // @Function sec(x)
    namespace sec {
        double value(double x) { return 1.0 / std::cos(x); }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::tan, ExpressionMath::sec;
            auto x = args.next();
            return -tan(x) * sec(x);
        }
    }

    // @Function cot(x)
    namespace cot {
        double value(double x) { return 1.0 / std::tan(x); }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::csc;
            auto x = args.next();
            return -(csc(x) ^ 2); }
    }

    // @Function acsc(x): arccsc arcsc
    namespace acsc {
        double value(double x) { return std::asin(1.0 / x); }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = args.next();
            return -1 / (abs(x) * sqrt((x ^ 2) - 1)); }
    }

    // @Function asec(x): arcsec arsec
    namespace asec {
        double value(double x) { return std::acos(1.0 / x); }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = args.next();
            return 1 / (abs(x) * sqrt((x ^ 2) - 1));
        }
    }

    // @Function acot(x): arccot arcot
    namespace acot {
        double value(double x) { return (x > 0 ? M_PI_2 : -M_PI_2) - std::atan(x); }
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return -1 / (1 + (x ^ 2));
        }
    }

    // @Function csch(x)
    namespace csch {
        double value(double x) { return 1.0 / std::sinh(x); }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::coth, ExpressionMath::csch;
            auto x = args.next();
            return -coth(x) * csch(x);
        }
    }

    // @Function sech(x)
    namespace sech {
        double value(double x) { return 1.0 / std::cosh(x); }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::tanh, ExpressionMath::sech;
            auto x = args.next();
            return -tanh(x) * sech(x);
        }
    }

    // @Function coth(x)
    namespace coth {
        double value(double x) { return 1.0 / std::tanh(x); }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::csch;
            auto x = args.next();
            return -(csch(x) ^ 2);
        }
    }

    // @Function acsch(x): arccsch arcsch
    namespace acsch {
        double value(double x) {
            if (x == 0){ return GSL_NAN; }
            return std::log(1 / x + std::sqrt(1 / (x * x) + 1));
        }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = args.next();
            return -1 / (abs(x) * sqrt((x ^ 2) - 1)); }
    }

    // @Function asech(x): arcsech arsech
    namespace asech {
        double value(double x) {
            if (x <= 0 || x > 1){ return GSL_NAN; }
            return std::log(1 / x + std::sqrt(1 / (x * x) - 1));
        }
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = args.next();
            return -1 / (abs(x) * sqrt(1 - (x ^ 2))); }
    }

    // @Function acoth(x): arccoth arcoth
    namespace acoth {
        double value(double x) {
            if (x >= -1 && x <= 1){ return GSL_NAN; }
            return std::log((x + 1) / (x - 1)) / 2;
        }
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return 1 / (1 - (x ^ 2));
        }
    }
}
