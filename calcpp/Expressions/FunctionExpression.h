#pragma once

#include "Expression.h"

namespace calcpp {

    class FunctionExpression: public Expression {
        const int functionIndex;

      protected:
        FunctionExpression(const int functionIndex);

      public:
        EXPRESSION_OVERRIDES
    };

    // class ValueFunctionExpression: public FunctionExpression {
    //   protected:
    //     typedef double (*ValueFunction)(double);
    //     ValueFunction f;

    //     ValueFunctionExpression(int functionIndex, ValueFunction f, expression arg);

    //   public:
    //     static expression construct(int functionIndex, ValueFunction f, expression
    //     arg);

    //     virtual double value(const Variables& vars = emptyVars) const override;
    // };

    // #define MAKE_VALUEFUNCTION_EXPRESSION(name, f)                                         \
//     expression make_fe_##name(int functionIndex, expression arg) {                     \
//         return ValueFunctionExpression::construct(functionIndex, f, arg);              \
//     }

    // struct OperatorFunctionExpression: public FunctionExpression {
    //     OperatorFunctionExpression(int functionIndex, expression arg);

    //     std::ostream& print(std::ostream& out, const bool pretty = false) const
    //     override; std::ostream& postfix(std::ostream& out) const override;
    // };

}  // namespace calcpp
