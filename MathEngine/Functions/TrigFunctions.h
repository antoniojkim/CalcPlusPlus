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
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("cos", e);
        }
    } sin ("sin", std::sin);

    // @Function cos
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -FunctionExpression::construct("sin", e);
        }
    } cos ("cos", std::cos);

    // @Function tan
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("sec", e) ^ 2;
        }
    } tan ("tan", std::tan);

    // @Function asin arcsin arsin
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / sqrt(1 - (e ^ 2));
        }
    } asin ("asin", std::asin);

    // @Function acos arccos arcos
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -1 / sqrt(1 - (e ^ 2));
        }
    } acos ("acos", std::acos);

    // @Function atan arctan artan
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / (1 + (e ^ 2));
        }
    } atan ("atan", std::atan);

    // @Function sinh
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("cosh", e);
        }
    } sinh ("sinh", std::sinh);

    // @Function cosh
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("sinh", e);
        }
    } cosh ("cosh", std::cosh);

    // @Function tanh
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return FunctionExpression::construct("sech", e) ^ 2;
        }
    } tanh ("tanh", std::tanh);

    // @Function asinh arcsinh arsinh
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / sqrt((e ^ 2) + 1);
        }
    } asinh ("asinh", std::asinh);

    // @Function acosh arccosh arcosh
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / sqrt((e ^ 2) - 1);
        }
    } acosh ("acosh", std::acosh);

    // @Function atanh arctanh artanh
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / (1 - (e ^ 2));
        }
    } atanh ("atanh", std::atanh);

    // @Function csc
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -FunctionExpression::construct("cot", e) * FunctionExpression::construct("csc", e);
        }
    } csc ("csc", [](double x) -> double { return 1.0 / std::sin(x); });

    // @Function sec
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -FunctionExpression::construct("tan", e) * FunctionExpression::construct("sec", e);
        }
    } sec ("sec", [](double x) -> double { return 1.0 / std::cos(x); });

    // @Function cot
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -(FunctionExpression::construct("csc", e) ^ 2);
        }
    } cot ("cot", [](double x) -> double { return 1.0 / std::tan(x); });

    // @Function acsc arccsc arcsc
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -1 / (abs(e) * sqrt((e ^ 2) - 1));
        }
    } acsc ("acsc", [](double x) -> double { return std::asin(1.0 / x); });

    // @Function asec arcsec arsec
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / (abs(e) * sqrt((e ^ 2) - 1));
        }
    } asec ("asec", [](double x) -> double { return std::acos(1.0 / x); });

    // @Function acot arccot arcot
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -1 / (1 + (e ^ 2));
        }
    } acot ("acot", [](double x) -> double { return (x > 0 ? M_PI_2 : -M_PI_2) - std::atan(x); });

    // @Function csch
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -FunctionExpression::construct("coth", e) * FunctionExpression::construct("csch", e);
        }
    } csch ("csch", [](double x) -> double { return 1.0 / std::sinh(x); });

    // @Function sech
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -FunctionExpression::construct("tanh", e) * FunctionExpression::construct("sech", e);
        }
    } sech ("sech", [](double x) -> double { return 1.0 / std::cosh(x); });

    // @Function coth
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -(FunctionExpression::construct("csch", e) ^ 2);
        }
    } coth ("coth", [](double x) -> double { return 1.0 / std::tanh(x); });

    // @Function acsch arccsch arcsch
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -1 / (abs(e) * sqrt((e ^ 2) - 1));
        }
    } acsch ("acsch", [](double x) -> double {
        if (x == 0){
            return GSL_NAN;
        }
        return std::log(1 / x + std::sqrt(1 / (x * x) + 1));
    });

    // @Function asech arcsech arsech
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return -1 / (abs(e) * sqrt(1 - (e ^ 2)));
        }
    } asech ("asech", [](double x) -> double {
        if (x <= 0 || x > 1){
            return GSL_NAN;
        }
        return std::log(1 / x + std::sqrt(1 / (x * x) - 1));
    });

    // @Function acoth arccoth arcoth
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 1 / (1 - (e ^ 2));
        }
    } acoth ("acoth", [](double x) -> double {
        if (x >= -1 && x <= 1){
            return GSL_NAN;
        }
        return std::log((x + 1) / (x - 1)) / 2;
    });
}
