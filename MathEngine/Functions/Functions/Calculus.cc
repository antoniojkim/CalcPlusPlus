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
            // Signature: (f, x, var="x")
            {"f", Empty}, {"x", Empty}, {"var", VariableExpression::construct("x")}
        }) {}
        expression eval(const Variables& vars) override {
            return NumExpression::construct(value(vars));
        }
        double value(const Variables& vars = emptyVars) const override {
            auto f = arg->at(0);
            double x = arg->at(1)->value(vars);
            auto var = arg->at(2)->eval(vars);

            if (var != VAR){
                throw Exception("deriv expected var to be a variable. Got: ", var);
            }
            std::string varStr = var->repr();

            try{
                auto derivative = f->derivative(varStr);
                Variables _vars = vars;
                _vars[varStr] = NumExpression::construct(x);
                return derivative->value(_vars);
            } catch(const Exception& e){}

            gsl_function F = f->function(varStr);

            double result, abserr;
            gsl_set_error_handler_off();
            int status = gsl_deriv_central(&F, x, 1e-8, &result, &abserr);

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
            // Signature: (f, var="x")
            {"f", Empty}, {"var", VariableExpression::construct("x")}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            auto f = arg->at(0);
            auto var = arg->at(1);

            if (var != VAR){
                throw Exception("diff expected second argument to be a variable. Got: ", var);
            }

            return f->derivative(var->repr());
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(diff)

    // @Function integral
    struct integral: public FunctionExpression {
        integral(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (f, a, b, var="x")
            {"f", Empty}, {"a", Empty}, {"b", Empty}, {"var", VariableExpression::construct("x")}
        }) {}
        expression eval(const Variables& vars) override {
            return NumExpression::construct(value(vars));
        }
        double value(const Variables& vars = emptyVars) const override {
            using Scanner::NONE, Scanner::VAR;
            auto f = arg->at(0);
            double a = arg->at(1)->value(vars);
            double b = arg->at(2)->value(vars);
            auto var = arg->at(3);

            if (var != VAR){
                throw Exception("integral expected second argument to be a variable. Got: ", a, ". var = ", var);
            }

            gsl_function F = f->function(var->repr());

            double result, abserr;
            gsl_set_error_handler_off();
            gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
            int status = gsl_integration_qags(&F, a, b, 1e-8, 1e-8, 1000, w, &result, &abserr);
            gsl_integration_workspace_free (w);

            if (status != GSL_FAILURE){
                return result;
            }
            throw Exception("Error encountered when computing numerical integral. Args: ", arg);
        }
    };
    MAKE_FUNCTION_EXPRESSION(integral)

}
