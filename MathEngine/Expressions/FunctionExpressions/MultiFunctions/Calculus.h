#pragma once

#include <list>
#include <cmath>
#include <gsl/gsl_deriv.h>

#include "../../../Utils/exceptions.h"
#include "../../Expression.h"
#include "../FunctionDirectory.h"

using namespace std;

double f_deriv(list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto arg = args.begin();
        gsl_function F = (*(arg++))->function();
        double x = (*arg)->value();

        double result, abserr;
        gsl_deriv_central(&F, x, 1e-8, &result, &abserr);
        
        return result;
    }
    throw Exception("Invalid Number of Arguments for f_deriv");
}
