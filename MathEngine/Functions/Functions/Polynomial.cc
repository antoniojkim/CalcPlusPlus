#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_poly.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/TupleExpression.h"
#include "../Functions.h"

namespace Function {
    // @Function quad(a, b, c)
    namespace quad {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double b = args.nextValue();
            double c = args.nextValue();
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
    }

    // @Function quadc(a, b, c)
    namespace quadc {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double b = args.nextValue();
            double c = args.nextValue();
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
    }

    // @Function cubic(a, b, c, d)
    namespace cubic {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double b = args.nextValue() / a;
            double c = args.nextValue() / a;
            double d = args.nextValue() / a;
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
    }

    // @Function cubicc(a, b, c, d)
    namespace cubicc {
        expression eval(Function::Args& args) {
            double a = args.nextValue();
            double b = args.nextValue() / a;
            double c = args.nextValue() / a;
            double d = args.nextValue() / a;
            gsl_complex z0, z1, z2;
            gsl_poly_complex_solve_cubic(b, c, d, &z0, &z1, &z2);
            return TupleExpression::construct({z0, z1, z2});
        }
    }
}
