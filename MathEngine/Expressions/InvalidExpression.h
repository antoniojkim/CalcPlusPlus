#pragma once

#include <string>

#include "Expression.h"
#include "../Utils/exceptions.h"

class InvalidExpression: public Expression {

    std::string message;
  
  public:
    InvalidExpression(const Exception&);

    EXPRESSION_OVERRIDES

};

