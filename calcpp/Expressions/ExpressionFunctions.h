#pragma once

#include "../Functions/Functions.h"
#include "Expression.h"
#include "FunctionExpression.h"

namespace calcpp {

    expression call(expression f, expression arg);
    expression call(const std::string& name, expression arg);

    expression var(const std::string& name);
    expression arg(const std::string& name);
    expression kwarg(const std::string& name, expression arg);
    expression kwarg(const std::string& name, Double val);

    namespace math {
        // begin sourcegen functions
        expression cb(expression);
        expression cbrt(expression);
        expression cos(expression);
        expression cot(expression);
        expression csc(expression);
        expression ln(expression);
        expression log(expression);
        expression sec(expression);
        expression sin(expression);
        expression sqr(expression);
        expression sqrt(expression);
        expression tan(expression);
        // end sourcegen
    }  // namespace math

}  // namespace calcpp
