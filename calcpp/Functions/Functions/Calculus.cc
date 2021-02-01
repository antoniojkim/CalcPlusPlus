#include <cmath>
#include <iostream>
#include <string>

#include <gsl/gsl_deriv.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/FunctionExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

using namespace std;

namespace calcpp {
    namespace fexpr {
        // @Function deriv
        struct deriv: public FunctionExpression {
            deriv() :
                FunctionExpression("deriv", {arg("f"), arg("x"), kwarg("var", "x")}) {}
            expression call(expression args) const override {
                auto f = args->at(0);
                double x = (double) args->get(1);
                auto var = args->get(2);

                if (var != Type::VAR) {
                    throw Exception("deriv expected var to be a variable. Got: ", var);
                }

                try {
                    auto derivative = f->derivative(var);
                    Environment env;
                    env.set(var, x);
                    return derivative->value(env);
                } catch (const Exception& e) {}

                gsl_function F = f->function(var);

                double result, abserr;
                gsl_set_error_handler_off();
                int status = gsl_deriv_central(&F, x, 1e-8, &result, &abserr);

                if (status != GSL_FAILURE) { return num(result); }
                THROW_ERROR(
                    "Error encountered when computing numerical derivative. Args: "
                    << args);
            }
        };

        // @Function diff
        struct diff: public FunctionExpression {
            diff() : FunctionExpression("diff", {arg("f"), kwarg("var", "x")}) {}
            expression call(expression args) const override {
                auto f = args->at(0);
                auto var = args->at(1);

                if (var != Type::VAR) {
                    THROW_ERROR(
                        "diff expected second argument to be a variable. Got: " << var);
                }

                return f->derivative(var);
            }
        };

        // @Function integral
        struct integral: public FunctionExpression {
            integral() :
                FunctionExpression(
                    "integral", {arg("f"), arg("a"), arg("b"), kwarg("var", "x")}) {}
            expression call(expression args) const override {
                auto f = args->at(0);
                double a = (double) args->get(1);
                double b = (double) args->get(2);
                auto var = args->at(3);

                if (var != Type::VAR) {
                    THROW_ERROR(
                        "integral expected second argument to be a variable. Got: "
                        << a << ". var = " << var);
                }

                gsl_function F = f->function(var);

                double result, abserr;
                gsl_set_error_handler_off();
                gsl_integration_workspace* w = gsl_integration_workspace_alloc(1000);
                int status = 0;
                switch (gsl_isinf(a)) {
                    case 1: {
                        switch (gsl_isinf(b)) {
                            case 1:
                                result = 0;
                                break;
                            case -1:
                                status = gsl_integration_qagi(
                                    &F, 1e-8, 1e-8, 1000, w, &result, &abserr);
                                break;
                            default:
                                status = gsl_integration_qagiu(
                                    &F, b, 1e-8, 1e-8, 1000, w, &result, &abserr);
                                break;
                        }
                        result *= -1;
                        break;
                    }
                    case -1: {
                        switch (gsl_isinf(b)) {
                            case 1:
                                status = gsl_integration_qagi(
                                    &F, 1e-8, 1e-8, 1000, w, &result, &abserr);
                                break;
                            case -1:
                                result = 0;
                                break;
                            default:
                                status = gsl_integration_qagil(
                                    &F, b, 1e-8, 1e-8, 1000, w, &result, &abserr);
                                break;
                        }
                        break;
                    }
                    default: {
                        switch (gsl_isinf(b)) {
                            case 1:
                                status = gsl_integration_qagiu(
                                    &F, a, 1e-8, 1e-8, 1000, w, &result, &abserr);
                                break;
                            case -1:
                                status = gsl_integration_qagiu(
                                    &F, b, 1e-8, 1e-8, 1000, w, &result, &abserr);
                                result *= -1;
                                break;
                            default:
                                status = gsl_integration_qags(
                                    &F, a, b, 1e-8, 1e-8, 1000, w, &result, &abserr);
                                break;
                        }
                        break;
                    }
                }
                gsl_integration_workspace_free(w);

                if (status != GSL_FAILURE) { return num(result); }
                THROW_ERROR(
                    "Error encountered when computing numerical integral. Args: "
                    << arg);
            }
        };
    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression deriv = std::shared_ptr<fexpr::deriv>(new fexpr::deriv());
        const expression diff = std::shared_ptr<fexpr::diff>(new fexpr::diff());
        const expression integral = std::shared_ptr<fexpr::integral>(new fexpr::integral());
        // end sourcegen
    }  // namespace functions

}  // namespace calcpp
