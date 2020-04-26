#pragma once

#include "Expression.h"

class VariableExpression: public Expression {

    const std::string name;
    double num;

    VariableExpression(const std::string& name);
    VariableExpression(const std::string& name, double num);

    public:
        static expression construct(const std::string& name);
        static expression construct(const std::string& name, double num);

        expression evaluate(const Variables& vars) override;

        inline VariableExpression* variable(){ return this; }
        inline const std::string& getName(){ return name; }

        EXPRESSION_OVERRIDES

};
