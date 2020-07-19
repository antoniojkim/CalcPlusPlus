#include <cmath>

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {
    // @Function gamma
    MAKE_VALUEFUNCTION_EXPRESSION(gamma, gsl_sf_gamma)

    // @Function lngamma
    MAKE_VALUEFUNCTION_EXPRESSION(lngamma, gsl_sf_lngamma)

    // @Function gammastar
    MAKE_VALUEFUNCTION_EXPRESSION(gammastar, gsl_sf_gammastar)

    // @Function gammainv(x)
    MAKE_VALUEFUNCTION_EXPRESSION(gammainv, gsl_sf_gammainv)

    // @Function fact
    struct fact: public ValueFunctionExpression {
        fact(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            if (x > GSL_SF_FACT_NMAX){
                return GSL_POSINF;
            }
            if (x < 0 || (std::trunc(x) != x)) {
                return gsl_sf_gamma(x + 1);
            }
            return gsl_sf_fact((unsigned int) x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(fact);

    // @Function dfact
    struct dfact: public ValueFunctionExpression {
        dfact(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            if (x > GSL_SF_DOUBLEFACT_NMAX){
                return GSL_POSINF;
            }
            if (x >= 0 && std::trunc(x) == x) {
                return gsl_sf_doublefact((unsigned int) x);
            }
            return GSL_NAN;
        }
    };
    MAKE_FUNCTION_EXPRESSION(dfact);

    // @Function lnfact
    struct lnfact: public ValueFunctionExpression {
        lnfact(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            if (x >= 0 && std::trunc(x) == x) {
                return gsl_sf_lnfact((unsigned int) x);
            }
            return GSL_NAN;
        }
    };
    MAKE_FUNCTION_EXPRESSION(lnfact);

    // @Function lndfact
    struct lndfact: public ValueFunctionExpression {
        lndfact(int functionIndex, expression arg): ValueFunctionExpression(functionIndex, nullptr, arg) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(1)->value(vars);
            if (x >= 0 && std::trunc(x) == x) {
                return gsl_sf_lndoublefact((unsigned int) x);
            }
            return GSL_NAN;
        }
    };
    MAKE_FUNCTION_EXPRESSION(lndfact);

    // @Function choose: comb C
    struct choose: public FunctionExpression {
        choose(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (n, r)
            {"n", Empty}, {"r", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double n = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return gsl_sf_choose((unsigned int) n, (unsigned int) r);
            }
            throw Exception("nCr expects integers n >= r. Got: ", arg);
        }
        std::ostream& print(std::ostream& out, const bool pretty) {
            auto n = arg->at(1);
            auto r = arg->at(2);
            return out << "C("; n->print(out, pretty) << ", "; r->print(out, pretty) << ")";
        }
    };
    MAKE_FUNCTION_EXPRESSION(choose);

    // @Function lnchoose: lncomb
    struct lnchoose: public FunctionExpression {
        lnchoose(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (n, r)
            {"n", Empty}, {"r", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double n = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return gsl_sf_lnchoose((unsigned int) n, (unsigned int) r);
            }
            throw Exception("lnchoose expects integers n >= r. Got: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(lnchoose);

    // @Function permute: perm P
    struct permute: public FunctionExpression {
        permute(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (n, r)
            {"n", Empty}, {"r", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double n = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return gsl_sf_choose((unsigned int) n, (unsigned int) r) * gsl_sf_fact((unsigned int) r);
            }
            throw Exception("nPr expects integers n >= r. Got: ", arg);
        }
        std::ostream& print(std::ostream& out, const bool pretty) {
            auto n = arg->at(1);
            auto r = arg->at(2);
            return out << "P("; n->print(out, pretty) << ", "; r->print(out, pretty) << ")";
        }
    };
    MAKE_FUNCTION_EXPRESSION(permute);

    // @Function lnpermute: lnperm
    struct lnpermute: public FunctionExpression {
        lnpermute(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (n, r)
            {"n", Empty}, {"r", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double n = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return gsl_sf_lnchoose((unsigned int) n, (unsigned int) r) + gsl_sf_lnfact((unsigned int) r);
            }
            throw Exception("lnpermute expects integers n >= r. Got: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(lnpermute);

    // @Function taylorcoeff
    struct taylorcoeff: public FunctionExpression {
        taylorcoeff(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (n, x)
            {"n", Empty}, {"x", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double n = arg->at(1)->value(vars);
            double x = arg->at(2)->value(vars);
            if (x >= 0 && n >= 0 && std::trunc(n) == n){
                return gsl_sf_taylorcoeff((int) n, x);
            }
            throw Exception("taylorcoeff expects an integer n and double x. Got ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(taylorcoeff);

    // @Function poch
    struct poch: public FunctionExpression {
        poch(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, x)
            {"a", Empty}, {"x", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(1)->value(vars);
            double x = arg->at(2)->value(vars);
            return gsl_sf_poch(a, x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(poch);

    // @Function lnpoch
    struct lnpoch: public FunctionExpression {
        lnpoch(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, x)
            {"a", Empty}, {"x", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(1)->value(vars);
            double x = arg->at(2)->value(vars);
            return gsl_sf_lnpoch(a, x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(lnpoch);

    // @Function pochrel
    struct pochrel: public FunctionExpression {
        pochrel(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, x)
            {"a", Empty}, {"x", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(1)->value(vars);
            double x = arg->at(2)->value(vars);
            return gsl_sf_pochrel(a, x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(pochrel);

    // @Function gamma_inc: gammainc
    struct gamma_inc: public FunctionExpression {
        gamma_inc(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, x)
            {"a", Empty}, {"x", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(1)->value(vars);
            double x = arg->at(2)->value(vars);
            return gsl_sf_gamma_inc(a, x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(gamma_inc);

    // @Function gamma_inc_Q: gammaincq
    struct gamma_inc_Q: public FunctionExpression {
        gamma_inc_Q(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, x)
            {"a", Empty}, {"x", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(1)->value(vars);
            double x = arg->at(2)->value(vars);
            return gsl_sf_gamma_inc_Q(a, x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(gamma_inc_Q);

    // @Function gamma_inc_P: gammaincp
    struct gamma_inc_P: public FunctionExpression {
        gamma_inc_P(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, x)
            {"a", Empty}, {"x", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(1)->value(vars);
            double x = arg->at(2)->value(vars);
            return gsl_sf_gamma_inc_P(a, x);
        }
    };
    MAKE_FUNCTION_EXPRESSION(gamma_inc_P);

    // @Function Beta(a, b)
    struct Beta: public FunctionExpression {
        Beta(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, b)
            {"a", Empty}, {"b", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(1)->value(vars);
            double b = arg->at(2)->value(vars);
            if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                return gsl_sf_beta(a, b);
            }
            throw Exception("Beta function expected positive integers a and b. Got ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(Beta);

    // @Function lnBeta(a, b)
    struct lnBeta: public FunctionExpression {
        lnBeta(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, b)
            {"a", Empty}, {"b", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(1)->value(vars);
            double b = arg->at(2)->value(vars);
            if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                return gsl_sf_lnbeta(a, b);
            }
            throw Exception("lnBeta function expected positive integers a and b. Got ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(lnBeta);

    // @Function Betainc(a, b, x)
    struct Betainc: public FunctionExpression {
        Betainc(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, b)
            {"a", Empty}, {"b", Empty}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            double a = arg->at(1)->value(vars);
            double b = arg->at(2)->value(vars);
            double x = arg->at(3)->value(vars);
            if (x >= 0 && x <= 1){
                return gsl_sf_beta_inc(a, b, x);
            }
            throw Exception("Betainc expected doubles a, b, and x between 0 and 1. Got ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(Betainc);
}
