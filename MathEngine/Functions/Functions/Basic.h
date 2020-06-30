#pragma once

#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Utils/Exception.h"
#include "../AbstractFunction.h"

namespace Function {
    // @Function neg
    const struct __neg__: public Function::AbstractFunction {
        __neg__(): Function::AbstractFunction("neg", "(x,)") {}
        expression eval(Function::Args& args) const override {
            auto x = args["x"];
            if (x->isComplex()){
                return NumExpression::construct(gsl_complex_negative(x->complex()));
            }
            return NumExpression::construct(-x->value());
        }
        double value(double x) const override { return -x; }
        expression derivative(Function::Args& args, const std::string& var) const override {
            return -args["x"]->derivative(var);
        }
    } neg;

    // @Function frexp
    const struct __frexp__: public Function::AbstractFunction {
        __frexp__(): AbstractFunction("frexp", "(x,)") {}
        expression eval(Function::Args& args) const override {
            double x = args["x"]->value();
            int e;
            double f = gsl_frexp(x, &e);
            return TupleExpression::construct({f, (double) e});
        }
    } frexp;

    // @Function num
    const struct __num__: public Function::AbstractFunction {
        __num__(): AbstractFunction("num", "(x,)") {}
        expression eval(Function::Args& args) const override {
            return NumExpression::construct(args["x"]->value());
        }
        double value(double x) const override { return x; }
    } num;

    // @Function hex
    const struct __hex__: public Function::AbstractFunction {
        __hex__(): AbstractFunction("hex", "(x,)") {}
        expression eval(Function::Args& args) const override {
            auto x = args["x"];
            if (x->isComplex()){
                double val = x->value();
                if (std::trunc(val) == val){
                    return HexExpression::construct((unsigned long long) std::trunc(val));
                }
            }
            throw Exception("Unable to convert to hex: ", x);
        }
    } hex;

    // @Function bin
    const struct __bin__: public Function::AbstractFunction {
        __bin__(): AbstractFunction("bin", "(x,)") {}
        expression eval(Function::Args& args) const override {
            auto x = args["x"];
            if (x->isComplex()){
                double val = x->value();
                if (std::trunc(val) == val){
                    return BinExpression::construct((unsigned long long) std::trunc(val));
                }
            }
            throw Exception("Unable to convert to bin: ", x);
        }
    } bin;

    // @Function abs
    const struct __abs__: public Function::ValueFunction {
        __abs__(): ValueFunction("abs", std::abs) {}
        expression derivative(Function::Args& args, const std::string& var) const override {
            using ExpressionMath::abs;
            auto x = args["x"];
            return x / abs(x) * x->derivative(var);
        }
    } abs;

    // @Function sqr
    const struct __sqr__: public Function::ValueFunction {
        __sqr__(): ValueFunction("sqr", gsl_pow_2) {}
        expression derivative(Function::Args& args, const std::string& var) const override {
            auto x = args["x"];
            return 2 * x * x->derivative(var);
        }
        std::ostream& print(std::ostream& out, Function::Args& args) const override {
            return out << "(" << args["x"] << ")^2";
        }
    } sqr;

    // @Function sqrt
    const struct __sqrt__: public Function::ValueFunction {
        __sqrt__(): ValueFunction("sqrt", std::sqrt) {}
        expression derivative(Function::Args& args, const std::string& var) const override {
            using ExpressionMath::sqrt;
            auto x = args["x"];
            return 0.5 / sqrt(x) * x->derivative(var);
        }
        std::ostream& print(std::ostream& out, Function::Args& args) const override {
            return out << "(" << args["x"] << ")^3";
        }
    } sqrt;

    // @Function cb
    const struct __cb__: public Function::ValueFunction {
        __cb__(): ValueFunction("cb", gsl_pow_3) {}
        expression derivative(Function::Args& args, const std::string& var) const override {
            using ExpressionMath::sqr;
            auto x = args["x"];
            return 3 / sqr(x) * x->derivative(var);
        }
        std::ostream& print(std::ostream& out, Function::Args& args) const override {
            return out << "(" << args["x"] << ")^3";
        }
    } cb;

    // @Function cbrt
    const struct __cbrt__: public Function::ValueFunction {
        __cbrt__(): ValueFunction("cbrt", std::cbrt) {}
        expression derivative(Function::Args& args, const std::string& var) const override {
            using ExpressionMath::sqr, ExpressionMath::cbrt;
            auto x = args["x"];
            return (1.0 / 3) / sqr(cbrt(x)) * x->derivative(var);
        }
    } cbrt;

    // @Function rad
    const struct __rad__: public Function::ValueFunction {
        __rad__(): ValueFunction("rad", nullptr) {}
        double value(double x) const override { return x * M_PI / 180; }
    } rad;

    // @Function deg
    const struct __deg__: public Function::ValueFunction {
        __deg__(): ValueFunction("deg", nullptr) {}
        double value(double x) const override { return x * M_PI / 180; }
    } deg;

    // @Function hypot
    const struct __hypot__: public Function::AbstractFunction {
        __hypot__(): AbstractFunction("hypot", "(a...,)") {}
        expression eval(Function::Args& args) const override {
            auto a = args["a"];
            switch(a->size()){
                case 2:
                    return NumExpression::construct(gsl_hypot(a->get(0), a->get(1)));
                case 3:
                    return NumExpression::construct(gsl_hypot3(a->get(0), a->get(1), a->get(2)));
                default: {
                    double sum = 0;
                    for (auto e : *a){
                        sum += gsl_pow_2(e->value());
                    }
                    return NumExpression::construct(std::sqrt(sum));
                }
            }
        }
    } hypot;

    // @Function ldexp
    const struct __ldexp__: public Function::AbstractFunction {
        __ldexp__(): AbstractFunction("ldexp", "(x, e)") {}
        expression eval(Function::Args& args) const override {
            double x = args["x"]->value();
            double e = args["e"]->value();
            if (std::trunc(e) == e){
                return NumExpression::construct(gsl_ldexp(x, (int) e));
            }
            throw Exception("ldexp expected an integer for 'e'. Got: ", e);
        }
    } ldexp;

    // @Function fcmp
    const struct __fcmp__: public Function::AbstractFunction {
        __fcmp__(): AbstractFunction("fcmp", "(x, y, tol=1e-8)") {}
        expression eval(Function::Args& args) const override {
            return NumExpression::construct(gsl_fcmp(
                args["x"]->value(),
                args["y"]->value(),
                args["tol"]->value()
            ));
        }
    } fcmp;

    // @Function gcd
    const struct __gcd__: public Function::AbstractFunction {
        __gcd__(): AbstractFunction("gcd", "(a...,)") {}
        expression eval(Function::Args& args) const override {
            auto a = args["a"];
            long long g = 0;
            for (auto e : *a){
                double v = e->value();
                if (std::trunc(v) == v){
                    g = g == 0 ? v : std::gcd(g, (long long) v);
                }
                else{
                    throw Exception("gcd expected integer arguments. Got: ", args);
                }
            }
            return NumExpression::construct(g);
        }
    } gcd;

    // @Function lcm
    const struct __lcm__: public Function::AbstractFunction {
        __lcm__(): AbstractFunction("lcm", "(a...,)") {}
        expression eval(Function::Args& args) const override {
            auto a = args["a"];
            long long l = 0;
            for (auto e : *a){
                double v = e->value();
                if (std::trunc(v) == v){
                    l = l == 0 ? v : std::lcm(l, (long long) v);
                }
                else{
                    throw Exception("lcm expected integer arguments. Got: ", args);
                }
            }
            return NumExpression::construct(l);
        }
    } lcm;
}
