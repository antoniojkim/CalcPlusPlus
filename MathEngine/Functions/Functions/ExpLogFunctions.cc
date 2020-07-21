#include <cmath>

#include <gsl/gsl_sf_log.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../Functions.h"

namespace Function {
    // @Function exp
    struct exp: public ValueFunctionExpression {
        exp(int functionIndex, expression arg):
            ValueFunctionExpression(functionIndex, std::exp, arg) {}
        expression derivative(const std::string& var) {
            using ExpressionMath::exp;
            auto x = arg->at(0);
            return exp(x) * x->derivative(var);
        }
    };
    MAKE_FUNCTION_EXPRESSION(exp)

    // @Function exp2
    struct exp2: public ValueFunctionExpression {
        exp2(int functionIndex, expression arg):
            ValueFunctionExpression(functionIndex, std::exp2, arg) {}
        expression derivative(const std::string& var) {
            using ExpressionMath::exp2;
            auto x = arg->at(0);
            return exp2(x) * M_LN2 * x->derivative(var);
        }
    };
    MAKE_FUNCTION_EXPRESSION(exp2)

    // @Function expm1
    struct expm1: public ValueFunctionExpression {
        expm1(int functionIndex, expression arg):
            ValueFunctionExpression(functionIndex, std::expm1, arg) {}
        expression derivative(const std::string& var) {
            using ExpressionMath::expm1;
            auto x = arg->at(0);
            return expm1(x) * x->derivative(var);
        }
    };
    MAKE_FUNCTION_EXPRESSION(expm1)

    // @Function ln
    struct ln: public ValueFunctionExpression {
        ln(int functionIndex, expression arg):
            ValueFunctionExpression(functionIndex, std::log, arg) {}
        expression derivative(const std::string& var) {
            auto x = arg->at(0);
            return x->derivative(var) / x;
        }
    };
    MAKE_FUNCTION_EXPRESSION(ln)

    // @Function ln2: log2
    struct ln2: public ValueFunctionExpression {
        ln2(int functionIndex, expression arg):
            ValueFunctionExpression(functionIndex, std::log2, arg) {}
        expression derivative(const std::string& var) {
            auto x = arg->at(0);
            return x->derivative(var) / (x * M_LN2);
        }
    };
    MAKE_FUNCTION_EXPRESSION(ln2)

    // @Function ln1p: log1p
    struct ln1p: public ValueFunctionExpression {
        ln1p(int functionIndex, expression arg):
            ValueFunctionExpression(functionIndex, std::log1p, arg) {}
        expression derivative(const std::string& var) {
            auto x = arg->at(0);
            return x->derivative(var) / (x + 1);
        }
    };
    MAKE_FUNCTION_EXPRESSION(ln1p)

    // @Function log: log10
    struct log: public ValueFunctionExpression {
        log(int functionIndex, expression arg):
            ValueFunctionExpression(functionIndex, std::log10, arg) {}
        expression derivative(const std::string& var) {
            auto x = arg->at(0);
            return x->derivative(var) / (x * M_LN10);
        }
    };
    MAKE_FUNCTION_EXPRESSION(log)

    // @Function log1pm
    MAKE_VALUEFUNCTION_EXPRESSION(log1pm, gsl_sf_log_1plusx_mx)

    // @Function logabs
    MAKE_VALUEFUNCTION_EXPRESSION(logabs, gsl_sf_log_abs)

    // @Function logn
    struct logn: public FunctionExpression {
        logn(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"a", Empty}, {"b", Empty}}) {}  // Signature: (a, b)
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(0)->value(vars);
            double b = arg->at(1)->value(vars);
            return std::log(a) / std::log(b);
        }
        expression derivative(const std::string& var) {
            using ExpressionMath::ln;
            auto a = arg->at(0);
            auto b = arg->at(1);
            return a->derivative(var) / (a * ln(b));
        }
    };
    MAKE_FUNCTION_EXPRESSION(logn)
}
