#pragma once

#include "Expression.h"

class VariableExpression: public Expression {

    protected:
        const std::string name;
        expression var;

        VariableExpression(const std::string& name, expression var = nullptr);

    public:
        static expression construct(const std::string& name);
        static expression construct(const std::string& name, double var);
        static expression construct(const std::string& name, gsl_complex var);
        static expression construct(const std::string& name, expression var);

        expression simplify() override;
        expression derivative(const std::string& var) override;
        expression integrate(const std::string& var) override;

        expression at(const int index) override;

        std::string repr() const override { return name; }

        EXPRESSION_OVERRIDES

};

class VarArgsExpression: public Expression {
    expression var;

    VarArgsExpression();
    VarArgsExpression(expression var);

    public:
        static expression construct();
        static expression construct(expression var);

        expression at(const int index) override;

        EXPRESSION_OVERRIDES

};

extern expression EmptyVarArgs;
