#pragma once

#include <list>

#include "Expression.h"
#include "FunctionExpressions/FunctionDirectory.h"

class UnaryFunctionExpression: public Expression {

    int functionIndex;
    // UnaryFunction fprime;
    // UnaryFunction fint;
    expression arg;

    UnaryFunctionExpression(const char * name, expression&& arg);
    UnaryFunctionExpression(std::string& name, expression&& arg);
    UnaryFunctionExpression(int functionIndex, expression&& arg);

    public:

        static expression construct(const char * name, expression&& arg);
        static expression construct(std::string& name, expression&& arg);
        static expression construct(int functionIndex, expression&& arg);

        expression evaluate(const Variables& vars) override;

        EXPRESSION_OVERRIDES

};

class MultiFunctionExpression: public Expression {

    int functionIndex;
    std::list<expression> args;

    MultiFunctionExpression(const char * name, std::list<expression>&& args);
    MultiFunctionExpression(std::string& name, std::list<expression>&& args);
    MultiFunctionExpression(int functionIndex, std::list<expression>&& args);

    public:

        static expression construct(const char * name, std::list<expression>&& args);
        static expression construct(std::string& name, std::list<expression>&& args);
        static expression construct(int functionIndex, std::list<expression>&& args);

        expression evaluate(const Variables& vars) override;

        EXPRESSION_OVERRIDES

};
