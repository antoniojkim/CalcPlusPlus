#pragma once

#include <map>
#include <vector>
#include <string>
#include <utility>

#include "../Expressions/Expression.h"

namespace Function {

    class Args {
        std::map<std::string, expression> kwargs;

        public:
            inline expression operator[](const std::string name){ return kwargs.at(name); }
            inline double get(const std::string name){ return kwargs.at(name)->value(); }
            inline double get(const std::string name, double defaultArg){
                if (kwargs.count(name) == 0){
                    return defaultArg;
                }
                return kwargs.at(name)->value();
            }

            inline size_t size() { return kwargs.size(); }

            decltype(kwargs.begin()) begin(){ return kwargs.begin(); }
            decltype(kwargs.end()) end(){ return kwargs.end(); }

            friend std::ostream& operator<<(std::ostream& out, Args& args);
            friend class Signature;
    };

    class Signature {
        const std::string signature;
        std::vector<std::pair<std::string, expression>> argnames;

        public:
            Signature(const std::string& signature);

            std::unique_ptr<Args> parse(expression args) const ;

            friend std::ostream& operator<<(std::ostream& out, Signature& signature);
    };

}
