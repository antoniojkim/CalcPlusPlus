#pragma once

#include <map>
#include <vector>

#include "../Expressions/Expression.h"

class ParsedArgs {
    std::vector<expression> args;
    std::map<std::string, expression> kwargs;

    bool insert(expression e);

    public:
        ParsedArgs(expression args);

        inline expression operator[](const int index){ return args.at(index); }
        inline expression operator[](const std::string index){ return kwargs.at(index); }
        inline bool contains(const std::string index){ return kwargs.count(index) > 0; }

        inline size_t size() { return args.size(); }
};
