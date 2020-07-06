#include <cmath>

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {
    // @Function gamma(x)
    namespace gamma {
        double (*value)(double) = gsl_sf_gamma;
    }

    // @Function lngamma(x)
    namespace lngamma {
        double (*value)(double) = gsl_sf_lngamma;
    }

    // @Function gammastar(x)
    namespace gammastar {
        double (*value)(double) = gsl_sf_gammastar;
    }

    // @Function gammainv(x)
    namespace gammainv {
        double (*value)(double) = gsl_sf_gammainv;
    }

    // @Function fact(x)
    namespace fact {
        double value(double x) {
            if (x > GSL_SF_FACT_NMAX){
                return GSL_POSINF;
            }
            if (x < 0 || (std::trunc(x) != x)) {
                return gsl_sf_gamma(x + 1);
            }
            return gsl_sf_fact((unsigned int) x);
        }
    }

    // @Function dfact(x)
    namespace dfact {
        double value(double x) {
            if (x > GSL_SF_DOUBLEFACT_NMAX){
                return GSL_POSINF;
            }
            if (x >= 0 && std::trunc(x) == x) {
                return gsl_sf_doublefact((unsigned int) x);
            }
            return GSL_NAN;
        }
    }

    // @Function lnfact(x)
    namespace lnfact {
        double value(double x) {
            if (x >= 0 && std::trunc(x) == x) {
                return gsl_sf_lnfact((unsigned int) x);
            }
            return GSL_NAN;
        }
    }

    // @Function lndfact(x)
    namespace lndfact {
        double value(double x) {
            if (x >= 0 && std::trunc(x) == x) {
                return gsl_sf_lndoublefact((unsigned int) x);
            }
            return GSL_NAN;
        }
    }

    // @Function choose(x): comb(n, r)
    namespace choose {
        expression eval(Function::Args& args) {
            double n = args.nextValue();
            double r = args.nextValue();
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return NumExpression::construct(gsl_sf_choose((unsigned int) n, (unsigned int) r));
            }
            throw Exception("nCr expects integers n >= r. Got: ", args);
        }
        std::ostream& print(std::ostream& out, Function::Args& args, const bool pretty) {
            auto n = args.next();
            auto r = args.next();
            return out << "(" << n << ")C(" << r << ")";
        }
    }

    // @Function lnchoose(n, r): lncomb
    namespace lnchoose {
        expression eval(Function::Args& args) {
            double n = args.nextValue();
            double r = args.nextValue();
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return NumExpression::construct(gsl_sf_lnchoose((unsigned int) n, (unsigned int) r));
            }
            throw Exception("lnchoose expects integers n >= r. Got: ", args);
        }
    }

    // @Function permute(n, r): perm
    namespace permute {
        expression eval(Function::Args& args) {
            double n = args.nextValue();
            double r = args.nextValue();
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return NumExpression::construct(gsl_sf_choose((unsigned int) n, (unsigned int) r) * gsl_sf_fact((unsigned int) r));
            }
            throw Exception("nPr expects integers n >= r. Got: ", args);
        }
        std::ostream& print(std::ostream& out, Function::Args& args, const bool pretty) {
            auto n = args.next();
            auto r = args.next();
            return out << "(" << n << ")P(" << r << ")";
        }
    }

    // @Function lnpermute(n, r): lnperm
    namespace lnpermute {
        expression eval(Function::Args& args) {
            double n = args.nextValue();
            double r = args.nextValue();
            if (r >= 0 && n >= r && std::trunc(n) == n && std::trunc(r) == r){
                return NumExpression::construct(gsl_sf_lnchoose((unsigned int) n, (unsigned int) r) + gsl_sf_lnfact((unsigned int) r));
            }
            throw Exception("lnpermute expects integers n >= r. Got: ", args);
        }
    }

    // @Function taylorcoeff(n, x)
    namespace taylorcoeff {
        expression eval(Function::Args& args) {
            double n = args.nextValue();
            double x = args.nextValue();
            if (x >= 0 && n >= 0 && std::trunc(n) == n){
                return NumExpression::construct(gsl_sf_taylorcoeff((int) n, x));
            }
            throw Exception("taylorcoeff expects an integer n and double x. Got ", args);
        }
    }

    // @Function poch(a, x)
    namespace poch {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double x = args.nextValue();
            return NumExpression::construct(gsl_sf_poch(a, x));
        }
    }

    // @Function lnpoch(a, x)
    namespace lnpoch {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double x = args.nextValue();
            return NumExpression::construct(gsl_sf_lnpoch(a, x));
        }
    }

    // @Function pochrel(a, x)
    namespace pochrel {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double x = args.nextValue();
            return NumExpression::construct(gsl_sf_pochrel(a, x));
        }
    }

    // @Function gamma_inc(a, x): gammainc
    namespace gamma_inc {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double x = args.nextValue();
            return NumExpression::construct(gsl_sf_gamma_inc(a, x));
        }
    }

    // @Function gamma_inc_Q(a, x): gammaincq
    namespace gamma_inc_Q {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double x = args.nextValue();
            return NumExpression::construct(gsl_sf_gamma_inc_Q(a, x));
        }
    }

    // @Function gamma_inc_P(a, x): gammaincp
    namespace gamma_inc_P {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double x = args.nextValue();
            return NumExpression::construct(gsl_sf_gamma_inc_P(a, x));
        }
    }

    // @Function Beta(a, b)
    namespace Beta {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double b = args.nextValue();
            if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                return NumExpression::construct(gsl_sf_beta(a, b));
            }
            throw Exception("Beta function expected positive integers a and b. Got ", args);
        }
    }

    // @Function lnBeta(a, b)
    namespace lnBeta {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double b = args.nextValue();
            if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                return NumExpression::construct(gsl_sf_lnbeta(a, b));
            }
            throw Exception("lnBeta function expected positive integers a and b. Got ", args);
        }
    }

    // @Function Betainc(a, b, x)
    namespace Betainc {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double b = args.nextValue();
            double x = args.nextValue();
            if (x >= 0 && x <= 1){
                return NumExpression::construct(gsl_sf_beta_inc(a, b, x));
            }
            throw Exception("Betainc expected doubles a, b, and x between 0 and 1. Got ", args);
        }
    }
}
