#pragma once

#include <list>
#include <cmath>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_integration.h>

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

double f_integral(list<expression>& args, const Variables& vars){
    if (args.size() == 3){
        auto arg = args.begin();
        gsl_function F = (*(arg++))->function();
        double a = (*(arg++))->value();
        double b = (*arg)->value();

        double result, abserr;

        gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
        gsl_integration_qags(&F, a, b, 1e-8, 1e-8, 1000, w, &result, &abserr);
        gsl_integration_workspace_free (w);
        
        return result;
    }
    throw Exception("Invalid Number of Arguments for f_integral");
}
