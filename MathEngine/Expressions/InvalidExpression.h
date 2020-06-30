#pragma once

#include <string>

#include "Expression.h"
#include "../Utils/Exception.h"

class InvalidExpression: public Expression {
    std::string message;

    InvalidExpression(const std::string& message);

    public:
        static expression construct(const Exception&);

        EXPRESSION_OVERRIDES

};
