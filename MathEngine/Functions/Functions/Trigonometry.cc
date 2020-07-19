#include <cmath>

#include <gsl/gsl_math.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../Functions.h"

namespace Function {

    // @Function sin(x)
    struct sin: public ValueFunctionExpression {
        sin(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::sin, arg) {}
        expression derivative(const std::string& var) {
            using ExpressionMath::cos;
            auto x = arg->at(1);
            return cos(x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(sin)

    // @Function cos(x)
    struct cos: public ValueFunctionExpression {
        cos(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::cos, arg) {}
        expression derivative(const std::string& var) {
            using ExpressionMath::cos;
            auto x = arg->at(1);
            return -cos(x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(cos)

    // @Function tan(x)
    struct tan: public ValueFunctionExpression {
        tan(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::tan, arg) {};
        expression derivative(const std::string& var) {
            using ExpressionMath::sec;
            auto x = arg->at(1);
            return sec(x) ^ 2;
        }
    };
    MAKE_FUNCTION_EXPRESSION(tan)

    // @Function asin: arcsin arsin
    struct asin: public ValueFunctionExpression {
        asin(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::asin, arg) {};
        expression derivative(const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = arg->at(1);
            return 1 / sqrt(1 - (x ^ 2));
        }
    };
    MAKE_FUNCTION_EXPRESSION(asin)

    // @Function acos: arccos arcos
    struct acos: public ValueFunctionExpression {
        acos(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::acos, arg) {};
        expression derivative(const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = arg->at(1);
            return -1 / sqrt(1 - (x ^ 2));
        }
    };
    MAKE_FUNCTION_EXPRESSION(acos)

    // @Function atan: arctan artan
    struct atan: public ValueFunctionExpression {
        atan(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::atan, arg) {};
        expression derivative(const std::string& var) {
            auto x = arg->at(1);
            return 1 / (1 + (x ^ 2));
        }
    };
    MAKE_FUNCTION_EXPRESSION(atan)

    // @Function sinh(x)
    struct sinh: public ValueFunctionExpression {
        sinh(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::sinh, arg) {};
        expression derivative(const std::string& var) {
            using ExpressionMath::cosh;
            auto x = arg->at(1);
            return cosh(x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(sinh)

    // @Function cosh(x)
    struct cosh: public ValueFunctionExpression {
        cosh(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::cosh, arg) {};
        expression derivative(const std::string& var) {
            using ExpressionMath::sinh;
            auto x = arg->at(1);
            return sinh(x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(cosh)

    // @Function tanh(x)
    struct tanh: public ValueFunctionExpression {
        tanh(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::tanh, arg) {};
        expression derivative(const std::string& var) {
            using ExpressionMath::sech;
            auto x = arg->at(1);
            return sech(x) ^ 2;
        }
    };
    MAKE_FUNCTION_EXPRESSION(tanh)

    // @Function asinh: arcsinh arsinh
    struct asinh: public ValueFunctionExpression {
        asinh(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::asinh, arg) {};
        expression derivative(const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = arg->at(1);
            return 1 / sqrt((x ^ 2) + 1);
        }
    };
    MAKE_FUNCTION_EXPRESSION(asinh)

    // @Function acosh: arccosh arcosh
    struct acosh: public ValueFunctionExpression {
        acosh(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::acosh, arg) {};
        expression derivative(const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = arg->at(1);
            return 1 / sqrt((x ^ 2) - 1);
        }
    };
    MAKE_FUNCTION_EXPRESSION(acosh)

    // @Function atanh: arctanh artanh
    struct atanh: public ValueFunctionExpression {
        atanh(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::atanh, arg) {};
        expression derivative(const std::string& var) {
            auto x = arg->at(1);
            return 1 / (1 - (x ^ 2));
        }
    };
    MAKE_FUNCTION_EXPRESSION(atanh)

    // @Function csc(x)
    struct csc: public ValueFunctionExpression {
        csc(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            return 1.0 / std::sin(x);
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::cot, ExpressionMath::csc;
            auto x = arg->at(1);
            return -cot(x) * csc(x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(csc)

    // @Function sec(x)
    struct sec: public ValueFunctionExpression {
        sec(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            return 1.0 / std::cos(x);
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::tan, ExpressionMath::sec;
            auto x = arg->at(1);
            return -tan(x) * sec(x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(sec)

    // @Function cot(x)
    struct cot: public ValueFunctionExpression {
        cot(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            return 1.0 / std::tan(x);
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::csc;
            auto x = arg->at(1);
            return -(csc(x) ^ 2); }
    };
    MAKE_FUNCTION_EXPRESSION(cot)

    // @Function acsc: arccsc arcsc
    struct acsc: public ValueFunctionExpression {
        acsc(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            return std::asin(1.0 / x);
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = arg->at(1);
            return -1 / (abs(x) * sqrt((x ^ 2) - 1)); }
    };
    MAKE_FUNCTION_EXPRESSION(acsc)

    // @Function asec: arcsec arsec
    struct asec: public ValueFunctionExpression {
        asec(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            return std::acos(1.0 / x);
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = arg->at(1);
            return 1 / (abs(x) * sqrt((x ^ 2) - 1));
        }
    };
    MAKE_FUNCTION_EXPRESSION(asec)

    // @Function acot: arccot arcot
    struct acot: public ValueFunctionExpression {
        acot(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            return (x > 0 ? M_PI_2 : -M_PI_2) - std::atan(x);
        }
        expression derivative(const std::string& var) {
            auto x = arg->at(1);
            return -1 / (1 + (x ^ 2));
        }
    };
    MAKE_FUNCTION_EXPRESSION(acot)

    // @Function csch(x)
    struct csch: public ValueFunctionExpression {
        csch(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            return 1.0 / std::sinh(x);
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::coth, ExpressionMath::csch;
            auto x = arg->at(1);
            return -coth(x) * csch(x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(csch)

    // @Function sech(x)
    struct sech: public ValueFunctionExpression {
        sech(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            return 1.0 / std::cosh(x);
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::tanh, ExpressionMath::sech;
            auto x = arg->at(1);
            return -tanh(x) * sech(x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(sech)

    // @Function coth(x)
    struct coth: public ValueFunctionExpression {
        coth(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            return 1.0 / std::tanh(x);
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::csch;
            auto x = arg->at(1);
            return -(csch(x) ^ 2);
        }
    };
    MAKE_FUNCTION_EXPRESSION(coth)

    // @Function acsch: arccsch arcsch
    struct acsch: public ValueFunctionExpression {
        acsch(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            if (x == 0){ return GSL_NAN; }
            return std::log(1 / x + std::sqrt(1 / (x * x) + 1));
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = arg->at(1);
            return -1 / (abs(x) * sqrt((x ^ 2) - 1)); }
    };
    MAKE_FUNCTION_EXPRESSION(acsch)

    // @Function asech: arcsech arsech
    struct asech: public ValueFunctionExpression {
        asech(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            if (x <= 0 || x > 1){ return GSL_NAN; }
            return std::log(1 / x + std::sqrt(1 / (x * x) - 1));
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = arg->at(1);
            return -1 / (abs(x) * sqrt(1 - (x ^ 2))); }
    };
    MAKE_FUNCTION_EXPRESSION(asech)

    // @Function acoth: arccoth arcoth
    struct acoth: public ValueFunctionExpression {
        acoth(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {};
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            if (x >= -1 && x <= 1){ return GSL_NAN; }
            return std::log((x + 1) / (x - 1)) / 2;
        }
        expression derivative(const std::string& var) {
            auto x = arg->at(1);
            return 1 / (1 - (x ^ 2));
        }
    };
    MAKE_FUNCTION_EXPRESSION(acoth)
}
