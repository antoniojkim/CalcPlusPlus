#pragma once

#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../Expressions/ExpressionFunctions.h"
#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/TupleExpression.h"
#include "AbstractFunction.h"

namespace Function {
    // @Function neg
    const struct neg: public Function::ValueFunction {
        neg(): ValueFunction("neg", [](double x) -> double { return -x; }) {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 1){
                if (args[0]->isComplex()){
                    return NumExpression::construct(gsl_complex_negative(args[0]->complex()));
                }
                return NumExpression::construct(-args[0]->value());
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: neg(x). Args: ", args));
        }
        expression derivative(expression e, const std::string& var) override {
            return NumExpression::construct(-1);
        }
    } __neg__;

    // @Function frexp
    const struct frexp: public Function::NamedFunction {
        frexp(): NamedFunction("frexp") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 1){
                double x = args[0]->value();
                int e;
                double f = gsl_frexp(x, &e);
                return TupleExpression::construct({f, (double) e});
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: frexp(x, e). Args: ", args));
        }
    } __frexp__;

    // @Function num
    const struct num: public Function::NamedFunction {
        num(): NamedFunction("num") {}
        expression evaluate(Function::Args& args) override {
            return NumExpression::construct(args[0]->value());
        }
        double value(double x) override { return x; }
    } __num__;

    // @Function hex
    const struct hex: public Function::NamedFunction {
        hex(): NamedFunction("hex") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 1){
                if (!args[0]->isComplex()){
                    double val = args[0]->value();
                    if (std::trunc(val) == val){
                        return HexExpression::construct((unsigned long long) std::trunc(val));
                    }
                }
            }
            return InvalidExpression::construct(Exception("Unable to compute: hex(x). Args: ", args));
        }
    } __hex__;

    // @Function bin
    const struct bin: public Function::NamedFunction {
        bin(): NamedFunction("bin") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 1){
                if (!args[0]->isComplex()){
                    double val = args[0]->value();
                    if (std::trunc(val) == val){
                        return BinExpression::construct((unsigned long long) std::trunc(val));
                    }
                }
            }
            return InvalidExpression::construct(Exception("Unable to compute: bin(x). Args: ", args));
        }
    } __bin__;

    // @Function abs
    const struct abs: public Function::ValueFunction {
        abs(): ValueFunction("abs", std::abs) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::abs;
            return e / abs(e);
        }
    } __abs__;

    // @Function sqr
    const struct sqr: public Function::ValueFunction {
        sqr(): ValueFunction("sqr", gsl_pow_2) {}
        expression derivative(expression e, const std::string& var) override {
            return 2 * e;
        }
    } __sqr__;

    // @Function sqrt
    const struct sqrt: public Function::ValueFunction {
        sqrt(): ValueFunction("sqrt", std::sqrt) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sqrt;
            return 0.5 / sqrt(e);
        }
    } __sqrt__;

    // @Function cb
    const struct cb: public Function::ValueFunction {
        cb(): ValueFunction("cb", gsl_pow_3) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sqr;
            return 3 * sqr(e);
        }
    } __cb__;

    // @Function cbrt
    const struct cbrt: public Function::ValueFunction {
        cbrt(): ValueFunction("cbrt", std::cbrt) {}
        expression derivative(expression e, const std::string& var) override {
            using ExpressionMath::sqr, ExpressionMath::cbrt;
            return (1.0 / 3) / sqr(cbrt(e));
        }
    } __cbrt__;

    // @Function rad
    const Function::ValueFunction __rad__ ("rad", [](double x) -> double { return x * M_PI / 180; });

    // @Function deg
    const Function::ValueFunction __deg__ ("deg", [](double x) -> double { return x * 180 / M_PI; });

    // @Function hypot
    const struct hypot: public Function::NamedFunction {
        hypot(): NamedFunction("hypot") {}
        expression evaluate(Function::Args& args) override {
            switch(args.size()){
                case 2:
                    return NumExpression::construct(gsl_hypot(
                        args[0]->value(),
                        args[1]->value()
                    ));
                case 3:
                    return NumExpression::construct(gsl_hypot3(
                        args[0]->value(),
                        args[1]->value(),
                        args[2]->value()
                    ));
                default: {
                    double sum = 0;
                    for (auto e : args){
                        sum += gsl_pow_2(e->value());
                    }
                    return NumExpression::construct(std::sqrt(sum));
                }
            }
            return InvalidExpression::construct(Exception("Unable to compute: hypot(a_1,...,a_n). Args: ", args));
        }
    } __hypot__;

    // @Function ldexp
    const struct ldexp: public Function::NamedFunction {
        ldexp(): NamedFunction("ldexp") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double x = args[0]->value();
                double e = args[1]->value();
                if (std::trunc(e) == e){
                    return NumExpression::construct(gsl_ldexp(x, (int) e));
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: ldexp(x, e). Args: ", args));
        }
    } __ldexp__;

    // @Function fcmp
    const struct fcmp: public Function::NamedFunction {
        fcmp(): NamedFunction("fcmp") {}
        expression evaluate(Function::Args& args) override {
            switch(args.size()){
                case 2:
                    return NumExpression::construct(gsl_fcmp(args[0]->value(), args[1]->value(), 1e-8));
                case 3:
                    return NumExpression::construct(gsl_fcmp(args[0]->value(), args[1]->value(), args[2]->value()));
                default:
                    break;
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: fcmp(x, y, err=1e-8). Args: ", args.size()));
        }
    } __fcmp__;

    // @Function gcd
    const struct gcd: public Function::NamedFunction {
        gcd(): NamedFunction("gcd") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() >= 1){
                long long g = 0;
                for (auto arg : args){
                    double a = arg->value();
                    if (std::trunc(a) == a){
                        g = g == 0 ? a : std::gcd(g, (long long) a);
                    }
                    else{
                        return InvalidExpression::construct(Exception("gcd expected integer arguments. Args: ", args));
                    }
                }
                return NumExpression::construct(g);
            }
            return InvalidExpression::construct(Exception("Unable to compute: gcd(a_1,...,a_n). Args: ", args));
        }
    } __gcd__;

    // @Function lcm
    const struct lcm: public Function::NamedFunction {
        lcm(): NamedFunction("lcm") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() >= 1){
                long long l = 0;
                for (auto arg : args){
                    double a = arg->value();
                    if (std::trunc(a) == a){
                        l = l == 0 ? a : std::lcm(l, (long long) a);
                    }
                    else{
                        return InvalidExpression::construct(Exception("lcm expected integer arguments. Args: ", args));
                    }
                }
                return NumExpression::construct(l);
            }
            return InvalidExpression::construct(Exception("Unable to compute: lcm(a_1,...,a_n). Args: ", args));
        }
    } __lcm__;
}
