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
        expression simplify() override;
        expression derivative(const std::string& var) override;
        expression integrate(const std::string& var) override;

        expression at(const int index) override;
        size_t size() const override;

        expression apply(TransformerFunction f) override;

        EXPRESSION_OVERRIDES

        template<typename... Args>
        friend expression tuple(Args&&... args);
    };

    template<typename... Args>
    expression tuple(Args&&... args) {
        return std::shared_ptr<TupleExpression>(
            new TupleExpression(std::forward<Args>(args)...));
    }

}  // namespace calcpp
