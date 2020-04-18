#pragma once

#include <cmath>
#include <list>

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../../Expression.h"
#include "../FunctionDirectory.h"

double f_choose(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double n = (*(arg++))->value(vars);
        double m = (*arg)->value(vars);
        if (n >= 0 && m >= 0 && std::trunc(n) == n && std::trunc(m) == m){
            return gsl_sf_choose((unsigned int) n, (unsigned int) m);
        }
    }
    return GSL_NAN;
}
double f_lnchoose(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double n = (*(arg++))->value(vars);
        double m = (*arg)->value(vars);
        if (n >= 0 && m >= 0 && std::trunc(n) == n && std::trunc(m) == m){
            return gsl_sf_lnchoose((unsigned int) n, (unsigned int) m);
        }
    }
    return GSL_NAN;
}
double f_permute(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double n = (*(arg++))->value(vars);
        double m = (*arg)->value(vars);
        if (n >= 0 && m >= 0 && std::trunc(n) == n && std::trunc(m) == m){
            return gsl_sf_choose((unsigned int) n, (unsigned int) m) * gsl_sf_fact((unsigned int) m);
        }
    }
    return GSL_NAN;
}
double f_lnpermute(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double n = (*(arg++))->value(vars);
        double m = (*arg)->value(vars);
        if (n >= 0 && m >= 0 && std::trunc(n) == n && std::trunc(m) == m){
            return gsl_sf_lnchoose((unsigned int) n, (unsigned int) m) + gsl_sf_lnfact((unsigned int) m);
        }
    }
    return GSL_NAN;
}
double f_taylorcoeff(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double n = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        if (x >= 0 && n >= 0 && std::trunc(n) == n){
            return gsl_sf_taylorcoeff((int) n, x);
        }
    }
    return GSL_NAN;
}
double f_poch(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_poch(a, x);
    }
    return GSL_NAN;
}
double f_lnpoch(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_lnpoch(a, x);
    }
    return GSL_NAN;
}
double f_pochrel(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_pochrel(a, x);
    }
    return GSL_NAN;
}
double f_gammainc(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_gamma_inc(a, x);
    }
    return GSL_NAN;
}
double f_gammaincq(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_gamma_inc_Q(a, x);
    }
    return GSL_NAN;
}
double f_gammaincp(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double a = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        return gsl_sf_gamma_inc_P(a, x);
    }
    return GSL_NAN;
}
double f_beta(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double a = (*(arg++))->value(vars);
        double b = (*arg)->value(vars);
        if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
            return gsl_sf_beta(a, b);
        }
    }
    return GSL_NAN;
}
double f_lnbeta(std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double a = (*(arg++))->value(vars);
        double b = (*arg)->value(vars);
        if ((a > 0 || std::trunc(a) != a) && (b > 0 || std::trunc(b) != b)){
            return gsl_sf_lnbeta(a, b);
        }
    }
    return GSL_NAN;
}
double f_betainc(std::list<expression>& args, const Variables& vars){
    if (args.size() == 3){
        auto arg = args.begin();
        double a = (*(arg++))->value(vars);
        double b = (*(arg++))->value(vars);
        double x = (*arg)->value(vars);
        if (x >= 0 && x <= 1){
            return gsl_sf_beta_inc(a, b, x);
        }
    }
    return GSL_NAN;
}
