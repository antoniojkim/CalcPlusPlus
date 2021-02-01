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

namespace calcpp {

    namespace fexpr {

        // @Function quad
        struct quad: public FunctionExpression {
            quad() : FunctionExpression("quad", {arg("a"), arg("b"), arg("c")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double b = (double) args->get(1);
                double c = (double) args->get(2);
                double x1, x2;
                int num_roots = gsl_poly_solve_quadratic(a, b, c, &x1, &x2);
                switch (num_roots) {
                    case 0:
                        return tuple();
                    case 1:
                        return tuple({var("x1", x1)});
                    case 2:
                        if (gsl_fcmp(x1, x2, 1e-15) == 0) {
                            return tuple({var("x1", x1)});
                        }
                        return tuple({var("x1", x1), var("x2", x2)});
                    default:
                        throw;  // Should never throw;
                }
            }
        };

        // @Function quadc
        struct quadc: public FunctionExpression {
            quadc() : FunctionExpression("quadc", {arg("a"), arg("b"), arg("c")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double b = (double) args->get(1);
                double c = (double) args->get(2);
                gsl_complex z1, z2;
                int num_roots = gsl_poly_complex_solve_quadratic(a, b, c, &z1, &z2);
                switch (num_roots) {
                    case 1:
                        return tuple({var("z1", z1)});
                    case 2:
                        return tuple({var("z1", z1), var("z2", z2)});
                    default:
                        throw;  // Should never throw;
                }
            }
        };

        // @Function cubic
        struct cubic: public FunctionExpression {
            cubic() :
                FunctionExpression("cubic", {arg("a"), arg("b"), arg("c"), arg("d")}) {}
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double b = (double) args->get(1) / a;
                double c = (double) args->get(2) / a;
                double d = (double) args->get(3) / a;
                double x1, x2, x3;
                int num_roots = gsl_poly_solve_cubic(b, c, d, &x1, &x2, &x3);
                switch (num_roots) {
                    case 1:
                        return tuple({var("x1", x1)});
                    case 3:
                        return tuple({var("x1", x1), var("x2", x2), var("x3", x3)});
                    default:
                        throw;  // Should never throw;
                }
            }
        };

        // @Function cubicc
        struct cubicc: public FunctionExpression {
            cubicc() :
                FunctionExpression("cubicc", {arg("a"), arg("b"), arg("c"), arg("d")}) {
            }
            expression call(expression args) const override {
                double a = (double) args->get(0);
                double b = (double) args->get(1) / a;
                double c = (double) args->get(2) / a;
                double d = (double) args->get(3) / a;
                gsl_complex z1, z2, z3;
                gsl_poly_complex_solve_cubic(b, c, d, &z1, &z2, &z3);
                return tuple(
                    {var("z1", z1,
                     var("z2", z2),
                     var("z3", z3)});
            }
        };

    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression cubic = std::shared_ptr<fexpr::cubic>(new fexpr::cubic());
        const expression cubicc = std::shared_ptr<fexpr::cubicc>(new fexpr::cubicc());
        const expression quad = std::shared_ptr<fexpr::quad>(new fexpr::quad());
        const expression quadc = std::shared_ptr<fexpr::quadc>(new fexpr::quadc());
        // end sourcegen
    }  // namespace functions
}  // namespace calcpp
