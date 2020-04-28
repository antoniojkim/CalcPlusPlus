#pragma once

#include <list>
#include <cmath>
#include <gsl/gsl_math.h>

#include "../../../Utils/exceptions.h"
#include "../../Expression.h"
#include "../FunctionDirectory.h"

double f_hypot(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double x = (*(arg++))->value(vars);
        double y = (*arg)->value(vars);
        return gsl_hypot(x, y);
    }
    else if (args.size() == 3){
        auto arg = args.begin();
        double x = (*(arg++))->value(vars);
        double y = (*(arg++))->value(vars);
        double z = (*arg)->value(vars);
        return gsl_hypot3(x, y, z);
    }
    else if (args.size() > 0){
        double sum = 0;
        for (auto& arg : args){
            double x = arg->value(vars);
            sum += x*x;
        }
        return sqrt(sum);
    }
    throw Exception("Invalid Number of Arguments for f_hypot");
}

double f_ldexp(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        double x = (*(arg++))->value(vars);
        double e = (*arg)->value(vars);
        if (std::trunc(e) == e){
            return gsl_ldexp(x, (int) e);
        }
        return GSL_NAN;
    }
    throw Exception("Invalid Number of Arguments for f_ldexp");
}

double f_fcmp(const std::list<expression>& args, const Variables& vars){
    if (args.size() >= 2){
        auto arg = args.begin();
        double x = (*(arg++))->value(vars);
        double y = (*(arg++))->value(vars);
        double epsilon = 1e-8;
        if (args.size() >= 3){
            epsilon = (*arg)->value(vars);
        }
        return gsl_fcmp(x, y, epsilon) == 0;
    }
    return GSL_NAN;
}
