#pragma once

#include <cmath>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../Expressions/Expression.h"
#include "../Expressions/ExpressionFunctions.h"
#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/TupleExpression.h"
#include "../Utils/Argparse.h"
#include "AbstractFunction.h"

namespace Functions {
    // @Function neg
    const struct: public ValueFunction {
        expression evaluate(expression arg) override {
            if (arg->isComplex()){
                return NumExpression::construct(gsl_complex_negative(arg->complex()));
            }
            return NumExpression::construct(-arg->value());
        }
        expression derivative(expression e, const std::string& var) override {
            return NumExpression::construct(-1);
        }
    } neg ("neg", [](double x) -> double { return -x; });

    // @Function frexp
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 1){
                double x = args[0]->value();
                int e;
                double f = gsl_frexp(x, &e);
                return TupleExpression::construct({f, (double) e});
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: frexp. Expected 1. Got ", args.size()));
        }
    } frexp ("frexp");

    // @Function num
    const struct: public NamedFunction {
        expression evaluate(expression arg) override {
            return NumExpression::construct(arg->value(vars));
        }
        double value(double x) override { return x; }
    } num ("num");

    // @Function hex
    const struct: public NamedFunction {
        expression evaluate(expression arg) override {
            if (!arg->isComplex()){
                double val = arg->value(vars);
                if (std::trunc(val) == val){
                    return HexExpression::construct((unsigned long long) std::trunc(val));
                }
            }
            return InvalidExpression::construct(Exception("Unable to convert value to hex: ", arg));
        }
    } hex ("hex");

    // @Function bin
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 1){
                if (!args[0]->isComplex()){
                    double val = args[0]->value();
                    if (std::trunc(val) == val){
                        return BinExpression::construct((unsigned long long) std::trunc(val));
                    }
                }
            }
            return InvalidExpression::construct(Exception("Unable to convert value to bin: ", e));
        }
    } bin ("bin");

    // @Function abs
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return e / abs(e);
        }
    } abs ("abs", std::abs);

    // @Function sqr
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 2 * e;
        }
    } sqr ("sqr", gsl_pow_2);

    // @Function sqrt
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 0.5 / sqrt(arg);
        }
    } sqrt ("sqrt", std::sqrt);

    // @Function cb
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return 3 * sqr(arg);
        }
    } cb ("cb", gsl_pow_3);

    // @Function cbrt
    const struct: public ValueFunction {
        expression derivative(expression e, const std::string& var) override {
            return (1.0 / 3) / sqr(cbrt(arg));
        }
    } cbrt ("cbrt", std::cbrt);

    // @Function rad
    const ValueFunction rad ("rad", [](double x) -> double { return x * M_PI / 180; });

    // @Function deg
    const ValueFunction deg ("deg", [](double x) -> double { return x * 180 / M_PI; });

    // @Function hypot
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            switch(args.size()){
                case 2:
                    return gsl_hypot(
                        args[0]->value(),
                        args[1]->value()
                    );
                case 3:
                    return gsl_hypot(
                        args[0]->value(),
                        args[1]->value(),
                        args[2]->value()
                    );
                default: {
                    double sum = 0;
                    for (auto arg : args){
                        sum += gsl_pow_2(arg->value());
                    }
                    return sqrt(sum);
                }
            }
            return InvalidExpression::construct(Exception("Unable to compute: hypot"));
        }
    } hypot ("hypot");

    // @Function ldexp
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 2){
                double x = args[0]->value();
                double e = args[1]->value();
                if (std::trunc(e) == e){
                    return gsl_ldexp(x, (int) e);
                }
            }
            return InvalidExpression::construct(Exception("Unable to compute: ldexp"));
        }
    } ldexp ("ldexp");

    // @Function fcmp
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            switch(args.size()){
                case 2:
                    return gsl_fcmp(args[0]->value(), args[1]->value(), 1e-8) == 0;
                case 3:
                    return gsl_fcmp(args[0]->value(), args[1]->value(), args[2]->value()) == 0;
                default:
                    break;
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: fcmp. Expected (2, 3). Got ", args.size()));
        }
    } fcmp ("fcmp");

    // @Function gcd
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() >= 1){
                long long g = 0;
                for (auto arg : args){
                    double e = arg->value();
                    if (std::trunc(e) == e){
                        g = g == 0 ? e : std::gcd(g, (long long) e);
                    }
                    else{
                        return InvalidExpression::construct(Exception("gcd expected integer arguments. Got ", arg));
                    }
                }
                return NumExpression::construct(g);
            }
            return InvalidExpression::construct(Exception("Unable to compute: gcd"));
        }
    } gcd ("gcd");

    // @Function lcm
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() >= 1){
                long long l = 0;
                for (auto arg : args){
                    double e = arg->value();
                    if (std::trunc(e) == e){
                        l = l == 0 ? e : std::lcm(l, (long long) e);
                    }
                    else{
                        return InvalidExpression::construct(Exception("lcm expected integer arguments. Got ", arg));
                    }
                }
                return NumExpression::construct(l);
            }
            return InvalidExpression::construct(Exception("Unable to compute: lcm"));
        }
    } lcm ("lcm");
}
