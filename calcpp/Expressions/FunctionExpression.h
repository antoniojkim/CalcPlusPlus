#pragma once

#include <initializer_list>

#include "Expression.h"

namespace calcpp {

    class FunctionExpression: public Expression {
        const std::string& name;
        const std::vector<expression> signature;

      protected:
        FunctionExpression(
            const std::string& name, std::initializer_list<expression> signature);

      public:
        expression at(const int index);
        size_t size();

        EXPRESSION_OVERRIDES
    };

    class ValueFunctionExpression: public FunctionExpression {
      protected:
        typedef double (*ValueFunction)(double);
        ValueFunction f;

        ValueFunctionExpression(const std::string, ValueFunction);

      public:
        virtual expression call(expression args) const override;
    };

}  // namespace calcpp
