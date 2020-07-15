#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {
    // @Function neg(x)
    namespace neg {
        expression eval(Function::Args& args) {
            auto x = args.next();
            if (x->isComplex()){
                return NumExpression::construct(gsl_complex_negative(x->complex()));
            }
            return NumExpression::construct(-x->value());
        }
        double value(double x) { return -x; }
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return -x->derivative(var);
        }
    }

    // @Function frexp(x)
    namespace frexp {
        expression eval(Function::Args& args) {
            double x = args.nextValue();
            int e;
            double f = gsl_frexp(x, &e);
            return TupleExpression::construct({f, (double) e});
        }
    }

    // @Function num(x)
    namespace num {
        expression eval(Function::Args& args) {
            return NumExpression::construct(args.nextValue());
        }
        double value(double x) { return x; }
    }

    // @Function hex(x)
    namespace hex {
        expression eval(Function::Args& args) {
            auto x = args.next();
            if (!x->isComplex()){
                double val = x->value();
                if (std::trunc(val) == val){
                    return HexExpression::construct((unsigned long long) std::trunc(val));
                }
            }
            throw Exception("Unable to convert to hex: ", x);
        }
    }

    // @Function bin(x)
    namespace bin {
        expression eval(Function::Args& args) {
            auto x = args.next();
            if (!x->isComplex()){
                double val = x->value();
                if (std::trunc(val) == val){
                    return BinExpression::construct((unsigned long long) std::trunc(val));
                }
            }
            throw Exception("Unable to convert to bin: ", x);
        }
    }

    // @Function abs(x)
    namespace abs {
        double (*value)(double) = std::abs;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::abs;
            auto x = args.next();
            return x / abs(x) * x->derivative(var);
        }
    }

    // @Function sqr(x)
    namespace sqr {
        double (*value)(double) = gsl_pow_2;
        expression derivative(Function::Args& args, const std::string& var) {
            auto x = args.next();
            return 2 * x * x->derivative(var);
        }
        std::ostream& print(std::ostream& out, Function::Args& args, const bool pretty) {
            auto x = args.next();
            return out << "(" << x << ")²";
        }
    }

    // @Function sqrt(x)
    namespace sqrt {
        double (*value)(double) = std::sqrt;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sqrt;
            auto x = args.next();
            return 0.5 / sqrt(x) * x->derivative(var);
        }
        std::ostream& print(std::ostream& out, Function::Args& args, const bool pretty) {
            auto x = args.next();
            return out << "√(" << x << ")";
        }
    }

    // @Function cb(x)
    namespace cb {
        double (*value)(double) = gsl_pow_3;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sqr;
            auto x = args.next();
            return 3 / sqr(x) * x->derivative(var);
        }
        std::ostream& print(std::ostream& out, Function::Args& args, const bool pretty) {
            return out << "(" << args.next() << ")³";
        }
    }

    // @Function cbrt(x)
    namespace cbrt {
        double (*value)(double) = std::cbrt;
        expression derivative(Function::Args& args, const std::string& var) {
            using ExpressionMath::sqr, ExpressionMath::cbrt;
            auto x = args.next();
            return (1.0 / 3) / sqr(cbrt(x)) * x->derivative(var);
        }
    }

    // @Function rad(x)
    namespace rad {
        double value(double x) { return x * M_PI / 180; }
    }

    // @Function deg(x)
    namespace deg {
        double value(double x) { return x * M_PI / 180; }
    }

    // @Function hypot(a...)
    namespace hypot {
        expression eval(Function::Args& args) {
            auto a = args.next();
            switch(a->size()){
                case 2:
                    return NumExpression::construct(gsl_hypot(a->get(0), a->get(1)));
                case 3:
                    return NumExpression::construct(gsl_hypot3(a->get(0), a->get(1), a->get(2)));
                default: {
                    double sum = 0;
                    for (auto e : *a){
                        sum += gsl_pow_2(e->value());
                    }
                    return NumExpression::construct(std::sqrt(sum));
                }
            }
        }
    }

    // @Function ldexp(x, e)
    namespace ldexp {
        expression eval(Function::Args& args) {
            double x = args.nextValue();
            double e = args.nextValue();
            if (std::trunc(e) == e){
                return NumExpression::construct(gsl_ldexp(x, (int) e));
            }
            throw Exception("ldexp expected an integer for 'e'. Got: ", e);
        }
    }

    // @Function fcmp(x, y, tol=1e-8)
    namespace fcmp {
        expression eval(Function::Args& args) {
            double x = args.nextValue();
            double y = args.nextValue();
            double tol = args.nextValue();
            return NumExpression::construct(gsl_fcmp(x, y, tol));
        }
    }

    // @Function gcd(a...)
    namespace gcd {
        expression eval(Function::Args& args) {
            auto a = args.next();
            long long g = 0;
            for (auto e : *a){
                double v = e->value();
                if (std::trunc(v) == v){
                    g = g == 0 ? v : std::gcd(g, (long long) v);
                }
                else{
                    throw Exception("gcd expected integer arguments. Got: ", args);
                }
            }
            return NumExpression::construct(g);
        }
    }

    // @Function lcm(a...)
    namespace lcm {
        expression eval(Function::Args& args) {
            auto a = args.next();
            long long l = 0;
            for (auto e : *a){
                double v = e->value();
                if (std::trunc(v) == v){
                    l = l == 0 ? v : std::lcm(l, (long long) v);
                }
                else{
                    throw Exception("lcm expected integer arguments. Got: ", args);
                }
            }
            return NumExpression::construct(l);
        }
    }
}
