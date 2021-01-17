#pragma once

#include <list>

#include "../Functions/AbstractFunction.h"
#include "../Functions/FunctionDispatch.h"
#include "Expression.h"

class CallableExpression: public Expression {

    CallableExpression(int functionIndex);

    public:
        static expression construct(int functionIndex);

        expression evaluate(const Variables& vars) override;

        EXPRESSION_OVERRIDES

};

// class VariableFunctionExpression: public FunctionExpression{

// };
