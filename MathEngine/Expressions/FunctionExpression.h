#pragma once

#include <map>
#include <list>
#include <utility>

#include "../Functions/Functions.h"
#include "Expression.h"

class FunctionExpression: public Expression {
    protected:
        const int functionIndex;
        expression arg;  // TupleExpression

        FunctionExpression(
            int functionIndex,
            expression arg,
            std::initializer_list<std::pair<std::string, expression>> signature={}
        );

    public:

        static expression construct(const char * name, expression arg);
        static expression construct(std::string& name, expression arg);
        static expression construct(int functionIndex, expression arg);
        static expression construct(const char * name, std::initializer_list<expression> args);
        static expression construct(std::string& name, std::initializer_list<expression> args);
        static expression construct(int functionIndex, std::initializer_list<expression> args);

        virtual expression eval(const Variables& vars = emptyVars) override;

        expression at(const int index) override;

        std::string repr() const override;
        int id() const override;

        EXPRESSION_PARTIAL_OVERRIDES

};

#define MAKE_FUNCTION_EXPRESSION(name)                                     \
    expression make_fe_##name(int functionIndex, expression arg){          \
        return std::make_shared<Function::name>(functionIndex, arg);       \
    }


class ValueFunctionExpression: public FunctionExpression {
    protected:
        typedef double (*ValueFunction)(double);
        ValueFunction f;

        ValueFunctionExpression(int functionIndex, ValueFunction f, expression arg);

    public:
        static expression construct(int functionIndex, ValueFunction f, expression arg);

        virtual double value(const Variables& vars = emptyVars) const override;

};

#define MAKE_VALUEFUNCTION_EXPRESSION(name, f)                             \
    expression make_fe_##name(int functionIndex, expression arg){          \
        return ValueFunctionExpression::construct(functionIndex, f, arg);  \
    }
