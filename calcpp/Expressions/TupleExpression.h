#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include <gsl/gsl_complex.h>

#include "Expression.h"
namespace calcpp {

    class TupleExpression: public Expression {
        std::vector<expression> data;

        TupleExpression();
        TupleExpression(std::vector<expression>&& tuple);
        TupleExpression(std::list<expression>& tuple);
        TupleExpression(std::initializer_list<expression> tuple);
        TupleExpression(std::initializer_list<double> tuple);
        TupleExpression(std::initializer_list<gsl_complex> tuple);

      public:
        DECLARE_TEMPLATE_CONSTRUCTOR(tuple);
        DECLARE_INITIALIZER_LIST_CONSTRUCTOR(tuple);

        expression simplify() override;
        expression derivative(const expression var) override;
        expression integrate(const expression var) override;

        expression at(const int index) override;
        size_t size() const override;

        expression apply(TransformerFunction f) override;

        EXPRESSION_OVERRIDES
    };

    DEFINE_TEMPLATE_CONSTRUCTOR(Tuple, tuple);
    DEFINE_INITIALIZER_LIST_CONSTRUCTOR(Tuple, tuple);

}  // namespace calcpp
