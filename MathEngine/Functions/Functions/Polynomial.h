#pragma once

#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_poly.h>

#include "../Expressions/Expression.h"
#include "../Expressions/TupleExpression.h"
#include "../Utils/Argparse.h"
#include "../AbstractFunction.h"

namespace Function {
    // @Function quad
    const struct __quad__: public Function::AbstractFunction {
        __quad__(): AbstractFunction("quad", "(a, b, c)") {}
        expression evaluate(Function::Args& args) override {
            double a = args["a"]->value();
            double b = args["b"]->value();
            double c = args["c"]->value();
            double x0, x1;
            int num_roots = gsl_poly_solve_quadratic(a, b, c, &x0, &x1);
            switch(num_roots){
                case 0:
                    return TupleExpression::construct();
                case 1:
                    return TupleExpression::construct({x0});
                case 2:
                    if (gsl_fcmp(x0, x1, 1e-15) == 0){
                        return TupleExpression::construct({x0});
                    }
                    return TupleExpression::construct({x0, x1});
                default:
                    throw; // Should never throw;
            }
        }
    } quad;

    // @Function quadc
    const struct __quadc__: public Function::AbstractFunction {
        __quadc__(): AbstractFunction("quadc", "(a, b, c)") {}
        expression evaluate(Function::Args& args) override {
            double a = args["a"]->value();
            double b = args["b"]->value();
            double c = args["c"]->value();
            gsl_complex z0, z1;
            int num_roots = gsl_poly_complex_solve_quadratic(a, b, c, &z0, &z1);
            switch(num_roots){
                case 1:
                    return TupleExpression::construct({z0});
                case 2:
                    return TupleExpression::construct({z0, z1});
                default:
                    throw; // Should never throw;
            }
        }
    } quadc;

    // @Function cubic
    const struct __cubic__: public Function::AbstractFunction {
        __cubic__(): AbstractFunction("cubic", "(a, b, c, d)") {}
        expression evaluate(Function::Args& args) override {
            double a = args["a"]->value();
            double b = args["b"]->value() / a;
            double c = args["c"]->value() / a;
            double d = args["d"]->value() / a;
            double x0, x1, x2;
            int num_roots = gsl_poly_solve_cubic(b, c, d, &x0, &x1, &x2);
            switch(num_roots){
                case 1:
                    return TupleExpression::construct({x0});
                case 3:
                    return TupleExpression::construct({x0, x1, x2});
                default:
                    throw; // Should never throw;
            }
        }
    } cubic;

    // @Function cubicc
    const struct __cubicc__: public Function::AbstractFunction {
        __cubicc__(): AbstractFunction("cubicc", "(a, b, c, d)") {}
        expression evaluate(Function::Args& args) override {
            double a = args["a"]->value();
            double b = args["b"]->value() / a;
            double c = args["c"]->value() / a;
            double d = args["d"]->value() / a;
            gsl_complex z0, z1, z2;
            gsl_poly_complex_solve_cubic(b, c, d, &z0, &z1, &z2);
            return TupleExpression::construct({z0, z1, z2});
        }
    } cubicc;
}
