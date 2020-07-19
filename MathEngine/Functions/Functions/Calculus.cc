#include <cmath>
#include <iostream>
#include <string>

#include <gsl/gsl_deriv.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/FunctionExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/VariableExpression.h"
#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

using namespace std;
using namespace Scanner;

namespace Function {
    // @Function deriv
    struct deriv: public FunctionExpression {
        deriv(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (f, x, var=None)
            {"f", Empty}, {"x", Empty}, {"var", None}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            auto f = arg->at(1)->eval(vars);
            auto x = arg->at(2)->eval(vars);
            auto var = arg->at(3)->eval(vars);

            std::string varStr = "x";
            if (var != NONE){
                if (var != VAR){
                    throw Exception("deriv expected var to be a variable. Got: ", var);
                }
                varStr = var->repr();
            }

            try{
                auto derivative = f->derivative(varStr);
                Variables vars;
                vars[varStr] = x;
                return derivative->value(vars);
            } catch(const Exception& e){}

            gsl_function F = f->function(varStr);

            double result, abserr;
            gsl_set_error_handler_off();
            int status = gsl_deriv_central(&F, x->value(), 1e-8, &result, &abserr);

            if (status != GSL_FAILURE){
                return result;
            }
            throw Exception("Error encountered when computing numerical derivative. Args: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(deriv)

    // @Function diff
    struct diff: public FunctionExpression {
        diff(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (f, var=None)
            {"f", Empty}, {"var", None}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            auto f = arg->at(1);
            auto x = arg->at(2);

            std::string var = "x";
            if (x != NONE){
                if (x != VAR){
                    throw Exception("diff expected second argument to be a variable. Got: ", x);
                }
                var = x->repr();
            }
            return f->derivative(var);
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(diff)

    // @Function integral
    struct integral: public FunctionExpression {
        integral(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (f, a, b, var=None)
            {"f", Empty}, {"a", Empty}, {"b", Empty}, {"var", None}
        }) {}
        double value(const Variables& vars = emptyVars) const override {
            using Scanner::NONE, Scanner::VAR;
            auto f = arg->at(1);
            auto a = arg->at(2);
            auto b = arg->at(3);
            auto var = arg->at(4);

            std::string varStr = "x";
            if (var != NONE){
                if (var != VAR){
                    throw Exception("integral expected second argument to be a variable. Got: ", a, ". x = ", x);
                }
                varStr = var->repr();
            }

            gsl_function F = f->function(varStr);

            double result, abserr;
            gsl_set_error_handler_off();
            gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
            int status = gsl_integration_qags(&F, a->value(), b->value(), 1e-8, 1e-8, 1000, w, &result, &abserr);
            gsl_integration_workspace_free (w);

            if (status != GSL_FAILURE){
                return result;
            }
            throw Exception("Error encountered when computing numerical integral. Args: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(integral)

}
