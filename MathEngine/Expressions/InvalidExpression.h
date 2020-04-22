#pragma once

#include <string>

#include "Expression.h"
#include "../Utils/exceptions.h"

class InvalidExpression: public Expression {

    std::string message;

  public:
    InvalidExpression(const std::string& message);
    explicit InvalidExpression(const Exception&);

    EXPRESSION_OVERRIDES

};
