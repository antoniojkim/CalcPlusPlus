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
#include "AbstractFunction.h"

namespace Function {

    // @Function sin
    const struct sin: public Function::ValueFunction {
        sin(): ValueFunction("sin", std::sin) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::cos;
            return cos(e);
        }
    } __sin__;

    // @Function cos
    const struct cos: public Function::ValueFunction {
        cos(): ValueFunction("cos", std::cos) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::cos;
            return -cos(e);
        }
    } __cos__;

    // @Function tan
    const struct tan: public Function::ValueFunction {
        tan(): ValueFunction("tan", std::tan) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sec;
            return sec(e) ^ 2;
        }
    } __tan__;

    // @Function asin arcsin arsin
    const struct asin: public Function::ValueFunction {
        asin(): ValueFunction("asin", std::asin) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sqrt;
            return 1 / sqrt(1 - (e ^ 2));
        }
    } __asin__;

    // @Function acos arccos arcos
    const struct acos: public Function::ValueFunction {
        acos(): ValueFunction("acos", std::acos) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sqrt;
            return -1 / sqrt(1 - (e ^ 2));
        }
    } __acos__;

    // @Function atan arctan artan
    const struct atan: public Function::ValueFunction {
        atan(): ValueFunction("atan", std::atan) {}
        expression derivative(expression e, const std::string& var) override { return 1 / (1 + (e ^ 2)); }
    } __atan__;

    // @Function sinh
    const struct sinh: public Function::ValueFunction {
        sinh(): ValueFunction("sinh", std::sinh) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::cosh;
            return cosh(e);
        }
    } __sinh__;

    // @Function cosh
    const struct cosh: public Function::ValueFunction {
        cosh(): ValueFunction("cosh", std::cosh) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sinh;
            return sinh(e);
        }
    } __cosh__;

    // @Function tanh
    const struct tanh: public Function::ValueFunction {
        tanh(): ValueFunction("tanh", std::tanh) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sech;
            return sech(e) ^ 2;
        }
    } __tanh__;

    // @Function asinh arcsinh arsinh
    const struct asinh: public Function::ValueFunction {
        asinh(): ValueFunction("asinh", std::asinh) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sqrt;
            return 1 / sqrt((e ^ 2) + 1);
        }
    } __asinh__;

    // @Function acosh arccosh arcosh
    const struct acosh: public Function::ValueFunction {
        acosh(): ValueFunction("acosh", std::acosh) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sqrt;
            return 1 / sqrt((e ^ 2) - 1);
        }
    } __acosh__;

    // @Function atanh arctanh artanh
    const struct atanh: public Function::ValueFunction {
        atanh(): ValueFunction("atanh", std::atanh) {}
        expression derivative(expression e, const std::string& var) override { return 1 / (1 - (e ^ 2)); }
    } __atanh__;

    // @Function csc
    const struct csc: public Function::ValueFunction {
        csc(): ValueFunction("csc") {}
        double value(double x) override { return 1.0 / std::sin(x); }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::cot, ExpressionMath::csc;
            return -cot(e) * csc(e);
        }
    } __csc__;

    // @Function sec
    const struct sec: public Function::ValueFunction {
        sec(): ValueFunction("sec") {}
        double value(double x) override { return 1.0 / std::cos(x); }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::tan, ExpressionMath::sec;
            return -tan(e) * sec(e);
        }
    } __sec__;

    // @Function cot
    const struct cot: public Function::ValueFunction {
        cot(): ValueFunction("cot") {}
        double value(double x) override { return 1.0 / std::tan(x); }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::csc;
            return -(csc(e) ^ 2); }
    } __cot__;

    // @Function acsc arccsc arcsc
    const struct acsc: public Function::ValueFunction {
        acsc(): ValueFunction("acsc") {}
        double value(double x) override { return std::asin(1.0 / x); }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            return -1 / (abs(e) * sqrt((e ^ 2) - 1)); }
    } __acsc__;

    // @Function asec arcsec arsec
    const struct asec: public Function::ValueFunction {
        asec(): ValueFunction("asec") {}
        double value(double x) override { return std::acos(1.0 / x); }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            return 1 / (abs(e) * sqrt((e ^ 2) - 1));
        }
    } __asec__;

    // @Function acot arccot arcot
    const struct acot: public Function::ValueFunction {
        acot(): ValueFunction("acot") {}
        double value(double x) override { return (x > 0 ? M_PI_2 : -M_PI_2) - std::atan(x); }
        expression derivative(expression e, const std::string& var) override {
            return -1 / (1 + (e ^ 2));
        }
    } __acot__;

    // @Function csch
    const struct csch: public Function::ValueFunction {
        csch(): ValueFunction("csch") {}
        double value(double x) override { return 1.0 / std::sinh(x); }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::coth, ExpressionMath::csch;
            return -coth(e) * csch(e);
        }
    } __csch__;

    // @Function sech
    const struct sech: public Function::ValueFunction {
        sech(): ValueFunction("sech") {}
        double value(double x) override { return 1.0 / std::cosh(x); }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::tanh, ExpressionMath::sech;
            return -tanh(e) * sech(e);
        }
    } __sech__;

    // @Function coth
    const struct coth: public Function::ValueFunction {
        coth(): ValueFunction("coth") {}
        double value(double x) override { return 1.0 / std::tanh(x); }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::csch;
            return -(csch(e) ^ 2);
        }
    } __coth__;

    // @Function acsch arccsch arcsch
    const struct acsch: public Function::ValueFunction {
        acsch(): ValueFunction("acsch") {}
        double value(double x) override {
            if (x == 0){ return GSL_NAN; }
            return std::log(1 / x + std::sqrt(1 / (x * x) + 1));
        }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            return -1 / (abs(e) * sqrt((e ^ 2) - 1)); }
    } __acsch__;

    // @Function asech arcsech arsech
    const struct asech: public Function::ValueFunction {
        asech(): ValueFunction("asech") {}
        double value(double x) override {
            if (x <= 0 || x > 1){ return GSL_NAN; }
            return std::log(1 / x + std::sqrt(1 / (x * x) - 1));
        }
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::abs, ExpressionMath::sqrt;
            return -1 / (abs(e) * sqrt(1 - (e ^ 2))); }
    } __asech__;

    // @Function acoth arccoth arcoth
    const struct acoth: public Function::ValueFunction {
        acoth(): ValueFunction("acoth") {}
        double value(double x) override {
            if (x >= -1 && x <= 1){ return GSL_NAN; }
            return std::log((x + 1) / (x - 1)) / 2;
        }
        expression derivative(expression e, const std::string& var) override {
            return 1 / (1 - (e ^ 2));
        }
    } __acoth__;
}
