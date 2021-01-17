#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_poly.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/FunctionExpression.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Expressions/VariableExpression.h"
#include "../Functions.h"

namespace Function {
    // @Function quad
    struct quad: public FunctionExpression {
        quad(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, b, c)
            {"a", Empty}, {"b", Empty}, {"c", Empty}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            double a = arg->at(0)->value(vars);
            double b = arg->at(1)->value(vars);
            double c = arg->at(2)->value(vars);
            double x1, x2;
            int num_roots = gsl_poly_solve_quadratic(a, b, c, &x1, &x2);
            switch(num_roots){
                case 0:
                    return TupleExpression::construct();
                case 1:
                    return TupleExpression::construct({
                        VariableExpression::construct("x1", x1)
                    });
                case 2:
                    if (gsl_fcmp(x1, x2, 1e-15) == 0){
                        return TupleExpression::construct({
                            VariableExpression::construct("x1", x1)
                        });
                    }
                    return TupleExpression::construct({
                        VariableExpression::construct("x1", x1),
                        VariableExpression::construct("x2", x2)
                    });
                default:
                    throw; // Should never throw;
            }
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(quad)

    // @Function quadc
    struct quadc: public FunctionExpression {
        quadc(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, b, c)
            {"a", Empty}, {"b", Empty}, {"c", Empty}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            double a = arg->at(0)->value(vars);
            double b = arg->at(1)->value(vars);
            double c = arg->at(2)->value(vars);
            gsl_complex z1, z2;
            int num_roots = gsl_poly_complex_solve_quadratic(a, b, c, &z1, &z2);
            switch(num_roots){
                case 1:
                    return TupleExpression::construct({
                        VariableExpression::construct("z1", z1)
                    });
                case 2:
                    return TupleExpression::construct({
                        VariableExpression::construct("z1", z1),
                        VariableExpression::construct("z2", z2)
                    });
                default:
                    throw; // Should never throw;
            }
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(quadc)

    // @Function cubic
    struct cubic: public FunctionExpression {
        cubic(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, b, c, d)
            {"a", Empty}, {"b", Empty}, {"c", Empty}, {"d", Empty}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            double a = arg->at(0)->value(vars);
            double b = arg->at(1)->value(vars) / a;
            double c = arg->at(2)->value(vars) / a;
            double d = arg->at(3)->value(vars) / a;
            double x1, x2, x3;
            int num_roots = gsl_poly_solve_cubic(b, c, d, &x1, &x2, &x3);
            switch(num_roots){
                case 1:
                    return TupleExpression::construct({
                        VariableExpression::construct("x1", x1)
                    });
                case 3:
                    return TupleExpression::construct({
                        VariableExpression::construct("x1", x1),
                        VariableExpression::construct("x2", x2),
                        VariableExpression::construct("x3", x3)
                    });
                default:
                    throw; // Should never throw;
            }
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(cubic)

    // @Function cubicc
    struct cubicc: public FunctionExpression {
        cubicc(int functionIndex, expression arg): FunctionExpression(functionIndex, arg, {
            // Signature: (a, b, c, d)
            {"a", Empty}, {"b", Empty}, {"c", Empty}, {"d", Empty}
        }) {}
        expression eval(const Variables& vars = emptyVars) override {
            double a = arg->at(0)->value(vars);
            double b = arg->at(1)->value(vars) / a;
            double c = arg->at(2)->value(vars) / a;
            double d = arg->at(3)->value(vars) / a;
            gsl_complex z1, z2, z3;
            gsl_poly_complex_solve_cubic(b, c, d, &z1, &z2, &z3);
            return TupleExpression::construct({
                VariableExpression::construct("z1", z1),
                VariableExpression::construct("z2", z2),
                VariableExpression::construct("z3", z3)
            });
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(cubicc)
}
