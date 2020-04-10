#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include "Expression.h"

class TupleExpression: public Expression {

  public:
    std::list<expression> tuple;
  
    TupleExpression();
    TupleExpression(std::list<expression>&& tuple);
    TupleExpression(std::initializer_list<double> tuple);

    EXPRESSION_OVERRIDES

};
