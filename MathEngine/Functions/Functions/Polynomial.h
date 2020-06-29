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
    const struct quad: public Function::NamedFunction {
        quad(): NamedFunction("quad") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 3){
                double a = args[0]->value();
                double b = args[1]->value();
                double c = args[2]->value();
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
            return InvalidExpression::construct(Exception("Invalid number of arguments for quad. Expected 3. Got: ", args.size()));
        }
    } __quad__;

    // @Function quadc
    const struct quadc: public Function::NamedFunction {
        quadc(): NamedFunction("quadc") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 3){
                double a = args[0]->value();
                double b = args[1]->value();
                double c = args[2]->value();
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
            return InvalidExpression::construct(Exception("Invalid number of arguments for quadc. Expected 3. Got: ", args.size()));
        }
    } __quadc__;

    // @Function cubic
    const struct cubic: public Function::NamedFunction {
        cubic(): NamedFunction("cubic") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 4){
                double a = args[0]->value();
                double b = args[1]->value() / a;
                double c = args[2]->value() / a;
                double d = args[3]->value() / a;
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
            return InvalidExpression::construct(Exception("Invalid number of arguments for cubic. Expected 4. Got: ", args.size()));
        }
    } __cubic__;

    // @Function cubicc
    const struct cubicc: public Function::NamedFunction {
        cubicc(): NamedFunction("cubicc") {}
        expression evaluate(Function::Args& args) override {
            if (args.size() == 4){
                double a = args[0]->value();
                double b = args[1]->value() / a;
                double c = args[2]->value() / a;
                double d = args[3]->value() / a;
                gsl_complex z0, z1, z2;
                gsl_poly_complex_solve_cubic(b, c, d, &z0, &z1, &z2);
                return TupleExpression::construct({z0, z1, z2});
            }
            return InvalidExpression::construct(Exception("Invalid number of arguments for cubicc. Expected 4. Got: ", args.size()));
        }
    } __cubicc__;
}
