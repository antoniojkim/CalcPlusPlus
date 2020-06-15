#pragma once

#include <map>
#include <vector>

#include "../Expressions/Expression.h"
#include "../Utils/HeapArray.h"

namespace Function {
    class Args {
        std::vector<expression> args;
        // std::map<std::string, expression> kwargs;

        bool insert(expression e);

        public:
            Args(expression args);

            inline expression operator[](const int index){ return args.at(index); }
            // inline expression operator[](const std::string index){ return kwargs.at(index); }
            // inline bool contains(const std::string index){ return kwargs.count(index) > 0; }

            inline size_t size() { return args.size(); }

            decltype(args.begin()) begin(){ return args.begin(); }
            decltype(args.end()) end(){ return args.end(); }

            HeapArray<double> array();
    };
}
