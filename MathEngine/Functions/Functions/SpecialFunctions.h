#pragma once

#include <cmath>

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../Expressions/Expression.h"
#include "../Expressions/InvalidExpression.h"
#include "../Utils/Argparse.h"
#include "../AbstractFunction.h"

namespace Function {
    // @Function gamma
    const Function::ValueFunction __gamma__ ("gamma", gsl_sf_gamma);

    // @Function lngamma
    const Function::ValueFunction __lngamma__ ("lngamma", gsl_sf_lngamma);

    // @Function gammastar
    const Function::ValueFunction __gammastar__ ("gammastar", gsl_sf_gammastar);

    // @Function gammainv
    const Function::ValueFunction __gammainv__ ("gammainv", gsl_sf_gammainv);

    // @Function fact
    const Function::ValueFunction __fact__ ("fact", [](double x) -> double {
        if (x > GSL_SF_FACT_NMAX){
            return GSL_POSINF;
        }
        if (x < 0 || (std::trunc(x) != x)) {
            return gsl_sf_gamma(x + 1);
        }
        return gsl_sf_fact((unsigned int) x);
    });

    // @Function dfact
    const Function::ValueFunction __dfact__ ("dfact", [](double x) -> double {
        if (x > GSL_SF_DOUBLEFACT_NMAX){
            return GSL_POSINF;
        }
        if (x >= 0 && std::trunc(x) == x) {
            return gsl_sf_doublefact((unsigned int) x);
        }
        return GSL_NAN;
    });

    // @Function lnfact
    const Function::ValueFunction __lnfact__ ("lnfact", [](double x) -> double {
        if (x >= 0 && std::trunc(x) == x) {
            return gsl_sf_lnfact((unsigned int) x);
        }
        return GSL_NAN;
    });

    // @Function lndfact
    const Function::ValueFunction __lndfact__ ("lndfact", [](double x) -> double {
        if (x >= 0 && std::trunc(x) == x) {
            return gsl_sf_lndoublefact((unsigned int) x);
        }
        return GSL_NAN;
    });

    // @Function choose comb
    const struct choose: public Function::NamedFunction {
        choose(): NamedFunction("choose") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double n = args[0]->value();
                double m = args[1]->value();
                if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
                    return NumExpression::construct(gsl_sf_choose((unsigned int) n, (unsigned int) m));
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for choose. Expected 2. Got ", args.size()));
        }
        virtual std::ostream& print(std::ostream& out, expression e){
            Function::Args args(e);
            if (args.size() == 2){
                return out << "(" << args[0] << ")C(" << args[1] << ")";
            }
            return out << "Invalid Number of Arguments for choose. Expected 2. Got " << args.size();
        }
    } __choose__;

    // @Function lnchoose lncomb
    const struct lnchoose: public Function::NamedFunction {
        lnchoose(): NamedFunction("lnchoose") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double n = args[0]->value();
                double m = args[1]->value();
                if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
                    return NumExpression::construct(gsl_sf_lnchoose((unsigned int) n, (unsigned int) m));
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for lnchoose. Expected 2. Got ", args.size()));
        }
    } __lnchoose__;

    // @Function permute perm
    const struct permute: public Function::NamedFunction {
        permute(): NamedFunction("permute") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double n = args[0]->value();
                double m = args[1]->value();
                if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
                    return NumExpression::construct(gsl_sf_choose((unsigned int) n, (unsigned int) m) * gsl_sf_fact((unsigned int) m));
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for permute. Expected 2. Got ", args.size()));
        }
        virtual std::ostream& print(std::ostream& out, expression e){
            Function::Args args(e);
            if (args.size() == 2){
                return out << "(" << args[0] << ")P(" << args[1] << ")";
            }
            return out << "Invalid Number of Arguments for permute. Expected 2. Got " << args.size();
        }
    } __permute__;

    // @Function lnpermute lnperm
    const struct lnpermute: public Function::NamedFunction {
        lnpermute(): NamedFunction("lnpermute") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double n = args[0]->value();
                double m = args[1]->value();
                if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
                    return NumExpression::construct(gsl_sf_lnchoose((unsigned int) n, (unsigned int) m) + gsl_sf_lnfact((unsigned int) m));
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for lnpermute. Expected 2. Got ", args.size()));
        }
    } __lnpermute__;

    // @Function taylorcoeff
    const struct taylorcoeff: public Function::NamedFunction {
        taylorcoeff(): NamedFunction("taylorcoeff") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double n = args[0]->value();
                double x = args[1]->value();
                if (x >= 0 && n >= 0 && std::trunc(n) == n){
                    return NumExpression::construct(gsl_sf_taylorcoeff((int) n, x));
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for taylorcoeff. Expected 2. Got ", args.size()));
        }
    } __taylorcoeff__;

    // @Function poch
    const struct poch: public Function::NamedFunction {
        poch(): NamedFunction("poch") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return NumExpression::construct(gsl_sf_poch(a, x));
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for poch. Expected 2. Got ", args.size()));
        }
    } __poch__;

    // @Function lnpoch
    const struct lnpoch: public Function::NamedFunction {
        lnpoch(): NamedFunction("lnpoch") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return NumExpression::construct(gsl_sf_lnpoch(a, x));
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for lnpoch. Expected 2. Got ", args.size()));
        }
    } __lnpoch__;

    // @Function pochrel
    const struct pochrel: public Function::NamedFunction {
        pochrel(): NamedFunction("pochrel") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return NumExpression::construct(gsl_sf_pochrel(a, x));
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for pochrel. Expected 2. Got ", args.size()));
        }
    } __pochrel__;

    // @Function gamma_inc gammainc
    const struct gamma_inc: public Function::NamedFunction {
        gamma_inc(): NamedFunction("gamma_inc") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return NumExpression::construct(gsl_sf_gamma_inc(a, x));
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for gamma_inc. Expected 2. Got ", args.size()));
        }
    } __gamma_inc__;

    // @Function gamma_inc_Q gammaincq
    const struct gamma_inc_Q: public Function::NamedFunction {
        gamma_inc_Q(): NamedFunction("gamma_inc_Q") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return NumExpression::construct(gsl_sf_gamma_inc_Q(a, x));
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for gamma_inc_Q. Expected 2. Got ", args.size()));
        }
    } __gamma_inc_Q__;

    // @Function gamma_inc_P gammaincp
    const struct gamma_inc_P: public Function::NamedFunction {
        gamma_inc_P(): NamedFunction("gamma_inc_P") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return NumExpression::construct(gsl_sf_gamma_inc_P(a, x));
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for gammaincp. Expected 2. Got ", args.size()));
        }
    } __gamma_inc_P__;

    // @Function Beta
    const struct Beta: public Function::NamedFunction {
        Beta(): NamedFunction("Beta") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double a = args[0]->value();
                double b = args[1]->value();
                if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                    return NumExpression::construct(gsl_sf_beta(a, b));
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for Beta. Expected 2. Got ", args.size()));
        }
    } __Beta__;

    // @Function lnBeta
    const struct lnBeta: public Function::NamedFunction {
        lnBeta(): NamedFunction("lnBeta") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                double a = args[0]->value();
                double b = args[1]->value();
                if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                    return NumExpression::construct(gsl_sf_lnbeta(a, b));
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for lnBeta. Expected 2. Got ", args.size()));
        }
    } __lnBeta__;

    // @Function Betainc
    const struct Betainc: public Function::NamedFunction {
        Betainc(): NamedFunction("Betainc") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 3){
                double a = args[0]->value();
                double b = args[1]->value();
                double x = args[2]->value();
                if (x >= 0 && x <= 1){
                    return NumExpression::construct(gsl_sf_beta_inc(a, b, x));
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for Betainc. Expected 3. Got ", args.size()));
        }
    } __Betainc__;
}
