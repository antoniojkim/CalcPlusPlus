#pragma once

#include <cmath>

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/InvalidExpression.h"
#include "../AbstractFunction.h"

namespace Function {
    // @Function gamma
    const Function::ValueFunction gamma ("gamma", gsl_sf_gamma);

    // @Function lngamma
    const Function::ValueFunction lngamma ("lngamma", gsl_sf_lngamma);

    // @Function gammastar
    const Function::ValueFunction gammastar ("gammastar", gsl_sf_gammastar);

    // @Function gammainv
    const Function::ValueFunction gammainv ("gammainv", gsl_sf_gammainv);

    // @Function fact
    const Function::ValueFunction fact ("fact", [](double x) -> double {
        if (x > GSL_SF_FACT_NMAX){
            return GSL_POSINF;
        }
        if (x < 0 || (std::trunc(x) != x)) {
            return gsl_sf_gamma(x + 1);
        }
        return gsl_sf_fact((unsigned int) x);
    });

    // @Function dfact
    const Function::ValueFunction dfact ("dfact", [](double x) -> double {
        if (x > GSL_SF_DOUBLEFACT_NMAX){
            return GSL_POSINF;
        }
        if (x >= 0 && std::trunc(x) == x) {
            return gsl_sf_doublefact((unsigned int) x);
        }
        return GSL_NAN;
    });

    // @Function lnfact
    const Function::ValueFunction lnfact ("lnfact", [](double x) -> double {
        if (x >= 0 && std::trunc(x) == x) {
            return gsl_sf_lnfact((unsigned int) x);
        }
        return GSL_NAN;
    });

    // @Function lndfact
    const Function::ValueFunction lndfact ("lndfact", [](double x) -> double {
        if (x >= 0 && std::trunc(x) == x) {
            return gsl_sf_lndoublefact((unsigned int) x);
        }
        return GSL_NAN;
    });

    // @Function choose comb
    const struct __choose__: public Function::AbstractFunction {
        __choose__(): AbstractFunction("choose", "(n, r)") {}
        expression eval(Function::Args& args) const override {
            double n = args["n"]->value();
            double r = args["r"]->value();
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return NumExpression::construct(gsl_sf_choose((unsigned int) n, (unsigned int) r));
            }
            throw Exception("nCr expects integers n >= r. Got: ", args);
        }
        std::ostream& print(std::ostream& out, Function::Args& args) const override {
            return out << "(" << args["n"] << ")C(" << args["r"] << ")";
        }
    } choose;

    // @Function lnchoose lncomb
    const struct __lnchoose__: public Function::AbstractFunction {
        __lnchoose__(): AbstractFunction("lnchoose", "(n, r)") {}
        expression eval(Function::Args& args) const override {
            double n = args["n"]->value();
            double r = args["r"]->value();
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return NumExpression::construct(gsl_sf_lnchoose((unsigned int) n, (unsigned int) r));
            }
            throw Exception("lnchoose expects integers n >= r. Got: ", args);
        }
    } lnchoose;

    // @Function permute perm
    const struct __permute__: public Function::AbstractFunction {
        __permute__(): AbstractFunction("permute", "(n, r)") {}
        expression eval(Function::Args& args) const override {
            double n = args["n"]->value();
            double r = args["r"]->value();
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return NumExpression::construct(gsl_sf_choose((unsigned int) n, (unsigned int) r) * gsl_sf_fact((unsigned int) r));
            }
            throw Exception("nPr expects integers n >= r. Got: ", args);
        }
        std::ostream& print(std::ostream& out, Function::Args& args) const override {
            return out << "(" << args["n"] << ")P(" << args["r"] << ")";
        }
    } permute;

    // @Function lnpermute lnperm
    const struct __lnpermute__: public Function::AbstractFunction {
        __lnpermute__(): AbstractFunction("lnpermute", "(n, r)") {}
        expression eval(Function::Args& args) const override {
            double n = args["n"]->value();
            double r = args["r"]->value();
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return NumExpression::construct(gsl_sf_lnchoose((unsigned int) n, (unsigned int) r) + gsl_sf_lnfact((unsigned int) r));
            }
            throw Exception("lnpermute expects integers n >= r. Got: ", args);
        }
    } lnpermute;

    // @Function taylorcoeff
    const struct __taylorcoeff__: public Function::AbstractFunction {
        __taylorcoeff__(): AbstractFunction("taylorcoeff", "(n, x)") {}
        expression eval(Function::Args& args) const override {
            double n = args["n"]->value();
            double x = args["x"]->value();
            if (x >= 0 && n >= 0 && std::trunc(n) == n){
                return NumExpression::construct(gsl_sf_taylorcoeff((int) n, x));
            }
            throw Exception("taylorcoeff expects an integer n and double x. Got ", args);
        }
    } taylorcoeff;

    // @Function poch
    const struct __poch__: public Function::AbstractFunction {
        __poch__(): AbstractFunction("poch", "(a, x)") {}
        expression eval(Function::Args& args) const override {
            double a = args["a"]->value();
            double x = args["x"]->value();
            return NumExpression::construct(gsl_sf_poch(a, x));
        }
    } poch;

    // @Function lnpoch
    const struct __lnpoch__: public Function::AbstractFunction {
        __lnpoch__(): AbstractFunction("lnpoch", "(a, x)") {}
        expression eval(Function::Args& args) const override {
            double a = args["a"]->value();
            double x = args["x"]->value();
            return NumExpression::construct(gsl_sf_lnpoch(a, x));
        }
    } lnpoch;

    // @Function pochrel
    const struct __pochrel__: public Function::AbstractFunction {
        __pochrel__(): AbstractFunction("pochrel", "(a, x)") {}
        expression eval(Function::Args& args) const override {
            double a = args["a"]->value();
            double x = args["x"]->value();
            return NumExpression::construct(gsl_sf_pochrel(a, x));
        }
    } pochrel;

    // @Function gamma_inc gammainc
    const struct __gamma_inc__: public Function::AbstractFunction {
        __gamma_inc__(): AbstractFunction("gamma_inc", "(a, x)") {}
        expression eval(Function::Args& args) const override {
            double a = args["a"]->value();
            double x = args["x"]->value();
            return NumExpression::construct(gsl_sf_gamma_inc(a, x));
        }
    } gamma_inc;

    // @Function gamma_inc_Q gammaincq
    const struct __gamma_inc_Q__: public Function::AbstractFunction {
        __gamma_inc_Q__(): AbstractFunction("gamma_inc_Q", "(a, x)") {}
        expression eval(Function::Args& args) const override {
            double a = args["a"]->value();
            double x = args["x"]->value();
            return NumExpression::construct(gsl_sf_gamma_inc_Q(a, x));
        }
    } gamma_inc_Q;

    // @Function gamma_inc_P gammaincp
    const struct __gamma_inc_P__: public Function::AbstractFunction {
        __gamma_inc_P__(): AbstractFunction("gamma_inc_P", "(a, x)") {}
        expression eval(Function::Args& args) const override {
            double a = args["a"]->value();
            double x = args["x"]->value();
            return NumExpression::construct(gsl_sf_gamma_inc_P(a, x));
        }
    } gamma_inc_P;

    // @Function Beta
    const struct __Beta__: public Function::AbstractFunction {
        __Beta__(): AbstractFunction("Beta", "(a, b)") {}
        expression eval(Function::Args& args) const override {
            double a = args["a"]->value();
            double b = args["b"]->value();
            if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                return NumExpression::construct(gsl_sf_beta(a, b));
            }
            throw Exception("Beta function expected positive integers a and b. Got ", args.size());
        }
    } Beta;

    // @Function lnBeta
    const struct __lnBeta__: public Function::AbstractFunction {
        __lnBeta__(): AbstractFunction("lnBeta", "(a, b)") {}
        expression eval(Function::Args& args) const override {
            double a = args["a"]->value();
            double b = args["b"]->value();
            if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                return NumExpression::construct(gsl_sf_lnbeta(a, b));
            }
            throw Exception("lnBeta function expected positive integers a and b. Got ", args.size());
        }
    } lnBeta;

    // @Function Betainc
    const struct __Betainc__: public Function::AbstractFunction {
        __Betainc__(): AbstractFunction("Betainc", "(a, b, x)") {}
        expression eval(Function::Args& args) const override {
            double a = args["a"]->value();
            double b = args["b"]->value();
            double x = args["x"]->value();
            if (x >= 0 && x <= 1){
                return NumExpression::construct(gsl_sf_beta_inc(a, b, x));
            }
            throw Exception("Betainc expected doubles a, b, and x between 0 and 1. Got ", args.size());
        }
    } Betainc;
}
