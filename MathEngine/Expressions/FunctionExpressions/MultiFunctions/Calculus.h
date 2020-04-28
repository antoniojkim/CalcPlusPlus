#pragma once

#include <list>
#include <cmath>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#include "../../../Utils/exceptions.h"
#include "../../Expression.h"
#include "../FunctionDirectory.h"

double f_deriv(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 2){
        auto derivative = args.front()->derivative("x");
        if (!derivative->invalid()){
            Variables xvars;
            xvars["x"] = args.back()->evaluate(vars);
            return derivative->value(xvars);
        }

        auto arg = args.begin();
        gsl_function F = (*(arg++))->function();
        double x = (*arg)->value(vars);

        double result, abserr;
        gsl_set_error_handler_off();
        int status = gsl_deriv_central(&F, x, 1e-8, &result, &abserr);

        if (status == GSL_FAILURE){
            return GSL_NAN;
        }

        return result;
    }
    throw Exception("Invalid Number of Arguments for f_deriv");
}

double f_integral(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 3){
        auto arg = args.begin();
        gsl_function F = (*(arg++))->function();
        double a = (*(arg++))->value(vars);
        double b = (*arg)->value(vars);

        double result, abserr;

        gsl_set_error_handler_off();
        gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
        int status = gsl_integration_qags(&F, a, b, 1e-8, 1e-8, 1000, w, &result, &abserr);
        gsl_integration_workspace_free (w);

        if (status == GSL_FAILURE){
            return GSL_NAN;
        }

        return result;
    }
    throw Exception("Invalid Number of Arguments for f_integral");
}
