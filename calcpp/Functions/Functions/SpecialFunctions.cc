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

namespace calcpp {

    namespace fexpr {

        // @Function gamma
        struct gamma: public ValueFunctionExpression {
            gamma() : ValueFunctionExpression("gamma", gsl_sf_gamma) {}
        };

        // @Function lngamma
        struct lngamma: public ValueFunctionExpression {
            lngamma() : ValueFunctionExpression("lngamma", gsl_sf_lngamma) {}
        };

        // @Function gammastar
        struct gammastar: public ValueFunctionExpression {
            gammastar() : ValueFunctionExpression("gammastar", gsl_sf_gammastar) {}
        };

        // @Function gammainv(x)
        struct gammainv: public ValueFunctionExpression {
            gammainv() : ValueFunctionExpression("gammainv", gsl_sf_gammainv) {}
        };

        // @Function fact
        struct fact: public FunctionExpression {
            fact() : FunctionExpression("fact", {arg("x")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                if (x > GSL_SF_FACT_NMAX) { return num(GSL_POSINF); }
                if (x < 0 || !IS_INT(x)) { return num(gsl_sf_gamma(x + 1)); }
                return num(gsl_sf_fact((unsigned int) x));
            }
        };

        // @Function dfact
        struct dfact: public ValueFunctionExpression {
            dfact() : FunctionExpression("dfact", {arg("x")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                if (x > GSL_SF_DOUBLEFACT_NMAX) { return num(GSL_POSINF); }
                if (x >= 0 && IS_INT(x)) {
                    return num(gsl_sf_doublefact((unsigned int) x));
                }
                return num(GSL_NAN);
            }
        };

        // @Function lnfact
        struct lnfact: public ValueFunctionExpression {
            lnfact() : FunctionExpression("lnfact", {arg("x")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                if (x >= 0 && IS_INT(x)) {
                    return num(gsl_sf_lnfact((unsigned int) x));
                }
                return num(GSL_NAN);
            }
        };

        // @Function lndfact
        struct lndfact: public ValueFunctionExpression {
            lndfact() : FunctionExpression("lndfact", {arg("x")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                if (x >= 0 && IS_INT(x)) {
                    return num(gsl_sf_lndoublefact((unsigned int) x));
                }
                return num(GSL_NAN);
            }
        };

        // @Function choose: comb C
        struct choose: public FunctionExpression {
            choose() : FunctionExpression("choose", {arg("n"), arg("r")}) {}
            expression call(expression args) const override {
                double n = (double) args->get(0);
                double r = (double) args->get(1);
                if (r >= 0 && n >= r && IS_INT(n) && IS_INT(r)) {
                    return num(gsl_sf_choose((unsigned int) n, (unsigned int) r));
                }
                THROW_ERROR("nCr expects integers n >= r. Got: n=" << n << ", r=" << r);
            }
            std::ostream& print(std::ostream& out) override { return out << "C"; }
        };

        // @Function lnchoose: lncomb
        struct lnchoose: public FunctionExpression {
            lnchoose() : FunctionExpression("lnchoose", {arg("n"), arg("r")}) {}
            expression call(expression args) const override {
                double n = (double) args->get(0);
                double r = (double) args->get(1);
                if (r >= 0 && n >= r && IS_INT(n) && IS_INT(r)) {
                    return num(gsl_sf_lnchoose((unsigned int) n, (unsigned int) r));
                }
                THROW_ERROR(
                    "lnchoose expects integers n >= r. Got: n=" << n << ", r=" << r);
            }
        };

        // @Function permute: perm P
        struct permute: public FunctionExpression {
            permute() : FunctionExpression("permute", {arg("n"), arg("r")}) {}
            expression call(expression args) const override {
                double n = (double) args->get(0);
                double r = (double) args->get(1);
                if (r >= 0 && n >= r && IS_INT(n) && IS_INT(r)) {
                    return num(
                        gsl_sf_choose((unsigned int) n, (unsigned int) r) *
                        gsl_sf_fact((unsigned int) r));
                }
                THROW_ERROR("nPr expects integers n >= r. Got: n=" << n << ", r=" << r);
            }
            std::ostream& print(std::ostream& out, const bool pretty) {
                return out << "P";
            }
        };

        // @Function lnpermute: lnperm
        struct lnpermute: public FunctionExpression {
            lnpermute() : FunctionExpression("lnpermute", {arg("n"), arg("r")}) {}
            expression call(expression args) const override {
                double n = (double) args->get(0);
                double r = (double) args->get(1);
                if (r >= 0 && n >= r && IS_INT(n) && IS_INT(r)) {
                    return num(
                        gsl_sf_lnchoose((unsigned int) n, (unsigned int) r) +
                        gsl_sf_lnfact((unsigned int) r));
                }
                THROW_ERROR(
                    "lnpermute expects integers n >= r. Got: " << n << ", r=" << r);
            }
        };

        // @Function taylorcoeff
        struct taylorcoeff: public FunctionExpression {
            taylorcoeff() : FunctionExpression("taylorcoeff", {arg("n"), arg("x")}) {}
            expression call(expression args) const override {
                double n = (double) args->get(0);
                double x = (double) args->get(1);
                if (x >= 0 && n >= 0 && IS_INT(n)) {
                    return num(gsl_sf_taylorcoeff((int) n, x));
                }
                THROW_ERROR(
                    "taylorcoeff expects an integer n and double x. Got "
                    << n << ", x=" << x);
            }
        };

        // @Function poch
        struct poch: public FunctionExpression {
            poch() : FunctionExpression("poch", {arg("a"), arg("x")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double x = (double) args->get(1);
                return num(gsl_sf_poch(a, x));
            }
        };

        // @Function lnpoch
        struct lnpoch: public FunctionExpression {
            lnpoch() : FunctionExpression("lnpoch", {arg("a"), arg("x")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double x = (double) args->get(1);
                return num(gsl_sf_lnpoch(a, x));
            }
        };

        // @Function pochrel
        struct pochrel: public FunctionExpression {
            pochrel() : FunctionExpression("pochrel", {arg("a"), arg("x")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double x = (double) args->get(1);
                return num(gsl_sf_pochrel(a, x));
            }
        };

        // @Function gamma_inc: gammainc
        struct gamma_inc: public FunctionExpression {
            gamma_inc() : FunctionExpression("gamma_inc", {arg("a"), arg("x")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double x = (double) args->get(1);
                return num(gsl_sf_gamma_inc(a, x));
            }
        };
        MAKE_FUNCTION_EXPRESSION(gamma_inc)

        // @Function gamma_inc_Q: gammaincq
        struct gamma_inc_Q: public FunctionExpression {
            gamma_inc_Q() : FunctionExpression("gamma_inc_Q", {arg("a"), arg("x")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double x = (double) args->get(1);
                return num(gsl_sf_gamma_inc_Q(a, x));
            }
        };

        // @Function gamma_inc_P: gammaincp
        struct gamma_inc_P: public FunctionExpression {
            gamma_inc_P() : FunctionExpression("gamma_inc_P", {arg("a"), arg("x")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double x = (double) args->get(1);
                return num(gsl_sf_gamma_inc_P(a, x));
            }
        };

        // @Function Beta(a, b)
        struct Beta: public FunctionExpression {
            Beta() : FunctionExpression("Beta", {arg("a"), arg("b")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double b = (double) args->get(1);
                if ((a > 0 || !IS_INT(a)) && (b > 0 || !IS_INT(b))) {
                    return num(gsl_sf_beta(a, b));
                }
                THROW_ERROR(
                    "Beta function expected positive integers a and b. Got a="
                    << a << ", b=" << b);
            }
        };

        // @Function lnBeta(a, b)
        struct lnBeta: public FunctionExpression {
            lnBeta() : FunctionExpression("lnBeta", {arg("a"), arg("b")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double b = (double) args->get(1);
                if ((a > 0 || !IS_INT(a)) && (b > 0 || !IS_INT(b))) {
                    return num(gsl_sf_lnbeta(a, b));
                }
                THROW_ERROR(
                    "lnBeta function expected positive integers a and b. Got "
                    << a << ", b=" << b);
            }
        };

        // @Function Betainc(a, b, x)
        struct Betainc: public FunctionExpression {
            Betainc() : FunctionExpression("Betainc", {arg("a"), arg("b"), arg("x")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double b = (double) args->get(1);
                double x = (double) args->get(2);
                if (x >= 0 && x <= 1) { return num(gsl_sf_beta_inc(a, b, x)); }
                THROW_ERROR(
                    "Betainc expected doubles a, b, and x between 0 and 1. Got "
                    << a << ", b=" << b << ", x=" << x);
            }
        };

    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression Beta = std::shared_ptr<fexpr::Beta>(new fexpr::Beta());
        const expression Betainc = std::shared_ptr<fexpr::Betainc>(new fexpr::Betainc());
        const expression choose = std::shared_ptr<fexpr::choose>(new fexpr::choose());
        const expression dfact = std::shared_ptr<fexpr::dfact>(new fexpr::dfact());
        const expression fact = std::shared_ptr<fexpr::fact>(new fexpr::fact());
        const expression gamma = std::shared_ptr<fexpr::gamma>(new fexpr::gamma());
        const expression gamma_inc = std::shared_ptr<fexpr::gamma_inc>(new fexpr::gamma_inc());
        const expression gamma_inc_P = std::shared_ptr<fexpr::gamma_inc_P>(new fexpr::gamma_inc_P());
        const expression gamma_inc_Q = std::shared_ptr<fexpr::gamma_inc_Q>(new fexpr::gamma_inc_Q());
        const expression gammainv = std::shared_ptr<fexpr::gammainv>(new fexpr::gammainv());
        const expression gammastar = std::shared_ptr<fexpr::gammastar>(new fexpr::gammastar());
        const expression lnBeta = std::shared_ptr<fexpr::lnBeta>(new fexpr::lnBeta());
        const expression lnchoose = std::shared_ptr<fexpr::lnchoose>(new fexpr::lnchoose());
        const expression lndfact = std::shared_ptr<fexpr::lndfact>(new fexpr::lndfact());
        const expression lnfact = std::shared_ptr<fexpr::lnfact>(new fexpr::lnfact());
        const expression lngamma = std::shared_ptr<fexpr::lngamma>(new fexpr::lngamma());
        const expression lnpermute = std::shared_ptr<fexpr::lnpermute>(new fexpr::lnpermute());
        const expression lnpoch = std::shared_ptr<fexpr::lnpoch>(new fexpr::lnpoch());
        const expression permute = std::shared_ptr<fexpr::permute>(new fexpr::permute());
        const expression poch = std::shared_ptr<fexpr::poch>(new fexpr::poch());
        const expression pochrel = std::shared_ptr<fexpr::pochrel>(new fexpr::pochrel());
        const expression taylorcoeff = std::shared_ptr<fexpr::taylorcoeff>(new fexpr::taylorcoeff());
        // end sourcegen
    }  // namespace functions

}  // namespace calcpp
