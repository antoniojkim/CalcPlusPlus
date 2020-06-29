#pragma once

#include <list>

#include "../Functions/AbstractFunction.h"
#include "../Functions/FunctionDispatch.h"
#include "Expression.h"

class FunctionExpression: public Expression {

    const Function::AbstractFunction* f;
    const expression arg;

    FunctionExpression(int functionIndex, const expression arg);

    public:

        static expression construct(const char * name, const expression arg);
        static expression construct(std::string& name, const expression arg);
        static expression construct(int functionIndex, const expression arg);

        EXPRESSION_OVERRIDES

};
