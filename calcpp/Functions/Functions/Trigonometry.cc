#include <cmath>

#include <gsl/gsl_math.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../Functions.h"

namespace calcpp {

    namespace fexpr {

        // @Function sin
        struct sin: public ValueFunctionExpression {
            sin() : ValueFunctionExpression("sin", std::sin) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return cos(x);
            }
        };

        // @Function cos
        struct cos: public ValueFunctionExpression {
            cos() : ValueFunctionExpression("cos", std::cos) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -sin(x)
            }
        };

        // @Function tan
        struct tan: public ValueFunctionExpression {
            tan() : ValueFunctionExpression("tan", std::tan) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return sec(x) ^ 2;
            }
        };

        // @Function asin: arcsin arsin
        struct asin: public ValueFunctionExpression {
            asin() : ValueFunctionExpression("asin", std::asin) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return 1 / sqrt(1 - (x ^ 2));
            }
        };

        // @Function acos: arccos arcos
        struct acos: public ValueFunctionExpression {
            acos() : ValueFunctionExpression("acos", std::acos) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -1 / sqrt(1 - (x ^ 2));
            }
        };

        // @Function atan: arctan artan
        struct atan: public ValueFunctionExpression {
            atan() : ValueFunctionExpression("atan", std::atan) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return 1 / (1 + (x ^ 2));
            }
        };

        // @Function sinh
        struct sinh: public ValueFunctionExpression {
            sinh() : ValueFunctionExpression("sinh", std::sinh){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return cosh(x);
            }
        };

        // @Function cosh
        struct cosh: public ValueFunctionExpression {
            cosh() : ValueFunctionExpression("cosh", std::cosh){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return sinh(x);
            }
        };

        // @Function tanh
        struct tanh: public ValueFunctionExpression {
            tanh() : ValueFunctionExpression("tanh", std::tanh){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return sech(x) ^ 2;
            }
        };

        // @Function asinh: arcsinh arsinh
        struct asinh: public ValueFunctionExpression {
            asinh() : ValueFunctionExpression("asinh", std::asinh){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return 1 / sqrt((x ^ 2) + 1);
            }
        };

        // @Function acosh: arccosh arcosh
        struct acosh: public ValueFunctionExpression {
            acosh() : ValueFunctionExpression("acosh", std::acosh){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return 1 / sqrt((x ^ 2) - 1);
            }
        };

        // @Function atanh: arctanh artanh
        struct atanh: public ValueFunctionExpression {
            atanh() : ValueFunctionExpression("atanh", std::atanh){};
            expression derivative(const expression x) { return 1 / (1 - (x ^ 2)); }
        };

        // @Function csc
        struct csc: public ValueFunctionExpression {
            static double f(double x) { return 1 / std::sin(x); }
            csc() : ValueFunctionExpression("csc", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -cot(x) * csc(x);
            }
        };

        // @Function sec
        struct sec: public ValueFunctionExpression {
            static double f(double x) { return 1 / std::cos(x); }
            sec() : ValueFunctionExpression("sec", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -tan(x) * sec(x);
            }
        };

        // @Function cot
        struct cot: public ValueFunctionExpression {
            static double f(double x) { return 1 / std::tan(x); }
            cot() : ValueFunctionExpression("cot", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -(csc(x) ^ 2);
            }
        };

        // @Function acsc: arccsc arcsc
        struct acsc: public ValueFunctionExpression {
            static double f(double x) { return std::asin(1.0 / x); }
            acsc() : ValueFunctionExpression("acsc", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -1 / (abs(x) * sqrt((x ^ 2) - 1));
            }
        };

        // @Function asec: arcsec arsec
        struct asec: public ValueFunctionExpression {
            static double f(double x) { return std::acos(1.0 / x); }
            asec() : ValueFunctionExpression("asec", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                using ExpressionMath::abs, ExpressionMath::sqrt;
                auto x = arg->at(0);
                return x->derivative(var) / (abs(x) * sqrt((x ^ 2) - 1));
            }
        };

        // @Function acot: arccot arcot
        struct acot: public ValueFunctionExpression {
            static double f(double x) {
                return (x > 0 ? M_PI_2 : -M_PI_2) - std::atan(x);
            }
            acot() : ValueFunctionExpression("acot", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -1 / (1 + (x ^ 2));
            }
        };

        // @Function csch
        struct csch: public ValueFunctionExpression {
            static double f(double x) { return 1.0 / std::sinh(x); }
            csch() : ValueFunctionExpression("csch", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -coth(x) * csch(x);
            }
        };

        // @Function sech
        struct sech: public ValueFunctionExpression {
            static double f(double x) { return 1.0 / std::cosh(x); }
            sech() : ValueFunctionExpression("sech", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -tanh(x) * sech(x);
            }
        };

        // @Function coth
        struct coth: public ValueFunctionExpression {
            static double f(double x) { return 1.0 / std::tanh(x); }
            coth() : ValueFunctionExpression("coth", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -(csch(x) ^ 2);
            }
        };

        // @Function acsch: arccsch arcsch
        struct acsch: public ValueFunctionExpression {
            static double f(double x) {
                if (x == 0) { return GSL_NAN; }
                return std::log(1 / x + std::sqrt(1 / (x * x) + 1));
            }
            acsch() : ValueFunctionExpression("acsch", f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -1 / (abs(x) * sqrt((x ^ 2) - 1));
            }
        };

        // @Function asech: arcsech arsech
        struct asech: public ValueFunctionExpression {
            static double f(double x) {
                if (x <= 0 || x > 1) { return GSL_NAN; }
                return std::log(1 / x + std::sqrt(1 / (x * x) - 1));
            }
            asech() : ValueFunctionExpression(functionIndex, f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return -1 / (abs(x) * sqrt(1 - (x ^ 2)));
            }
        };

        // @Function acoth: arccoth arcoth
        struct acoth: public ValueFunctionExpression {
            static double f(double x) {
                if (x >= -1 && x <= 1) { return GSL_NAN; }
                return std::log((x + 1) / (x - 1)) / 2;
            }
            acoth() : ValueFunctionExpression(functionIndex, f){};
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return 1 / (1 - (x ^ 2));
            }
        };
    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression acos = std::shared_ptr<fexpr::acos>(new fexpr::acos());
        const expression acosh = std::shared_ptr<fexpr::acosh>(new fexpr::acosh());
        const expression acot = std::shared_ptr<fexpr::acot>(new fexpr::acot());
        const expression acoth = std::shared_ptr<fexpr::acoth>(new fexpr::acoth());
        const expression acsc = std::shared_ptr<fexpr::acsc>(new fexpr::acsc());
        const expression acsch = std::shared_ptr<fexpr::acsch>(new fexpr::acsch());
        const expression asec = std::shared_ptr<fexpr::asec>(new fexpr::asec());
        const expression asech = std::shared_ptr<fexpr::asech>(new fexpr::asech());
        const expression asin = std::shared_ptr<fexpr::asin>(new fexpr::asin());
        const expression asinh = std::shared_ptr<fexpr::asinh>(new fexpr::asinh());
        const expression atan = std::shared_ptr<fexpr::atan>(new fexpr::atan());
        const expression atanh = std::shared_ptr<fexpr::atanh>(new fexpr::atanh());
        const expression cos = std::shared_ptr<fexpr::cos>(new fexpr::cos());
        const expression cosh = std::shared_ptr<fexpr::cosh>(new fexpr::cosh());
        const expression cot = std::shared_ptr<fexpr::cot>(new fexpr::cot());
        const expression coth = std::shared_ptr<fexpr::coth>(new fexpr::coth());
        const expression csc = std::shared_ptr<fexpr::csc>(new fexpr::csc());
        const expression csch = std::shared_ptr<fexpr::csch>(new fexpr::csch());
        const expression sec = std::shared_ptr<fexpr::sec>(new fexpr::sec());
        const expression sech = std::shared_ptr<fexpr::sech>(new fexpr::sech());
        const expression sin = std::shared_ptr<fexpr::sin>(new fexpr::sin());
        const expression sinh = std::shared_ptr<fexpr::sinh>(new fexpr::sinh());
        const expression tan = std::shared_ptr<fexpr::tan>(new fexpr::tan());
        const expression tanh = std::shared_ptr<fexpr::tanh>(new fexpr::tanh());
        // end sourcegen
    }  // namespace functions
}  // namespace calcpp
