#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include <gsl/gsl_complex.h>

#include "Expression.h"

class TupleExpression: public Expression {

  public:
    std::list<expression> data;
  
    TupleExpression();
    TupleExpression(std::list<expression>&& tuple);
    TupleExpression(std::initializer_list<double> tuple);
    TupleExpression(std::initializer_list<gsl_complex> tuple);

    inline TupleExpression* tuple() override { return this; }

    expression evaluate(const Variables& vars) override;

    EXPRESSION_OVERRIDES

};
