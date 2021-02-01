#include <cmath>
#include <memory>
#include <numeric>

#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/FunctionExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

using namespace std;

namespace calcpp {

    namespace fexpr {

        // @Function neg
        struct neg: public FunctionExpression {
            neg() : FunctionExpression("neg", {arg("x")}) {}
            expression call(expression args) const override {
                auto x = args->at(0);
                if (x == Type::COMPLEX) {
                    return complex(gsl_complex_negative(x->complex()));
                }
                if (x != Type::EVALUABLE) { return -x; }
                return num(-x->value());
            }
            expression derivative(const expression x) { return num(-1); }
        };

        // @Function frexp
        struct frexp: public FunctionExpression {
            frexp() : FunctionExpression("frexp", {arg("x")}) {}
            expression call(expression args) const override {
                double x = (double) arg->get(0);
                int e;
                Double f = (Double) gsl_frexp(x, &e);
                return tuple({f, (Double) e});
            }
        };

        // @Function num
        struct num: public FunctionExpression {
            num() : FunctionExpression("num", {arg("x")}) {}
            expression call(expression args) const override { return args->at(0); }
        };

        // @Function hex
        struct hex: public FunctionExpression {
            hex() : FunctionExpression("hex", {arg("x")}) {}
            expression call(expression args) const override {
                auto x = arg->at(0);
                if (x != Type::COMPLEX) {
                    Double val = x->value();
                    if (std::trunc(val) == val) {
                        return hex((unsigned long long) std::trunc(val));
                    }
                }
                THROW_ERROR("Unable to convert to hex: " << x);
            }
        };

        // @Function bin
        struct bin: public FunctionExpression {
            bin() : FunctionExpression("bin", {arg("x")}) {}
            expression call(expression args) const override {
                auto x = arg->at(0);
                if (x != Type::COMPLEX) {
                    Double val = x->value();
                    if (std::trunc(val) == val) {
                        return bin((unsigned long long) std::trunc(val));
                    }
                }
                THROW_ERROR("Unable to convert to bin: " << x);
            }
        };

        // @Function abs
        struct abs: public ValueFunctionExpression {
            abs() : ValueFunctionExpression("abs", std::abs) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return x / abs(x);
            }
        };

        // @Function sqr
        struct sqr: public ValueFunctionExpression {
            sqr() : ValueFunctionExpression("sqr", gsl_pow_2) {}
            expression derivative(const expression x) { return 2 * x; }
            std::ostream& print(std::ostream& out) { return out << "²"; }
        };

        // @Function sqrt
        struct sqrt: public ValueFunctionExpression {
            sqrt() : ValueFunctionExpression("sqrt", std::sqrt) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return 0.5 / sqrt(x);
            }
            std::ostream& print(std::ostream& out) {
                auto x = arg->at(0);
                return out << "√(";
                x->print(out, pretty) << ")";
            }
        };

        // @Function cb
        struct cb: public ValueFunctionExpression {
            cb() : ValueFunctionExpression("cb", gsl_pow_3) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return 3 * sqr(x);
            }
            std::ostream& print(std::ostream& out) { return out << "³"; }
        };

        // @Function cbrt
        struct cbrt: public ValueFunctionExpression {
            cbrt() : ValueFunctionExpression("cbrt", std::cbrt) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return (x ^ (-2.0 / 3)) / 3;
            }
        };

        // @Function rad
        struct rad: public FunctionExpression {
            rad() : FunctionExpression("rad", {arg("x")}) {}
            expression call(expression args) const override {
                Double x = args->get(0);
                return num(x * M_PI / 180);
            }
        };

        // @Function deg
        struct deg: public FunctionExpression {
            deg() : FunctionExpression("deg", {arg("x")}) {}
            expression call(expression args) const override {
                Double x = arg->get(0);
                return num(x * 180 / M_PI);
            }
        };

        // @Function hypot
        struct hypot: public FunctionExpression {
            hypot() : FunctionExpression("hypot", {vararg("a")}) {}
            expression call(expression args) const override {
                auto a = arg->at(0)->array();
                switch (a.size()) {
                    case 2:
                        return num(gsl_hypot(a.at(0), a.at(1)));
                    case 3:
                        return num(gsl_hypot3(a.at(0), a.at(1), a.at(2)));
                    default: {
                        gsl_vector v;
                        v.data = a.data();
                        v.size = a.size();
                        v.stride = 1;
                        return num(gsl_blas_dnrm2(&v));
                    }
                }
            }
        };

        // @Function ldexp
        struct ldexp: public FunctionExpression {
            ldexp() : FunctionExpression("ldexp", {arg("x"), arg("e")}) {}
            expression call(expression args) const override {
                Double x = arg->get(0);
                Double e = arg->get(1);
                if (std::trunc(e) == e) { return num(gsl_ldexp((double) x, (int) e)); }
                THROW_ERROR("ldexp expected an integer for 'e'. Got: " << e);
            }
        };

        // @Function fcmp
        struct fcmp: public FunctionExpression {
            fcmp() :
                FunctionExpression("fcmp", {arg("x"), arg("e"), kwarg("tol", 1e-8)}) {}
            expression call(expression args) const override {
                double x = (double) arg->get(0);
                double y = (double) arg->get(1);
                double tol = (double) arg->get(2);
                return num(gsl_fcmp(x, y, tol));
            }
        };

        // @Function gcd
        struct gcd: public FunctionExpression {
            gcd() : FunctionExpression("gcd", {vararg("a")}) {}
            expression call(expression args) const override {
                auto a = arg->at(0)->array();
                long long g = 0;
                for (auto v : a) {
                    if (std::trunc(v) == v) {
                        g = g == 0 ? v : std::gcd(g, (long long) v);
                    } else {
                        THROW_ERROR("gcd expected integer arguments. Got: " << arg);
                    }
                }
                return num((Double) g);
            }
        };

        // @Function lcm
        struct lcm: public FunctionExpression {
            lcm() : FunctionExpression("lcm", {vararg("a")}) {}
            expression call(expression args) const override {
                auto a = arg->at(0)->array();
                long long l = 0;
                for (auto v : a) {
                    if (std::trunc(v) == v) {
                        l = l == 0 ? v : std::lcm(l, (long long) v);
                    } else {
                        THROW_ERROR("lcm expected integer arguments. Got: " << arg);
                    }
                }
                return num(l);
            }
        };

    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression abs = std::shared_ptr<fexpr::abs>(new fexpr::abs());
        const expression bin = std::shared_ptr<fexpr::bin>(new fexpr::bin());
        const expression cb = std::shared_ptr<fexpr::cb>(new fexpr::cb());
        const expression cbrt = std::shared_ptr<fexpr::cbrt>(new fexpr::cbrt());
        const expression deg = std::shared_ptr<fexpr::deg>(new fexpr::deg());
        const expression fcmp = std::shared_ptr<fexpr::fcmp>(new fexpr::fcmp());
        const expression frexp = std::shared_ptr<fexpr::frexp>(new fexpr::frexp());
        const expression gcd = std::shared_ptr<fexpr::gcd>(new fexpr::gcd());
        const expression hex = std::shared_ptr<fexpr::hex>(new fexpr::hex());
        const expression hypot = std::shared_ptr<fexpr::hypot>(new fexpr::hypot());
        const expression lcm = std::shared_ptr<fexpr::lcm>(new fexpr::lcm());
        const expression ldexp = std::shared_ptr<fexpr::ldexp>(new fexpr::ldexp());
        const expression neg = std::shared_ptr<fexpr::neg>(new fexpr::neg());
        const expression num = std::shared_ptr<fexpr::num>(new fexpr::num());
        const expression rad = std::shared_ptr<fexpr::rad>(new fexpr::rad());
        const expression sqr = std::shared_ptr<fexpr::sqr>(new fexpr::sqr());
        const expression sqrt = std::shared_ptr<fexpr::sqrt>(new fexpr::sqrt());
        // end sourcegen
    }  // namespace functions

}  // namespace calcpp
