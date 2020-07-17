#include <cmath>
#include <iostream>
#include <string>

#include <gsl/gsl_deriv.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/VariableExpression.h"
#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

using namespace std;

namespace Function {
    // @Function deriv(f, x, x1=None)
    namespace deriv {
        expression eval(Function::Args& args) {
            using Scanner::NONE, Scanner::VAR;
            auto f = args.next();
            auto x = args.next();
            auto x1 = args.next();

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
                cout << "Derivative: " << derivative << endl;
                Variables vars;
                vars[var] = x;
                return derivative->eval(vars);
            } catch(const Exception& e){
                cout << "Could not differentiate: " << e.what() << endl;
            }

            gsl_function F = f->function(var);

            double result, abserr;
            gsl_set_error_handler_off();
            int status = gsl_deriv_central(&F, x->value(), 1e-8, &result, &abserr);

            if (status != GSL_FAILURE){
                return NumExpression::construct(result);
            }
            throw Exception("Error encountered when computing numerical derivative. Args: ", args);
        }
    }

    // @Function diff(f, x=None)
    namespace diff {
        expression eval(Function::Args& args) {
            using Scanner::NONE, Scanner::VAR;
            auto f = args.next();
            auto x = args.next();

            std::string var = "x";
            if (x != NONE){
                if (x != VAR){
                    throw Exception("diff expected second argument to be a variable. Got: ", args);
                }
                var = x->repr();
            }
            return f->derivative(var);
        }
    }

    // @Function integral(f, a, b, x=None)
    namespace integral {
        expression eval(Function::Args& args) {
            using Scanner::NONE, Scanner::VAR;
            auto f = args.next();
            auto a = args.next();
            auto b = args.next();
            auto x = args.next();

            std::string var = "x";
            if (x != NONE){
                if (a != VAR){
                    throw Exception("integral expected second argument to be a variable. Got: ", a, ". x = ", x);
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
    }

}
