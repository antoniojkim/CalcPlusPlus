#pragma once

#include <cmath>

#include <gsl/gsl_math.h>

#include "../Expressions/Expression.h"
#include "../Expressions/ExpressionFunctions.h"
#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/TupleExpression.h"
#include "../Utils/Argparse.h"
#include "../AbstractFunction.h"

namespace Function {

    // @Function sin
    const struct __sin__: public Function::ValueFunction {
        __sin__(): ValueFunction("sin", std::sin) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::cos;
            auto x = args["x"];
            return cos(x);
        }
    } sin;

    // @Function cos
    const struct __cos__: public Function::ValueFunction {
        __cos__(): ValueFunction("cos", std::cos) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::cos;
            auto x = args["x"];
            return -cos(x);
        }
    } cos;

    // @Function tan
    const struct __tan__: public Function::ValueFunction {
        __tan__(): ValueFunction("tan", std::tan) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::sec;
            auto x = args["x"];
            return sec(x) ^ 2;
        }
    } tan;

    // @Function asin arcsin arsin
    const struct __asin__: public Function::ValueFunction {
        __asin__(): ValueFunction("asin", std::asin) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::sqrt;
            auto x = args["x"];
            return 1 / sqrt(1 - (x ^ 2));
        }
    } asin;

    // @Function acos arccos arcos
    const struct __acos__: public Function::ValueFunction {
        __acos__(): ValueFunction("acos", std::acos) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::sqrt;
            auto x = args["x"];
            return -1 / sqrt(1 - (x ^ 2));
        }
    } acos;

    // @Function atan arctan artan
    const struct __atan__: public Function::ValueFunction {
        __atan__(): ValueFunction("atan", std::atan) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            auto x = args["x"];
            return 1 / (1 + (x ^ 2));
        }
    } atan;

    // @Function sinh
    const struct __sinh__: public Function::ValueFunction {
        __sinh__(): ValueFunction("sinh", std::sinh) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::cosh;
            auto x = args["x"];
            return cosh(x);
        }
    } sinh;

    // @Function cosh
    const struct __cosh__: public Function::ValueFunction {
        __cosh__(): ValueFunction("cosh", std::cosh) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::sinh;
            auto x = args["x"];
            return sinh(x);
        }
    } cosh;

    // @Function tanh
    const struct __tanh__: public Function::ValueFunction {
        __tanh__(): ValueFunction("tanh", std::tanh) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::sech;
            auto x = args["x"];
            return sech(x) ^ 2;
        }
    } tanh;

    // @Function asinh arcsinh arsinh
    const struct __asinh__: public Function::ValueFunction {
        __asinh__(): ValueFunction("asinh", std::asinh) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::sqrt;
            auto x = args["x"];
            return 1 / sqrt((x ^ 2) + 1);
        }
    } asinh;

    // @Function acosh arccosh arcosh
    const struct __acosh__: public Function::ValueFunction {
        __acosh__(): ValueFunction("acosh", std::acosh) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::sqrt;
            auto x = args["x"];
            return 1 / sqrt((x ^ 2) - 1);
        }
    } acosh;

    // @Function atanh arctanh artanh
    const struct __atanh__: public Function::ValueFunction {
        __atanh__(): ValueFunction("atanh", std::atanh) {}
        expression derivative(Function::Args& args, const std::string& var) override {
            auto x = args["x"];
            return 1 / (1 - (x ^ 2));
        }
    } atanh;

    // @Function csc
    const struct __csc__: public Function::ValueFunction {
        __csc__(): ValueFunction("csc") {}
        double value(double x) override { return 1.0 / std::sin(x); }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::cot, ExpressionMath::csc;
            auto x = args["x"];
            return -cot(x) * csc(x);
        }
    } csc;

    // @Function sec
    const struct __sec__: public Function::ValueFunction {
        __sec__(): ValueFunction("sec") {}
        double value(double x) override { return 1.0 / std::cos(x); }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::tan, ExpressionMath::sec;
            auto x = args["x"];
            return -tan(x) * sec(x);
        }
    } sec;

    // @Function cot
    const struct __cot__: public Function::ValueFunction {
        __cot__(): ValueFunction("cot") {}
        double value(double x) override { return 1.0 / std::tan(x); }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::csc;
            auto x = args["x"];
            return -(csc(x) ^ 2); }
    } cot;

    // @Function acsc arccsc arcsc
    const struct __acsc__: public Function::ValueFunction {
        __acsc__(): ValueFunction("acsc") {}
        double value(double x) override { return std::asin(1.0 / x); }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = args["x"];
            return -1 / (abs(x) * sqrt((x ^ 2) - 1)); }
    } acsc;

    // @Function asec arcsec arsec
    const struct __asec__: public Function::ValueFunction {
        __asec__(): ValueFunction("asec") {}
        double value(double x) override { return std::acos(1.0 / x); }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = args["x"];
            return 1 / (abs(x) * sqrt((x ^ 2) - 1));
        }
    } asec;

    // @Function acot arccot arcot
    const struct __acot__: public Function::ValueFunction {
        __acot__(): ValueFunction("acot") {}
        double value(double x) override { return (x > 0 ? M_PI_2 : -M_PI_2) - std::atan(x); }
        expression derivative(Function::Args& args, const std::string& var) override {
            auto x = args["x"];
            return -1 / (1 + (x ^ 2));
        }
    } acot;

    // @Function csch
    const struct __csch__: public Function::ValueFunction {
        __csch__(): ValueFunction("csch") {}
        double value(double x) override { return 1.0 / std::sinh(x); }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::coth, ExpressionMath::csch;
            auto x = args["x"];
            return -coth(x) * csch(x);
        }
    } csch;

    // @Function sech
    const struct __sech__: public Function::ValueFunction {
        __sech__(): ValueFunction("sech") {}
        double value(double x) override { return 1.0 / std::cosh(x); }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::tanh, ExpressionMath::sech;
            auto x = args["x"];
            return -tanh(x) * sech(x);
        }
    } sech;

    // @Function coth
    const struct __coth__: public Function::ValueFunction {
        __coth__(): ValueFunction("coth") {}
        double value(double x) override { return 1.0 / std::tanh(x); }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::csch;
            auto x = args["x"];
            return -(csch(x) ^ 2);
        }
    } coth;

    // @Function acsch arccsch arcsch
    const struct __acsch__: public Function::ValueFunction {
        __acsch__(): ValueFunction("acsch") {}
        double value(double x) override {
            if (x == 0){ return GSL_NAN; }
            return std::log(1 / x + std::sqrt(1 / (x * x) + 1));
        }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = args["x"];
            return -1 / (abs(x) * sqrt((x ^ 2) - 1)); }
    } acsch;

    // @Function asech arcsech arsech
    const struct __asech__: public Function::ValueFunction {
        __asech__(): ValueFunction("asech") {}
        double value(double x) override {
            if (x <= 0 || x > 1){ return GSL_NAN; }
            return std::log(1 / x + std::sqrt(1 / (x * x) - 1));
        }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            auto x = args["x"];
            return -1 / (abs(x) * sqrt(1 - (x ^ 2))); }
    } asech;

    // @Function acoth arccoth arcoth
    const struct __acoth__: public Function::ValueFunction {
        __acoth__(): ValueFunction("acoth") {}
        double value(double x) override {
            if (x >= -1 && x <= 1){ return GSL_NAN; }
            return std::log((x + 1) / (x - 1)) / 2;
        }
        expression derivative(Function::Args& args, const std::string& var) override {
            auto x = args["x"];
            return 1 / (1 - (x ^ 2));
        }
    } acoth;
}
