#include <cmath>
#include <memory>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {

    const gsl_rng_type * T;
    typedef std::unique_ptr<gsl_rng, decltype(&gsl_rng_free)> unique_gsl_rng;
    static unique_gsl_rng setup_rand(){
        gsl_rng_env_setup();
        T = gsl_rng_default;
        return unique_gsl_rng(gsl_rng_alloc(T), gsl_rng_free);
    }

    unique_gsl_rng r = setup_rand();


    // @Function rand(): random
    struct rand: public FunctionExpression {
        rand(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {}) {}  // Signature: ()
        double value(const Variables& vars = emptyVars) const override {
            return gsl_rng_uniform(r.get());
        }
    };
    MAKE_FUNCTION_EXPRESSION(rand);
}
