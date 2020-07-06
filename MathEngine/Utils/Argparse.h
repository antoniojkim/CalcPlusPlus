#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "../Expressions/Expression.h"

namespace Function {

    /*
    An iterator-like class that returns the next argument
    */
    class Args {
        int numPositional;
        bool hasVarArgs;
        const std::vector<double>& defaultArgs;
        expression e;
        size_t argIndex, eIndex;

        public:
            Args(int numPositional, bool hasVarArgs, const std::vector<double>& defaultArgs, expression e);

            expression next();
            double nextValue();

            friend std::ostream& operator<<(std::ostream& out, Args& args){
                return out << args.e << std::endl;
            }
    };

    class Signature {
        int numPositional;
        bool hasVarArgs;
        std::vector<double> defaultArgs;

        public:
            Signature(int numPositional, bool hasVarArgs, std::initializer_list<double> defaultArgs);

            Function::Args parse(expression e) const;
    };

}
