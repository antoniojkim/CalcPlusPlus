#pragma once

#include <cmath>
#include <list>
#include <string>

#include <gsl/gsl_deriv.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#include "../../Expressions/VariableExpression.h"
#include "../../Scanner/scanner.h"
#include "../AbstractFunction.h"

namespace Function {
    // @Function deriv
    const struct __deriv__: public Function::AbstractFunction {
        __deriv__(): AbstractFunction("deriv", "(f, x, x1=None)") {}
        expression eval(Function::Args& args) const override {
            using Scanner::NONE, Scanner::VAR;
            auto f = args["f"];
            auto x = args["x"];
            auto x1 = args["x1"];

            std::string var = "x";
            if (x1 != NONE){
                if (x != VAR){
                    throw Exception("deriv expected second argument to be a variable. Got: ", x);
                }
                var = x->repr();
                x = x1;
            }

            try{
                auto derivative = f->derivative(var);
                Variables vars;
                vars[var] = x;
                return derivative->eval(vars);
            } catch(const Exception& e){}


            gsl_function F = f->function(var);

            double result, abserr;
            gsl_set_error_handler_off();
            int status = gsl_deriv_central(&F, x->value(), 1e-8, &result, &abserr);

            if (status != GSL_FAILURE){
                return NumExpression::construct(result);
            }
            throw Exception("Error encountered when computing numerical derivative. Args: ", args);
        }
    } deriv;

    // @Function diff
    const struct __diff__: public Function::AbstractFunction {
        __diff__(): AbstractFunction("diff", "(f, x=None)") {}
        expression eval(Function::Args& args) const override {
            using Scanner::NONE, Scanner::VAR;
            auto f = args["f"];
            auto x = args["x"];

            std::string var = "x";
            if (x != NONE){
                if (x != VAR){
                    throw Exception("diff expected second argument to be a variable. Got: ", x);
                }
                var = x->repr();
            }
            return f->derivative(var);
        }
    } diff;

    // @Function integral
    const struct __integral__: public Function::AbstractFunction {
        __integral__(): AbstractFunction("integral", "(f, a, b, x=None)") {}
        expression eval(Function::Args& args) const override {
            using Scanner::NONE, Scanner::VAR;
            auto f = args["f"];
            auto a = args["a"];
            auto b = args["b"];
            auto x = args["x"];

            std::string var = "x";
            if (x != NONE){
                if (a != VAR){
                    throw Exception("diff expected second argument to be a variable. Got: ", a);
                }
                var = a->repr();
                a = b;
                b = x;
            }

            gsl_function F = f->function(var);

            double result, abserr;
            gsl_set_error_handler_off();
            gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
            int status = gsl_integration_qags(&F, a->value(), b->value(), 1e-8, 1e-8, 1000, w, &result, &abserr);
            gsl_integration_workspace_free (w);

            if (status != GSL_FAILURE){
                return NumExpression::construct(result);
            }
            throw Exception("Error encountered when computing numerical integral. Args: ", args);
        }
    } integral;

}
