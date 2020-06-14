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
#include "AbstractFunction.h"

namespace Functions {
    // @Function quad
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
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
    } quad ("quad");

    // @Function quadc
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 3){
                double a = args[0]->value();
                double b = args[1]->value();
                double c = args[2]->value();
                gsl_complex z0, z1;
                int num_roots = gsl_poly_complex_solve_quadratic(a, b, c, &z0, &z1);
                switch(num_roots){
                    case 0:
                        return TupleExpression::construct();
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
    } quadc ("quadc");

    // @Function cubic
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
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
    } cubic ("cubic");

    // @Function cubicc
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
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
    } cubicc ("cubicc");
}
