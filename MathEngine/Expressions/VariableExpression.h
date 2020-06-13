#pragma once

#include "Expression.h"

class VariableExpression: public Expression {

    const std::string name;
    expression var;

    VariableExpression(const std::string& name, expression var = nullptr);

    public:
        static expression construct(const std::string& name);
        static expression construct(const std::string& name, double var);
        static expression construct(const std::string& name, expression var);

        expression evaluate(const Variables& vars) override;

        inline VariableExpression* variable() override { return this; }
        inline const std::string& getName() const { return name; }
        inline expression getVar() const { return var; }

        EXPRESSION_OVERRIDES

};
