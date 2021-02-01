#include <cmath>

#include <gsl/gsl_sf_log.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../Functions.h"

namespace calcpp {

    namespace fexpr {
        // @Function exp
        struct exp: public ValueFunctionExpression {
            exp() : ValueFunctionExpression("expr", std::exp) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return exp(x);
            }
        };

        // @Function exp2
        struct exp2: public ValueFunctionExpression {
            exp2() : ValueFunctionExpression("exp2", std::exp2) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return exp2(x) * M_LN2;
            }
        };

        // @Function expm1
        struct expm1: public ValueFunctionExpression {
            expm1() : ValueFunctionExpression("expm1", std::expm1) {}
            expression derivative(const expression x) {
                using namespace calcpp::math;
                return expm1(x);
            }
        };

        // @Function ln
        struct ln: public ValueFunctionExpression {
            ln() : ValueFunctionExpression("ln", std::log) {}
            expression derivative(const expression x) { return 1 / x; }
        };

        // @Function ln2: log2
        struct ln2: public ValueFunctionExpression {
            ln2() : ValueFunctionExpression("ln2", std::log2) {}
            expression derivative(const expression x) { return 1 / (x * M_LN2); }
        };

        // @Function ln1p: log1p
        struct ln1p: public ValueFunctionExpression {
            ln1p() : ValueFunctionExpression("ln1p", std::log1p) {}
            expression derivative(const expression var) { return 1 / (x + 1); }
        };

        // @Function log: log10
        struct log: public ValueFunctionExpression {
            log() : ValueFunctionExpression("log", std::log10) {}
            expression derivative(const expression x) { return 1 / (x * M_LN10); }
        };

        // @Function log1pm
        struct log1pm: public ValueFunctionExpression {
            log1pm() : ValueFunctionExpression("log1pm", gsl_sf_log_1plusx_mx) {}
        };

        // @Function logabs
        struct logabs: public ValueFunctionExpression {
            logabs() : ValueFunctionExpression("logabs", gsl_sf_log_abs) {}
        };

        // @Function logn
        struct logn: public FunctionExpression {
            logn() : FunctionExpression("logn", {arg("x"), arg("b")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double b = (double) args->get(1);
                return std::log(x) / std::log(b);
            }
        };

        // @Function sigmoid
        struct sigmoid: public FunctionExpression {
            sigmoid() : FunctionExpression("sigmoid", {arg("x")}) {}
            expression call(expression args) const override {
                double x = (double) arg->get(0);
                return 1 / (1 + std::exp(-x));
            }
            expression derivative(const std::string& var) {
                using namespace calpp::math;
                auto s = sigmoid(x);
                return s * (1 - s);
            }
            std::ostream& repr(std::ostream& out) const override {
                return out << "sigmoid";
            }
            std::ostream& print(std::ostream& out) const override { return out << "σ"; }
        };

    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression exp = std::shared_ptr<fexpr::exp>(new fexpr::exp());
        const expression exp2 = std::shared_ptr<fexpr::exp2>(new fexpr::exp2());
        const expression expm1 = std::shared_ptr<fexpr::expm1>(new fexpr::expm1());
        const expression ln = std::shared_ptr<fexpr::ln>(new fexpr::ln());
        const expression ln1p = std::shared_ptr<fexpr::ln1p>(new fexpr::ln1p());
        const expression ln2 = std::shared_ptr<fexpr::ln2>(new fexpr::ln2());
        const expression log = std::shared_ptr<fexpr::log>(new fexpr::log());
        const expression log1pm = std::shared_ptr<fexpr::log1pm>(new fexpr::log1pm());
        const expression logabs = std::shared_ptr<fexpr::logabs>(new fexpr::logabs());
        const expression logn = std::shared_ptr<fexpr::logn>(new fexpr::logn());
        const expression sigmoid = std::shared_ptr<fexpr::sigmoid>(new fexpr::sigmoid());
        // end sourcegen
    }  // namespace functions
}  // namespace calcpp
