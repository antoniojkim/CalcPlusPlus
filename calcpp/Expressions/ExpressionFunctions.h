#pragma once

#include <initializer_list>
#include <utility>

#include "../Functions/Functions.h"
#include "Expression.h"
#include "FunctionExpression.h"
#include "MatrixExpression.h"
#include "NumericalExpression.h"
#include "TupleExpression.h"

namespace calcpp {

    inline expression num(const Double val) {
        return NumericalExpression::construct(val);
    }
    inline expression complex(const gsl_complex& z) {
        return ComplexExpression::construct(z);
    }
    inline expression hex(const unsigned long long num) {
        return HexExpression::construct(num);
    }

    expression call(const expression f, const expression arg);
    expression call(const std::string& name, const expression arg);

    expression var(const std::string& name);
    expression arg(const std::string& name);
    expression vararg(const std::string& name);
    expression kwarg(const std::string& name, const expression arg);
    expression kwarg(const std::string& name, const Double val);

    namespace math {
        // begin sourcegen functions
        expression cb(expression);
        expression cbrt(expression);
        expression cos(expression);
        expression cot(expression);
        expression csc(expression);
        expression exp(expression);
        expression exp2(expression);
        expression expm1(expression);
        expression ln(expression);
        expression log(expression);
        expression sec(expression);
        expression sigmoid(expression);
        expression sin(expression);
        expression sqr(expression);
        expression sqrt(expression);
        expression tan(expression);
        // end sourcegen
    }  // namespace math

}  // namespace calcpp
