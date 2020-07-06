#pragma once

#include <list>

#include "../Functions/Functions.h"
#include "Expression.h"

class FunctionExpression: public Expression {

    const int functionIndex;
    const expression arg;

    FunctionExpression(int functionIndex, const expression arg);

    public:

        static expression construct(const char * name, const expression arg);
        static expression construct(std::string& name, const expression arg);
        static expression construct(int functionIndex, const expression arg);
        static expression construct(const char * name, std::initializer_list<expression> args);
        static expression construct(std::string& name, std::initializer_list<expression> args);
        static expression construct(int functionIndex, std::initializer_list<expression> args);

        expression simplify() override;
        expression derivative(const std::string& var) override;
        expression integrate(const std::string& var) override;

        expression at(const int index) override;

        std::string repr() const override;
        int id() const override;

        EXPRESSION_OVERRIDES

};
