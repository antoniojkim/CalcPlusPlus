#pragma once

#include <list>

#include "Expression.h"
#include "FunctionExpressions/FunctionDirectory.h"



class FunctionExpression: public Expression {

    int functionIndex;
    const expression arg;

    FunctionExpression(int functionIndex, const expression arg);

    public:

        static expression construct(const char * name, const expression arg);
        static expression construct(std::string& name, const expression arg);
        static expression construct(int functionIndex, const expression arg);

        expression evaluate(const Variables& vars) override;

        EXPRESSION_OVERRIDES

};

// class VariableFunctionExpression: public FunctionExpression{

// };
