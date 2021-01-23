#pragma once

#include <list>

#include "../Functions/AbstractFunction.h"
#include "../Functions/FunctionDispatch.h"
#include "Expression.h"

namespace calcpp {

    class CallableExpression: public Expression {
        expression f;
        expression arg;

        CallableExpression(expression f, expression arg);

      public:
        static expression construct(expression f, expression arg);

        expression at(const int index) override;

        EXPRESSION_OVERRIDES
    };

}  // namespace calcpp
