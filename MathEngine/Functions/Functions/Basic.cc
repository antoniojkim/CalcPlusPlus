#include <cmath>
#include <memory>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/FunctionExpression.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Expressions/VariableExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

using namespace std;

namespace Function {

    // @Function neg
    struct neg: public FunctionExpression {
        neg(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"x", Empty}}) {}  // Signature: (x)
        expression eval(const Variables& vars = emptyVars) override {
            auto x = arg->at(0)->eval(vars);
            if (x->isComplex()){
                return NumExpression::construct(gsl_complex_negative(x->complex()));
            }
            if (!x->isEvaluable()){
                return -x;
            }
            return NumExpression::construct(-x->value());
        }
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            return -x;
        }
        expression derivative(const std::string& var) {
            auto x = arg->at(0)->eval();
            return -x->derivative(var);
        }
    };
    expression make_fe_neg(int functionIndex, expression arg){
        if (arg->isNumber()){
            if (arg->isComplex()){
                return NumExpression::construct(gsl_complex_negative(arg->complex()));
            }
            return NumExpression::construct(-arg->value());
        }
        return std::make_shared<Function::neg>(functionIndex, arg);
    }


    // @Function frexp
    struct frexp: public FunctionExpression {
        frexp(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"x", Empty}}) {}  // Signature: (x)
        expression eval(const Variables& vars = emptyVars) override {
            double x = arg->at(0)->value(vars);
            int e;
            double f = gsl_frexp(x, &e);
            return TupleExpression::construct({f, (double) e});
        }
        double value(const Variables& vars = emptyVars) const { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(frexp)

    // @Function num
    struct num: public FunctionExpression {
        num(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"x", Empty}}) {}  // Signature: (x)
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            return x;
        }
    };
    MAKE_FUNCTION_EXPRESSION(num)

    // @Function hex
    struct hex: public FunctionExpression {
        hex(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"x", Empty}}) {}  // Signature: (x)
        expression eval(const Variables& vars = emptyVars) override {
            auto x = arg->at(0)->eval(vars);
            if (!x->isComplex()){
                double val = x->value();
                if (std::trunc(val) == val){
                    return HexExpression::construct((unsigned long long) std::trunc(val));
                }
            }
            throw Exception("Unable to convert to hex: ", x);
        }
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            return x;
        }
    };
    MAKE_FUNCTION_EXPRESSION(hex)

    // @Function bin
    struct bin: public FunctionExpression {
        bin(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"x", Empty}}) {}  // Signature: (x)
        expression eval(const Variables& vars = emptyVars) override {
            auto x = arg->at(0)->eval(vars);
            if (!x->isComplex()){
                double val = x->value();
                if (std::trunc(val) == val){
                    return BinExpression::construct((unsigned long long) std::trunc(val));
                }
            }
            throw Exception("Unable to convert to bin: ", x);
        }
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            return x;
        }
    };
    MAKE_FUNCTION_EXPRESSION(bin)

    // @Function abs
    struct abs: public ValueFunctionExpression {
        abs(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::abs, arg) {}
        expression derivative(const std::string& var) {
            using ExpressionMath::abs;
            auto x = arg->at(0);
            return x / abs(x) * x->derivative(var);
        }
    };
    MAKE_FUNCTION_EXPRESSION(abs)

    // @Function sqr
    struct sqr: public ValueFunctionExpression {
        sqr(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, gsl_pow_2, arg) {}
        expression derivative(const std::string& var) {
            auto x = arg->at(0)->eval();
            return 2 * x * x->derivative(var);
        }
        std::ostream& print(std::ostream& out, const bool pretty) {
            auto x = arg->at(0);
            return out << "("; x->print(out, pretty) << ")²";
        }
    };
    MAKE_FUNCTION_EXPRESSION(sqr)

    // @Function sqrt
    struct sqrt: public ValueFunctionExpression {
        sqrt(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::sqrt, arg) {}
        expression derivative(const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = arg->at(0)->eval();
            return 0.5 / sqrt(x) * x->derivative(var);
        }
        std::ostream& print(std::ostream& out, const bool pretty) {
            auto x = arg->at(0);
            return out << "√("; x->print(out, pretty) << ")";
        }
    };
    MAKE_FUNCTION_EXPRESSION(sqrt)

    // @Function cb
    struct cb: public ValueFunctionExpression {
        cb(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, gsl_pow_3, arg) {}
        expression derivative(const std::string& var) {
            using ExpressionMath::sqr;
            auto x = arg->at(0)->eval();
            return 3 * sqr(x) * x->derivative(var);
        }
        std::ostream& print(std::ostream& out, const bool pretty) {
            auto x = arg->at(0);
            return out << "("; x->print(out, pretty) << ")³";
        }
    };
    MAKE_FUNCTION_EXPRESSION(cb)

    // @Function cbrt
    struct cbrt: public ValueFunctionExpression {
        cbrt(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, std::cbrt, arg) {}
        expression derivative(const std::string& var) {
            using ExpressionMath::sqr, ExpressionMath::cbrt;
            auto x = arg->at(0)->eval();
            return (1.0 / 3) / sqr(cbrt(x)) * x->derivative(var);
        }
    };
    MAKE_FUNCTION_EXPRESSION(cbrt)

    // @Function rad
    struct rad: public ValueFunctionExpression {
        rad(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {}
        double value(const Variables& vars = emptyVars) const override {
            auto x = arg->at(0)->value(vars);
            return x * M_PI / 180;
        }
    };
    MAKE_FUNCTION_EXPRESSION(rad)

    // @Function deg
    struct deg: public ValueFunctionExpression {
        deg(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {}
        double value(const Variables& vars = emptyVars) const override {
            auto x = arg->at(0)->value(vars);
            return x * 180 / M_PI;
        }
    };
    MAKE_FUNCTION_EXPRESSION(deg)

    // @Function hypot
    struct hypot: public FunctionExpression {
        hypot(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"a", EmptyVarArgs}}) {}  // Signature: (a...)
        double value(const Variables& vars = emptyVars) const override {
            auto a = arg->at(0)->eval(vars)->array();
            switch(a.size()){
                case 2:
                    return gsl_hypot(a.at(0), a.at(1));
                case 3:
                    return gsl_hypot3(a.at(0), a.at(1), a.at(2));
                default: {
                    double sum = 0;
                    for (auto e : a){
                        sum += gsl_pow_2(e);
                    }
                    return std::sqrt(sum);
                }
            }
        }
    };
    MAKE_FUNCTION_EXPRESSION(hypot)

    // @Function ldexp
    struct ldexp: public FunctionExpression {
        ldexp(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"x", Empty}, {"e", Empty}}) {}  // Signature: (x, e)
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double e = arg->at(1)->value(vars);
            if (std::trunc(e) == e){
                return gsl_ldexp(x, (int) e);
            }
            throw Exception("ldexp expected an integer for 'e'. Got: ", e);
        }
    };
    MAKE_FUNCTION_EXPRESSION(ldexp)

    // @Function fcmp
    struct fcmp: public FunctionExpression {
        fcmp(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                 // Signature: (x, y, tol=1e-8)
                {"x", Empty}, {"y", Empty}, {"tol", NumExpression::construct(1e-8)}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double y = arg->at(1)->value(vars);
            double tol = arg->at(2)->value(vars);
            return gsl_fcmp(x, y, tol);
        }
    };
    MAKE_FUNCTION_EXPRESSION(fcmp)

    // @Function gcd
    struct gcd: public FunctionExpression {
        gcd(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"a", EmptyVarArgs}}) {}  // Signature: (a...)
        double value(const Variables& vars = emptyVars) const override {
            auto a = arg->at(0)->eval(vars)->array();
            long long g = 0;
            for (auto v : a){
                if (std::trunc(v) == v){
                    g = g == 0 ? v : std::gcd(g, (long long) v);
                }
                else{
                    throw Exception("gcd expected integer arguments. Got: ", arg);
                }
            }
            return g;
        }
    };
    MAKE_FUNCTION_EXPRESSION(gcd)

    // @Function lcm
    struct lcm: public FunctionExpression {
        lcm(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"a", EmptyVarArgs}}) {}  // Signature: (a...)
        double value(const Variables& vars = emptyVars) const override {
            auto a = arg->at(0)->eval(vars)->array();
            long long l = 0;
            for (auto v : a){
                if (std::trunc(v) == v){
                    l = l == 0 ? v : std::lcm(l, (long long) v);
                }
                else{
                    throw Exception("lcm expected integer arguments. Got: ", arg);
                }
            }
            return l;
        }
    };
    MAKE_FUNCTION_EXPRESSION(lcm)
}
