#pragma once

#include <cmath>
#include <list>
#include <string>

#include <gsl/gsl_deriv.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#include "../Expressions/VariableExpression.h"
#include "AbstractFunction.h"

namespace Function {
    // @Function deriv
    const struct deriv: public Function::NamedFunction {
        deriv(): NamedFunction("deriv") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 2){
                std::string var = "x";
                expression val = args[1];
                if (val->variable()){
                    var = val->variable()->getName();
                    val = val->variable()->getVar();
                    if (!val){
                        return InvalidExpression::construct(Exception("deriv expected value. Got: ", args[1]));
                    }
                }

                auto derivative = args[0]->derivative(var);
                if (!derivative->invalid()){
                    Variables vars;
                    vars[var] = val;
                    return derivative->evaluate(vars);
                }

                gsl_function F = args[0]->function(var);
                double x = val->value();

                double result, abserr;
                gsl_set_error_handler_off();
                int status = gsl_deriv_central(&F, x, 1e-8, &result, &abserr);

                if (status != GSL_FAILURE){
                    return NumExpression::construct(result);
                }
            }
            return InvalidExpression::construct(Exception("Invalid Number of Arguments: deriv. Expected 2. Args: ", args));
        }
    } __deriv__;

    // @Function diff
    const struct diff: public Function::NamedFunction {
        diff(): NamedFunction("diff") {}
        expression evaluate(Function::Args& args) override {
            std::string var = "x";
            switch(args.size()){
                case 2: {
                    if (args[1]->variable()){
                        var = args[1]->variable()->getName();
                    }
                    else{
                        return InvalidExpression::construct(Exception("diff expected variable. Got: ", args[1]));
                    }
                }
                case 1:
                    return args[0]->derivative(var);
                default:
                    return InvalidExpression::construct(Exception("Invalid number of arguments for differentiation(f, var=x). Got: ", args));
            }
        }
    } __diff__;

    // @Function integral
    const struct integral: public Function::NamedFunction {
        integral(): NamedFunction("integral") {}
        expression evaluate(Function::Args& args) override {
            std::string var = "x";
            switch (args.size()){
                case 4: {
                    if (args[3]->variable()){
                        var = args[3]->variable()->getName();
                    }
                    else{
                        return InvalidExpression::construct(Exception("integral expected variable. Got: ", args[3]));
                    }
                }
                case 3: {
                    gsl_function F = args[0]->function(var);
                    double a = args[1]->value();
                    double b = args[2]->value();

                    double result, abserr;

                    gsl_set_error_handler_off();
                    gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
                    int status = gsl_integration_qags(&F, a, b, 1e-8, 1e-8, 1000, w, &result, &abserr);
                    gsl_integration_workspace_free (w);

                    if (status != GSL_FAILURE){
                        return NumExpression::construct(result);
                    }
                    return InvalidExpression::construct(Exception("Unable to compute integral. Args: ", args));
                }
                default:
                    return InvalidExpression::construct(Exception("Invalid Number of Arguments: integral. Expected 3. Got ", args.size()));
            }
        }
    } __integral__;

}
