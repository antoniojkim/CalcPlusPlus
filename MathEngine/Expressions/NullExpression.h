#pragma once

#include <string>

#include "Expression.h"
#include "../Utils/Exception.h"

class NullExpression: public Expression {
    NullExpression();

    public:
        static expression construct();

        EXPRESSION_OVERRIDES

};

extern expression None;

class EmptyExpression: public Expression {
    EmptyExpression();

    public:
        static expression construct();

        EXPRESSION_OVERRIDES

};

extern expression Empty;
