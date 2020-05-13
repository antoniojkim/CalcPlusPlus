#pragma once

#include <list>

#include "Expression.h"

class RandomDistributionExpression: public Expression {

    int distIndex;
    std::list<expression> args;

    RandomDistributionExpression(const char * name, std::list<expression>&& args);
    RandomDistributionExpression(std::string& name, std::list<expression>&& args);
    RandomDistributionExpression(int distIndex, std::list<expression>&& args);

    public:

        static expression construct(const char * name, std::list<expression>&& args);
        static expression construct(std::string& name, std::list<expression>&& args);
        static expression construct(int distIndex, std::list<expression>&& args);

        expression evaluate(const Variables& vars) override;

        EXPRESSION_OVERRIDES

};
