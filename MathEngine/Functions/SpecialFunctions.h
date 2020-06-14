#pragma once

#include <cmath>

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../Expressions/Expression.h"
#include "../Expressions/InvalidExpression.h"
#include "../Utils/Argparse.h"
#include "AbstractFunction.h"

namespace Function {
    // @Function gamma
    const ValueFunction gamma ("gamma", gsl_sf_gamma);

    // @Function lngamma
    const ValueFunction lngamma ("lngamma", gsl_sf_lngamma);

    // @Function gammastar
    const ValueFunction gammastar ("gammastar", gsl_sf_gammastar);

    // @Function gammainv
    const ValueFunction gammainv ("gammainv", gsl_sf_gammainv);

    // @Function fact
    const ValueFunction fact ("fact", [](double x) -> double {
        if (x > GSL_SF_FACT_NMAX){
            return GSL_POSINF;
        }
        if (x < 0 || (std::trunc(x) != x)) {
            return gsl_sf_gamma(x + 1);
        }
        return gsl_sf_fact((unsigned int) x);
    });

    // @Function dfact
    const ValueFunction dfact ("dfact", [](double x) -> double {
        if (x > GSL_SF_DOUBLEFACT_NMAX){
            return GSL_POSINF;
        }
        if (x >= 0 && std::trunc(x) == x) {
            return gsl_sf_doublefact((unsigned int) x);
        }
        return GSL_NAN;
    });

    // @Function lnfact
    const ValueFunction lnfact ("lnfact", [](double x) -> double {
        if (x >= 0 && std::trunc(x) == x) {
            return gsl_sf_lnfact((unsigned int) x);
        }
        return GSL_NAN;
    });

    // @Function lndfact
    const ValueFunction lndfact ("lndfact", [](double x) -> double {
        if (x >= 0 && std::trunc(x) == x) {
            return gsl_sf_lndoublefact((unsigned int) x);
        }
        return GSL_NAN;
    });

    // @Function choose comb
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double n = args[0]->value();
                double m = args[1]->value();
                if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
                    return gsl_sf_choose((unsigned int) n, (unsigned int) m);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for choose. Expected 2. Got ", args->size()));
        }
        virtual std::ostream& print(std::ostream& out, expression e){
            ParsedArgs args(e);
            if (args->size() == 2){
                return out << args[0] << "C" << args[1];
            }
            return out << "Invalid Number of Arguments for choose. Expected 2. Got " << args->size();
        }
    } choose ("choose");

    // @Function lnchoose lncomb
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double n = args[0]->value();
                double m = args[1]->value();
                if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
                    return gsl_sf_lnchoose((unsigned int) n, (unsigned int) m);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for lnchoose. Expected 2. Got ", args->size()));
        }
    } lnchoose ("lnchoose");

    // @Function permute perm
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double n = args[0]->value();
                double m = args[1]->value();
                if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
                    return gsl_sf_choose((unsigned int) n, (unsigned int) m) * gsl_sf_fact((unsigned int) m);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for permute. Expected 2. Got ", args->size()));
        }
        virtual std::ostream& print(std::ostream& out, expression e){
            ParsedArgs args(e);
            if (args->size() == 2){
                return out << args[0] << "P" << args[1];
            }
            return out << "Invalid Number of Arguments for permute. Expected 2. Got " << args->size();
        }
    } permute ("permute");

    // @Function lnpermute lnperm
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double n = args[0]->value();
                double m = args[1]->value();
                if (m >= 0 && n >= m && std::trunc(n) == n && std::trunc(m) == m){
                    return gsl_sf_lnchoose((unsigned int) n, (unsigned int) m) + gsl_sf_lnfact((unsigned int) m);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for lnpermute. Expected 2. Got ", args->size()));
        }
    } lnpermute ("lnpermute");

    // @Function taylorcoeff
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double n = args[0]->value();
                double x = args[1]->value();
                if (x >= 0 && n >= 0 && std::trunc(n) == n){
                    return gsl_sf_taylorcoeff((int) n, x);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for taylorcoeff. Expected 2. Got ", args->size()));
        }
    } taylorcoeff ("taylorcoeff");

    // @Function poch
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return gsl_sf_poch(a, x);
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for poch. Expected 2. Got ", args->size()));
        }
    } poch ("poch");

    // @Function lnpoch
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return gsl_sf_lnpoch(a, x);
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for lnpoch. Expected 2. Got ", args->size()));
        }
    } lnpoch ("lnpoch");

    // @Function pochrel
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return gsl_sf_pochrel(a, x);
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for pochrel. Expected 2. Got ", args->size()));
        }
    } pochrel ("pochrel");

    // @Function gammainc gamma_inc
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return gsl_sf_gamma_inc(a, x);
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for gammainc. Expected 2. Got ", args->size()));
        }
    } gammainc ("gammainc");

    // @Function gammaincq gamma_inc_Q
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return gsl_sf_gamma_inc_Q(a, x);
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for gammaincq. Expected 2. Got ", args->size()));
        }
    } gammaincq ("gammaincq");

    // @Function gammaincp gamma_inc_P
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double a = args[0]->value();
                double x = args[1]->value();
                return gsl_sf_gamma_inc_P(a, x);
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for gammaincp. Expected 2. Got ", args->size()));
        }
    } gammaincp ("gammaincp");

    // @Function Beta
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double a = args[0]->value();
                double b = args[1]->value();
                if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                    return gsl_sf_beta(a, b);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for Beta. Expected 2. Got ", args->size()));
        }
    } Beta ("Beta");

    // @Function lnBeta
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 2){
                double a = args[0]->value();
                double b = args[1]->value();
                if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
                    return gsl_sf_lnbeta(a, b);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for lnBeta. Expected 2. Got ", args->size()));
        }
    } lnBeta ("lnBeta");

    // @Function Betainc
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args->size() == 3){
                double a = args[0]->value();
                double b = args[1]->value();
                double x = args[2]->value();
                if (x >= 0 && x <= 1){
                    return gsl_sf_beta_inc(a, b, x);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments for Betainc. Expected 3. Got ", args->size()));
        }
    } Betainc ("Betainc");
}
