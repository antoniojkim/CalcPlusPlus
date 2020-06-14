#pragma once

#include <list>
#include <cmath>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#include "../Expressions/Expression.h"
#include "../Utils/Argparse.h"
#include "../Utils/exceptions.h"
#include "AbstractFunction.h"

namespace Functions {
    // @Function deriv
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 2){
                auto derivative = args[0]->derivative("x");
                if (!derivative->invalid()){
                    Variables xvars;
                    xvars["x"] = args[1]->evaluate(vars);
                    return derivative->value(xvars);
                }

                gsl_function F = args[0]->function();
                double x = args[1]->value(vars);

                double result, abserr;
                gsl_set_error_handler_off();
                int status = gsl_deriv_central(&F, x, 1e-8, &result, &abserr);

                if (status != GSL_FAILURE){
                    return NumExpression::construct(result);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: deriv. Expected 2. Got ", args.size()));
        }
    } deriv ("deriv");

    // @Function diff
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            switch(args.size()){
                case 1:
                    return tuple->front()->derivative("x");
                case 2: {
                    auto var = tuple->back()->variable()->getName();
                    return tuple->front()->derivative(var);
                }
                default:
                    return InvalidExpression::construct(Exception("Invalid number of arguments for differentiation"));
            }
        }
    } diff ("diff");

    // @Function integral
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 3){
                gsl_function F = args[0]->function();
                double a = args[1]->value(vars);
                double b = args[2]->value(vars);

                double result, abserr;

                gsl_set_error_handler_off();
                gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
                int status = gsl_integration_qags(&F, a, b, 1e-8, 1e-8, 1000, w, &result, &abserr);
                gsl_integration_workspace_free (w);

                if (status != GSL_FAILURE){
                    return NumExpression::construct(result);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: integral. Expected 3. Got ", args.size()));
        }
    } integral ("integral");

}
